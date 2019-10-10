#pragma once

#include <memory>
#include <string>
#include "SQLiteDatabase.hpp"
#include "SQLiteStatement.hpp"

namespace SQLite {

	class PreparedStatementFactory {
	public:
		explicit PreparedStatementFactory(std::shared_ptr<SQLite::Database> db);

		Statement createTable();
		Statement findByName(const std::string& path);
		Statement listFiles(const std::string& path);
		Statement createDirectory(const std::string& path);
		Statement createFile(const std::string& path, const std::string& blob);
		Statement remove(const std::string& path);

	private:
		std::shared_ptr<SQLite::Database> mDB;
	};
}
