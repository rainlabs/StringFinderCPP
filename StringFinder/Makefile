CXX	  = g++
CXXFLAGS  = -c -pedantic -Wall -std=c++0x -I./Public -I./Public/Unix -I./Public/Interfaces
#LDFLAGS   = "-Wl"
#LDFLAGS   = -L../build -ldaemon

DIRS      = . Private Private/Unix Private/Interfaces Private/ResultWriters

REL_SOURCES   = $(addprefix ./, $(DIRS))
SOURCES   = $(wildcard *.cpp) $(wildcard Private/*.cpp) $(wildcard Private/Unix/*.cpp) $(wildcard Private/Interfaces/*.cpp) $(wildcard Private/ResultWriters/*.cpp)
OBJECTS   = $(SOURCES:.cpp=.o)
TARGET    = StringFinder

.PHONY: all
release: CXXFLAGS += -O2
release: $(SOURCES) $(TARGET)
all: release

debug: CXXFLAGS += -gdwarf -g2 -DDEBUG -g
debug: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

obj/%.o: %.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

clean:
	rm -rf $(TARGET) $(OBJECTS)
