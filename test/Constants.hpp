#pragma once

namespace Constants {
	constexpr static const char* UNKNOWN_FILE = "unknown.db";
	constexpr static const char* DB_FILE = ":memory:";

	constexpr static const char* TEST_CREATE_TABLE = "CREATE TABLE IF NOT EXISTS Test ("
		"first INTEGER PRIMARY KEY, "
		"second DOUBLE, "
		"third TEXT, "
		"fourth BLOB)";
	constexpr static const char* TEST_INSERT_DATA = "INSERT INTO Test VALUES (1, 2.0, 'three', '³×¹øÂ°')";
	constexpr static const char* TEST_INSERT_PREPARED_STMT = "INSERT INTO Test VALUES (:first, :second, :third, :fourth)";
	constexpr static const char* TEST_SELECT_ALL_DATA = "SELECT * FROM Test";
}