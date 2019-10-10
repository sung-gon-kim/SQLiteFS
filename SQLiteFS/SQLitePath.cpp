#include "SQLitePath.hpp"

namespace SQLite {

	Path::Path(std::shared_ptr<SQLite::Database> db, const std::string& path) :
		Entry(db, path) {
	}

	bool Path::exist() const {
		return false;
	}

	bool Path::isDirectory() const {
		return false;
	}

	bool Path::isFile() const {
		return false;
	}

	NTSTATUS DOKAN_CALLBACK Path::createFile(PDOKAN_IO_SECURITY_CONTEXT SecurityContext, ACCESS_MASK DesiredAccess, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_SUCCESS;
	}

	void DOKAN_CALLBACK Path::closeFile(PDOKAN_FILE_INFO DokanFileInfo) {
		return;
	}

	void DOKAN_CALLBACK Path::cleanup(PDOKAN_FILE_INFO DokanFileInfo) {
		return;
	}

	NTSTATUS DOKAN_CALLBACK Path::readFile(LPVOID Buffer, DWORD BufferLength, LPDWORD ReadLength, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_OBJECT_NAME_NOT_FOUND;
	}

	NTSTATUS DOKAN_CALLBACK Path::writeFile(LPCVOID Buffer, DWORD NumberOfBytesToWrite, LPDWORD NumberOfBytesWritten, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Path::flushFileBuffers(PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_SUCCESS;
	}

	NTSTATUS DOKAN_CALLBACK Path::getFileInformation(LPBY_HANDLE_FILE_INFORMATION HandleFileInformation, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_OBJECT_NAME_NOT_FOUND;;
	}

	NTSTATUS DOKAN_CALLBACK Path::findFiles(PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_OBJECT_NAME_NOT_FOUND;;
	}

	NTSTATUS DOKAN_CALLBACK Path::deleteFile(PDOKAN_FILE_INFO DokanFileInfo) {
		if (!DokanFileInfo->DeleteOnClose) {
			return STATUS_SUCCESS;
		}
		return STATUS_OBJECT_NAME_NOT_FOUND;
	}

	NTSTATUS DOKAN_CALLBACK Path::deleteDirectory(PDOKAN_FILE_INFO DokanFileInfo) {
		if (!DokanFileInfo->DeleteOnClose) {
			return STATUS_SUCCESS;
		}
		return STATUS_OBJECT_PATH_NOT_FOUND;
	}

	NTSTATUS DOKAN_CALLBACK Path::moveFile(LPCWSTR NewFileName, BOOL ReplaceIfExisting, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Path::setEndOfFile(LONGLONG ByteOffset, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Path::setAllocationSize(LONGLONG AllocSize, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Path::setFileAttributes(DWORD FileAttributes, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Path::setFileTime(const FILETIME* CreationTime, const FILETIME* LastAccessTime, const FILETIME* LastWriteTime, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Path::getFileSecurity(PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG BufferLength, PULONG LengthNeeded, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK Path::setFileSecurity(PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG SecurityDescriptorLength, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}
}
