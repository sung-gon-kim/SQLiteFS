#include "Constants.hpp"
#include "Util.hpp"
#include "SQLiteRootDirectory.hpp"

namespace SQLite {

	RootDirectory::RootDirectory(std::shared_ptr<SQLite::Database> db) :
		Directory(db, "") {
	}

	NTSTATUS DOKAN_CALLBACK RootDirectory::getFileInformation(LPBY_HANDLE_FILE_INFORMATION HandleFileInformation, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK RootDirectory::findFiles(PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}
}

