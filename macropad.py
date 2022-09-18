import serial
import time
import psutil

# mac: /dev/tty.usbmodemHIDJB1
# win: COM4
arduino = serial.Serial(port='/dev/tty.usbmodemHIDJB1',
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

    if (last_sec != time.localtime().tm_sec or last_screen != screen and screen != 4):
        # every second OR you changed screens
        dt = time.localtime()
        if (screen == "0"):
            # clock
            # formatted_date = ":d:"+str(dt.tm_wday) + ', ' + str(dt.tm_mon) + ':' + str(dt.tm_mday)
            # arduino.write(bytes(formatted_date, 'utf-8'))
            formatted_time = str(dt.tm_hour).zfill(2) + ':' + \
                str(dt.tm_min).zfill(2) + ':' + str(dt.tm_sec).zfill(2)
            arduino.write(bytes(formatted_time, 'utf-8'))
        elif (screen == "1"):
            # cpu
            cpu_info = f"CPU Info:\nCores: {str(psutil.cpu_count(logical=False))}\nThreads: {str(psutil.cpu_count(logical=True))}\nFrequency: {psutil.cpu_freq().current / 1000}Ghz\nUsage: {psutil.cpu_percent()}%"
            arduino.write(bytes(cpu_info, 'utf-8'))
        elif (screen == "2"):
            # ram
            mem = psutil.virtual_memory()
            mem_info = f"Memory Info:\nTotal: {get_size(mem.total)}\nUsed: {get_size(mem.used)} ({mem.percent}%)"
            arduino.write(bytes(mem_info, 'utf-8'))
        last_sec = dt.tm_sec
    last_screen = screen

    # sleep 100ms
    time.sleep(0.1)