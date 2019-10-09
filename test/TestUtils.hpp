#pragma once

#include <memory>
#include "../SQLiteFS/Constants.hpp"
#include "../SQLiteFS/SQLiteDatabase.hpp"

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

		constexpr static const wchar_t* UNKNOWN_PATH = L"\\폴더1\\폴더2\\폴더3";
		constexpr static const wchar_t* ROOT_PATH = L"\\";
		constexpr static const wchar_t* DIR_PATH = L"\\폴더1";
		constexpr static const wchar_t* FILE_PATH = L"\\폴더1\\파일2.txt";
	}
}

namespace TestUtils {

	inline std::shared_ptr<SQLite::Database> populateDatabase() {
		auto db = std::make_shared<SQLite::Database>(":memory:");
		db->execute(Constants::CREATE_TABLE);
		auto stmt = db->prepare("INSERT INTO Files (path, type, blob) VALUES (:path, :type, :blob)");
		stmt.bind(":path", "폴더1")
			.bind(":type", Constants::DIRECTORY_TYPE)
			.bind(":blob")
			.execute();
		stmt.reset();
		stmt.bind(":path", "폴더1/폴더2")
			.bind(":type", Constants::DIRECTORY_TYPE)
			.bind(":blob")
			.execute();
		stmt.reset();
		stmt.bind(":path", "파일1.txt")
			.bind(":type", Constants::FILE_TYPE)
			.bind(":blob", "파일1.txt")
			.execute();
		stmt.reset();
		stmt.bind(":path", "폴더1/파일2.txt")
			.bind(":type", Constants::FILE_TYPE)
			.bind(":blob", "폴더1/파일2.txt")
			.execute();
		stmt.reset();
		return db;
	}
}