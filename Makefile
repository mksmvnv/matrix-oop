.PHONY: all gcov_report test leaks cppcheck style format 

CC 			= g++
CCFLAGS 	= -Wall -Werror -Wextra -g -pedantic
COVFLAGS 	= -fprofile-arcs -ftest-coverage
TESTFLAGS 	= -lgtest -lgtest_main
LEAKSFLAGS 	= --leak-check=full --show-leak-kinds=all --track-origins=yes
CHECKFLAGS 	= --enable=all --suppress=missingIncludeSystem

LIB_NAME 	= matrix_oop.a

SRC_DIR 	= src
BUILD_DIR 	= build
OBJ_DIR 	= $(BUILD_DIR)/obj
TEST_DIR 	= $(BUILD_DIR)/test
GCOV_DIR 	= $(BUILD_DIR)/gcov

$(shell mkdir -p $(OBJ_DIR) $(TEST_DIR) $(GCOV_DIR))

all: $(LIB_NAME)

gcov_report: test
	gcov -f $(OBJ_DIR)/*.gcda
	mv matrix_oop.cc.gcov $(GCOV_DIR)/
	lcov -t "test" -o $(GCOV_DIR)/test.info -c -d $(OBJ_DIR) --rc branch_coverage=0
	genhtml -o $(GCOV_DIR)/report $(GCOV_DIR)/test.info --rc branch_coverage=0

test: $(LIB_NAME)
	$(CC) $(CCFLAGS) -c $(SRC_DIR)/test.cc -o $(TEST_DIR)/test.o
	$(CC) $(CCFLAGS) $(COVFLAGS) -o $(TEST_DIR)/test.out $(TEST_DIR)/test.o $(TESTFLAGS) -L. $(OBJ_DIR)/$(LIB_NAME)
	./$(TEST_DIR)/test.out

$(LIB_NAME): $(OBJ_DIR)/matrix_oop.o
	ar rc $(OBJ_DIR)/$(LIB_NAME) $(OBJ_DIR)/matrix_oop.o
	ranlib $(OBJ_DIR)/$(LIB_NAME)

$(OBJ_DIR)/matrix_oop.o:
	$(CC) -c $(COVFLAGS) $(SRC_DIR)/matrix_oop.cc -o $(OBJ_DIR)/matrix_oop.o

leaks: test
	valgrind $(LEAKSFLAGS) ./$(TEST_DIR)/test.out

cppcheck:
	cppcheck $(CHECKFLAGS) $(SRC_DIR)/*.cc

style:
	clang-format -n $(SRC_DIR)/*.cc $(SRC_DIR)/*.h

format:
	clang-format -i $(SRC_DIR)/*.cc $(SRC_DIR)/*.h

clean:
	rm -rf $(BUILD_DIR)
