#include<iostream>
#include "gdsii_reader.hpp"

using namespace std;

int main(const int argc, const char* argv[]) {
	GDSIIReader reader;

	if (argc < 2) {
		cout << "Error: No file path provided" << endl;
		return 1;
	}

	string file_path = argv[1];
	reader.exec(file_path);

	return 0;
}