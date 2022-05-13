import socket
 
server_socket = socket.socket()         
 
server_socket.bind(('0.0.0.0', 8090 ))
server_socket.listen(0)                 
 
while True:
 
    client, addr = server_socket.accept()
 
    while True:
        content = client.recv(32)
 
        if len(content) ==0:
           break
 
        else:
            print(content)
 
    print("Closing connection")
    client.close()