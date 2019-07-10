#include "rename2ascii.h"
#include <iostream>
#include <filesystem>
#include <string>


int main(int argc, char **argv) {
	std::cout << "rename2ascii:\n"
		"Rename all midi files in this and all subdirectories such that only\n"
		"ASCII characters >=32 and < 127 appear in the new filenames.  Also\n"
		"replace characters that are invalid in Windows filenames ('/','\\',':',\n"
		"'?','<','>').  Replace illegal chars with '_'.  Does not change\n"
		"directory names.  \n\n";

	std::string pathstr;
	if (argc <= 1) {
		std::cout << "You must supply a path.  \n";
		return 0;
	} else {
		pathstr.append(argv[1]);
	}
	if (pathstr.back() != '\\' && pathstr.back() != '/') {
		pathstr.push_back('\\');
	}
	std::cout << "Renaming files in \n" << pathstr << "\n\n";

	auto base_path = std::filesystem::path(pathstr);
	auto rdi = std::filesystem::recursive_directory_iterator(base_path.parent_path());
	int n_files = 0;  int n_renamed = 0;
	for (const auto& dir_ent : rdi) {
		if (!std::filesystem::is_regular_file(dir_ent)) {
			continue;  // Only rename files; not directories, block devices, etc
		}
		auto curr_path = dir_ent.path();
		auto ext = wstring_to_ascii(curr_path.extension().native());
		++n_files;
		if ((ext!=".mid") && (ext!=".midi")) {
			continue;
		}

		auto init_fname_native = curr_path.filename().native();
		if (!needs_renamed(init_fname_native)) {
			continue;
		}
		std::string new_fname = to_valid_filename(init_fname_native);
		std::string curr_path_ascii = wstring_to_ascii(curr_path.native());
		
		auto new_path = curr_path.parent_path() / new_fname;
		std::filesystem::rename(curr_path,new_path);
		++n_renamed;
		std::cout << n_renamed << '\n' 
			<< curr_path_ascii << '\n' 
			<< new_fname << '\n' << '\n';
	}

	std::cout << "Renamed " << n_renamed << " out of " 
		<< n_files << " files total\n\n";

	return 0;
}

