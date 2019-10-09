#include <gtest/gtest.h>
#include "../SQLiteFS/Util.hpp"

class UtilTest : public ::testing::Test {
};

TEST_F(UtilTest, test_string_to_string) {
	EXPECT_EQ("테스트", util::string::to_string(L"테스트"));
	EXPECT_EQ(u8"테스트", util::string::to_string(L"테스트", CP_UTF8));
}

TEST_F(UtilTest, test_string_to_wstring) {
	EXPECT_EQ(L"테스트", util::string::to_wstring("테스트"));
	EXPECT_EQ(L"테스트", util::string::to_wstring(u8"테스트", CP_UTF8));
}

TEST_F(UtilTest, test_string_trim) {
	EXPECT_EQ("테스트", util::string::trim("//테스트//", '/'));
}

TEST_F(UtilTest, test_string_replace) {
	EXPECT_EQ("path/to/file", util::string::replace("path\\to\\file", '\\', '/'));
}

TEST_F(UtilTest, test_string_endsWith) {
	EXPECT_TRUE(util::string::endsWith("path/to/", "/"));
	EXPECT_FALSE(util::string::endsWith("path/to/file", "/"));
}

TEST_F(UtilTest, test_filesystem_dirname) {
	EXPECT_EQ("path/to", util::filesystem::dirname("path/to/file"));
}

TEST_F(UtilTest, test_filesystem_filename) {
	EXPECT_EQ("file", util::filesystem::filename("path/to/file"));
}