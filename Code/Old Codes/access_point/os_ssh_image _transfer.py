import os
from wireless import Wireless
import requests 

# connecting to the Access point
wire = Wireless()
wire.connect(ssid='PortableBraille',password='PB@spider')

# sending image from current machine to ssh machine

#````````    One Time Setiings before SSH   ````````````````````````
#       creating a .sh file with the commands
#       --> $ sudo apt install openssh-server
#       --> $ ssh-keygen -t rsa -b 2048
#           Generating public/private rsa key pair.
#           Enter file in which to save the key (/home/username/.ssh/id_rsa): 
#           Enter passphrase (empty for no passphrase): (Don't give any password)
#           Enter same passphrase again: 
#           Your identification has been saved in /home/username/.ssh/id_rsa.
#           Your public key has been saved in /home/username/.ssh/id_rsa.pub.
#       --> $ ssh-copy-id id@server
#           id@server's password: 
os.chdir("/home/raj")
os.system("scp ~/Desktop/ww.jpg pi@192.168.4.1:~/Desktop/")