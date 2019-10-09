#include "Constants.hpp"
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

	static std::wstring to_wfilename(const std::string& path) {
		return util::string::to_wstring(util::filesystem::filename(path, '/'), CP_UTF8);
	}

	NTSTATUS DOKAN_CALLBACK RootDirectory::findFiles(PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo) {
		auto stmt = getDB()->prepare(Constants::SELECT_ROOT_FILES);
		while (stmt.fetch()) {
			WIN32_FIND_DATAW data = {};
			data.dwFileAttributes = (stmt.getColumn("type").getInt() == Constants::DIRECTORY_TYPE) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL;
			wcscpy_s(data.cFileName, to_wfilename(stmt.getColumn("path").getString()).c_str());
			util::time::TimeToFileTime(stmt.getColumn("ctime").getInt64(), &data.ftCreationTime);
			util::time::TimeToFileTime(stmt.getColumn("atime").getInt64(), &data.ftLastAccessTime);
			util::time::TimeToFileTime(stmt.getColumn("mtime").getInt64(), &data.ftLastWriteTime);
			auto size = stmt.getColumn("size").getInt64();
			data.nFileSizeHigh = reinterpret_cast<PLARGE_INTEGER>(&size)->HighPart;
			data.nFileSizeLow = reinterpret_cast<PLARGE_INTEGER>(&size)->LowPart;
			FillFindData(&data, DokanFileInfo);
		}
		return STATUS_SUCCESS;
	}
}

