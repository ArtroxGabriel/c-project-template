# C Project Template

A comprehensive C project template with CMake build system, automated testing, code formatting, and memory checking capabilities.

## Project Structure

```
c-project-template/
├── CMakeLists.txt          # Main CMake configuration
├── .gitignore              # Git ignore rules for C projects
├── README.md               # This file
├── include/                # Header files
│   └── example.h           # Example header file
├── src/                    # Source files
│   ├── main.c             # Main application entry point
│   └── example.c          # Example implementation
└── test/                   # Test files
    ├── CMakeLists.txt     # Test-specific CMake configuration
    └── test_example.c     # Example unit tests
```

## Features

- **Modern CMake**: Uses CMake 3.10+ with proper target management
- **Code Quality**: Integrated clang-format for consistent code style
- **Unit Testing**: Uses the Check library for comprehensive unit testing
- **Memory Testing**: Valgrind integration for memory leak detection
- **Automatic Dependencies**: Downloads and builds dependencies if not found
- **Cross-Platform**: Works on Linux, macOS, and Windows

## Requirements

### Required
- CMake 3.10 or higher
- C compiler (GCC, Clang, or MSVC)

### Optional (for enhanced features)
- `clang-format` - for code formatting
- `valgrind` - for memory leak detection
- `pkg-config` - for better dependency detection

## Building the Project

### Quick Start

```bash
# Clone or create your project from this template
# Configure with CMake (generate build directory)
cmake -S . -B build

# Build the project
cmake --build build
```

### Available CMake Targets

| Target | Description |
|--------|-------------|
| `build` | Build the main executable (default) |
| `format` | Format all source code with clang-format (LLVM style) |
| `format-check` | Check if code is properly formatted |
| `test` | Run all unit tests (built-in CTest target) |
| `test-run` | Run all unit tests |
| `test-memory` | Run tests with memory checking (requires valgrind) |
| `lint` | Run clang-tidy linter on source code |

### Building and Running

```bash
# Generate build directory
cmake -S . -B build

# Build the project
cmake --build build

# Run the executable
./build/c-project-template
```

### Running Tests

```bash
# Run unit tests (using built-in test target)
cmake --build build --target test

# Or run custom test-run target
cmake --build build --target test-run

# Or use CTest directly
cd build && ctest --output-on-failure

# Run tests with memory checking (requires valgrind)
cmake --build build --target test-memory
```

### Code Formatting

```bash
# Format all source code (using LLVM style)
cmake --build build --target format

# Check if code is properly formatted
cmake --build build --target format-check

# Run linter on source code
cmake --build build --target lint
```

## Development Workflow

1. **Add new features**:
   - Add header files to `include/`
   - Add implementation files to `src/`
   - Add corresponding tests to `test/`

2. **Test your changes**:
   ```bash
   cmake --build build             # Build the project
   cmake --build build --target test      # Run tests
   cmake --build build --target format-check  # Check formatting
   cmake --build build --target lint      # Run linter
   ```

3. **Format your code**:
   ```bash
   cmake --build build --target format    # Auto-format code
   ```

4. **Memory testing** (if valgrind is available):
   ```bash
   cmake --build build --target test-memory   # Check for memory leaks
   ```

## Adding New Tests

1. Create a new test file in the `test/` directory (e.g., `test_newfeature.c`)
2. Follow the Check library test structure:

```c
#include <check.h>
#include <stdlib.h>
#include "your_header.h"

START_TEST(test_your_function) {
    // Your test implementation
    ck_assert_int_eq(your_function(input), expected_output);
}
END_TEST

Suite *your_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("YourFeature");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_your_function);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = your_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
```

3. Rebuild the project - CMake will automatically detect and build the new test

## Customization

### Compiler Flags

Edit `CMakeLists.txt` to modify compiler flags:

```cmake
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Werror -pedantic")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
```

### Code Formatting Style

The project uses an LLVM-based clang-format style. Modify `.clang-format` to customize:

```yaml
---
Language: Cpp
BasedOnStyle: LLVM
IndentWidth: 4
TabWidth: 4
# ... other options
```

### Adding Dependencies

To add new dependencies, modify the main `CMakeLists.txt`:

```cmake
# Example: Adding a new library
find_package(YourLibrary REQUIRED)
target_link_libraries(${PROJECT_NAME} YourLibrary::YourLibrary)
```

## License

This template is provided as-is for you to use in your own projects. Modify as needed for your specific requirements.

## Contributing

This is a template repository. If you have improvements to suggest for the template itself, please contribute to the original repository.