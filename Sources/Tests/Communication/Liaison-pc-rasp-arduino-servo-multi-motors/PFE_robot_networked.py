# This file permlits the test in manual mode of the robot
# Not yet finished.

import time
import os
import sys
import socket
import threading

from network_manager import *

connected = False

def handler_data(data) :
	print ' INCOMMING DATA :' + str(data)

def read_from_port(net,connected) :
	while not connected:
		connected = True
	
	while True:
		print 'test'
		reading = net.read()
		handler_data(reading)

# init socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('localhost', 5000))

# init serial connection
try :
	net = Network_Manager("/dev/ttyACM0",9600)
except :
	print 'Please connect an arduino.'

# starting reading thread
thread = threading.Thread(target=read_from_port, args=(net,connected))
thread.start()

# Sending start frame and manual state
frame = net.create_packed_data_frame(chr(0),chr(0),chr(1),chr(0),chr(0),chr(0))
net.send(str(frame))

# Trying to get response :
# frame = net.read_unpack()
# print 'New raw data : ' + str(frame)

# waiting the connection
s.listen(1)
while(1):
	(client, addr) = s.accept()
	run = True

	# Run the app
	while (run):
		data = client.recv(1024)
		if not data:
			run = False
	
		else: 
			datas = data.split(':')
	
			jj = int(datas[0])
			ii = int(datas[1])
			vvv = int(datas[2])
	
			#print those datas
			#os.system('clear')
			#print '--------------------------------------------------------------   ---'
			#for i in range(0, 20):
			#	sys.stdout.write('-')
			#	for j in range(0, 20):
			#		if ((j == jj) & (i == ii)):
			#			sys.stdout.write(' x ')
			#		else:
			#			sys.stdout.write('   ')
			#
			#	sys.stdout.write('-   -')
			#	if (vvv == i):
			#		sys.stdout.write('x')
			#	else:
			#		sys.stdout.write(' ')
			#	sys.stdout.write('-\n')
			#print '--------------------------------------------------------------   ---'

			# Send them to the arduino
			data1 = ii * 10
			data2 = jj * 10
			data3 = vvv * 10
			
			byte1 = 0
			byte2 = 0
			byte3 = 0
			byte4 = 0
			
			# if data1 > 100 :
			# 	byte1 = data3
			# 	byte4 = data3
			# elif data1 < 100 :
			# 	byte2 = data3
			# 	byte3 = data3
				
			# if data2 > 100 :
			# 	byte1 = data3
			# 	byte2 = data3
			# elif data2 < 100 :
			# 	byte4 = data3
			# 	byte3 = data3
			
			if data1 > 100 :
				byte1 = data1-100 # Intervalle : [0;99]
				byte4 = data1-100
			elif data1 < 100 :
				byte2 = 100 - data1
				byte3 = 100 - data1

			if data2 > 100 :
				byte1 = data2 - 100 # intervalle : [0;99]
				byte2 = data2 - 100
			elif data2 < 100 :
				byte4 = 100 - data2
				byte3 = 100 - data2

			byte5 = data3
			
			#frame = net.create_packed_data_frame(chr(2), chr(byte1), chr(byte2), chr(byte3), chr(byte4), chr(byte5))
			#print 'Test data3 value : ' + str(int(data3))
			#print 'Test data1 and data 2 : ' + str(int(data1)) + ':' + str(int(data2))			
			#print 'Test b1, b2, b3, b4 : ' + str(int(byte1)) + ':' + str(int(byte2)) + ':' + str(int(byte3)) + ':' + str(int(byte4))			
			#print str(frame)

			# if byte1 != 0 or byte2 != 0 or byte3 != 0 or byte4 != 0 :
			frame = '2'
			frame += chr(byte1+48) # transforming the Int value to the char Int value
			frame += chr(byte2+48)
			frame += chr(byte3+48)
			frame += chr(byte4+48)

			net.send(str(frame))
			# Trying to get response :
			# frame = net.read_unpack()
			
			# size = sys.getsizeof(frame)
			# st = ''
			# stt = ''
			# for i in range(0,size/8) :
			# 	st = st + 'c'
			# 	stt += frame[i]		
			# print 'DBG : ' + st
			# frame = unpack(st,stt)
		
			# print 'New raw data : ' + str(frame)
			# print ' Test on raw : ' + str(int(frame[1]))
			#print "wait ln\n"
			#print ser.readline()
			#time.sleep(0.05)
			#print "wait ended\n"

# Stopping Reading Thread...
thread.exit()

