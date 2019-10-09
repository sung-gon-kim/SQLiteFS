#include <stdexcept>
#include "SQLiteArchive.hpp"
#include "SQLiteFS.hpp"

namespace SQLite {

	static std::wstring pathToFile;
	static std::wstring mountPoint;
	static SQLite::Archive archive;

	BOOL WINAPI ConsoleControlHandler(DWORD dwCtrlType) {
		switch (dwCtrlType) {
		case CTRL_C_EVENT:
		case CTRL_BREAK_EVENT:
		case CTRL_CLOSE_EVENT:
		case CTRL_LOGOFF_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			SetConsoleCtrlHandler(ConsoleControlHandler, FALSE);
			DokanRemoveMountPoint(mountPoint.c_str());
			return TRUE;
		default:
			return FALSE;
		}
	}

	std::shared_ptr<DOKAN_OPTIONS> FS::parse(const std::vector<std::wstring>& args) {
		if (args.size() < 3) {
			throw std::invalid_argument("Not enough arguments");
		}

		pathToFile = args[1];
		mountPoint = args[2];

		archive.open(pathToFile);

		if (!SetConsoleCtrlHandler(ConsoleControlHandler, TRUE)) {
			throw std::runtime_error("Failed to set up the console control handler");
		}

		auto options = std::make_shared<DOKAN_OPTIONS>();
		options->Version = DOKAN_VERSION;
		options->ThreadCount = 0;
		options->MountPoint = mountPoint.c_str();
		// options->Options |= DOKAN_OPTION_STDERR;
		// options->Options |= DOKAN_OPTION_DEBUG;
		return options;
	}

	static NTSTATUS DOKAN_CALLBACK createFile(LPCWSTR FileName, PDOKAN_IO_SECURITY_CONTEXT SecurityContext, ACCESS_MASK DesiredAccess, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->createFile(SecurityContext, DesiredAccess, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, DokanFileInfo);
	}

	static void DOKAN_CALLBACK closeFile(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->closeFile(DokanFileInfo);
	}

	static void DOKAN_CALLBACK cleanup(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->cleanup(DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK readFile(LPCWSTR FileName, LPVOID Buffer, DWORD BufferLength, LPDWORD ReadLength, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->readFile(Buffer, BufferLength, ReadLength, Offset, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK writeFile(LPCWSTR FileName, LPCVOID Buffer, DWORD NumberOfBytesToWrite, LPDWORD NumberOfBytesWritten, LONGLONG Offset, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->writeFile(Buffer, NumberOfBytesToWrite, NumberOfBytesWritten, Offset, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK flushFileBuffers(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->flushFileBuffers(DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK getFileInformation(LPCWSTR FileName, LPBY_HANDLE_FILE_INFORMATION HandleFileInformation, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->getFileInformation(HandleFileInformation, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK findFiles(LPCWSTR FileName, PFillFindData FillFindData, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->findFiles(FillFindData, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK deleteFile(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->deleteFile(DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK deleteDirectory(LPCWSTR FileName, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->deleteDirectory(DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK moveFile(LPCWSTR FileName, LPCWSTR NewFileName, BOOL ReplaceIfExisting, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->moveFile(NewFileName, ReplaceIfExisting, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK setEndOfFile(LPCWSTR FileName, LONGLONG ByteOffset, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->setEndOfFile(ByteOffset, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK setAllocationSize(LPCWSTR FileName, LONGLONG AllocSize, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->setAllocationSize(AllocSize, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK setFileAttributes(LPCWSTR FileName, DWORD FileAttributes, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->setFileAttributes(FileAttributes, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK setFileTime(LPCWSTR FileName, CONST FILETIME* CreationTime, CONST FILETIME* LastAccessTime, CONST FILETIME* LastWriteTime, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->setFileTime(CreationTime, LastAccessTime, LastWriteTime, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK getFileSecurity(LPCWSTR FileName, PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG BufferLength, PULONG LengthNeeded, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->getFileSecurity(SecurityInformation, SecurityDescriptor, BufferLength, LengthNeeded, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK setFileSecurity(LPCWSTR FileName, PSECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR SecurityDescriptor, ULONG SecurityDescriptorLength, PDOKAN_FILE_INFO DokanFileInfo) {
		return archive.get(FileName)->setFileSecurity(SecurityInformation, SecurityDescriptor, SecurityDescriptorLength, DokanFileInfo);
	}

	static NTSTATUS DOKAN_CALLBACK getVolumeInformation(LPWSTR VolumeNameBuffer, DWORD VolumeNameSize, LPDWORD VolumeSerialNumber, LPDWORD MaximumComponentLength, LPDWORD FileSystemFlags, LPWSTR FileSystemNameBuffer, DWORD FileSystemNameSize, PDOKAN_FILE_INFO DokanFileInfo) {
		wcscpy_s(FileSystemNameBuffer, FileSystemNameSize, L"NTFS");
		return STATUS_SUCCESS;
	}

	static NTSTATUS DOKAN_CALLBACK getDiskFreeSpace(PULONGLONG FreeBytesAvailable, PULONGLONG TotalNumberOfBytes, PULONGLONG TotalNumberOfFreeBytes, PDOKAN_FILE_INFO DokanFileInfo) {
		*TotalNumberOfBytes = 1024ULL * 1024 * 1024 * 2;
		*FreeBytesAvailable = 1024ULL * 1024 * 1024;
		*TotalNumberOfFreeBytes = 1024ULL * 1024 * 1024;
		return STATUS_SUCCESS;
	}

	static NTSTATUS DOKAN_CALLBACK mounted(PDOKAN_FILE_INFO DokanFileInfo) {
		UNREFERENCED_PARAMETER(DokanFileInfo);
		return STATUS_SUCCESS;
	}

	static NTSTATUS DOKAN_CALLBACK unmounted(PDOKAN_FILE_INFO DokanFileInfo) {
		UNREFERENCED_PARAMETER(DokanFileInfo);
		return STATUS_SUCCESS;
	}

	std::shared_ptr<DOKAN_OPERATIONS> FS::populate() {
		auto operations = std::make_shared<DOKAN_OPERATIONS>();
		operations->ZwCreateFile = createFile;
		operations->CloseFile = closeFile;
		operations->Cleanup = cleanup;
		operations->ReadFile = readFile;
		operations->WriteFile = writeFile;
		operations->FlushFileBuffers = flushFileBuffers;
		operations->GetFileInformation = getFileInformation;
		operations->FindFiles = findFiles;
		operations->FindFilesWithPattern = nullptr;
		operations->DeleteFile = deleteFile;
		operations->DeleteDirectory = deleteDirectory;
		operations->MoveFile = moveFile;
		operations->LockFile = nullptr;
		operations->SetEndOfFile = setEndOfFile;
		operations->SetAllocationSize = setAllocationSize;
		operations->SetFileAttributes = setFileAttributes;
		operations->SetFileTime = setFileTime;
		operations->UnlockFile = nullptr;
		operations->GetFileSecurity = getFileSecurity;
		operations->SetFileSecurity = setFileSecurity;
		operations->GetVolumeInformation = getVolumeInformation;
		operations->GetDiskFreeSpace = getDiskFreeSpace;
		operations->FindStreams = nullptr;
		operations->Mounted = mounted;
		operations->Unmounted = unmounted;
		return operations;
	}
}
