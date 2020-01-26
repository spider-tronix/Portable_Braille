import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((socket.gethostname(), 8461))

server_out = ''
while True:
    msg = s.recv(8)
    if len(msg) <= 0: break
    server_out += msg.decode('utf-8')
# s.bind((socket.gethostname(), 8461))
# s.listen(5)
#
# server_out = ''
# while True:
#     c_socket, address = s.accept()
#     msg = c_socket.recv(8)
#     if len(msg) <=0 :
#         break
#     server_out += msg.decod("utf-8")

print(server_out)
