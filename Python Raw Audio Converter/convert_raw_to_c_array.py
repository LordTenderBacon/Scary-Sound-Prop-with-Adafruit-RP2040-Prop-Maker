import sys
import os

if len(sys.argv) < 3:
    print("Usage: python convert_raw_to_c_array.py input_file output_file")
    sys.exit(1)

input_file = sys.argv[1]
output_file = sys.argv[2]

if not os.path.isfile(input_file):
    print(f"Error: File '{input_file}' does not exist.")
    sys.exit(1)

with open(input_file, 'rb') as f:
    data = f.read()

data_list = [b for b in data]

with open(output_file, 'w') as f:
    f.write(', '.join(str(b) for b in data_list))

print(f"Data successfully written to '{output_file}'.")
