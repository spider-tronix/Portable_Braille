import bluetooth
import time

bd_addr = "98:D3:31:F4:1C:C8"
port = 1
sock = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
sock.connect((bd_addr,port))

while 1:
  tosend = input("Enter a Number: ")
  if tosend != "q":
    sock.send(tosend)
  else:
    break
  time.sleep(0.1)
  buffer = sock.recv(4096)
  print(buffer)
sock.close()