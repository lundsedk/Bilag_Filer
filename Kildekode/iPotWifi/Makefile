#Makefile for exc5.1

ARCH?=x86-64

ifeq (${ARCH},arm)
CXX=arm-rpizw-g++
BUILD_DIR = build/arm
endif

ifeq (${ARCH},x86-64)
CXX=g++
BUILD_DIR = build/x86-64
endif

targets = 
CXXFLAGS = -I. 
executable = getDataTest
SOURCES = getDataTest.cpp iPotWifi.cpp
OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.d)
LIBS = -lncurses -lpthread

$(executable):$(OBJECTS) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $(executable) $(OBJECTS) $(LIBS)

$(BUILD_DIR)/%.o: %.cpp
	@echo making o file:     $(CXX) $(CXXFLAGS) -c $<
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILD_DIR)/%.d: %.cpp
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

format: $(SOURCES:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"...
	@clang-format -i $<
	@echo "" > $@

tidy: $(SOURCES:.cpp=.tidy)
%.tidy: %.cpp
	@echo " Tidying file '$<'"...
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@

.PHONY: all
all: $(targets)


.PHONY: test
test:
	@echo Running test...
	@echo targets = $(targets)
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo executable = $(executable)
	@echo SOURCES = $(SOURCES)
	@echo OBJECTS = $(OBJECTS)
	@echo DEPS = $(DEPS)

.PHONY: clean
clean:
	rm  -f *.o $(targets)
	rm  -f *.o $(OBJECTS)

.PHONY: help
help:
	@echo The following targets are available:
	@echo \n$(executable)\n - the main program
	@echo all - make all targets
	@echo clean - removes all .o files, and the executable \"$(executable)\"
	@echo help - writes this help text


ifneq ($(filter-out clean format tidy ,$(MAKECMDGOALS)),)
-include $(BUILD_DIR)/$(DEPS)
endif