#include <stdio.h>
#include <sqlite3.h>
#include "region.h"

void add_region(sqlite3 *db) {
    char name[100], capital[100];
    int population, country_id;
    float square;

    printf("Enter region name: ");
    scanf("%s", name);
    printf("Enter capital: ");
    scanf("%s", capital);
    printf("Enter population: ");
    scanf("%d", &population);
    printf("Enter square: ");
    scanf("%f", &square);
    printf("Enter country ID: ");
    scanf("%d", &country_id);

    char sql[500];
    snprintf(sql, sizeof(sql),
             "INSERT INTO region (name, capital_region, population_region, square_region, country_id) "
             "VALUES ('%s', '%s', %d, %f, %d)",
             name, capital, population, square, country_id);

    char *err;
    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
    } else {
        printf("Region added successfully!\n");
    }
}

void delete_region(sqlite3 *db, int id) {
    char sql[100];
    snprintf(sql, sizeof(sql), "DELETE FROM region WHERE id = %d", id);

    char *err;
    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
    } else {
        printf("Region deleted successfully!\n");
    }
}