// SPDX-License-Identifier: MIT

#include <Adafruit_NeoPixel.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>
#include <I2S.h>
#include <math.h>

// Using predefined pins
// PIN_EXTERNAL_NEOPIXELS, PIN_EXTERNAL_POWER, PIN_EXTERNAL_BUTTON,
// PIN_EXTERNAL_SERVO, PIN_I2S_BIT_CLOCK, PIN_I2S_DATA

Adafruit_NeoPixel strip(60, PIN_EXTERNAL_NEOPIXELS, NEO_GRB + NEO_KHZ800);
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
Servo servo_0;
uint8_t x = 0;

volatile bool tonePlaying = false;       // Global flag to indicate when audio is playing
volatile uint16_t currentAmplitude = 0;  // Shared variable to store audio amplitude

// Include your laugh audio data directly below

//Delete this line and add your code here for your audio data


// End Audio Data


// Specify that the sample rate is 44100 Hz
const uint32_t LAUGH_NUM_SAMPLES = sizeof(laughAudioData);
const uint32_t LAUGH_SAMPLE_RATE = 44100; // Audio sample rate set to 44100 Hz

void setup() {
  // Core 1 setup
  Serial.begin(115200);

  if (!lis.begin(0x18)) {   // Change to 0x19 if needed
    Serial.println("Could not start LIS3DH");
    while (1) yield();
  }

  lis.setRange(LIS3DH_RANGE_2_G);

  pinMode(PIN_EXTERNAL_POWER, OUTPUT);
  digitalWrite(PIN_EXTERNAL_POWER, HIGH);

  strip.begin();
  strip.show();
  strip.setBrightness(50);

  pinMode(PIN_EXTERNAL_BUTTON, INPUT_PULLUP);

  servo_0.attach(PIN_EXTERNAL_SERVO);
}

void loop() {
  delay(10);
  x++;

  if (tonePlaying) {
    // Update the NeoPixel ring based on currentAmplitude
    uint8_t brightness = map(currentAmplitude, 0, 32767, 0, 255);

    // Optional: Smooth the brightness changes
    static uint8_t smoothedBrightness = 0;
    smoothedBrightness = (smoothedBrightness * 7 + brightness) / 8;

    strip.setBrightness(smoothedBrightness);

    // Update the colors
    for (int32_t j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(255, 0, 0)); // Red color
    }
    strip.show();
  } else {
    // Turn off the NeoPixel ring when the audio is not playing
    strip.clear();
    strip.show();
  }

  // Print accelerometer data every 100ms
  if (x % 10 == 0) {
    sensors_event_t event;
    lis.getEvent(&event);
    Serial.print("Accel X: "); Serial.print(event.acceleration.x);
    Serial.print(" \tY: "); Serial.print(event.acceleration.y);
    Serial.print(" \tZ: "); Serial.print(event.acceleration.z);
    Serial.println(" m/s^2 ");
    Serial.println(x);
  }

  // Handle external button press
  if (!digitalRead(PIN_EXTERNAL_BUTTON)) {
    Serial.println("External button pressed");
    digitalWrite(PIN_EXTERNAL_POWER, LOW);
  } else {
    digitalWrite(PIN_EXTERNAL_POWER, HIGH);
  }

  // Control servo movement
  if (x < 128) {
    // Forward
    servo_0.writeMicroseconds(map(x, 0, 127, 1000, 2000));
  } else {
    // Backward
    servo_0.writeMicroseconds(map(x - 128, 0, 127, 2000, 1000));
  }
}

// Audio runs on core 2
#include <I2S.h>
#include <math.h>

I2S i2s(OUTPUT);

void setup1() {
  i2s.setBCLK(PIN_I2S_BIT_CLOCK);
  i2s.setDATA(PIN_I2S_DATA);
  i2s.setBitsPerSample(16);

  // No need to initialize strip here
}

void loop1() {
  tonePlaying = true; // Indicate that audio is playing
  play_laugh_audio_i2s(); // Play the laugh audio
  tonePlaying = false; // Audio finished
  delay(5000);
}

void play_laugh_audio_i2s() {
  uint32_t sampleRate = LAUGH_SAMPLE_RATE; // Sample rate is 44100 Hz
  uint32_t numSamples = LAUGH_NUM_SAMPLES;

  // Start I2S with the sample rate and 16-bits per sample
  if (!i2s.begin(sampleRate)) {
    delay(500);
    i2s.end();
    return;
  }

  delay(10); // Small delay to allow I2S device to initialize

  // Flush the I2S buffer
  i2s.flush();

  // Variables for audio amplitude analysis
  uint32_t sampleCounter = 0;
  uint32_t amplitudeAccumulator = 0;
  const uint32_t samplesPerUpdate = 100; // Adjust for responsiveness

  for (uint32_t i = 0; i < numSamples; i++) {
    // Convert 8-bit unsigned PCM to 16-bit signed PCM
    int16_t sample = ((int16_t)laughAudioData[i] - 128) << 8;

    // Accumulate the absolute value of the sample for amplitude calculation
    amplitudeAccumulator += abs(sample);
    sampleCounter++;

    // Write the sample twice for stereo output
    i2s.write(sample);
    i2s.write(sample);

    // Update amplitude every 'samplesPerUpdate' samples
    if (sampleCounter >= samplesPerUpdate) {
      // Calculate average amplitude
      uint16_t averageAmplitude = amplitudeAccumulator / sampleCounter;

      // Update the shared variable (make sure it's within the valid range)
      currentAmplitude = averageAmplitude;

      // Reset counters
      sampleCounter = 0;
      amplitudeAccumulator = 0;
    }
  }

  // Clear the amplitude when done
  currentAmplitude = 0;

  i2s.end();
}
