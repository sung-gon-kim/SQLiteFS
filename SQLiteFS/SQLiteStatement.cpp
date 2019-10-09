#include <stdexcept>
#include "SQLiteStatement.hpp"

namespace SQLite {
	Statement::Statement(sqlite3_stmt* statement) : 
		mStatement(statement, sqlite3_finalize) {
	}

	int Statement::execute() {
		auto status = sqlite3_step(getStmt());
		if (status == SQLITE_DONE) {
			return sqlite3_changes(getDB());
		}
		if (status == sqlite3_errcode(getDB())) {
			throw std::runtime_error(sqlite3_errmsg(getDB()));
		}
		throw std::runtime_error(sqlite3_errstr(SQLITE_MISUSE));
	}

	bool Statement::fetch() {
		auto status = sqlite3_step(getStmt());
		if (status == SQLITE_ROW) {
			return true;
		}
		if (status == SQLITE_DONE) {
			return false;
		}
		if (status == sqlite3_errcode(getDB())) {
			throw std::runtime_error(sqlite3_errmsg(getDB()));
		}
		throw std::runtime_error(sqlite3_errstr(SQLITE_MISUSE));
	}

	void Statement::reset() {
		sqlite3_reset(getStmt());
		sqlite3_clear_bindings(getStmt());
	}

	Statement& Statement::bind(const int index, const int value) {
		checkReturn(sqlite3_bind_int(getStmt(), index, value));
		return *this;
	}

	Statement& Statement::bind(const int index, const unsigned int value) {
		checkReturn(sqlite3_bind_int64(getStmt(), index, value));
		return *this;
	}

	Statement& Statement::bind(const int index, const long long value) {
		checkReturn(sqlite3_bind_int64(getStmt(), index, value));
		return *this;
	}

	Statement& Statement::bind(const int index, const double value) {
		checkReturn(sqlite3_bind_double(getStmt(), index, value));
		return *this;
	}

	Statement& Statement::bind(const int index, const std::string& value) {
		checkReturn(sqlite3_bind_text(getStmt(), index,
			value.c_str(), static_cast<int>(value.size()), SQLITE_TRANSIENT));
		return *this;
	}

	Statement& Statement::bind(const int index, const char* value) {
		checkReturn(sqlite3_bind_text(getStmt(), index, value, -1, SQLITE_TRANSIENT));
		return *this;
	}

	Statement& Statement::bind(const int index, const void* value, int size) {
		checkReturn(sqlite3_bind_blob(getStmt(), index, value, size, SQLITE_TRANSIENT));
		return *this;
	}

	Statement& Statement::bind(const int index) {
		checkReturn(sqlite3_bind_null(getStmt(), index));
		return *this;
	}

	Statement& Statement::bind(const std::string& name, const int value) {
		auto index = sqlite3_bind_parameter_index(getStmt(), name.c_str());
		return bind(index, value);
	}

	Statement& Statement::bind(const std::string& name, const unsigned int value) {
		auto index = sqlite3_bind_parameter_index(getStmt(), name.c_str());
		return bind(index, value);
	}

	Statement& Statement::bind(const std::string& name, const long long value) {
		auto index = sqlite3_bind_parameter_index(getStmt(), name.c_str());
		return bind(index, value);
	}

	Statement& Statement::bind(const std::string& name, const double value) {
		auto index = sqlite3_bind_parameter_index(getStmt(), name.c_str());
		return bind(index, value);
	}

	Statement& Statement::bind(const std::string& name, const std::string& value) {
		auto index = sqlite3_bind_parameter_index(getStmt(), name.c_str());
		return bind(index, value);
	}

	Statement& Statement::bind(const std::string& name, const char* value) {
		auto index = sqlite3_bind_parameter_index(getStmt(), name.c_str());
		return bind(index, value);
	}

	Statement& Statement::bind(const std::string& name, const void* value, int size) {
		auto index = sqlite3_bind_parameter_index(getStmt(), name.c_str());
		return bind(index, value, size);
	}

	Statement& Statement::bind(const std::string& name) {
		auto index = sqlite3_bind_parameter_index(getStmt(), name.c_str());
		return bind(index);
	}

	Column Statement::getColumn(const int index) {
		if (index < 0 || sqlite3_column_count(getStmt()) < index) {
			throw std::runtime_error(std::to_string(index) + ": index out of bounds");
		}
		return Column(getStmt(), index);
	}

	Column Statement::getColumn(const std::string& name) {
		for (auto i = 0; i < sqlite3_column_count(getStmt()); i++) {
			if (name == sqlite3_column_name(getStmt(), i)) {
				return Column(getStmt(), i);
			}
		}
		throw std::runtime_error(name + ": column name does not exist");
	}

	void Statement::checkReturn(int status) {
		if (status != SQLITE_OK) {
			throw std::runtime_error(sqlite3_errmsg(getDB()));
		}
	}

	sqlite3* Statement::getDB() {
		return sqlite3_db_handle(getStmt());
	}

	sqlite3_stmt* Statement::getStmt() {
		return mStatement.get();
	}
}