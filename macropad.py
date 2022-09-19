import serial
import time
import psutil
import datetime

# mac: /dev/tty.usbmodemHIDJB1
# mac: /dev/tty.usbmodemHIDEF1
# win: COM4
arduino = serial.Serial(port='/dev/tty.usbmodemHIDEF1',
                        baudrate=9600, timeout=.1)


last_sec = time.localtime().tm_sec
screen = "0"
last_screen = "-1"


def get_size(bytes, suffix="B"):
    factor = 1024
    for unit in ["", "K", "M", "G", "T", "P"]:
        if bytes < factor:
            return f"{bytes:.2f}{unit}{suffix}"
        bytes /= factor


while True:
    if (arduino.in_waiting > 0):
    # receive data from arduino
            screen = str(arduino.readline())[2]

    if (last_sec != time.localtime().tm_sec or last_screen != screen):
        # every second OR you changed screens
        dt = time.localtime()
        if (screen == "0"):
            # date & time
            formatted_date = str(datetime.date.today().strftime(
                "%A")) + ', ' + str(datetime.date.today().strftime("%B")) + ' ' + str(dt.tm_mday) + '\n'
            formatted_time = str(dt.tm_hour).zfill(2) + ':' + \
                str(dt.tm_min).zfill(2) + ':' + str(dt.tm_sec).zfill(2)
            arduino.write(bytes(formatted_date + '$'+formatted_time, 'utf-8'))

        elif (screen == "1"):
            # cpu
            cpu_info = f"CPU${psutil.cpu_percent()}%$Frequency: {psutil.cpu_freq().current / 1000}Ghz\nCores: {str(psutil.cpu_count(logical=False))}\nThreads: {str(psutil.cpu_count(logical=True))}"
            arduino.write(bytes(cpu_info, 'utf-8'))
        elif (screen == "2"):
            # ram
            mem = psutil.virtual_memory()
            mem_info = f"RAM${mem.percent}%$Used: {get_size(mem.used)}\nTotal: {get_size(mem.total)}\n"
            arduino.write(bytes(mem_info, 'utf-8'))
        last_sec = dt.tm_sec
    last_screen = screen

    # sleep 100ms
    time.sleep(0.1)
