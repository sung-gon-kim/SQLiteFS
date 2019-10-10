#include "SQLitePreparedStatementFactory.hpp"

namespace SQLite {

	PreparedStatementFactory::PreparedStatementFactory(std::shared_ptr<SQLite::Database> db) : mDB(db) {
	}

	Statement PreparedStatementFactory::createTable() {
		return mDB->prepare(
			"CREATE TABLE IF NOT EXISTS Files ("
			"path TEXT NOT NULL PRIMARY KEY, "
			"type INTEGER NOT NULL DEFAULT 0, "
			"blob BLOB, "
			"ctime TIMESTAMP NOT NULL DEFAULT (strftime('%s', 'now')), "
			"atime TIMESTAMP NOT NULL DEFAULT (strftime('%s', 'now')), "
			"mtime TIMESTAMP NOT NULL DEFAULT (strftime('%s', 'now'))) ");
	}

	Statement PreparedStatementFactory::findByName(const std::string& path) {
		auto stmt = mDB->prepare("SELECT path, type, blob, length(cast(blob as blob)) as size, ctime, atime, mtime FROM Files WHERE path == :path");
		stmt.bind(":path", path);
		return stmt;
	}

	Statement PreparedStatementFactory::listFiles(const std::string& path) {
		if (path == "") {
			return mDB->prepare("SELECT path, type, blob, length(cast(blob as blob)) as size, ctime, atime, mtime FROM Files WHERE path NOT LIKE '%/%'");
		}
		else {
			auto stmt = mDB->prepare("SELECT path, type, blob, length(cast(blob as blob)) as size, ctime, atime, mtime FROM Files WHERE path LIKE :path");
			stmt.bind(":path", path + "/%");
			return stmt;
		}
	}

	Statement PreparedStatementFactory::createDirectory(const std::string& path) {
		auto stmt = mDB->prepare("INSERT INTO Files (path, type) VALUES (:path, 1)");
		stmt.bind(":path", path);
		return stmt;
	}

	Statement PreparedStatementFactory::createFile(const std::string& path, const std::string& blob) {
		auto stmt = mDB->prepare("INSERT INTO Files (path, type, blob) VALUES (:path, 0, :blob)");
		stmt.bind(":path", path)
			.bind(":blob", blob);
		return stmt;
	}

	Statement PreparedStatementFactory::remove(const std::string& path) {
		auto stmt = mDB->prepare("DELETE FROM Files WHERE path == :path");
		stmt.bind(":path", path);
		return stmt;
	}
}
