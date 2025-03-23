# GDSII-Parser

## Environment Setup

### **Install the required libraries**

| Library    | Version          |
|------------|------------------|
| CMake      | >= 3.22.1        |
| G++        | >= 11.4.0        |
| GoogleTest | >= 1.16.0        |
| Boost      | >= 1.74.0        |
| GDB        | >= 12.1          |

You can install these libraries using the following commands:

```sh
# Update package list
sudo apt-get update

# Install CMake
sudo apt-get install -y cmake

# Install GCC
sudo apt-get install -y gcc g++

# Install GoogleTest
sudo apt-get install -y libgtest-dev
cd /usr/src/gtest
sudo cmake .
sudo make
sudo cp *.a /usr/lib

# Install Boost
sudo apt-get install -y libboost-all-dev

# Install GDB
sudo apt-get install -y gdb
```

The GoogleTest library used in this project is version **1.16.0**, which is the current stable release.

### **Build the project**

To build the project, follow these steps:

1. Clone the repository (if not already done):
   ```sh
   git clone <repository-url>
   cd GDSII-Parser
   ```

2. Create a build directory and navigate into it:
   ```sh
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:
   ```sh
   cmake ..
   ```

4. Build the project:
   ```sh
   cmake --build .
   ```

5. Run the tests (optional):
   ```sh
   ctest
   ```

The default CMake build generates an executable in Debug Mode, which may result in performance degradation due to the lack of optimizations. You can modify the compilation arguments to produce an executable that aligns with your performance requirements.

### **Development Machine**

This project was developed on the following machine specification:

- Operating System: Ubuntu 22.04.5 LTS
- Architecture: x86_64