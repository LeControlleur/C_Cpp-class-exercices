#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void finish_with_error(MYSQL *);

extern MYSQL *db_connexion();

extern MYSQL_RES *db_get_all(char *, MYSQL *);
