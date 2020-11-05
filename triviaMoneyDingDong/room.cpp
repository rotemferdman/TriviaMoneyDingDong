#include "room.h"

room::room(int room_num, std::string room_name)
{
	this->room_num = room_num;
	this->room_name = room_name;
	this->is_active = true;
	this->is_started = false;
}

void room::addUser(std::string player)
{
	this->players_in_room.push_back(player);
}

void room::removeUser(std::string player)
{

	for (std::vector<std::string>::iterator it = this->players_in_room.begin(); it != this->players_in_room.end(); ++it)
	{
		if (*it == player)
		{
			this->players_in_room.erase(it);
		}
	}
}

std::vector<std::string> room::getAllUsers()
{
	return this->players_in_room;
}

unsigned int room::getRoomNum()
{
	return this->room_num;
}

bool room::getRoomState()
{
	return this->is_active;
}

std::string room::getRoomName()
{
	return this->room_name;
}


void roomManager::createRoom(std::string roomName)
{
	this->number_of_rooms++;
	room newRoom(this->number_of_rooms, roomName);
	this->activate_rooms.push_back(newRoom);

}

void roomManager::deleteRoom(int room_num)
{
	for (std::vector<room>::iterator it = this->activate_rooms.begin(); it != this->activate_rooms.end(); ++it)
	{
		if (it->getRoomNum() == room_num)
		{
			this->activate_rooms.erase(it);
		}
	}
}

bool roomManager::getRoomState(int room_num)
{
	for (std::vector<room>::iterator it = this->activate_rooms.begin(); it != this->activate_rooms.end(); ++it)
	{
		if (it->getRoomNum() == room_num)
		{
			return it->getRoomState();
		}
	}
	return false;
}

std::vector<room> roomManager::getActiveRooms()
{
	return this->activate_rooms;
}

bool roomManager::addPlayerToRoom(std::string roomName, std::string player)
{
	int j = -1;
	
	for (int i = 0; i < this->activate_rooms.size(); i++)
	{
		if (this->activate_rooms.at(i).getRoomName() == roomName)
		{
			if (!(this->activate_rooms.at(i).getAllUsers().size() >= MAX_NUM_OF_USERS_IN_ROOM))
			{
				this->activate_rooms.at(i).addUser(player);
				j = 1;
			}
		}
	}
	if (j == -1)
	{
		return false;
	}
	return true;
}
