#pragma once

#pragma warning (push, 0)
#include <dokan/dokan.h>
#pragma warning (pop)
#include <memory>
#include <string>
#include <vector>

namespace Dokan {

	class Main {
	public:
		void start(int argc, wchar_t* argv[]);
		void start(const std::vector<std::wstring>& args);

	protected:
		virtual std::shared_ptr<DOKAN_OPTIONS> parse(const std::vector<std::wstring>& args) = 0;
		virtual std::shared_ptr<DOKAN_OPERATIONS> populate() = 0;
	};
}