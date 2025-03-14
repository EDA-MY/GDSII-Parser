#ifndef GDSII_READER_HPP
#define GDSII_READER_HPP

#include <map>
#include <vector>
#include <string>
#include "gdsii_common.hpp"

class GDSIIReader {
    public:
        GDSIIReader();
        ~GDSIIReader();
        bool exec(std::string file_path);
    private:
        void process_data();
        bool read(std::string file_path);

        std::map<uint16_t, std::vector<std::vector<uint8_t>>> byte_data_map;
};

#endif