#pragma once

#include <sqlite3.h>
#include <memory>
#include <string>
#include "SQLiteStatement.hpp"

namespace SQLite {

	class Database {
	public:
		enum OPEN {
			READONLY = SQLITE_OPEN_READONLY,
			READWRITE = SQLITE_OPEN_READWRITE,
			CREATE = SQLITE_OPEN_CREATE,
		};

		Database(const std::string& filename, int flags = OPEN::READWRITE | OPEN::CREATE);

		int execute(const std::string& statement);
		Statement prepare(const std::string& statement);

	private:
		void checkReturn(int status);
		sqlite3* getDB();

		std::unique_ptr<sqlite3, int(*)(sqlite3*)> mDB;
	};
}