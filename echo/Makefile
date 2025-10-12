CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = echo_client
SRC = echo_client.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: clean
