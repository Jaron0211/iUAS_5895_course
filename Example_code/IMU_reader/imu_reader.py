import serial

# Define the COM port and baud rate
com_port = 'COM9'
baud_rate = 115200

# Open the serial port
ser = serial.Serial(com_port, baud_rate)

while True:
    try:
        # Read a line of data from the serial port as bytes
        line = ser.readline()
        
        # Remove leading 'b' and decode bytes into a string
        decoded_line = line[1:].decode('utf-8').strip()
        
        # Split the string into individual values and convert to floats
        imu_data = list(map(float, decoded_line.split(',')))
        
        # Extract individual values
        ax, ay, az, p, q, r = imu_data
        
        # Print the extracted values
        print(f"Accelerometer: ({ax}, {ay}, {az}), Gyroscope: ({p}, {q}, {r})")
        ser.flush()
    except KeyboardInterrupt:
        break
    except:
        continue

# Close the serial port when done
ser.close()
