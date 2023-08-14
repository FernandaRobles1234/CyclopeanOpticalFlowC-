#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "exportResults.h"


void matrixToTxt(const std::vector<std::vector<double>>& m, std::string txt_name) {
	std::ofstream txt_file;

	// TODO: check if the format of the string is complete: .txt
	txt_file.open(txt_name);

	for (const auto& v : m) {

		txt_file << v[0];
		for (int i = 1; i < v.size(); i++) txt_file << " " << v[i];
		txt_file << "\n";
	}
	txt_file.close();
}
