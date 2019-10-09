#include <stdexcept>
#include "SQLiteArchive.hpp"
#include "Util.hpp"
#include "Constants.hpp"
#include "SQLiteRootDirectory.hpp"
#include "SQLiteDirectory.hpp"
#include "SQLiteFile.hpp"
#include "SQLitePath.hpp"

namespace SQLite {

	void Archive::open(std::shared_ptr<SQLite::Database> db) {
		mDB = db;
	}

	void Archive::open(const std::string& path) {
		try {
			mDB = std::make_shared<SQLite::Database>(path);
			mDB->execute(Constants::CREATE_TABLE);
		}
		catch (const std::runtime_error& e) {
			throw std::invalid_argument(e.what());
		}
	}

	void Archive::open(const std::wstring& path) {
		open(util::string::to_string(path, CP_UTF8));
	}

	static std::string normalize(const std::string& path) {
		return util::string::trim(util::string::replace(path, '\\', '/'), '/');
	}

	std::shared_ptr<SQLite::Entry> Archive::get(const std::string& path) {
		auto pathToFile = normalize(path);

		if (pathToFile == "") {
			return std::make_shared<SQLite::RootDirectory>(mDB);
		}

		auto stmt = mDB->prepare(Constants::SELECT_FILE);
		stmt.bind(":path", pathToFile);

		if (!stmt.fetch()) {
			return std::make_shared<SQLite::Path>(mDB, pathToFile);
		}
		if (stmt.getColumn("type").getInt() == Constants::DIRECTORY_TYPE) {
			return std::make_shared<SQLite::Directory>(mDB, pathToFile);
		}
		return std::make_shared <SQLite::File>(mDB, pathToFile);
	}

	std::shared_ptr<SQLite::Entry> Archive::get(const std::wstring& path) {
		return get(util::string::to_string(path, CP_UTF8));
	}
}
