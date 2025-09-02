# CRUSH.md - Daedalus Project Guidelines

## Build Commands
- Setup environment: `direnv allow`
- Build firmware: `cd firmware && make`
- Flash to RP2350: `cd firmware && make flash`
- Disassemble: `cd firmware && make disasm`
- Clean build: `cd firmware && make clean`
- Format code: `clang-format -i firmware/src/*.cpp firmware/src/*.h`
- Lint code: `cppcheck --enable=all firmware/src/`

## Test Commands
- Run all tests: `ctest -S build`
- Run single test: `ctest -R <test_name> -V`

## Code Style Guidelines

### General
- Use 2-space indentation
- Max line length: 100 characters
- UTF-8 encoding for all files
- Follow Google C++ Style Guide with modifications in .clang-format

### Naming Conventions
- Classes: PascalCase (e.g., `LedController`)
- Functions: camelCase (e.g., `initializeHardware()`)
- Variables: camelCase (e.g., `ledPin`)
- Constants: UPPER_SNAKE_CASE (e.g., `MAX_BUFFER_SIZE`)
- Files: snake_case.ext (e.g., `led_controller.cpp`)

### Error Handling
- Use return codes for error reporting
- Check return values from SDK functions
- Use assertions for invariants
- Avoid dynamic memory allocation when possible

### Nix Development
- Pico SDK is provided via nixpkgs with withSubmodules override
- All tools are managed through Nix
- Use `nix flake update` to update dependencies

## Code Style Guidelines

### General
- Use 2-space indentation
- Max line length: 100 characters
- UTF-8 encoding for all files

### Naming Conventions
- Functions/methods: camelCase
- Variables: camelCase
- Constants: UPPER_SNAKE_CASE
- Classes: PascalCase
- Files: kebab-case.ext

### Error Handling
- Use explicit error handling (no silent failures)
- Log errors with appropriate context
- Return meaningful error messages

### Comments
- Use JSDoc-style comments for functions
- Keep comments current with code changes
- Explain "why" not "what" in comments

### Git Practices
- Commit messages: Start with verb in present tense
- Keep commits focused on single changes
- Reference issues in commit messages when applicable