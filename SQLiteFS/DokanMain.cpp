#include <memory>
#include <stdexcept>
#include "DokanMain.hpp"

namespace Dokan {

	void Main::start(int argc, wchar_t* argv[]) {
		std::vector<std::wstring> args;
		for (auto i = 0; i < argc; i++) {
			args.push_back(argv[i]);
		}
		start(args);
	}

	void Main::start(const std::vector<std::wstring>& args) {
		auto options = parse(args);
		auto operations = populate();

		auto status = DokanMain(options.get(), operations.get());

		switch (status) {
		case DOKAN_SUCCESS:
			return;
		case DOKAN_ERROR:
			throw std::runtime_error("Dokan mount error");
		case DOKAN_DRIVE_LETTER_ERROR:
			throw std::runtime_error("Bad Drive letter");
		case DOKAN_DRIVER_INSTALL_ERROR:
			throw std::runtime_error("Can't install driver");
		case DOKAN_START_ERROR:
			throw std::runtime_error("Driver something wrong");
		case DOKAN_MOUNT_ERROR:
			throw std::runtime_error("Can't assign a drive letter");
		case DOKAN_MOUNT_POINT_ERROR:
			throw std::runtime_error("Mount point error");
		case DOKAN_VERSION_ERROR:
			throw std::runtime_error("Version error");
		default:
			throw std::runtime_error("Unknown error");
		}
	}
}
