//
// Created by Róbert Selvek on 07/04/2017.
//

#ifndef SEMESTRALKA_SQLITE_CLIENT_CPP
#define SEMESTRALKA_SQLITE_CLIENT_CPP

#include <cstring>

#include "SqliteClient.h"

namespace sqlite {

    Client::Client(const std::string &path, bool create) {
        auto flags = SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_READWRITE;
        if (create) {
            flags |= SQLITE_OPEN_CREATE;
        }
        int error = sqlite3_open_v2(path.c_str(), &db, flags, nullptr);
        if (error) {
            Exception exc(sqlite3_errmsg(db));
            sqlite3_close(db);
            throw exc;
        }
    }

    Client::~Client() {
        sqlite3_close_v2(db);
    }

    int Client::max_variables() {
        return sqlite3_limit(db, SQLITE_LIMIT_VARIABLE_NUMBER, -1);
    }

    void Client::exec(const std::string &sql) {
        char *error;
        sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        if (error != nullptr) {
            throw Exception(error);
        }
    }

}

#endif