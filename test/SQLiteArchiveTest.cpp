#include <gtest/gtest.h>
#include <stdexcept>
#include "Constants.hpp"
#include "../SQLiteFS/Constants.hpp"
#include "../SQLiteFS/SQLiteArchive.hpp"

class SQLiteArchiveTest : public ::testing::Test {
protected:
	constexpr static const wchar_t* UNKNOWN_PATH = L"\\폴더1\\폴더2\\폴더3";
	constexpr static const wchar_t* ROOT_PATH = L"\\";
	constexpr static const wchar_t* DIR_PATH = L"\\폴더1";
	constexpr static const wchar_t* FILE_PATH = L"\\폴더1\\파일2.txt";

	void SetUp() override {
		auto db = std::make_shared<SQLite::Database>(Constants::DB_FILE);
		db->execute(Constants::CREATE_TABLE);
		auto stmt = db->prepare("INSERT INTO Files VALUES (:path, :type, :blob)");
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
		archive.open(db);
	}

	SQLite::Archive archive;
};

TEST_F(SQLiteArchiveTest, testGetUnknownPath) {
	auto file = archive.get(UNKNOWN_PATH);
	EXPECT_EQ("폴더1/폴더2/폴더3", file->getPath());
}