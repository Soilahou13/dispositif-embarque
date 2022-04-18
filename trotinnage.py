
import serial,time
if __name__ == '__main__':
    
    print('Running. Press CTRL-C to exit.')
    with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
        time.sleep(0.1)
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            try:
                while True:
                    output=arduino.readline()
                    output = output.strip('\n')
                    output = output.strip('\r')
                    output = output.strip("b''")
                    print(output)
                    time.sleep(0.1)
                    arduino.flushInput()
            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")