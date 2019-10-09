#pragma once

#include <memory>
#include <string>
#include "SQLiteDatabase.hpp"
#include "SQLiteEntry.hpp"

namespace SQLite {

	class Archive {
	public:
		void open(std::shared_ptr<SQLite::Database> db);
		void open(const std::string& path);
		void open(const std::wstring& path);

		std::shared_ptr<SQLite::Entry> get(const std::string& path);
		std::shared_ptr<SQLite::Entry> get(const std::wstring& path);

	private:
		std::shared_ptr<SQLite::Database> mDB;
	};
}