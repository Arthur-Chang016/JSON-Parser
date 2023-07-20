# the compiler: gcc for C program, define as g++ for C++
CC = g++-13

# source directory
SRCDIR = src

# build directory
BUILDDIR = build

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS = -g -Wall 

# List all source files by finding .cpp files in SRCDIR
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Generate the object file names by replacing .cpp with .o in the source file names
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# The build target
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)  # Create the build directory if it doesn't exist
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECTS)
