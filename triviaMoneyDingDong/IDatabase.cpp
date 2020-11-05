#include "IDatabase.h"

std::string gUsername;
bool gFound = false;
std::string GBack;
std::vector<std::string> bestData;

bool SqliteDataBase::open()
{
	std::string dbFileName = "DingDong.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db); // open/create a DB for the program

	if (res != SQLITE_OK)
	{
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}

	if (doesFileExist == -1) // if there is a new DB, this part will add the tables and questions it needs
	{
		char* sqlStatement = (char*)"CREATE TABLE USERS (USERNAME TEXT PRIMARY KEY,PASSWORD TEXT, EMAIL TEXT);";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)"CREATE TABLE QUESTIONS1 (ID INTEGER PRIMARY KEY,QUESTION TEXT, ANSWER TEXT);";
		res = this->ask(sqlStatement);

		char String[] = u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(1, '��� ����� �� ��������? `�.���� ����`�.����`�.�� ������`�.����', '�.���� ����');";
		sqlStatement = String;
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(2, '��� ����� ������� �� 680 ���? `�.450`�.784`�.128`�.824', '�.824');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(3, '�� ��� ����� �� ������� �� ��������? `�.��� �������`�.���� ��������`�.������ ��������`�.���� �������', '�.���� �������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(4, '��� ������ �� ������ �� 450 ���? `�.21`�.27`�.66`�.32', '�.27');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(5, '�� ���� ���� ������ �� ������� ����� ����� ���� ����? `�.����� ����`�.��� ���`�.�� ����`�.�^�� ����', '�.�^�� ����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(6, '���� ����� ������ ��� ���� �����? `�.��������`�.�����`�.���`�.�����', '�.��������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(7, '���� ��� ���� ���� � �������? `�.��`�.����� �� �����`�.�����`�.������', '�.����� �� �����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(8, '��� �� �� ����� ��� ��� ���� ��� ��? `�.���`�.��������`�.������`�.�����', '�.������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(9, '���� ���� ���� ������ ������ ����� ��� ������? `�.���� �������������`�.���� �������`�.���� ����������`�.���� ��������', '�.���� �������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(10, '��� ����� ����� ����? `�.������ ���������`�.������ ��������`�.������ ����������`�.�������', '�.�������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(11, '��� ����� ��� ����� ������ ����? `�.����`�.�����`�.���`�.�����', '�.����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(12, '���� ����� ������ ��� ���� �����? `�.�����`�.�����`�.������`�.������', '�.�����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(13, '���� ���� �������� ������ �� ���������? `�.������`�.����`�.�����`�.��������', '�.������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(14, '��� ����� ����� ����� ����? `�.���� ���`�.�����`�.����`�.�����', '�.����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(15, '��� ����� �� ����� ����� ����� ����� ������? `�.52`�.51`�.49`�.50', '�.51');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(16, '��� ���� �������? `�.����� �� ��� ����`�.����� ������ ����`�.����� �� ��� ������ ��������`�.���� ������� ������ ������ ������', '�.���� ������� ������ ������ ������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(17, '�� �� ���������? `�.��� ��� ������`�.��� ������`�.��� ������ ������`�.��� ������', '�.��� ��� ������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(18, '��� ���� ������ ����� �����? `�.9`�.10`�.11`�.12', '�.12');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(19, '������ ���� �� ���� ����, ��� ���� ���� ���� ����? `�.6`�.12`�.18`�.24', '�.6');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(20, '��� ���� ������ �� �����? `�.1000`�.6860`�.7500`�.10020', '�.7500');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(21, '���� ���� ��� ������ ���� �� ����� ������? `�.����� ���������`�.������ ����`�.����� �������`�. ����� ������', '�.����� ������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(22, '��� ���� ���� ������ ����� (��������) ��� ����� ���� �����? `�.10`�.11`�.12`�.13', '�.10');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(23, '���� ��� ���� ����� ���� �� ��� ��� ���? `�.����`�.���`�.�����`�.���', '�.���');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(24, '����� ��� ����� ��� ��� ������ ������? `�.�����`�.���`�.�����`�.���', '�.���');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(25, '��� ����� ����� �����? `�.����`�.������ ���������`�.�����`�.������', '�.����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(26, '�� ��� 1996 ��� ������� ���� ���� ���� �������? `�.500 ������`�.10 �����`�.�������`�.250 ������', '�.�������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(27, '����� ����� ��� ����� �����? `�.������`�.����`�.�����`�.�������', '�.�����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(28, '�� ��� ������ ����� ����� �� ����� ������ ������? `�.�����`�.�����`�.����`�.������', '�.�����');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(29, '��� ���� ������ �� ����� ������? `�.8`�.9`�.10`�.11', '�.11');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS1 (ID, QUESTION, ANSWER) VALUES(30, '���� ����� �� ������, ���� ���� ������ ����? `�.����`�.������`�.�����`�.�����', '�.������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)"CREATE TABLE QUESTIONS2 (ID INTEGER PRIMARY KEY,QUESTION TEXT, ANSWER TEXT);";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(1, '����� ������ �����: _ _ _  _ _ _ _  _ _ _ _ _  _ _ _ _ _  _ _ � _  _ _ _ _  _ _ _ � _ _ _', '��� ���� ����� ����� ���� ���� �������' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(2, '����� �����: _ _ _ _ _ _  � _ _ _ _ _  _ � _ _', '������ ������ ����' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(3, '����: � _ _ _ _ _ �', '�������' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(4, '������: _ _ � _  _ � _ _ _ _  _ _ _ _ _ _', '���� ������ ������');";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(5, '��� �����: _ _ _ � _  _ _ _ _  _ � _ _ _ _', '����� ���� ������' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(6, '���� ���: _ _  _ _ �  _ ^ _ _ _  _ _ _ �','�� ��� �^��� ����' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(7, '��� ����: _ � _ _  _ _ _ _ _  _ _ _  � _ _ _ _ _', '���� ����� ��� ������' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(8, '������ ���: _ _ � _ _ _ _  _ _ _ _ _  _ _ _ _ _ _ �', '������� ����� �������' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(9, '����� �������: _ _ _  _ � _ _ _  _ � _ _ _  _ _ _', '��� ����� ����� ���' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"INSERT INTO QUESTIONS2 (ID, QUESTION, ANSWER) VALUES(10, '���� �����: _ _ � _ _  _ _ � _  _ _ _ _', '����� ���� ����' );";
		res = this->ask(sqlStatement);

		sqlStatement = (char*)u8"CREATE TABLE STATISTICS (USERNAME TEXT PRIMARY KEY,AVG REAL, NUMOFCORRANS INTEGER, NUMOFANS INTEGER, NUMOFGAMES INTEGER, NUMOFWINS INTEGER);";
		res = this->ask(sqlStatement);
	}
	return true;
}




bool SqliteDataBase::addUser(SignUp user)
{
	std::string sqlStatement = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES( '" + user.name + "', '" + user.pass + "', '" + user.email + "');";
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage); // creating the table
	if (res != SQLITE_OK)
	{
		return false;
	}
	sqlStatement = "INSERT INTO STATISTICS (USERNAME, AVG, NUMOFCORRANS, NUMOFANS, NUMOFGAMES, NUMOFWINS) VALUES( '" + user.name + "', " + '0' + ", " + '0' + ", " + '0' + ", " + '0' + ", " + '0' + ");";
	errMessage = nullptr;
	res = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage); // creating the table
	if (res != SQLITE_OK)
	{
		return false;
	}
	return true;
}

bool SqliteDataBase::doesUserExist(std::string username)
{
	std::string sqlStatement = "SELECT * FROM USERS WHERE USERNAME = '" + username + "';";
	char* errMessage = nullptr;
	gUsername = username;
	gFound = false;
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), callback, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return gFound;
}

bool SqliteDataBase::doesPasswordMatch(Login user)
{
	std::string sqlStatement = "SELECT * FROM USERS WHERE USERNAME = '" + user.name + "' AND PASSWORD = '" + user.pass + "';";
	char* errMessage = nullptr;
	gUsername = user.name;
	gFound = false;
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), callback, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return gFound;
}

bool SqliteDataBase::ask(char* state)
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->db, state, callback, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string name)
{
	std::string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME = '" + name + "';";
	char* errMessage = nullptr;
	gUsername = name;
	GBack = "";
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), AVGBack, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	std::string::size_type sz;
	return std::stof(GBack, &sz);
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string name)
{
	std::string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME = '" + name + "';";
	char* errMessage = nullptr;
	gUsername = name;
	GBack = "";
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), corrAns, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return atoi(GBack.c_str());
}

int SqliteDataBase::getNumOfTotalAnswers(std::string name)
{
	std::string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME = '" + name + "';";
	char* errMessage = nullptr;
	gUsername = name;
	GBack = "";
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), allAns, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return atoi(GBack.c_str());
}

int SqliteDataBase::getNumOfPlayerGames(std::string name)
{
	std::string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME = '" + name + "';";
	char* errMessage = nullptr;
	gUsername = name;
	GBack = "";
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), allAns, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return atoi(GBack.c_str());
}

int SqliteDataBase::getNumOfPlayerWins(std::string name)
{
	std::string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME = '" + name + "';";
	char* errMessage = nullptr;
	gUsername = name;
	GBack = "";
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), wins, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return atoi(GBack.c_str());
}

