#include "SQLiteEntry.hpp"
#include "Util.hpp"

namespace SQLite {

	Entry::Entry(std::shared_ptr<SQLite::Database> db, const std::string& path) :
		mDB(db), mPath(path) {
	}

	std::string Entry::getPath() const {
		return mPath;
	}

	std::string Entry::getDirname() const {
		return util::filesystem::dirname(getPath(), '/');
	}

	std::string Entry::getFilename() const {
		return util::filesystem::filename(getPath(), '/');
	}

	std::shared_ptr<SQLite::Database> Entry::getDB() {
		return mDB;
	}
}
