#pragma warning(push, 0)
#include <gtest/gtest.h>
#pragma warning(pop)
#include <memory>
#include <string>
#include "TestUtils.hpp"
#include "../SQLiteFS/SQLiteDatabase.hpp"

class SQLiteColumnTest : public ::testing::Test {
protected:
	void SetUp() override {
		database = std::make_unique<SQLite::Database>(Constants::Test::DB_FILE);
		database->execute(Constants::Test::CREATE_TABLE);
	}

	std::unique_ptr<SQLite::Database> database;
};

TEST_F(SQLiteColumnTest, testGetColumnData) {
	database->execute(Constants::Test::INSERT_DATA);
	auto stmt = database->prepare(Constants::Test::SELECT_ALL_DATA);
	stmt.fetch();
	EXPECT_STREQ("first", stmt.getColumn(0).getName());
	EXPECT_EQ(1, stmt.getColumn(0).getInt());
	EXPECT_EQ(2.0, stmt.getColumn(1).getDouble());
	EXPECT_STREQ("three", stmt.getColumn("third").getText());
	EXPECT_EQ("³×¹øÂ°", stmt.getColumn("fourth").getString());
}
