# compiler
CC = gcc

# source files
SRC = main.c

# output directory and binary name
BUILD_DIR = build
OUTPUT = $(BUILD_DIR)/program.exe

# default target: Build and run
default: $(OUTPUT)
	@echo "Running the program..."
	@./$(OUTPUT)   # Correct execution method for Cygwin

# build target
$(OUTPUT): $(SRC) | $(BUILD_DIR)
	$(CC) $(SRC) -o $(OUTPUT)

# ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# clean target
clean:
	rm -rf $(BUILD_DIR)

# for linux distros (a lot easier)
linux:
	gcc main.c -o main.o
	./main.o