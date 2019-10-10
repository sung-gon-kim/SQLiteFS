#include "Util.hpp"
#include "SQLiteRootDirectory.hpp"

namespace SQLite {

	RootDirectory::RootDirectory(std::shared_ptr<SQLite::Database> db) :
		Directory(db, "") {
	}

	NTSTATUS DOKAN_CALLBACK RootDirectory::getFileInformation(LPBY_HANDLE_FILE_INFORMATION HandleFileInformation, PDOKAN_FILE_INFO DokanFileInfo) {
		HandleFileInformation->dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
		HandleFileInformation->ftCreationTime = { 0, 0 };
		HandleFileInformation->ftLastAccessTime = { 0, 0 };
		HandleFileInformation->ftLastWriteTime = { 0, 0 };
		HandleFileInformation->nFileSizeHigh = 0;
		HandleFileInformation->nFileSizeLow = 0;
		return STATUS_SUCCESS;
	}
}

