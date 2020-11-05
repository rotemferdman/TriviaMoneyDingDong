#include "Server.h"
#include "IRequestHandler.h"
#include "ResponsePacketSerializer.h"
#include "IDatabase.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <map>

#define MAX 1000

SqliteDataBase Database;
std::map<SOCKET, IRequestHandler*>m_clients;
std::thread* arr = new std::thread[MAX];
std::map<std::string, SOCKET>m_users;
int index = 0;
roomManager rm;

Server::Server()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	bool start = Database.open();

	if (start == true)
	{
		while (true)
		{
			// the main thread is only accepting clients 
			// and add then to the list of handlers
			std::cout << "Waiting for client connection request" << std::endl;
			accept();
		}
	}
}


void Server::accept()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	// the function that handle the conversation with the client
	arr[index] = std::thread(client, client_socket); //creating a thead for each client
	index++;
}

void client(SOCKET clientSocket)
{
	statistics stat(Database);
	IRequestHandler* l = new LoginRequestHandler;
	std::pair< SOCKET, IRequestHandler* >p(clientSocket, l);
	m_clients.insert(p);

	while (true)
	{
		char m[MAX] = "";
		int err = recv(clientSocket, m, MAX, 0); //getting from client
		if (err == -1)
		{
			std::string name;
			for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
			{
				if (it->second == clientSocket)
				{
					
					name = it->first;
					std::cout << "removing from users online: " << name << std::endl;
				}
			}
			m_users.erase(name);
			std::cout << m_users.size() << std::endl;
			break;
		}
		
		m[MAX - 1] = 0;
		std::string ans = m;
		RequestInfo r;
		r.BData = ans;
		r.code = ans[0];

		LoginRequestHandler lo;
		short type = lo.isRequestRelevant(r);
		if (type == 1) //login
		{
			loginSend(clientSocket, lo, r);
		}
		else if (type == 2) //sign up
		{
			signUpSend(clientSocket, lo, r);
		}
		else if (type == 3) //sign out
		{
			logOutSend(clientSocket);
		}
		else if (type == 4) //get all the rooms in a list
		{
			GetRoomsSend(clientSocket);
		}
		else if (type == 5) //get all players in specific room
		{
			getPlayersInRoomSend(clientSocket, r);
		}
		else if (type == 6) //join room
		{
			joinRoomsend(clientSocket, r);
		}
		else if (type == 7) //create room
		{
			CreateRoomSend(clientSocket, r, lo);
		}
		else if (type == 8) //statistics
		{
			std::string username;
			for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
			{
				if (it->second == clientSocket)
				{
					username = it->first;
					break;
				}
			}
			std::string data = stat.getPersonalData(username);
			std::string full = "H" + std::to_string(data.size()) + data;
			send(clientSocket, full.c_str(), full.size(), 0);  // last parameter: flag. for us will be 0.
			std::cout << "sent the statistics to the client" << std::endl;
		}
		else if (type == 9) //start game
		{
			int ind = 0;
			for (ind = 0; ind < r.BData.size(); ind++)
			{
				if (r.BData[ind] == '`')
				{
					break;
				}
			}
			std::string str = "";
			for (ind = ind + 1; ind < r.BData.size(); ind++)
			{
				if (r.BData[ind] != '`')
				{
					str = str + r.BData[ind];
				}
				else
				{
					break;
				}
			}
			for (std::vector<room>::iterator it = rm.activate_rooms.begin(); it != rm.activate_rooms.end(); ++it)
			{
				if (it->getRoomName() == str)
				{
					it->is_started = true; //starting the game;
				}
			}
		}
		else if (type == 10) //check start game
		{
			int ind = 0;
			for (ind = 0; ind < r.BData.size(); ind++)
			{
				if (r.BData[ind] == '`')
				{
					break;
				}
			}
			std::string str = "";
			for (ind = ind + 1; ind < r.BData.size(); ind++)
			{
				if (r.BData[ind] != '`')
				{
					str = str + r.BData[ind];
				}
				else
				{
					break;
				}
			}
			int toSend = 1;
			for (std::vector<room>::iterator it = rm.activate_rooms.begin(); it != rm.activate_rooms.end(); ++it)
			{
				if (it->getRoomName() == str)
				{
					if (it->is_started == true) //game started
					{
						toSend = 0;
					}
				}
			}

			std::string full = "K" + '1' + std::to_string(toSend);
			send(clientSocket, full.c_str(), full.size(), 0);  // last parameter: flag. for us will be 0.
		}

	}



}

