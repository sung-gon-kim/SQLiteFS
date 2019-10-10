#pragma once

#include <memory>
#include "../SQLiteFS/SQLiteDatabase.hpp"
#include "../SQLiteFS/SQLitePreparedStatementFactory.hpp"

namespace Constants {

	namespace Test {

		constexpr static const char* UNKNOWN_FILE = "unknown.db";
		constexpr static const char* DB_FILE = ":memory:";

		constexpr static const char* CREATE_TABLE = "CREATE TABLE IF NOT EXISTS Test ("
			"first INTEGER PRIMARY KEY, "
			"second DOUBLE, "
			"third TEXT, "
			"fourth BLOB)";
		constexpr static const char* INSERT_DATA = "INSERT INTO Test VALUES (1, 2.0, 'three', '네번째')";
		constexpr static const char* INSERT_PREPARED_STMT = "INSERT INTO Test VALUES (:first, :second, :third, :fourth)";
		constexpr static const char* SELECT_ALL_DATA = "SELECT * FROM Test";
	}
}

namespace TestUtils {

	inline std::shared_ptr<SQLite::Database> populateDatabase() {
		auto db = std::make_shared<SQLite::Database>(":memory:");
		auto factory = SQLite::PreparedStatementFactory(db);
		factory.createTable().execute();
		factory.createDirectory(u8"폴더1").execute();
		factory.createDirectory(u8"폴더1/폴더2").execute();
		factory.createFile(u8"파일1.txt", "파일1.txt").execute();
		factory.createFile(u8"폴더1/파일2.txt", "폴더1/파일2.txt").execute();
		return db;
	}
}