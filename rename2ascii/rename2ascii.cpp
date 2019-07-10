#include "rename2ascii.h"
#include <string>
#include <algorithm>

bool is_illegal(const wchar_t& wc) {
	if ((wc == '\\') || (wc == '/') || (wc == ':') || (wc == '?') 
			|| (wc == '<') || (wc == '>') || (wc == '|') || wc <= 31
			|| wc > 126) {
		return true;
	}
	return false;
}

bool needs_renamed(const std::wstring& ws) {
	return (std::find_if(ws.begin(),ws.end(),is_illegal)!=ws.end());
}

std::string wstring_to_ascii(const std::wstring& ws) {
	std::string s;  s.reserve(ws.size());
	for (const auto& wc : ws) {
		if ((static_cast<int>(wc)<0) || (static_cast<int>(wc)>127)) {
			s += 'w';
			s += std::to_string(static_cast<int>(wc));
		}
		s.push_back(static_cast<char>(wc));
	}
	return s;
}

std::string to_valid_filename(const std::wstring& ws) {
	std::string s;  s.reserve(ws.size());
	for (const auto& wc : ws) {
		if (is_illegal(wc)) {
			s.push_back('_');
		} else {
			s.push_back(static_cast<char>(wc));
		}
	}
	return s;
}

