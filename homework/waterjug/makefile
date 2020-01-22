CXX      = g++
# Search directory for any file with any characters followed by .cpp
CXX_FILE = $(wildcard *.cpp)
# Makes the executable w/o .cpp
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE))
# -g includes debug information, c++ version, warn all, all warnings are errors
# Converts diagnostic warnings into error
CXXFLAGS = -g -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0

# Build instructions must be preceded by a tab (not spaces)
# These use the shortcuts from above, -o gives the output a name
# -f is force
all:
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe