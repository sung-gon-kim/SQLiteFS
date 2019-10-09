#pragma once

#pragma warning(push, 0)
#include <Windows.h>
#pragma warning(pop)
#include <ctime>
#include <algorithm>
#include <memory>
#include <string>

namespace util {

	namespace string {

		inline std::string to_string(const std::wstring& s, UINT codePage = CP_OEMCP) {
			int length = WideCharToMultiByte(codePage, 0, s.data(), static_cast<int>(s.size()), nullptr, 0, nullptr, nullptr);
			std::unique_ptr<char[]> data(new char[length]);
			WideCharToMultiByte(codePage, 0, s.data(), static_cast<int>(s.size()), data.get(), length, nullptr, nullptr);
			return std::string(data.get(), length);
		}

		inline std::wstring to_wstring(const std::string& s, UINT codePage = CP_OEMCP) {
			int length = MultiByteToWideChar(codePage, 0, s.data(), static_cast<int>(s.size()), nullptr, 0);
			std::unique_ptr<wchar_t[]> data(new wchar_t[length]);
			MultiByteToWideChar(codePage, 0, s.data(), static_cast<int>(s.size()), data.get(), length);
			return std::wstring(data.get(), length);
		}

		template <typename T>
		inline std::basic_string<T> ltrim(const std::basic_string<T>& s, const T ch) {
			auto first = std::find_if_not(s.begin(), s.end(), [&](const T c) { return ch == c; });
			auto last = s.end();
			return (first >= last) ? std::basic_string<T>() : std::basic_string<T>(first, last);
		}

		template <typename T>
		inline std::basic_string<T> ltrim(const T* s, const T ch) {
			return ltrim(std::basic_string<T>(s), ch);
		}

		template <typename T>
		inline std::basic_string<T> rtrim(const std::basic_string<T>& s, const T ch) {
			auto first = s.begin();
			auto last = std::find_if_not(s.rbegin(), s.rend(), [&](const T c) { return ch == c; }).base();
			return (first >= last) ? std::basic_string<T>() : std::basic_string<T>(first, last);
		}

		template <typename T>
		inline std::basic_string<T> rtrim(const T* s, const T ch) {
			return rtrim(std::basic_string<T>(s), ch);
		}

		template <typename T>
		inline std::basic_string<T> trim(const std::basic_string<T>& s, const T ch) {
			return ltrim(rtrim(s, ch), ch);
		}

		template <typename T>
		inline std::basic_string<T> trim(const T* s, const T ch) {
			return trim(std::basic_string<T>(s), ch);
		}

		template <typename T>
		inline std::basic_string<T> replace(std::basic_string<T> s, const T from, const T to) {
			std::replace(s.begin(), s.end(), from, to);
			return s;
		}

		template <typename T>
		inline std::basic_string<T> replace(const T* s, const T from, const T to) {
			return replace(std::basic_string<T>(s), from, to);
		}

		template <typename T>
		inline bool endsWith(const std::basic_string<T>& haystack, const std::basic_string<T>& needle) {
			return std::equal(needle.rbegin(), needle.rend(), haystack.rbegin());
		}

		template <typename T>
		inline bool endsWith(const std::basic_string<T>& haystack, const T* needle) {
			return endsWith(haystack, std::basic_string<T>(needle));
		}

		template <typename T>
		inline bool endsWith(const T* haystack, const std::basic_string<T>& needle) {
			return endsWith(std::basic_string<T>(haystack), needle);
		}

		template <typename T>
		inline bool endsWith(const T* haystack, const T* needle) {
			return endsWith(std::basic_string<T>(haystack), std::basic_string<T>(needle));
		}

	}  // namespace string

	namespace filesystem {

		inline std::string dirname(const std::string& path, const char delim = '/') {
			auto position = path.find_last_of(delim);
			return (position == std::string::npos) ? std::string() : path.substr(0, position);
		}

		inline std::string filename(const std::string& path, const char delim = '/') {
			auto position = path.find_last_of(delim);
			return (position == std::string::npos) ? path : path.substr(position + 1);
		}

	}  // namespace filename

	namespace time {

		inline void TimeToFileTime(std::time_t from, LPFILETIME to) {
			LONGLONG data = Int32x32To64(from, 10000000) + 116444736000000000;
			to->dwHighDateTime = reinterpret_cast<PLARGE_INTEGER>(&data)->HighPart;
			to->dwLowDateTime = reinterpret_cast<PLARGE_INTEGER>(&data)->LowPart;
		}

	}  // namespace

}  // namespace util