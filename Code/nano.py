import BT
import time

nano = BT.BTH_Nano()

def check_socket(A):
  if(A==4):
    print("Socket Not Found. Please check the connection.")
    return
  if nano.socket == False:
    print("Pairing with BT.....")
    ans = nano.pair_BT()
    if(ans == True ):
      print("Socket OK.")
      return
    else:
      print("Re-trying......")
      time.sleep(1.5)
      check_socket(A+1)

def check_connection(A):
  if(A==4):
    print("Connection could not be established. Please check the connection.")
    return
  if nano.connected == False:
    print("Establishing BT connection with PBrar...")
    ans = nano.connect()
    if(ans == True ):
      print("Connection OK.")
      print("==============================")
      return
    else:
      print("Re-trying......")
      time.sleep(1.5)
      check_connection(A+1)

def load_cell(string):
  # First checking the status of the cell buffer
  ans = nano.send_char('\0')
  if(ans=="0"):
    print("Terminal has 0 cells. Loading cells to it.....")
    i=0
    #Start of frame
    ans = nano.send_char(chr(2))
    if(ord(ans) is not 6):
      print("SOF Tx failed.")
    #Sending characters
    while(i<len(string)):
      ans = nano.send_char(string[i])
      i=i+1
      if(ord(ans) is not 6):
        print("Char Tx failed")
    #End of frame
    ans = nano.send_char(chr(3))
    if(ord(ans) is not 6):
        print("EOF Tx failed")

print("==============================")
check_socket(1)
check_connection(1)
load_cell("SEX")
time.sleep(2)
nano.close_socket()
