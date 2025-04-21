# logger.py
import serial
import csv
from datetime import datetime

# Set your Arduino port here (check with `ls /dev/tty.*` on Mac/Linux or COMx on Windows)
PORT = '/dev/tty.usbserial-2140'  # Replace with your actual port
BAUD = 115200

csv_filename = 'motor_test.csv'

ser = serial.Serial(PORT, BAUD, timeout=1)
print("Logging started. Press Ctrl+C to stop.")

# Wait for proper header
while True:
    line = ser.readline().decode().strip()
    if "PWM" in line:
        header = line.split(",")
        break

# Open CSV and write header
with open(csv_filename, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Time"] + header)

    try:
        while True:
            raw = ser.readline().decode().strip()
            if raw:
                print(raw)
                row = raw.split(",")
                writer.writerow([datetime.now().strftime("%H:%M:%S")] + row)
    except KeyboardInterrupt:
        print("\nLogging stopped.")
