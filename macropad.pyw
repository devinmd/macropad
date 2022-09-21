import serial
import time
import psutil
import datetime
import math

# mac: /dev/tty.usbmodemHIDJB1
# mac: /dev/tty.usbmodemHIDEF1
# win: COM4
# win: COM5

# go through ports finding the correct one
try:
	arduino = serial.Serial(port='COM4', baudrate=9600, timeout=.1)
	print("Running on port: COM5")
except:
	try:
		arduino = serial.Serial(port='COM5', baudrate=9600, timeout=.1)
		print("Running on port: COM5")
	except:
		try:
			arduino = serial.Serial(
				port='/dev/tty.usbmodemHIDJB1', baudrate=9600, timeout=.1)
			print("Running on port: /dev/tty.usbmodemHIDJB1")
		except:
			try:
				arduino = serial.Serial(
					port='/dev/tty.usbmodemHIDEF1', baudrate=9600, timeout=.1)
				print("Running on port: /dev/tty.usbmodemHIDEF1")
			except:
				print("Error finding macropad port")

last_sec = time.localtime().tm_sec
screen = "0"
last_screen = "-1"


def get_size(bytes, suffix="b"):
	factor = 1024
	for unit in ["", "K", "M", "G", "T", "P"]:
		if bytes < factor:
			return f"{bytes:.2f}{unit}{suffix}"
		bytes /= factor


def send_data(data):
	arduino.write(bytes(data, 'utf-8'))


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

			# 22 is the max length, calculate indent to center the date
			indent = " "*(math.floor((22 - len(formatted_date)) / 2))
			send_data(indent+formatted_date + '$'+formatted_time)

		elif (screen == "1"):
			# cpu
			cpu_percent = psutil.cpu_percent()
			indent = " "*(4 - len(str(cpu_percent)))
			send_data(f"CPU${indent}{cpu_percent}%$Frequency: {psutil.cpu_freq().current / 1000}Ghz$Cores: {str(psutil.cpu_count(logical=False))}$Threads: {str(psutil.cpu_count(logical=True))}")
		elif (screen == "2"):
			# ram
			mem = psutil.virtual_memory()
			mem_percent = mem.percent
			indent = " "*(4 - len(str(mem_percent)))
			send_data(f"RAM${indent}{mem.percent}%$Used: {get_size(mem.used)}$Total: {get_size(mem.total)}")
		last_sec = dt.tm_sec
	last_screen = screen

	# sleep 100ms
	time.sleep(0.1)
