#pragma once

namespace Constants {

	constexpr static const int DIRECTORY_TYPE = 1;
	constexpr static const int FILE_TYPE = 0;

	constexpr static const char* CREATE_TABLE =
		"CREATE TABLE IF NOT EXISTS Files("
		"path TEXT NOT NULL PRIMARY KEY, "
		"type INTEGER NOT NULL DEFAULT 0, "
		"blob BLOB, "
		"ctime TIMESTAMP NOT NULL DEFAULT (strftime('%s', 'now')), "
		"atime TIMESTAMP NOT NULL DEFAULT (strftime('%s', 'now')), "
		"mtime TIMESTAMP NOT NULL DEFAULT (strftime('%s', 'now')))";

	constexpr static const char* SELECT_FILE =
		"SELECT path, type, blob, length(blob) as size, ctime, atime, mtime FROM Files WHERE path == :path";

	constexpr static const char* SELECT_ROOT_FILES =
		"SELECT path, type, blob, length(blob) as size, ctime, atime, mtime FROM Files WHERE path NOT LIKE '%/%'";

	constexpr static const char* SELECT_SUB_FILES =
		"SELECT path, type, blob, length(blob) as size, ctime, atime, mtime FROM Files WHERE path LIKE :path";

	constexpr static const char* CREATE_DIRECTORY =
		"INSERT INTO Files (path, type) VALUES (?, 1)";
}