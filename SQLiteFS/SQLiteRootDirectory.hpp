#pragma once

#include "SQLiteDirectory.hpp"

namespace SQLite {

	class RootDirectory : public Directory {
	public:
		explicit RootDirectory(std::shared_ptr<SQLite::Database> db);

		NTSTATUS DOKAN_CALLBACK getFileInformation(LPBY_HANDLE_FILE_INFORMATION HandleFileInformation, PDOKAN_FILE_INFO DokanFileInfo) override;
	};
}
