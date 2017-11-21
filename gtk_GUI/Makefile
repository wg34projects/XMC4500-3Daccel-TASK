SOURCES = 3DacceltaskGUI.c menucallbacks.c rs232.c
HEADERS = $(SOURCES:.c=.h)
TARGET  = 3DaccelGUI
CXX      = gcc
CXXFLAGS = `pkg-config --cflags --libs gtk+-3.0` -Wall -g

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)
	
.PHONY: clean
clean:
	@rm -rf $(OBJECTS) $(TARGET) core
