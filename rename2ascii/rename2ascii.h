#pragma once
#include <string>

bool is_illegal(const wchar_t&);
bool needs_renamed(const std::wstring&);
std::string wstring_to_ascii(const std::wstring&);
std::string to_valid_filename(const std::wstring& ws);


