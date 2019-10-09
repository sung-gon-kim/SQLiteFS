#include "SQLiteColumn.hpp"

namespace SQLite {

	Column::Column(sqlite3_stmt* stmt, int index) :
		mStmt(stmt), mIndex(index) {
	}

	int Column::getInt() const noexcept {
		return sqlite3_column_int(mStmt, mIndex);
	}

	long long Column::getInt64() const noexcept {
		return sqlite3_column_int64(mStmt, mIndex);
	}

	double Column::getDouble() const noexcept {
		return sqlite3_column_double(mStmt, mIndex);
	}

	const char* Column::getText() const noexcept {
		return reinterpret_cast<const char*>(sqlite3_column_text(mStmt, mIndex));
	}

	std::string Column::getString() const noexcept {
		return std::string(getText(), size());
	}

	const void* Column::getBlob() const noexcept {
		return sqlite3_column_blob(mStmt, mIndex);
	}

	const char* Column::getName() const noexcept {
		return sqlite3_column_name(mStmt, mIndex);
	}

	int Column::size() const noexcept {
		return sqlite3_column_bytes(mStmt, mIndex);
	}
}