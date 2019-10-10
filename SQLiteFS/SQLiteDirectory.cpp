#include "SQLitePreparedStatementFactory.hpp"
#include "SQLiteDirectory.hpp"
#include "Util.hpp"

namespace SQLite {

	Directory::Directory(std::shared_ptr<SQLite::Database> db, const std::string& path) :
		Entry(db, path) {
	}

	bool Directory::exist() const {
		return true;
	}

	bool Directory::isDirectory() const {
		return true;
	}

	bool Directory::isFile() const {
		return false;
	}

	NTSTATUS DOKAN_CALLBACK Directory::createFile(PDOKAN_IO_SECURITY_CONTEXT SecurityContext, ACCESS_MASK DesiredAccess, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_SUCCESS;
	}

	void DOKAN_CALLBACK Directory::closeFile(PDOKAN_FILE_INFO DokanFileInfo) {
		return;
	}

	void DOKAN_CALLBACK Directory::cleanup(PDOKAN_FILE_INFO DokanFileInfo) {
		if (DokanFileInfo->DeleteOnClose) {
			if (DokanFileInfo->IsDirectory) {
				SQLite::PreparedStatementFactory(getDB()).remove(getPath()).execute();
			}
		}
		return;
	}

	NTSTATUS DOKAN_CALLBACK Directory::readFile(LPVOID Buffer, DWORD BufferLength, LPDWORD ReadLength, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_FILE_IS_A_DIRECTORY;
	}

	NTSTATUS DOKAN_CALLBACK Directory::writeFile(LPCVOID Buffer, DWORD NumberOfBytesToWrite, LPDWORD NumberOfBytesWritten, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Directory::flushFileBuffers(PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_SUCCESS;
	}

	NTSTATUS DOKAN_CALLBACK Directory::getFileInformation(LPBY_HANDLE_FILE_INFORMATION HandleFileInformation, PDOKAN_FILE_INFO DokanFileInfo) {
		auto stmt = SQLite::PreparedStatementFactory(getDB()).findByName(getPath());
		if (stmt.fetch()) {
			HandleFileInformation->dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
			util::time::TimeToFileTime(stmt.getColumn("ctime").getInt64(), &HandleFileInformation->ftCreationTime);
			util::time::TimeToFileTime(stmt.getColumn("atime").getInt64(), &HandleFileInformation->ftLastAccessTime);
			util::time::TimeToFileTime(stmt.getColumn("mtime").getInt64(), &HandleFileInformation->ftLastWriteTime);
			auto size = stmt.getColumn("size").getInt64();
			HandleFileInformation->nFileSizeHigh = reinterpret_cast<PLARGE_INTEGER>(&size)->HighPart;
			HandleFileInformation->nFileSizeLow = reinterpret_cast<PLARGE_INTEGER>(&size)->LowPart;
		}
		return STATUS_SUCCESS;
	}

	static std::wstring to_wfilename(const std::string& path) {
		return util::string::to_wstring(util::filesystem::filename(path, '/'), CP_UTF8);
	}

	NTSTATUS DOKAN_CALLBACK Directory::findFiles(PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo) {
		auto stmt = SQLite::PreparedStatementFactory(getDB()).listFiles(getPath());
		while (stmt.fetch()) {
			auto path = stmt.getColumn("path").getString();
			if (getPath() != util::filesystem::dirname(path, '/')) {
				continue;
			}
			WIN32_FIND_DATAW data = {};
			data.dwFileAttributes = (stmt.getColumn("type").getInt() == SQLite::Directory::TYPE) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL;
			wcscpy_s(data.cFileName, to_wfilename(path).c_str());
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

	NTSTATUS DOKAN_CALLBACK Directory::deleteFile(PDOKAN_FILE_INFO DokanFileInfo) {
		if (!DokanFileInfo->DeleteOnClose) {
			return STATUS_SUCCESS;
		}
		return STATUS_ACCESS_DENIED;
	}

	NTSTATUS DOKAN_CALLBACK Directory::deleteDirectory(PDOKAN_FILE_INFO DokanFileInfo) {
		if (!DokanFileInfo->DeleteOnClose) {
			return STATUS_SUCCESS;
		}
		auto stmt = SQLite::PreparedStatementFactory(getDB()).listFiles(getPath());
		if (stmt.fetch()) {
			return STATUS_DIRECTORY_NOT_EMPTY;
		}
		return STATUS_SUCCESS;
	}

	NTSTATUS DOKAN_CALLBACK Directory::moveFile(LPCWSTR NewFileName, BOOL ReplaceIfExisting, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Directory::setEndOfFile(LONGLONG ByteOffset, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Directory::setAllocationSize(LONGLONG AllocSize, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Directory::setFileAttributes(DWORD FileAttributes, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Directory::setFileTime(const FILETIME* CreationTime, const FILETIME* LastAccessTime, const FILETIME* LastWriteTime, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Directory::getFileSecurity(PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG BufferLength, PULONG LengthNeeded, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Directory::setFileSecurity(PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG SecurityDescriptorLength, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}
}
