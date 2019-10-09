#pragma once

#include "SQLiteEntry.hpp"

namespace SQLite {

	class Directory : public Entry {
	public:
		Directory(std::shared_ptr<SQLite::Database> db, const std::string& path);

		bool exist() const override;
		bool isDirectory() const override;
		bool isFile() const override;

		NTSTATUS DOKAN_CALLBACK createFile(PDOKAN_IO_SECURITY_CONTEXT SecurityContext, ACCESS_MASK DesiredAccess, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PDOKAN_FILE_INFO DokanFileInfo) override;
		void DOKAN_CALLBACK closeFile(PDOKAN_FILE_INFO DokanFileInfo) override;
		void DOKAN_CALLBACK cleanup(PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK readFile(LPVOID Buffer, DWORD BufferLength, LPDWORD ReadLength, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK writeFile(LPCVOID Buffer, DWORD NumberOfBytesToWrite, LPDWORD NumberOfBytesWritten, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK flushFileBuffers(PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK getFileInformation(LPBY_HANDLE_FILE_INFORMATION HandleFileInformation, PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK findFiles(PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK deleteFile(PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK deleteDirectory(PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK moveFile(LPCWSTR NewFileName, BOOL ReplaceIfExisting, PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK setEndOfFile(LONGLONG ByteOffset, PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK setAllocationSize(LONGLONG AllocSize, PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK setFileAttributes(DWORD FileAttributes, PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK setFileTime(CONST FILETIME* CreationTime, CONST FILETIME* LastAccessTime, CONST FILETIME* LastWriteTime, PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK getFileSecurity(PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG BufferLength, PULONG LengthNeeded, PDOKAN_FILE_INFO DokanFileInfo) override;
		NTSTATUS DOKAN_CALLBACK setFileSecurity(PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG SecurityDescriptorLength, PDOKAN_FILE_INFO DokanFileInfo) override;
	};
}