# AGENTS.md

This file provides guidance to agents when working with code in this repository.

## Build, Lint, Test, and Run Commands

### Build Commands
1. **Using CMake directly**:
   - Configure: 
     ```bash
     cmake -S <path to cml-root> -G{generator name} -DBUILD_TESTING=On -DCMAKE_BUILD_TYPE=Release
     ```
   - Build:
     ```bash
     cmake --build . --config Release
     ```
   - Parallel Build (e.g., 4 threads):
     ```bash
     cmake --build . --config Release -- -j4
     ```

2. **Using CMake Presets**:
   - List available presets:
     ```bash
     cmake --list-presets=all
     ```
   - Example preset-based build:
     ```bash
     cmake --preset=windows-ninja-clangcl-mt-s-vcpkg
     cmake --build --preset=windows-ninja-clangcl-mt-s-vcpkg-release
     ```

### Test Commands
1. **Run all tests**:
   ```bash
   ctest -C Release
   ```
2. **Parallel Test Execution**:
   ```bash
   ctest -C Release -j4
   ```

### Lint Commands
No explicit linting commands were found in the analyzed files.

### Run Commands
The project appears to be a library (header-only), so there are no explicit "run" commands for an application. However, the tests and timing executables can be run as described above.

## Code Style Guidelines
1. **Formatting**:
   - **Column Limit**: 80 characters.
   - **Indentation**: 2 spaces, no tabs.
   - **Line Endings**: LF (Unix-style).
   - **Insert Newline at EOF**: Enabled.

2. **Braces**:
   - **After Class/Struct/Enum/Function**: Always place braces on a new line.
   - **Control Statements**: No braces for single-line statements.

3. **Alignment**:
   - **Trailing Comments**: Aligned.
   - **Operands**: No alignment.
   - **Pointer Alignment**: Left-aligned (`int* ptr`).

4. **Spaces**:
   - **Before Parentheses**: None (e.g., `if(condition)`).
   - **Around Operators**: Space before assignment operators.
   - **In Empty Blocks/Parentheses**: None.

5. **Includes**:
   - **Sorting**: Disabled.
   - **Blocks**: Preserve original order.

6. **Miscellaneous**:
   - **Short Functions**: Inline only.
   - **Short If Statements**: Allowed on a single line.
   - **Namespace Indentation**: None.
   - **Header Include Guards**: Use `#pragma once` only, never `#ifdef/#endif` guards.

7. **New Files**:
   - **File Naming**: Use descriptive names that reflect the content of the file.
   - **File Extension for C++**: `.cpp`, `.h`, `.inl`, `.tpp`, `.hpp`.
   - **File header**: Use the default file header for all new files.

8. **Comments**:
   - **C++ Comment Style**: Use C comment delimiters for C++ files.
   - **Short Comments**: Allowed on a single line if they are short.
   - **Long Comments**: Aligned at the beginning of the block.


### Standard File Headers by Language
1. C++:
   ```cpp
   /*-------------------------------------------------------------------------
    @@COPYRIGHT@@
    *-----------------------------------------------------------------------*/
   ```

2. Python
   ```python
   #*-------------------------------------------------------------------------
   # @@COPYRIGHT@@
   #*-------------------------------------------------------------------------
   ```

## Core Architecture and Components
1. **Vectors (`cml/vector/`)**:
   - Provides various vector types (e.g., fixed, dynamic, external).
   - Includes operations like dot product, cross product, and normalization.
   - Supports expression templates for efficient computation.

2. **Matrices (`cml/matrix/`)**:
   - Implements matrix types and operations (e.g., inversion, transformation).
   - Includes support for fixed and dynamic sizes.
   - Provides utilities for matrix concatenation and basis generation.

3. **Quaternions (`cml/quaternion/`)**:
   - Encapsulates quaternion operations for rotations and transformations.
   - Includes scalar and vector operations on quaternions.
   - Provides utilities for normalization, inversion, and logarithmic operations.

4. **Storage (`cml/storage/`)**:
   - Defines storage strategies for vectors, matrices, and quaternions.
   - Includes dynamic, fixed, and external storage types.
   - Provides utilities for resizing and reshaping storage.

5. **Utilities (`cml/util/`)**:
   - Contains helper functions for printing and hashing.
   - Includes mathematical utilities for field-of-view conversions and more.

6. **Testing (`tests/`)**:
   - Organized into subdirectories for each core component (e.g., `vector`, `matrix`, `quaternion`).
   - Uses Catch2 for unit testing.
   - Includes timing tests for performance evaluation.

## Testing Setup
1. **Framework**:
   - The project uses **Catch2** for unit testing.
   - The main entry point for tests is defined in [`tests/main/catch_main.cpp`](tests/main/catch_main.cpp:11), which initializes the Catch2 session.

2. **Test Organization**:
   - Tests are organized into subdirectories under `tests/`, corresponding to the core components.

3. **Test Execution**:
   - Build the tests:
     ```bash
     cmake --build . --config Release
     ```
   - Run the tests:
     ```bash
     ctest -C Release
     ```

4. **Timing Tests**:
   - Timing tests are conditionally included if `BUILD_TIMING` is enabled in the CMake configuration.
   - These tests are located in the `tests/timing/` directory.