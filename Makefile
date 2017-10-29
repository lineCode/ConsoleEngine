CC = g++
PREFIX = /usr/local

CFLAGS_COMMON = -fopenmp -m64 -std=c++17 -fPIC
CFLAGS_DEBUG = $(CFLAGS_COMMON) -O0 -Wall
CFLAGS_RELEASE = $(CFLAGS_COMMON) -Os -w
CFLAGS = $(CFLAGS_DEBUG)

LIB_NAME = ConsoleEngine
OBJECTS_DIR = objects
BUILD_DIR = build

ENGINE_INCLUDE = $(LIB_NAME)/include
ENGINE_SOURCE = $(LIB_NAME)/src
ENGINE_SOURCES = $(wildcard $(ENGINE_SOURCE)/*.cpp)
ENGINE_OBJECTS = $(patsubst $(ENGINE_SOURCE)/%.cpp, $(OBJECTS_DIR)/%.o, $(ENGINE_SOURCES))

TESTS_INCLUDE = Tests/include
TESTS_SOURCE = Tests/src
TESTS_SOURCES = $(wildcard $(TESTS_SOURCE)/*.cpp)
TESTS_OBJECTS = $(patsubst $(TESTS_SOURCE)/%.cpp, $(OBJECTS_DIR)/%.o, $(TESTS_SOURCES))

MKDIR = \mkdir -p
RM = \rm -f
CP = \cp

all: folders lib-static lib-dynamic test-static
	@echo "|----->     To compile test-dynamic, run the following command:      <-----|"
	@echo "|----->  'sudo make install && sudo ldconfig && make test-dynamic'   <-----|"

folders:
	$(MKDIR) $(BUILD_DIR)
	$(MKDIR) $(OBJECTS_DIR)

$(OBJECTS_DIR)/%.o: $(ENGINE_SOURCE)/%.cpp
	$(CC) $(CFLAGS) -c -I$(ENGINE_INCLUDE) -o $@ $<

lib-static: $(ENGINE_OBJECTS)
	ar rvs $(BUILD_DIR)/lib$(LIB_NAME).a $^

lib-dynamic: $(ENGINE_OBJECTS)
	$(CC) $(CFLAGS) -I$(ENGINE_INCLUDE) -o $(BUILD_DIR)/lib$(LIB_NAME).so $(ENGINE_SOURCES) -shared

test-static:
	$(CC) $(CFLAGS) -I$(ENGINE_INCLUDE) -I$(TESTS_INCLUDE) -o $(BUILD_DIR)/$@ $(TESTS_SOURCES) -L$(BUILD_DIR) -l:lib$(LIB_NAME).a

test-dynamic:
	$(CC) $(CFLAGS) -I$(PREFIX)/include/$(LIB_NAME) -I$(TESTS_INCLUDE) -o $(BUILD_DIR)/$@ $(TESTS_SOURCES) -l$(LIB_NAME)

run-static:
	$(shell ./$(BUILD_DIR)/test-static)

run-dynamic:
	$(shell ./$(BUILD_DIR)/test-dynamic)

.PHONY: install
install:
	$(MKDIR) $(PREFIX)/lib
	$(CP) $(BUILD_DIR)/lib$(LIB_NAME).so $(PREFIX)/lib/lib$(LIB_NAME).so
	$(CP) $(BUILD_DIR)/lib$(LIB_NAME).a $(PREFIX)/lib/lib$(LIB_NAME).a

	$(MKDIR) $(PREFIX)/include/$(LIB_NAME)
	$(CP) $(LIB_NAME)/include/* $(PREFIX)/include/$(LIB_NAME)/

uninstall:
	$(RM) $(PREFIX)/lib/lib$(LIB_NAME).so
	$(RM) -r $(PREFIX)/include/$(LIB_NAME)/
	@echo "|----->           It is recommended to run 'sudo ldconfig'           <-----|"

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(OBJECTS_DIR)
