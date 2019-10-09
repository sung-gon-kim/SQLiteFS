#pragma once

#include <sqlite3.h>
#include <string>

namespace SQLite {

	class Column {
	public:
		Column(sqlite3_stmt* stmt, int index);

		int getInt() const noexcept;
		long long getInt64() const noexcept;
		double getDouble() const noexcept;
		const char* getText() const noexcept;
		std::string getString() const noexcept;
		const void* getBlob() const noexcept;

		const char* getName() const noexcept;
		int size() const noexcept;

	private:
		sqlite3_stmt* mStmt;
		int mIndex;
	};
}