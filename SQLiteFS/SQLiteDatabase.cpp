#include <stdexcept>
#include "SQLiteDatabase.hpp"

namespace SQLite {

	Database::Database(const std::string& filename, int flags) : mDB(nullptr, nullptr) {
		sqlite3* db = nullptr;
		checkReturn(sqlite3_open_v2(filename.c_str(), &db, flags, nullptr));
		mDB = { db, sqlite3_close_v2 };
	}

	int Database::execute(const std::string& statement) {
		checkReturn(sqlite3_exec(getDB(), statement.c_str(), nullptr, nullptr, nullptr));
		return sqlite3_changes(getDB());
	}

	Statement Database::prepare(const std::string& statement) {
		sqlite3_stmt* stmt = nullptr;
		checkReturn(sqlite3_prepare_v2(getDB(), statement.c_str(), statement.size(), &stmt, nullptr));
		return Statement(stmt);
	}

	void Database::checkReturn(int status) {
		if (status != SQLITE_OK) {
			throw std::runtime_error(sqlite3_errmsg(getDB()));
		}
	}

	sqlite3* Database::getDB() {
		return mDB.get();
	}
}