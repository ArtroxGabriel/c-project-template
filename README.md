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

## Using This Template

When using this template for your own project, you'll need to customize several fields and replace the example code. Here's a comprehensive list of what needs to be changed:

### Required Changes

#### 1. Project Configuration (`CMakeLists.txt`)

Update the project metadata at the top of the file:

```cmake
# Change these values:
project(your-project-name VERSION 1.0.0 LANGUAGES C)
```

- **`your-project-name`**: Replace with your actual project name (use lowercase with hyphens)
- **`VERSION 1.0.0`**: Set your initial version number

#### 2. Documentation (`README.md`)

Replace the template-specific content:

- **Project title**: Change `# C Project Template` to `# Your Project Name`
- **Project description**: Replace the template description with your project's purpose
- **Project structure**: Update the directory tree to reflect your actual files
- **Features section**: Describe your project's features instead of template features
- **Requirements**: Update with your project's specific dependencies
- **Building instructions**: Adapt if you have special build requirements
- **License section**: Update with your project's license information

#### 3. Source Code (`src/` directory)

Replace all example code with your actual implementation:

- **`src/main.c`**: Replace the example main function with your application's entry point
- **`src/example.c`**: Replace with your actual source files (rename as needed)
- Remove or replace example functions (`add`, `multiply`, `is_even`)

#### 4. Header Files (`include/` directory)

Replace example headers with your actual interfaces:

- **`include/example.h`**: Replace with your actual header files (rename as needed)
- Update function declarations to match your implementation
- Update comments and documentation

#### 5. Test Files (`test/` directory)

Replace example tests with tests for your actual code:

- **`test/test_example.c`**: Replace with tests for your actual functions
- Update test function names and test cases
- Update suite names to reflect your project
- Add new test files as needed for different modules

#### 6. Repository Metadata

Update version control and project files:

- **`.gitignore`**: Add any project-specific ignore patterns
- **Repository name**: If using GitHub, rename your repository
- **Repository description**: Update the repository description on GitHub

### Optional Changes

#### 1. Code Style (`.clang-format`)

The template uses LLVM style by default. Modify if you prefer different formatting:

```yaml
# Customize these values:
IndentWidth: 4        # Your preferred indent width
TabWidth: 4           # Your preferred tab width
ColumnLimit: 100      # Your preferred line length
# ... other style options
```

#### 2. Compiler Flags (`CMakeLists.txt`)

Adjust compiler flags based on your requirements:

```cmake
# Customize these flags:
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Werror -pedantic")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
```

#### 3. C Standard (`CMakeLists.txt`)

Change the C standard if needed:

```cmake
# Change if you need a different C standard:
set(CMAKE_C_STANDARD 99)  # Options: 90, 99, 11, 17, 23
```

### Verification Checklist

After customization, verify your changes:

- [ ] Project builds successfully: `cmake -S . -B build && cmake --build build`
- [ ] Tests pass: `cmake --build build --target test`
- [ ] Code formatting works: `cmake --build build --target format-check`
- [ ] Your executable runs correctly: `./build/your-project-name`
- [ ] README.md accurately describes your project
- [ ] All example code has been replaced with your implementation

## License

This template is provided as-is for you to use in your own projects. Modify as needed for your specific requirements.

## Contributing

This is a template repository. If you have improvements to suggest for the template itself, please contribute to the original repository.