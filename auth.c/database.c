#include <stdio.h>
#include <sqlite3.h>
#include "database.h"

sqlite3* init_db() {
    sqlite3 *db;
    if (sqlite3_open("countries.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    return db;
}

void close_db(sqlite3 *db) {
    sqlite3_close(db);
}