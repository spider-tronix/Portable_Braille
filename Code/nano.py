import BT
import segmenter as SM
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
  print("Terminal has 0 cells. Loading cells to it.....")
  st_time = int(round(time.time() * 1000))
  i=0
  #Start of frame
  ans = nano.send_char(chr(2))
  if(int(ans) is not 6):
    print("SOF Tx failed.")
  #Sending characters
  while(i<len(string)):
    ans = nano.send_char(string[i])
    #print(string[i])
    i=i+1
    if(int(ans) is not 6):
      print("Char Tx failed at index %d",i-1)
  #End of frame
  ans = nano.send_char(chr(3))
  if(int(ans) is not 3):
      print("EOF Tx failed")
  else:
      end_time = int(round(time.time() * 1000))
      print("Loading sucessfull. Loading took ",str(end_time-st_time)," milliSeconds.")

def process_data(arr):
  if(len(arr)):
    string =""
    for i in arr:
      string += str(int(i))
    return string
  return " "

def check_next_loading():
  flag = True
  while(flag):
    ans = nano.send_char('\0')
    if(ans=="0"):
      flag= False
    else:
      print("Terminal has cells. No need to load.")
    time.sleep(1.5)
  return True


def initial_check():  
  print("==============================")
  #Checking socket and connecting to bluetooth
  check_socket(1)
  check_connection(1)

def load_txt(txt):
  SM.SEG.load_data(txt)

def start_sending():
  while(True):
    nxt = check_next_loading()
    if(nxt):
      data_to_load = SM.SEG.generate_data()
      load_cell(process_data(data_to_load))
      if(len(data_to_load)<=54):
        break

def closeall():
  time.sleep(2)
  nano.close_socket()

initial_check()
load_txt([[1, 1, 1, 1, 1, 1],[1, 0, 1, 0, 1, 1],[0, 1, 0, 1, 1, 0],[1, 1, 0, 0, 0, 0],[1, 1, 0, 1, 1, 1],[1, 0,0, 0, 1, 1],
     [1, 1, 1, 1, 1, 1],[1, 0, 1, 0, 1, 1],[0, 1, 0, 1, 1, 0],[1, 1, 0, 0, 0, 0],[1, 1, 0, 1, 1, 1],[1, 0,0, 0, 1, 1]])
start_sending()
closeall()
