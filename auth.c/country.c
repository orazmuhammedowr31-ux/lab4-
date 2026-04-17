#include <stdio.h>
#include <sqlite3.h>
#include "country.h"

void add_country(sqlite3 *db) {
    char name[100], capital[100], language[50], currency[50], head[100];
    int population;
    float square;

    printf("Enter country name: ");
    scanf("%s", name);
    printf("Enter capital: ");
    scanf("%s", capital);
    printf("Enter language: ");
    scanf("%s", language);
    printf("Enter population: ");
    scanf("%d", &population);
    printf("Enter square: ");
    scanf("%f", &square);
    printf("Enter currency: ");
    scanf("%s", currency);
    printf("Enter head of country: ");
    scanf("%s", head);

    char sql[500];
    snprintf(sql, sizeof(sql),
             "INSERT INTO country (name, capital, language, population_country, square_country, currency, head_country) "
             "VALUES ('%s', '%s', '%s', %d, %f, '%s', '%s')",
             name, capital, language, population, square, currency, head);

    char *err;
    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
    } else {
        printf("Country added successfully!\n");
    }
}

void delete_country(sqlite3 *db, int id) {
    char sql[100];
    snprintf(sql, sizeof(sql), "DELETE FROM country WHERE id = %d", id);

    char *err;
    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
    } else {
        printf("Country deleted successfully!\n");
    }
}

void list_regions(sqlite3 *db, int country_id) {
    char sql[100];
    snprintf(sql, sizeof(sql), "SELECT name, capital_region FROM region WHERE country_id = %d", country_id);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        printf("Regions for country ID %d:\n", country_id);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("- %s (Capital: %s)\n",
                   sqlite3_column_text(stmt, 0),
                   sqlite3_column_text(stmt, 1));
        }
    }
    sqlite3_finalize(stmt);
}

void avg_population(sqlite3 *db, int country_id) {
    char sql[100];
    snprintf(sql, sizeof(sql), "SELECT AVG(population_region) FROM region WHERE country_id = %d", country_id);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("Average population for country ID %d: %.2f\n",
                   country_id, sqlite3_column_double(stmt, 0));
        }
    }
    sqlite3_finalize(stmt);
}

void total_population(sqlite3 *db) {
    const char *sql = "SELECT SUM(population_country) FROM country";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("Total population across all countries: %lld\n",
                   sqlite3_column_int64(stmt, 0));
        }
    }
    sqlite3_finalize(stmt);
}