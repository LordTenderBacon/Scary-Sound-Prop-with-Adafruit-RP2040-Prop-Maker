# Scary Sound Prop with Adafruit RP2040 Prop-Maker
A fun Halloween project using an Adafruit RP2040 Prop-Maker with a 16-LED NeoPixel ring, a 4-ohm speaker, and a 3.7V 2200mAh lithium battery. This prop plays a scary voice or sound effect (easily customizable) and controls a servo. The NeoPixel ring lights up in sync with the audio for a spooky effect!

(This Project assumes you know some basic C++, Python and Arduino IDE) I did my best to lay out the steps i took to get the results in this video

[![Watch the Demo on YouTube](https://img.youtube.com/vi/MXi40_avDd0/0.jpg)](https://www.youtube.com/watch?v=MXi40_avDd0&autoplay=1)


# PLEASE NOTE YOU HAVE TO ADD THE AUDIO DATA TO THE MAIN CODE
There has been an update made with a audio sample txt file called audio_data.txt in the Main folder that contains c-array data for you to use as a demo Just replace the data in the main .ino code where it says
There is a place holder in the code where you can put your own c-array data after following the instructions provided below to get the required format. Github sadly does not allow large codes like the data in c-array

Put the audio data directly where it says in the main code file. It is in C Array I will provide a convert.py you can download to your desktop. Follow the instructions below exactly if you are converting a .wav to raw c arrary. Also make sure the start of your c-array data starts with const uint8_t laughAudioData[] = {


## Features
- **Customizable Sounds**: Easily swap sound files to play different effects.
- **Animated Lighting**: NeoPixel ring lights up as sounds play.
- **Servo Control**: Optionally control a servo for additional movement.
- **Battery-Powered**: Portable with a 3.7V 2200mAh lithium battery.

- ## Components
- [Adafruit RP2040 Prop-Maker - https://www.adafruit.com/product/5768
- [NeoPixel Ring - 16 LEDs https://www.adafruit.com/product/1463
- 4-ohm speaker - https://www.microcenter.com/product/631684/grs-3fr-4-full-range-3-speaker-4-ohm
- 3.7V 2200mAh lithium battery - https://www.microcenter.com/product/636273/adafruit-industries-lithium-ion-cylindrical-battery-37v-2200mah
- Servo motor (optional)


# Follow These instructions below to convert your sound to raw from what ever format its in like MP4 to raw or WAV to raw. Then we will take that raw data and convert it int C-Arrary for our code to run the sound you want

1. We need to download Audacity the free version

2. Once downloaded upload/import your sound and make sure its sounds good.

3. Export your Audio to your computer and name it audio.raw in the same folder with the python code

4. Select the "Other uncompressed Files"

5. Select Mono

6. Sample Rate should be 48000Hz

7. Header RAW (HeaderLess)

8. Encoding should be signed 8-bit PCM

9. Export Entire Project
# Image Of what your settings should look like on Export

![Capture of the setup](https://github.com/LordTenderBacon/Scary-Sound-Prop-with-Adafruit-RP2040-Prop-Maker/blob/804db1c28a2784631b4bd8cdda2664431bfb2219/Images/Capture.PNG)


10. (optional to select trime blank space) I do on certain audios that i have blank playback issues with

11. Install Python on your PC if you havnt already

12.Go to folder where you exported your raw audio data to 

13. create a new text document and label it convert_raw_to_h.py

14. open the file and insert the python code from the .py file provided and save it

15. Open a Terminal window and navigate to the folder with your code and files you created using "cd" Exmaple "cd Documents/code"

16. Type in python convert_raw_to_h.py in command promt

17. If done correctly after a couple seconds you should see a new files in your folder with your c-array open that in a notepad and copy it into the main code where it says in the Propmaker project

18.  Please make sure after coping and pasting your new audio data to the main arduino file the beginning of it starts with "const uint8_t laughAudioData[] = {"
with out the quotions 
