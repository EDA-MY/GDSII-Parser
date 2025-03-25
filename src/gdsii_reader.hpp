#ifndef GDSII_READER_HPP
#define GDSII_READER_HPP

#include <map>
#include <string>
#include "gdsii_common.hpp"

struct GDSIIRecord {
    const uint16_t record_type {0};
    const vec_vec_uint8_t* byte_data {nullptr};
    int decode_int_data {};
    std::string decode_str_data {};
    vec_vec_str_t decode_vec_vec_str_data {};
    vec_vec_int_t decode_vec_vec_int_data {};

    GDSIIRecord() = default;
    GDSIIRecord(uint16_t record_t, vec_vec_uint8_t* byte_dat) : record_type(record_t), byte_data(byte_dat) {}
};

class GDSIIReader {
    public:
        GDSIIReader();
        ~GDSIIReader();
        bool exec(std::string& file_path);
    private:
        void process_data();
        bool read(std::string& file_path);
        void plain_read(std::string& file_path);
        bool process_gdsii_header(GDSIIRecord& record_data);
        bool process_gdsii_bgn_lib(GDSIIRecord& record_data);

        // [record_type] =[[byte_data], [byte_data], ...]
        std::map<uint16_t, vec_vec_uint8_t> m_byte_data_map;

        // [record_type] = [[decoded_data], [decoded_data], ...]
        std::map<uint16_t, vec_vec_str_t> m_decoded_data_map;
};

#endif