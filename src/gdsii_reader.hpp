#ifndef GDSII_READER_HPP
#define GDSII_READER_HPP

#include <string>

class GDSIIReader {
    public:
        GDSIIReader();
        ~GDSIIReader();
        bool exec(std::string file_path);
    private:
        void read(std::string file_path);
};

#endif