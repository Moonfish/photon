import serial

s = serial.Serial('/dev/ttyACM0')
s.write(b'D')
s.close()

