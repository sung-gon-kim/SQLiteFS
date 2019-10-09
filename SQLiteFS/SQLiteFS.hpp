#pragma once

#include "DokanMain.hpp"

namespace SQLite {

	class FS : public Dokan::Main {
	protected:
		std::shared_ptr<DOKAN_OPTIONS> parse(const std::vector<std::wstring>& args) override;
		std::shared_ptr<DOKAN_OPERATIONS> populate() override;
	};
}