void loginSend(SOCKET clientSocket, LoginRequestHandler lo, RequestInfo r)
{
	Login log = lo.getLogin(r.BData);
	std::cout << "username: " << log.name << "\npassword - " << log.pass << std::endl;

	std::string login = "";
	ResponsePacketSerializer rps;

	if (log.name == "" || log.pass == "")
	{
		loginRespons loginRes;
		loginRes.status = 1; //error
		login = rps.serializeLoginResponse(loginRes);
	}
	else
	{
		loginRespons loginRes;
		if (Database.doesPasswordMatch(log))
		{
			loginRes.status = 0;
			std::pair<std::string, SOCKET>p(log.name, clientSocket);
			m_users.insert(p);
		}
		else
		{
			loginRes.status = 1;
		}
		login = rps.serializeLoginResponse(loginRes);
	}

	send(clientSocket, login.c_str(), login.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the status to the client" << std::endl;
}

void signUpSend(SOCKET clientSocket, LoginRequestHandler lo, RequestInfo r)
{
	SignUp log = lo.getSignUp(r.BData);
	std::cout << "username: " << log.name << "\npassword - " << log.pass << "\nemail: " << log.email << std::endl;

	std::string login = "";
	ResponsePacketSerializer rps;

	if (log.name == "" || log.pass == "" || log.email == "")
	{
		signUpRespons signRes;
		signRes.status = 1; //error
		login = rps.serializeSignUpResponse(signRes);
	}
	else
	{
		if (Database.doesUserExist(log.name))
		{
			signUpRespons signRes;
			signRes.status = 1; //error
			login = rps.serializeSignUpResponse(signRes);
		}
		else if (Database.addUser(log))
		{
			signUpRespons signRes;
			signRes.status = 0; //not error
			login = rps.serializeSignUpResponse(signRes);
		}
		else
		{
			signUpRespons signRes;
			signRes.status = 1; //error
			login = rps.serializeSignUpResponse(signRes);
		}
	}

	send(clientSocket, login.c_str(), login.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the status to the client" << std::endl;
}

void logOutSend(SOCKET clientSocket)
{
	ResponsePacketSerializer rps;
	logOutResponse l;
	l.status = 0;
	std::string s = rps.serializeLogoutResponse(l); //sending log out response
	send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the logout to the client" << std::endl;

	std::string name;
	for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (it->second == clientSocket)
		{
			name = it->first;
			std::cout << "removing from users online: " << name << std::endl;
		}
	}
	m_users.erase(name);
	std::cout << m_users.size() << std::endl;
}

void GetRoomsSend(SOCKET clientSocket)
{
	ResponsePacketSerializer rps;
	getRoomsResponse l;
	l.rooms = rm.getActiveRooms();
	l.status = 0;
	std::string s = rps.serializeGetRoomResponse(l);
	send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the rooms list to the client" << std::endl;
}

void getPlayersInRoomSend(SOCKET clientSocket, RequestInfo r)
{
	char c1 = ' ';
	std::string num_s = "";
	int i = 1;
	for (i; c1 != '`'; i++)
	{
		c1 = r.BData[i + 1];
		num_s = num_s + r.BData[i];
	}
	int size = atoi(num_s.c_str());
	i = i + 1;
	std::string name = "";
	for (int j = 0; j < size; j++)
	{
		name = name + r.BData[i];
		i++;
	}
	std::vector<room>ro = rm.getActiveRooms();
	std::vector<std::string>list;
	for (int i = 0; i < ro.size(); i++)
	{
		if (ro.at(i).getRoomName() == name)
		{
			list = ro.at(i).getAllUsers();
		}
	}
	ResponsePacketSerializer rps;
	getPlayersInRoomResponse g;
	g.players = list;
	std::string s = rps.serializeGetPlayersInRoomResponse(g);
	char* buffer = (char*)malloc(s.length() * sizeof(char));
	memcpy(buffer, s.data(), s.length());
	send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
	//std::cout << "sent the players list of a room to the client" << std::endl;

	free(buffer); //freeing the heap memory
}

void joinRoomsend(SOCKET clientSocket, RequestInfo r)
{
	char c1 = ' ';
	std::string num_s = "";
	int i = 1;
	for (i; c1 != '`'; i++)
	{
		c1 = r.BData[i + 1];
		num_s = num_s + r.BData[i];
	}
	int size = atoi(num_s.c_str());
	i = i + 1;
	std::string name = "";
	for (int j = 0; j < size; j++)
	{
		name = name + r.BData[i];
		i++;
	}
	std::string username = "";
	for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (it->second == clientSocket) //finding the name of the client
		{
			username = it->first;
		}
	}
	bool b = rm.addPlayerToRoom(name, username);
	ResponsePacketSerializer rps;
	JoinRoomResponse j2;
	j2.status = 0;
	if (b == false)
	{
		j2.status = 1;
	}
	std::string final = rps.serializeJoinRoomResponse(j2);
	send(clientSocket, final.c_str(), final.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the status of joining to room to the client" << std::endl;
}

void CreateRoomSend(SOCKET clientSocket, RequestInfo r, LoginRequestHandler lo)
{
	CreateRoomRequest g = lo.deserializeCreateRoomRequest(r.BData);
	rm.createRoom(g.roomName);
	std::string name;
	for (std::map<std::string, SOCKET>::iterator it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (clientSocket == it->second)
		{
			name = it->first;
		}
	}
	rm.addPlayerToRoom(g.roomName, name);
	ResponsePacketSerializer rps;
	createRoomResponse f;
	f.status = 0;
	std::string s = rps.serializeCreateRoomResponse(f);

	send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
	std::cout << "sent the status of creating new room to the client" << std::endl;
}
