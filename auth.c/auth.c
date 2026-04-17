#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "auth.h"
#include "database.h"

int authenticate(const char *username, const char *password) {
    sqlite3 *db = init_db();
    if (!db) return 0;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT password_hash FROM user WHERE username = ?";
    int result = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *hash = (const char *)sqlite3_column_text(stmt, 0);
            // Для простоты сравниваем строки (в реальном проекте — хеширование)
            if (strcmp(hash, password) == 0) {
                result = 1;
            }
        }
    }
    sqlite3_finalize(stmt);
    close_db(db);
    return result;
}