import bluetooth
import time

class BTH_Nano:

  def __init__(self):
    self.connected = False
    self.sock = None
    self.socket = False
  
  def pair_BT(self):
    bd_addr = "98:D3:31:F4:1C:C8"
    port = 1
    self.sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    try:
      self.sock.connect((bd_addr,port))
      return True
    except:
      print("BT Socket not available.")
      return False
    
  def close_socket(self):
    if(self.sock):
      self.sock.close()
      
  def send_char(self, ch):
    self.sock.send(ch)
    #time.sleep(0.1)
    ans = self.sock.recv(2).decode('utf-8')
    return ans
  
  def connect(self):
    ans = self.send_char('#')
    #print(ans)
    if(ans=="@"):
      self.connected = True
    else:
      self.connected = False
    return self.connected
