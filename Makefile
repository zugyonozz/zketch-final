BUILD_DIR = build
BIN_DIR = bin
EXE_NAME = zketch

# Compiler flags (optional override)
CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release

# Default target: build the project
all:
	cmake -B$(BUILD_DIR) $(CMAKE_FLAGS)
	cmake --build $(BUILD_DIR)

# Run the program (make sure executable exists)
run: all
	./$(BIN_DIR)/$(EXE_NAME).exe

# Clean the entire build directory (dangerous!)
clean:
	@echo Cleaning full build directory...
	rm -rf $(BUILD_DIR)
	rm -f $(BIN_DIR)/$(EXE_NAME).exe

# Clean object files only (keep CMake configuration!)
update:
	cmd /C "echo Cleaning object files only - keep CMake cache and config && \
	if exist build\\CMakeFiles rmdir /s /q build\\CMakeFiles && \
	for /R build %%f in (*.obj *.pdb) do del /f /q \"%%f\""

.PHONY: all run clean update