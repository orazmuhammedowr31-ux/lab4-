#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

sqlite3* init_db();
void close_db(sqlite3 *db);

#endif