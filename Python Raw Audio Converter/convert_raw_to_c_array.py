# Python script to convert raw audio data to a header file for your project
output_file = r"C:\Users\media\Desktop\CONVERT WAV TO RAW\audio_data.h"

with open(r"C:\Users\media\Desktop\CONVERT WAV TO RAW\audio.raw", "rb") as f:
    raw_data = f.read()

with open(output_file, "w") as f:
    f.write("unsigned char audio_data[] = {\n")
    for i, byte in enumerate(raw_data):
        f.write(f"0x{byte:02x}")
        if i != len(raw_data) - 1:
            f.write(", ")
        if (i + 1) % 12 == 0:
            f.write("\n")
    f.write("\n};\n")

print(f"Header file created: {output_file}")
