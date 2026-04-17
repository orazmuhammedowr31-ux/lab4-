#ifndef REGION_H
#define REGION_H

#include <sqlite3.h>

void add_region(sqlite3 *db);
void delete_region(sqlite3 *db, int id);

#endif