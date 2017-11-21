# sources

SOURCE = terminal.h terminal.c rs232.c rs232.h

# target

TARGET = terminal

# flags

CXX      = gcc
CXXFLAGS = -Wall --pedantic -Wcpp

# create

$(TARGET): $(SOURCE)
	$(CXX) $(SOURCE) $(CXXFLAGS) -o $(TARGET) 

.PHONY: clean
clean:
	@rm -rf $(OBJECTS) $(TARGET) core *~
	rm -rf doc/html

doc: $(TARGET)
	doxygen

