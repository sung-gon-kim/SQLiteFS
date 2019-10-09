#include <gtest/gtest.h>
#include <stdexcept>
#include "TestUtils.hpp"
#include "../SQLiteFS/Constants.hpp"
#include "../SQLiteFS/SQLiteArchive.hpp"

class SQLiteArchiveTest : public ::testing::Test {
protected:
	void SetUp() override {
		archive.open(TestUtils::populateDatabase());
	}

	SQLite::Archive archive;
};

TEST_F(SQLiteArchiveTest, testGetUnknownPath) {
	auto file = archive.get(Constants::Test::UNKNOWN_PATH);
	EXPECT_EQ("폴더1/폴더2/폴더3", file->getPath());
	EXPECT_EQ("폴더1/폴더2", file->getDirname());
	EXPECT_EQ("폴더3", file->getFilename());
	EXPECT_FALSE(file->exist());
	EXPECT_FALSE(file->isDirectory());
	EXPECT_FALSE(file->isFile());
}

TEST_F(SQLiteArchiveTest, testGetRootPath) {
	auto file = archive.get(Constants::Test::ROOT_PATH);
	EXPECT_EQ("", file->getPath());
	EXPECT_EQ("", file->getDirname());
	EXPECT_EQ("", file->getFilename());
	EXPECT_TRUE(file->exist());
	EXPECT_TRUE(file->isDirectory());
	EXPECT_FALSE(file->isFile());
}

TEST_F(SQLiteArchiveTest, testGetDirPath) {
	auto file = archive.get(Constants::Test::DIR_PATH);
	EXPECT_EQ("폴더1", file->getPath());
	EXPECT_EQ("", file->getDirname());
	EXPECT_EQ("폴더1", file->getFilename());
	EXPECT_TRUE(file->exist());
	EXPECT_TRUE(file->isDirectory());
	EXPECT_FALSE(file->isFile());
}

TEST_F(SQLiteArchiveTest, testGetFilePath) {
	auto file = archive.get(Constants::Test::FILE_PATH);
	EXPECT_EQ("폴더1/파일2.txt", file->getPath());
	EXPECT_EQ("폴더1", file->getDirname());
	EXPECT_EQ("파일2.txt", file->getFilename());
	EXPECT_TRUE(file->exist());
	EXPECT_FALSE(file->isDirectory());
	EXPECT_TRUE(file->isFile());
}