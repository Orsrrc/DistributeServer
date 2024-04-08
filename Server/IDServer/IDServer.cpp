#include "IDServer.h"

int IDServer::connectToMysql(MYSQL* conn, const char* host, const char* user, const char* password, const char* database)
{                                                                   // MySQL connection object
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cerr << "Error initializing MySQL: " << mysql_error(conn) << std::endl;
        return NULL;
    }

    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL) 
    {
        std::cerr << "Error connecting to MySQL: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return NULL;
    }
    return OK;
}

int IDServer::insertServerInfo(MYSQL *conn, const char* ID, const char* ServerName, const char* IPAddress)
{

  MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (stmt == NULL) {
        std::cerr << "Error initializing statement: " << mysql_error(conn) << std::endl;
        return ERROR;
    }

    const char *sql = "INSERT INTO IDinfo (ID, ServerName, IPAddress) VALUES (?, ?, ?)";
    if (mysql_stmt_prepare(stmt, sql, strlen(sql)) != 0) {
        std::cerr << "Error preparing statement: " << mysql_error(conn) << std::endl;
        mysql_stmt_close(stmt);
        return ERROR;
    }

    //bind info
    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)ID;
    bind[0].buffer_length = strlen(ID);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)ServerName;
    bind[1].buffer_length = strlen(ServerName);

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)IPAddress;
    bind[2].buffer_length = strlen(IPAddress);

    if (mysql_stmt_bind_param(stmt, bind) != 0) {
        std::cerr << "Error binding parameters: " << mysql_error(conn) << std::endl;
        mysql_stmt_close(stmt);
        return ERROR;
    }

    if (mysql_stmt_execute(stmt) != 0) {
        std::cerr << "Error executing statement: " << mysql_error(conn) << std::endl;
        mysql_stmt_close(stmt);
        return ERROR;
    }

    mysql_stmt_close(stmt);
    return OK;
}
