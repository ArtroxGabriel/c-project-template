# C Project Template

A comprehensive C project template with modern development practices, testing infrastructure, and automated code quality tools.

## Features

- **Clean Project Structure**: Organized directories for headers (`include/`), source files (`src/`), and tests (`test/`)
- **CMake Build System**: Modern CMake configuration with automatic dependency management
- **Unit Testing**: Integrated Check testing framework with automatic download if not available
- **Code Formatting**: clang-format integration for consistent code style
- **Static Analysis**: cppcheck integration for code quality checks
- **Cross-platform**: Works on Linux, macOS, and Windows
- **Git Integration**: Comprehensive .gitignore for C projects

## Project Structure

```
c-project-template/
├── CMakeLists.txt          # Main CMake configuration
├── .clang-format           # Code formatting configuration
├── .gitignore              # Git ignore rules
├── README.md               # This file
├── include/                # Header files
│   └── example.h           # Example header
├── src/                    # Source files
│   ├── example.c           # Example implementation
│   └── main.c              # Main executable
└── test/                   # Test files
    ├── CMakeLists.txt      # Test configuration
    └── test_example.c      # Example tests
```

## Prerequisites

- CMake 3.15 or higher
- C99 compatible compiler (GCC, Clang, MSVC)
- Git

### Optional Tools

- **clang-format**: For code formatting (auto-installed on most systems)
- **cppcheck**: For static analysis (`sudo apt-get install cppcheck` on Ubuntu)
- **Check testing framework**: Automatically downloaded if not found

## Getting Started

### 1. Clone or Use as Template

```bash
# Clone this repository
git clone https://github.com/ArtroxGabriel/c-project-template.git my-project
cd my-project

# Or use GitHub's "Use this template" button
```

### 2. Build the Project

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make
```

### 3. Run the Application

```bash
./c_project_template
```

### 4. Run Tests

```bash
# Run all tests
make test

# Or run test executable directly
./test/test_example
```

## Development Workflow

### Building and Testing

```bash
# Full build and test cycle
mkdir build && cd build
cmake ..
make
make test
```

### Code Quality

```bash
# Check code formatting
make format-check

# Auto-format code
make format

# Run static analysis
make lint
```

### Adding New Files

1. **Add header files** to `include/` directory
2. **Add source files** to `src/` directory  
3. **Add test files** to `test/` directory
4. **Update CMakeLists.txt** if needed (automatic for most cases)

### Example: Adding a New Module

1. Create `include/math_utils.h`:
```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int factorial(int n);

#endif /* MATH_UTILS_H */
```

2. Create `src/math_utils.c`:
```c
#include "math_utils.h"

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

3. Create `test/test_math_utils.c`:
```c
#include <check.h>
#include "math_utils.h"

START_TEST(test_factorial) {
    ck_assert_int_eq(factorial(0), 1);
    ck_assert_int_eq(factorial(5), 120);
}
END_TEST

// Add suite and main function...
```

## CMake Targets

- **`make`** or **`make all`**: Build the project
- **`make test`**: Run all tests  
- **`make format`**: Format code with clang-format
- **`make format-check`**: Check if code is properly formatted
- **`make lint`**: Run cppcheck static analysis
- **`make clean`**: Clean build artifacts
- **`make install`**: Install the project

## Configuration

### CMake Options

```bash
# Debug build (default)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build
cmake -DCMAKE_BUILD_TYPE=Release ..

# Custom install prefix
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
```

### Code Style

The project uses clang-format with LLVM style. Customize `.clang-format` to match your preferences.

### Testing Framework

Tests use the Check framework, which provides:
- Unit testing macros (`ck_assert_*`)
- Test fixtures and suites
- Multiple output formats
- Memory leak detection

## Customization

### Project Name

Update the project name in `CMakeLists.txt`:
```cmake
project(your_project_name VERSION 1.0.0 LANGUAGES C)
```

### C Standard

Change the C standard in `CMakeLists.txt`:
```cmake
set(CMAKE_C_STANDARD 11)  # C11 instead of C99
```

### Dependencies

Add external dependencies using CMake's `find_package()` or `FetchContent`:
```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
target_link_libraries(${PROJECT_NAME}_lib ${GLIB_LIBRARIES})
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes with tests
4. Ensure code passes formatting and linting
5. Submit a pull request

## License

This template is provided under the MIT License. See LICENSE file for details.

## Features Included

- ✅ Modern CMake configuration (3.15+)
- ✅ Automatic dependency management
- ✅ Unit testing with Check framework
- ✅ Code formatting with clang-format
- ✅ Static analysis with cppcheck
- ✅ Comprehensive .gitignore
- ✅ Cross-platform support
- ✅ Example code and tests
- ✅ Installation and packaging support