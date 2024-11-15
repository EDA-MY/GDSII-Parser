#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "gdsii_reader.hpp"

using namespace std;

GDSIIReader::GDSIIReader() {
    // Constructor
}

GDSIIReader::~GDSIIReader() {
    // Destructor
}

bool GDSIIReader::exec(string file_path) {
    // Execute the GDSII reader
    read(file_path);
    return true;
}

void GDSIIReader::read(string file_path) {
    vector<vector<uint8_t>> chunk_data_vec {};

    // Print the file path
    cout << "Reading file: " << file_path << endl;

    // Open the file
    ifstream fin(file_path, ios::binary);
    if (!fin.is_open()) {
        cout << "Error: Unable to open file" << endl;
        return;
    }

    // Export the result into a text file
    ofstream fout("output.txt");
    if (!fout.is_open()) {
        cout << "Error: Unable to open output file" << endl;
        return;
    }

    // Buffer for reading data
    char byte_buffer;

    // Read the first 2 bytes to determine the number of bytes to read
    while(fin.get(byte_buffer)) {
        // Read the first byte
        uint8_t first_byte = static_cast<uint8_t>(byte_buffer);

        // Read the second byte
        fin.get(byte_buffer);
        uint8_t second_byte = static_cast<uint8_t>(byte_buffer);

        // Calculate the number of bytes to read
        uint16_t num_bytes = ((first_byte << 8) | second_byte) - 2;
        fout << "Number of bytes to read: " << dec << num_bytes << endl;

        // Read the data
        vector<uint8_t> chunk_data(num_bytes);
        for (auto& byte_data : chunk_data) {
            fin.get(byte_buffer);
            byte_data = static_cast<uint8_t>(byte_buffer);
        }

        // Print the chunk data
        fout << "Chunk data: ";
        for (const auto& byte_data : chunk_data) {
            fout << "0x" << setw(2) << setfill('0') << hex << +byte_data << " ";
        }
        fout << endl;

        // Add the chunk data to the vector
        chunk_data_vec.push_back(chunk_data);
    }

    // Close the input file
    fin.close();
    // Close the output file
    fout.close();
}
