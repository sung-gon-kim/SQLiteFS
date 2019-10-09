#include <iostream>
#include <stdexcept>
#include "../SQLiteFS/SQLiteFS.hpp"

int wmain(int argc, wchar_t* argv[]) {
	SQLite::FS filesystem;
	try {
		filesystem.start(argc, argv);
		return EXIT_SUCCESS;
	}
	catch (const std::invalid_argument& e) {
		std::cout << L"fatal: " << e.what() << std::endl << std::endl;
		std::cout << L"usage: sqlitefs.exe <filename> <mount_point>" << std::endl;
		return EXIT_FAILURE;
	}
	catch (const std::runtime_error& e) {
		std::cout << L"fatal: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