std::vector<std::string> SqliteDataBase::getBestData()
{
	bestData.clear();

	std::string sqlStatement = "SELECT * FROM STATISTICS ORDER BY NUMOFWINS DESC LIMIT 5;";
	char* errMessage = nullptr;
	GBack = "";
	int res = sqlite3_exec(this->db, sqlStatement.c_str(), best5, nullptr, &errMessage);

	return bestData;
}

sqlite3* SqliteDataBase::get_db()
{
	return this->db;
}

statistics::statistics(SqliteDataBase DB)
{
	this->DB = DB;
}

std::string statistics::getPersonalData(std::string username)
{
	std::string msg;
	msg = "`" + std::to_string(this->DB.getPlayerAverageAnswerTime(username)) + "`" + std::to_string(this->DB.getNumOfCorrectAnswers(username)) + "`" + std::to_string(this->DB.getNumOfTotalAnswers(username)) + "`" + std::to_string(this->DB.getNumOfPlayerGames(username)) + "`" + std::to_string(this->DB.getNumOfPlayerWins(username));
	return msg;
}

std::string statistics::getBest5()
{
	std::string msg;
	std::vector<std::string> final5 = this->DB.getBestData();

	for (std::vector<std::string>::iterator it = final5.begin(); it != final5.end(); ++it)
	{
		msg = msg + *it;
	}

	return msg;
}

int callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "USERNAME")
		{
			if (argv[i] == gUsername)
			{
				gFound = true;
			}
		}
	}
	return 0;
}

int AVGBack(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "AVG")
		{
			GBack = argv[i];
		}
	}
	return 0;
}

int corrAns(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "NUMOFCORRANS")
		{
			GBack = argv[i];
		}
	}
	return 0;
}

int allAns(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "NUMOFANS")
		{
			GBack = argv[i];
		}
	}
	return 0;
}

int allGames(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "NUMOFGAMES")
		{
			GBack = argv[i];
		}
	}
	return 0;
}

int wins(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "NUMOFWINS")
		{
			GBack = argv[i];
		}
	}
	return 0;
}

int best5(void* data, int argc, char** argv, char** azColName)
{
	std::string final;
	final = "`";
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "USERNAME")
		{
			final = final + argv[i] + "`";
		}

		if (std::string(azColName[i]) == "AVG")
		{
			final = final + argv[i] + "`";
		}

		if (std::string(azColName[i]) == "NUMOFCORRANS")
		{
			final = final + argv[i] + "`";
		}

		if (std::string(azColName[i]) == "NUMOFANS")
		{
			final = final + argv[i] + "`";
		}

		if (std::string(azColName[i]) == "NUMOFGAMES")
		{
			final = final + argv[i] + "`";
		}

		if (std::string(azColName[i]) == "NUMOFWINS")
		{
			final = final + argv[i];
			bestData.push_back(final);
		}
	}
	return 0;
}
