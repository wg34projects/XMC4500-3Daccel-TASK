SOURCES = catch_signals.c
TARGET  = catch_signals
CXX      = gcc
CXXFLAGS = `pkg-config --cflags --libs gtk+-3.0` -Wall -g -lm

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)
	
.PHONY: clean
clean:
	@rm -rf $(OBJECTS) $(TARGET) core
