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

| Target         | Description                                           |
| -------------- | ----------------------------------------------------- |
| `build`        | Build the main executable (default)                   |
| `format`       | Format all source code with clang-format (LLVM style) |
| `format-check` | Check if code is properly formatted                   |
| `test`         | Run all unit tests (built-in CTest target)            |
| `test-run`     | Run all unit tests                                    |
| `test-memory`  | Run tests with memory checking (requires valgrind)    |
| `lint`         | Run clang-tidy linter on source code                  |

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

## Using This Template

This section provides specific, actionable steps to customize this template for your own C project.

### Essential Field Changes

#### 1. Change the Binary Name (`CMakeLists.txt`)

**What to change**: Line 2 in `CMakeLists.txt`

```cmake
# FROM:
project(c-project-template VERSION 1.0.0 LANGUAGES C)

# TO:
project(my-calculator VERSION 1.0.0 LANGUAGES C)
```

**Result**: Your executable will be named `my-calculator` instead of `c-project-template`

#### 2. Change Project Version (`CMakeLists.txt`)

**What to change**: Same line as above

```cmake
# FROM:
project(my-calculator VERSION 1.0.0 LANGUAGES C)

# TO:
project(my-calculator VERSION 0.1.0 LANGUAGES C)
```

**Result**: Sets your initial version number

#### 3. Change Project Title (`README.md`)

**What to change**: Line 1 in `README.md`

```markdown
# FROM:

# C Project Template

# TO:

# My Calculator
```

**Result**: Updates the main project title in documentation

#### 4. Change Project Description (`README.md`)

**What to change**: Line 3 in `README.md`

```markdown
# FROM:

A comprehensive C project template with CMake build system, automated testing, code formatting, and memory checking capabilities.

# TO:

A simple command-line calculator written in C with basic arithmetic operations.
```

**Result**: Describes your actual project instead of the template

### Adding New Source Files

#### Adding a New C Source File

1. **Create the header file** in `include/` directory:

```bash
# Create include/math_operations.h
```

2. **Add function declarations**:

```c
// include/math_operations.h
#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H

double divide(double a, double b);
double power(double base, double exponent);

#endif /* MATH_OPERATIONS_H */
```

3. **Create the implementation file** in `src/` directory:

```bash
# Create src/math_operations.c
```

4. **Add function implementations**:

```c
// src/math_operations.c
#include "math_operations.h"
#include <math.h>

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    }
    return 0; // or handle error appropriately
}

double power(double base, double exponent) {
    return pow(base, exponent);
}
```

**Result**: CMake automatically detects and builds the new file

#### Adding a New Test File

1. **Create the test file** in `test/` directory:

```bash
# Create test/test_math_operations.c
```

2. **Add test implementation**:

```c
// test/test_math_operations.c
#include <check.h>
#include <stdlib.h>
#include "math_operations.h"

START_TEST(test_divide) {
    ck_assert_double_eq_tol(divide(10.0, 2.0), 5.0, 0.001);
    ck_assert_double_eq(divide(7.0, 0.0), 0.0); // Error case
}
END_TEST

START_TEST(test_power) {
    ck_assert_double_eq_tol(power(2.0, 3.0), 8.0, 0.001);
    ck_assert_double_eq_tol(power(5.0, 0.0), 1.0, 0.001);
}
END_TEST

Suite *math_operations_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("MathOperations");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_divide);
    tcase_add_test(tc_core, test_power);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = math_operations_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
```

**Result**: CMake automatically detects and builds the new test

### Replacing Example Code

#### Remove Example Files

1. **Delete example source file**:

```bash
rm src/example.c
```

2. **Delete example header file**:

```bash
rm include/example.h
```

3. **Delete example test file**:

```bash
rm test/test_example.c
```

4. **Update main.c** to use your new functions:

```c
// src/main.c
#include <stdio.h>
#include "math_operations.h"

int main() {
    printf("My Calculator\n");
    printf("=============\n");
    printf("10 / 2 = %.2f\n", divide(10.0, 2.0));
    printf("2^3 = %.2f\n", power(2.0, 3.0));
    return 0;
}
```

**Result**: Your project now has your own code instead of examples

### Quick Start Guide

Follow these steps to transform this template into your own project:

1. **Clone and rename**:

```bash
git clone https://github.com/ArtroxGabriel/c-project-template.git my-project
cd my-project
```

2. **Change project name** (edit `CMakeLists.txt` line 2):

```cmake
project(my-project VERSION 1.0.0 LANGUAGES C)
```

3. **Build and test**:

```bash
cmake -S . -B build
cmake --build build
./build/my-project  # Should run your renamed executable
```

4. **Replace example code** with your implementation:
   - Edit `src/main.c` for your main function
   - Replace `src/example.c` and `include/example.h` with your files
   - Replace `test/test_example.c` with your tests

5. **Update documentation**:
   - Change the title in `README.md`
   - Update project description
   - Update project structure diagram

6. **Verify everything works**:

```bash
cmake --build build --target test      # Run tests
cmake --build build --target format    # Format code
```

### Advanced Customization

#### 1. Change Code Style (`.clang-format`)

**What to change**: Edit the `.clang-format` file

```yaml
# FROM:
IndentWidth: 4
ColumnLimit: 100

# TO:
IndentWidth: 2        # Use 2-space indentation
ColumnLimit: 80       # Shorter line length
```

**Result**: Code formatting matches your preferred style

#### 2. Change Compiler Flags (`CMakeLists.txt`)

**What to change**: Lines 34-35 in `CMakeLists.txt`

```cmake
# FROM:
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Werror -pedantic")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

# TO:
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra")  # Less strict
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")        # Less aggressive optimization
```

**Result**: Compilation uses your preferred warning levels and optimization

#### 3. Change C Standard (`CMakeLists.txt`)

**What to change**: Line 5 in `CMakeLists.txt`

```cmake
# FROM:
set(CMAKE_C_STANDARD 99)

# TO:
set(CMAKE_C_STANDARD 11)  # Use C11 standard
```

**Result**: Enables C11 features in your code

### Verification Commands

After making changes, verify everything works:

```bash
# Build the project
cmake -S . -B build && cmake --build build

# Run tests
cmake --build build --target test

# Check code formatting
cmake --build build --target format-check

# Run your executable
./build/your-project-name

# Check for memory leaks (if valgrind is available)
cmake --build build --target test-memory
```

## License

This template is provided as-is for you to use in your own projects. Modify as needed for your specific requirements.

## Contributing

This is a template repository. If you have improvements to suggest for the template itself, please contribute to the original repository.
