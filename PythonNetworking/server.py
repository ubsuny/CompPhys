import socket  # Import socket module

port = 4242  # Reserve a port for your service
s = socket.socket()  # Create a socket object
host = ""  # Get local machine name
s.bind(('localhost', port))  # Bind to the port
s.listen(5)  # Now wait for client connection.

print('Server listening....')

x = 0

while True:
    conn, address = s.accept()  # Establish connection with client.

    while True:
        try:
            print('Got connection from {}'.format(address))
            data = conn.recv(1024) # receive 1024 bytes at a time
            print('Server received', data)

            st = 'That is some interesting data'
            byt = st.encode()
            conn.send(byt)

            x += 1

        except Exception as e:
            print(e)
            break

conn.close()