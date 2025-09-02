# C++ style guide for Daedalus firmware

## Formatting
- Use clang-format with the provided .clang-format file
- Run before committing: `clang-format -i firmware/src/*.cpp firmware/src/*.h`

## Naming
- Classes: PascalCase (e.g., `LedController`)
- Functions: camelCase (e.g., `initializeHardware()`)
- Variables: camelCase (e.g., `ledPin`)
- Constants: UPPER_SNAKE_CASE (e.g., `MAX_BUFFER_SIZE`)
- Macros: UPPER_SNAKE_CASE (e.g., `DEBUG_ENABLE`)
- Files: snake_case (e.g., `led_controller.cpp`)

## Headers
- Use `#pragma once` for header guards
- Order includes: standard library, Pico SDK, project headers

## Comments
- Use Doxygen-style comments for functions and classes
- Comment complex algorithms and non-obvious code

## Error handling
- Use return codes for error reporting
- Check return values from SDK functions
- Use assertions for invariants

## Memory management
- Avoid dynamic memory allocation when possible
- If needed, use RAII principles with smart pointers