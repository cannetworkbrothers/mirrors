"""
Python program to read data from CAN shiled via COM port
"""
import sys
import serial

def read_com_port():
    """
    function to read the COM port
    """
    try:
        ser = serial.Serial('COM3', 9600, timeout=0, rtscts=2)
        counter = 1
        while True:
            data = ser.read()
            if data:
                counter += 1
                # print("got data" + str(counter))
                sys.stdout.write(str(data.decode('cp1252').encode('utf-8').decode('utf-8')))
    except serial.serialutil.SerialException:
        print("COM port is unpluged. Bye!") 

def main():
    """
    main function for execution
    """
    read_com_port()

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(0)
