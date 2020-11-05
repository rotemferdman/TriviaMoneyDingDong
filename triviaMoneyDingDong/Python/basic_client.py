import socket
SERVER_IP = "127.0.0.1"
SERVER_PORT = 1111

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connecting to remote computer 80
server_address = (SERVER_IP, SERVER_PORT)
sock.connect(server_address)
while True:
    i = input("please choose one of the following:\n[1]sign up\n[2]sign in")
    if i == "1":  # sign up to the system

        # sending something to the server
        username = input("Enter your username.")
        password = input("Enter your password")
        email = input("Enter your email address")
        data = "`" + username + '`' + password + '`' + email
        allD = "S" + str(len(data)) + data
        print(allD)
        sock.sendall(allD.encode())

        server_msg = sock.recv(1024)
        server_msg = server_msg.decode()
        print(server_msg)

    elif i == "2":  # login to the server
        username = input("Enter your username.")
        password = input("Enter your password")
        data = "`" + username + '`' + password
        allD = "L" + str(len(data)) + data
        print(allD)
        sock.sendall(allD.encode())

        server_msg = sock.recv(1024)
        server_msg = server_msg.decode()
        print(server_msg)
        r = 0
        if server_msg[2] == '0':
            while r != -1:  # the login screen
                choice = input("welcome " + username + "!!\nWhat do you want to do?\n[1]log out\n[2]create a room\n[3]Join an existing room")
                if choice == "1":  # logout
                    allD = "O"
                    sock.sendall(allD.encode())
                    server_msg = sock.recv(1024)
                    server_msg = server_msg.decode()
                    print(server_msg)
                    r = -1
                if choice == "2":
                    allD = "C"
                    part = input("Enter the name of the room")
                    size = len(part)
                    allD = allD + str(size) + "`" + part
                    sock.sendall(allD.encode())
                    server_msg = sock.recv(1024)
                    server_msg = server_msg.decode()
                    print(server_msg)
                    if server_msg[2] == '0':
                        print("youre in a room! players with you: ")
                        list2 = []
                        while True:
                            allD = "P" + str(size) + "`" + part
                            sock.sendall(allD.encode())
                            server_msg = sock.recv(1024)
                            server_msg = server_msg.decode()
                            list1 = server_msg.split("`")
                            i = 0
                            for u in list1:
                                i = i + 1
                                if i > 1:
                                    if u != username:
                                        if u not in list2:
                                            list2.append(u)
                                            print(u)

                if choice == "3":
                    print("online rooms: \n")
                    allD = "R"
                    sock.sendall(allD.encode())
                    server_msg = sock.recv(1024)
                    server_msg = server_msg.decode()
                    list1 = server_msg.split("`")
                    i = 0
                    for u in list1:
                        i = i + 1
                        if i > 1:
                            if u != username:
                                print(u)

                    allD = "J"
                    part = input("what room you want to join to?")
                    size = len(part)
                    allD = allD + str(size) + "`" + part
                    sock.sendall(allD.encode())
                    server_msg = sock.recv(1024)
                    server_msg = server_msg.decode()
                    print(server_msg)
                    if server_msg[2] == '0':
                        print("your'e in a room! players with you: ")
                        list2 = []
                        while True:
                            allD = "P" + str(size) + "`" + part
                            sock.sendall(allD.encode())
                            server_msg = sock.recv(1024)
                            server_msg = server_msg.decode()
                            list1 = server_msg.split("`")
                            i = 0
                            for u in list1:
                                i = i + 1
                                if i > 1:
                                    if u != username:
                                        if u not in list2:
                                            list2.append(u)
                                            print(u)





