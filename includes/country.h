#ifndef COUNTRY_H
#define COUNTRY_H

#include <sqlite3.h>

void add_country(sqlite3 *db);
void delete_country(sqlite3 *db, int id);
void list_regions(sqlite3 *db, int country_id);
void avg_population(sqlite3 *db, int country_id);
void total_population(sqlite3 *db);

#endif