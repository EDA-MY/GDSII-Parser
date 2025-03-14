#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "gdsii_reader.hpp"
#include "gdsii_common.hpp"

#define DEBUG_MODE 1

using namespace std;

GDSIIReader::GDSIIReader() {
    // Constructor
}

GDSIIReader::~GDSIIReader() {
    // Destructor
}

bool GDSIIReader::exec(string file_path) {
    bool status = true;

    // Execute the GDSII reader
    status = read(file_path);
    // Process the GDSII data
    process_data();

    return status;
}

bool GDSIIReader::read(string file_path) {
    bool status                 {true};
    char byte_buffer            {'\0'};
    uint8_t header_cnt          {2};
    uint8_t first_byte          {0};
    uint8_t second_byte         {0};
    uint16_t record_type        {0};
    uint16_t num_bytes          {0};
    vector<uint8_t> byte_data   {};

    // Print the file path
    cout << "Reading file: " << file_path << endl;

    // Open the file
    ifstream fin(file_path, ios::binary);
    if (!fin.is_open()) {
        cout << "Error: Unable to open file" << endl;
        status = !status;
    }

    if (status) {
        // Read the first 2 bytes to determine the number of bytes to read
        while(fin.get(byte_buffer)) {
            // Reset
            header_cnt = 2;
            record_type = 0;
            byte_data.clear();

            // Get the number of bytes to read
            first_byte = static_cast<uint8_t>(byte_buffer);
            fin.get(byte_buffer);
            second_byte = static_cast<uint8_t>(byte_buffer);
            num_bytes = (static_cast<uint16_t>(first_byte) << 8 | second_byte) - 2;

            for (size_t i = 0; i < num_bytes; ++i) {
                fin.get(byte_buffer);

                if (header_cnt > 0) {
                    record_type = (record_type << 8) | static_cast<uint8_t>(byte_buffer);

                    --header_cnt;
                } else {
                    byte_data.push_back(static_cast<uint8_t>(byte_buffer));
                }
            }

            if (! byte_data.empty()) byte_data_map[record_type].push_back(byte_data);
        }
    }

    // Close the input file
    fin.close();

#if DEBUG_MODE
    // Print the byte data map
    cout << "Byte data map:" << endl;
    for (const auto& [record_header, multi_byte_data_list] : byte_data_map) {
        cout << "Record header: 0x" << setw(4) << setfill('0') <<  hex << record_header
             << " [" << recordEnumToStringMap[record_header] << "]"
             << endl;
        cout << "Number of bytes list: " << dec << multi_byte_data_list.size() << endl;
        cout << "Byte data: \n";
        for (const auto& byte_list : multi_byte_data_list) {
            cout << "\t";
            for (const auto& byte : byte_list) {
                cout << "0x" << setw(2) << setfill('0') << hex << +byte << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
#endif

    return status;
}

void GDSIIReader::process_data() {
    // Process the GDSII data
    cout << "TODO: Processing GDSII data" << endl;
}