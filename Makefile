
LIB_SOURCES = $(shell echo YOLConsoleEngine/src/*.cpp)
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)

ENGINETESTS_SOURCES = $(shell echo EngineTests/src/*.cpp)
ENGINETESTS_OBJECTS = $(ENGINETESTS_SOURCES:.c=.o)

all: YOLConsoleEngine.so EngineTests.out

YOLConsoleEngine.so: $(LIB_OBJECTS)
	g++ -g -Wall -std=c++11 -IYOLConsoleEngine/include -fPIC -w -march=native -o build/YOLConsoleEngine.so $(LIB_OBJECTS) -shared
	cp build/YOLConsoleEngine.so YOLConsoleEngine.so 

EngineTests.out: $(ENGINETESTS_SOURCES)
	g++ -g -Wall -std=c++11 -IYOLConsoleEngine/include -IEngineTests/include -fPIC -w -march=native -o build/EngineTests.out $(ENGINETESTS_OBJECTS) ./YOLConsoleEngine.so
	cp -R EngineTests/EngineCore build/EngineCore
	cp -R EngineTests/EngineCoreRaw build/EngineCoreRaw
	rm YOLConsoleEngine.so

clean:
	rm -rf build
	rm YOLConsoleEngine.so