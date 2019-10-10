#pragma warning(push, 0)
#include <gtest/gtest.h>
#pragma warning(pop)
#include <stdexcept>
#include "TestUtils.hpp"
#include "../SQLiteFS/SQLiteArchive.hpp"

class SQLiteArchiveTest : public ::testing::Test {
protected:
	void SetUp() override {
		archive.open(TestUtils::populateDatabase());
	}

	SQLite::Archive archive;
};

TEST_F(SQLiteArchiveTest, testGetUnknownPath) {
	auto file = archive.get(L"\\폴더1\\폴더2\\폴더3");
	EXPECT_EQ(u8"폴더1/폴더2/폴더3", file->getPath());
	EXPECT_EQ(u8"폴더1/폴더2", file->getDirname());
	EXPECT_EQ(u8"폴더3", file->getFilename());
	EXPECT_FALSE(file->exist());
	EXPECT_FALSE(file->isDirectory());
	EXPECT_FALSE(file->isFile());
}

TEST_F(SQLiteArchiveTest, testGetRootPath) {
	auto file = archive.get(L"\\");
	EXPECT_EQ(u8"", file->getPath());
	EXPECT_EQ(u8"", file->getDirname());
	EXPECT_EQ(u8"", file->getFilename());
	EXPECT_TRUE(file->exist());
	EXPECT_TRUE(file->isDirectory());
	EXPECT_FALSE(file->isFile());
}

TEST_F(SQLiteArchiveTest, testGetDirPath) {
	auto file = archive.get(L"\\폴더1");
	EXPECT_EQ(u8"폴더1", file->getPath());
	EXPECT_EQ(u8"", file->getDirname());
	EXPECT_EQ(u8"폴더1", file->getFilename());
	EXPECT_TRUE(file->exist());
	EXPECT_TRUE(file->isDirectory());
	EXPECT_FALSE(file->isFile());
}

TEST_F(SQLiteArchiveTest, testGetFilePath) {
	auto file = archive.get(L"\\폴더1\\파일2.txt");
	EXPECT_EQ(u8"폴더1/파일2.txt", file->getPath());
	EXPECT_EQ(u8"폴더1", file->getDirname());
	EXPECT_EQ(u8"파일2.txt", file->getFilename());
	EXPECT_TRUE(file->exist());
	EXPECT_FALSE(file->isDirectory());
	EXPECT_TRUE(file->isFile());
}