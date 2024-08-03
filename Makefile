CXX = g++
CXXFLAGS = -std=c++20 -Wall -pedantic

BUILD_DIR = build
TEMPLATE_DIR = .template
OUT_EXE = server.out

ifeq ($(OS),Windows_NT)
	LDLIBS += -l Ws2_32
endif

all: $(BUILD_DIR) $(OUT_EXE)

$(OUT_EXE): $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o \
            $(BUILD_DIR)/utilities.o $(BUILD_DIR)/strutils.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o \
            $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/System.o $(BUILD_DIR)/Data.o $(BUILD_DIR)/Account.o \
            $(BUILD_DIR)/CheckCommand.o $(BUILD_DIR)/DELETECommand.o $(BUILD_DIR)/FileHandler.o \
            $(BUILD_DIR)/GETCommand.o $(BUILD_DIR)/Post.o $(BUILD_DIR)/POSTCommand.o $(BUILD_DIR)/Professor.o \
            $(BUILD_DIR)/PUTCommand.o $(BUILD_DIR)/SocialPost.o $(BUILD_DIR)/Student.o $(BUILD_DIR)/UT_manager.o \
            $(BUILD_DIR)/TA_formPost.o
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rules for each class
$(BUILD_DIR)/System.o: UT_App/System/System.cpp UT_App/System/System.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Data.o: UT_App/System/Data.cpp UT_App/System/Data.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Account.o: UT_App/System/Account.cpp UT_App/System/Account.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/CheckCommand.o: UT_App/System/CheckCommand.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/DELETECommand.o: UT_App/System/DELETECommand.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/FileHandler.o: UT_App/System/FileHandler.cpp UT_App/System/FileHandler.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/GETCommand.o: UT_App/System/GETCommand.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Post.o: UT_App/System/Post.cpp UT_App/System/Post.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/POSTCommand.o: UT_App/System/POSTCommand.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Professor.o: UT_App/System/Professor.cpp UT_App/System/Professor.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/PUTCommand.o: UT_App/System/PUTCommand.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/SocialPost.o: UT_App/System/SocialPost.cpp UT_App/System/SocialPost.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Student.o: UT_App/System/Student.cpp UT_App/System/Student.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/UT_manager.o: UT_App/System/UT_manager.cpp UT_App/System/UT_manager.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/TA_formPost.o: UT_App/System/TA_formPost.cpp UT_App/System/TA_formPost.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Existing rules
$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/strutils.o: utils/strutils.cpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/server.o: UT_App/Server/server.cpp UT_App/Server/server.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/route.o: UT_App/Server/route.cpp UT_App/Server/route.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/handlers.o: utils/handlers.cpp utils/handlers.hpp utils/handlerConst.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: UT_App/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) $(OUT_EXE) *.o &> /dev/null
