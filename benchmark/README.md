# GDSII Benchmarks

In this directory, the GDSII benchmarks in _.gds_ format are used for the GDSII-Parser testing. Also, the text format (_.txt_) of the benchmarks are also provided to ease the developer understanding.

## List of Benchmarks
The following are the list of the benchmarks with a brief description:
1. **empty**: contains only a single cell named **EMPTY** without any element/shape
2. **box**: contains a single cell with a single box
3. **box_path_text**: contains a single cell with a single box, path and text
4. **polygon**: contains a single cell with multiple polygon shapes
5. **two_cell**: contains two cells: (1) box array, (2) polygon shape, both are not related to each another
6. **top_cell**: contains two cells: (1) box array, (2) top cell, top cell instantiate two box array cell inside