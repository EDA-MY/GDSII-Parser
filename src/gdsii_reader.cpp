#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "gdsii_reader.hpp"
#include "gdsii_common.hpp"

#define DEBUG_MODE_ALWAYS   1
#define DEBUG_MODE_AVRG     0
#define DEBUG_MODE_INTENSE  0

using namespace std;

GDSIIReader::GDSIIReader() {
    // Constructor
}

GDSIIReader::~GDSIIReader() {
    // Destructor
}

bool GDSIIReader::exec(string& file_path) {
    bool status = true;

    // plain_read(file_path);
    // Execute the GDSII reader
    status = read(file_path);
    // Process the GDSII data
    process_data();

    return status;
}

bool GDSIIReader::read(string& file_path) {
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

            for (size_t idx = 0; idx < num_bytes; ++idx) {
                fin.get(byte_buffer);

                if (header_cnt > 0) {
                    record_type = (record_type << 8) | static_cast<uint8_t>(byte_buffer);

                    --header_cnt;
                } else {
                    if (record_type == static_cast<uint8_t>(GDSIIRecordType::GDSIIEndRecordType)) break;

                    byte_data.push_back(static_cast<uint8_t>(byte_buffer));
                }
            }

            if (record_type == static_cast<uint8_t>(GDSIIRecordType::GDSIIEndRecordType)) {
                m_byte_data_map[record_type] = {};
                break;
            }

            if (! byte_data.empty()) m_byte_data_map[record_type].push_back(byte_data);
        }
    }

    // Close the input file
    fin.close();

#if DEBUG_MODE_INTENSE
    // Print the byte data map
    cout << "Byte data map:" << endl;
    for (const auto& [record_header, multi_byte_data_list] : m_byte_data_map) {
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

void GDSIIReader::plain_read(string& file_path) {
    bool status {true};
    char byte_buffer {'\0'};

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
            cout << "0x" << setw(2) << setfill('0') << hex
                 << static_cast<unsigned int>(static_cast<unsigned char>(byte_buffer)) << " ";
        }
    }

    // Close the input file
    fin.close();
}

void GDSIIReader::process_data() {
    uint16_t record_type {0};

    // Process the GDSII data
    cout << "Processing GDSII data\n" << endl;
    record_type = static_cast<uint64_t>(GDSIIRecordType::GDSIIHeaderRecord);
    GDSIIRecord record(record_type, &m_byte_data_map[record_type]);
    process_gdsii_header(record);

    // clear the record and replace with another type
    record_type = static_cast<uint64_t>(GDSIIRecordType::GDSIIBgnLib);
    record.~GDSIIRecord();
    new (&record) GDSIIRecord(record_type, &m_byte_data_map[record_type]);
    process_gdsii_bgn_lib(record);
}

bool GDSIIReader::process_gdsii_header(GDSIIRecord& record_data) {
    bool status {true};
    int16_t version_num {0};

    const vec_vec_uint8_t* byte_data = record_data.byte_data;
    assert(byte_data->size() == 1);
    assert(byte_data->front().size() == 2);

    // Comnvert 2 byte data into a signed integer
    version_num = (byte_data->front().at(0) << 8) | byte_data->front().at(1);
    record_data.decode_int_data = version_num;

#if DEBUG_MODE_ALWAYS
    uint64_t record_header = record_data.record_type;

    // Print the record data
    cout << recordEnumToStringMap[record_header] << " " << record_data.decode_int_data << endl;
#endif

    return status;
}

bool GDSIIReader::process_gdsii_bgn_lib(GDSIIRecord& record_data) {
    bool status {true};
    int16_t chunk_dat {0};
    vector<int> lib_data {};

    const vec_vec_uint8_t* byte_data = record_data.byte_data;
    assert(byte_data->size() == 1);

    for (size_t idx = 0; idx < byte_data->front().size() ; idx += 2) {
        chunk_dat = (byte_data->front().at(idx) << 8) | byte_data->front().at(idx + 1);
        lib_data.push_back(chunk_dat);
    }

    record_data.decode_vec_vec_int_data.push_back(lib_data);

#if DEBUG_MODE_ALWAYS
    stringstream ss;
    uint64_t record_header = record_data.record_type;
    vector<int>& lib_dat = record_data.decode_vec_vec_int_data.at(0);

    // Print the lib data
    cout << recordEnumToStringMap[record_header] << " ";
    for (size_t idx = 0; idx < lib_dat.size(); idx += 6) {
        ss.str("");
        ss << lib_dat.at(idx) << "/"
           << lib_dat.at(idx + 1) << "/"
           << lib_dat.at(idx + 2) << " "
           << lib_dat.at(idx + 3) << ":"
           << lib_dat.at(idx + 4) << ":"
           << lib_dat.at(idx + 5) << " ";
        cout << ss.str();
    }
    cout << endl;
#endif

    return status;
}