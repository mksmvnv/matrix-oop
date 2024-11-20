# Variables

EXE_NAME    := matrix
LIB_NAME    := matrix_oop.a

CXX         := g++ -fdiagnostics-color=always
CPPFLAGS    := -MMD -MP
CXXFLAGS    := --std=c++17 -pedantic -O2 -Wall -Wextra -Werror

BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/obj

SRC_LIB     := src/matrix_oop.cpp
SRC_MAIN    := src/main.cpp
SRC_TEST    := src/tests/test_matrix_oop.cpp

OBJ_LIB     := $(SRC_LIB:src/%.cpp=$(OBJ_DIR)/%.o)
OBJ_MAIN    := $(SRC_MAIN:src/%.cpp=$(OBJ_DIR)/%.o)
OBJ_TEST    := $(SRC_TEST:tests/%.cpp=$(OBJ_DIR)/%.o)

GTEST_FLAGS := -lgtest -lgtest_main -pthread

# Targets

all: $(EXE_NAME) $(LIB_NAME)

$(EXE_NAME): $(OBJ_MAIN) $(OBJ_LIB)
	$(CXX) $^ -o $@

$(LIB_NAME): $(OBJ_LIB)
	ar rcs $@ $^

$(TEST_EXE): $(OBJ_TEST) $(OBJ_LIB)
	$(CXX) $^ $(GTEST_FLAGS) -o $@

$(OBJ_DIR)/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: tests/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -vf $(OBJ_DIR)/*.o
	rm -vf $(OBJ_DIR)/*.d

fclean: clean
	rm -vf $(EXE_NAME)
	rm -vf $(LIB_NAME)
	rm -vf $(TEST_EXE)
	rm -rvf $(BUILD_DIR)

rebuild: fclean all

test: $(OBJ_TEST) $(OBJ_LIB)
	$(CXX) $^ $(GTEST_FLAGS) -o $@

format:
	clang-format -i $(shell find src -type f -name "*.cpp") \
                     $(shell find src -type f -name "*.hpp") \
                     $(shell find src/tests -type f -name "*.cpp")

style:
	clang-format -n $(shell find src -type f -name "*.cpp") \
                     $(shell find src -type f -name "*.hpp") \
                     $(shell find src/tests -type f -name "*.cpp")

valgrind: $(EXE_NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE_NAME)

-include $(OBJ_DIR)/*.d

.PHONY: all clean fclean rebuild test style valgrind
.SILENT: clean fclean test style valgrind
