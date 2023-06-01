SOURCES=ssd1331.cpp main.cpp display.cpp images.cpp iPotWifi.cpp PlanteID.cpp somo_class.cpp
OBJECTS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.d))
EXE=prog
CXXFLAGS=-I.
LDFLAGS=-pthread -lboost_system -lpthread

ARCH?=x86-64

ifeq (${ARCH},x86-64)
CXX=g++
BUILD_DIR=build/x86-64
BIN_DIR=bin/x86-64
endif

ifeq (${ARCH},arm)
CXX=arm-rpizw-g++
BUILD_DIR=build/arm
BIN_DIR=bin/arm
endif

$(BIN_DIR)/$(EXE): $(DEPS) $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

$(BUILD_DIR)/%.d: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@ 

ifneq ($(filter-out clean format tidy,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)

format: $(SOURCES:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"...
	@clang-format  -i $<
	@echo "" > $@

tidy: $(SOURCES:.cpp=.tidy)
%.tidy: %.cpp
	@echo "Tidying file '$<'"...
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@

