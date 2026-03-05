#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>


#define SERVER "127.0.0.1:3306"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "Videogame1"
void ConnectDatabase(sql::Driver*& driver, sql::Connection*& con) {
	try {
		driver = get_driver_instance();
		con = driver->connect(SERVER, USERNAME, PASSWORD);
		std::cout << "Connection Done" << std::endl;
	}

	catch (sql::SQLException e){
		std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
	}
}

void DisconnectDatabase(sql::Connection* con) {
	con->close();

	if (con->isClosed()) {
		std::cout << "Connection Close" << std::endl;
		delete con;
	}
}

void GetAllUsers(sql::Connection* con) {
	
	try {
		sql::Statement* stmt = con->createStatement();
		sql::ResultSet* res = stmt->executeQuery("SELECT userName FROM users");

		std::cout << "users in the database: " << std::endl;

		while (res->next()) {
			std::cout << res->getString("users") << std::endl;
		}

		delete res;
		delete stmt;
	}

	catch (sql::SQLException& e) {
		std::cout << "Error while fetching users: " << e.what() << std::endl;
	}
	
}


void main()
{
	sql::Driver* driver;
	sql::Connection* con;
	con->setSchema(DATABASE);

	ConnectDatabase(driver, con);
	GetAllUsers(con);
	DisconnectDatabase(con);

	system("pause");
}