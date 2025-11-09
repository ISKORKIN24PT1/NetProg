CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = echo
SOURCES = echo.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean
