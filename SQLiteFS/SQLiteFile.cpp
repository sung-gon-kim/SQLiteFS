#include "Constants.hpp"
#include "Util.hpp"
#include "SQLiteFile.hpp"

namespace SQLite {

	File::File(std::shared_ptr<SQLite::Database> db, const std::string& path) :
		Entry(db, path) {
	}

	bool File::exist() const {
		return true;
	}

	bool File::isDirectory() const {
		return false;
	}

	bool File::isFile() const {
		return true;
	}

	NTSTATUS DOKAN_CALLBACK File::createFile(PDOKAN_IO_SECURITY_CONTEXT SecurityContext, ACCESS_MASK DesiredAccess, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	void DOKAN_CALLBACK File::closeFile(PDOKAN_FILE_INFO DokanFileInfo) {
		return;
	}

	void DOKAN_CALLBACK File::cleanup(PDOKAN_FILE_INFO DokanFileInfo) {
		return;
	}

	NTSTATUS DOKAN_CALLBACK File::readFile(LPVOID Buffer, DWORD BufferLength, LPDWORD ReadLength, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::writeFile(LPCVOID Buffer, DWORD NumberOfBytesToWrite, LPDWORD NumberOfBytesWritten, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::flushFileBuffers(PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::getFileInformation(LPBY_HANDLE_FILE_INFORMATION HandleFileInformation, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::findFiles(PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::deleteFile(PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::deleteDirectory(PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::moveFile(LPCWSTR NewFileName, BOOL ReplaceIfExisting, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::setEndOfFile(LONGLONG ByteOffset, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::setAllocationSize(LONGLONG AllocSize, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::setFileAttributes(DWORD FileAttributes, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::setFileTime(const FILETIME* CreationTime, const FILETIME* LastAccessTime, const FILETIME* LastWriteTime, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::getFileSecurity(PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG BufferLength, PULONG LengthNeeded, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}

	NTSTATUS DOKAN_CALLBACK File::setFileSecurity(PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG SecurityDescriptorLength, PDOKAN_FILE_INFO DokanFileInfo) {
		return STATUS_NOT_IMPLEMENTED;
	}
}
