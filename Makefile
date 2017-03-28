
LIB_SOURCES = $(shell echo YOLConsoleEngine/src/*.cpp)
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)

ENGINETESTS_SOURCES = $(shell echo EngineTests/src/*.cpp)
ENGINETESTS_OBJECTS = $(ENGINETESTS_SOURCES:.c=.o)

all: libYOLConsoleEngine.so

libYOLConsoleEngine.so: $(LIB_OBJECTS)
	if [ ! -d "./build" ];then     \
		mkdir build;           \
	fi
	g++ -Wall -std=c++11 -IYOLConsoleEngine/include -fPIC -w -march=native -o build/libYOLConsoleEngine.so $(LIB_OBJECTS) -shared

tests: $(ENGINETESTS_SOURCES)
	g++ -Wall -std=c++11 -IYOLConsoleEngine/include -IEngineTests/include -fPIC -w -march=native -o build/EngineTests $(ENGINETESTS_OBJECTS) -lYOLConsoleEngine
	cp -R EngineTests/EngineCore build/EngineCore
	cp -R EngineTests/EngineCoreRaw build/EngineCoreRaw

install:
	install build/libYOLConsoleEngine.so /usr/lib/
	mkdir /usr/include/YOLConsoleEngine
	install YOLConsoleEngine/include/* /usr/include/YOLConsoleEngine/
	ln -sf /usr/include/YOLConsoleEngine/YOLConsoleEngine.h /usr/include/YOLConsoleEngine.h

uninstall:
	rm /usr/lib/libYOLConsoleEngine.so
	rm -rf /usr/include/YOLConsoleEngine
	rm /usr/include/YOLConsoleEngine.h

clean:
	rm -rf build