CC=g++
CFLAGS := -D _DEBUG -lm -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -Werror=vla
# CFLAGS = -D _DEBUG
# CFLAGS += -fsanitize=address

# [[fallthrough]]

# 1) libRun -> variable; testRun -> variable
# 2) build directory -> variable, -o flags for each compilation
# 3) @> @^ @< $<
# 4) PHONY - что делает

SOURCE_DIR                 := source
LIB_RUN_NAME     	       := libRun
TEST_PERFOMANCE_NAME       := perfomanceLibRun
BUILD_DIR              	   := building
TEST_PERFOMANCE_DEFINE 	   := -DTEST_PERFOMANCE
IS_OPT					   := 0
OPTIMIZE_FLAG              :=
DEBUG                  	   := 1
ASSERT_DEFINE          	   :=

ifeq ($(DEBUG), 0)
	ASSERT_DEFINE = -DNDEBUG
endif

ifeq ($(IS_OPT), 1)
	OPTIMIZE_FLAG = -O3
endif

# .PHONY: $(LIB_RUN_NAME) test run testrun $(TESTS_RUN_NAME) $(BUILD_DIR) clean
.PHONY: $(LIB_RUN_NAME) run $(TEST_PERFOMANCE_NAME) perf perfomance $(BUILD_DIR) clean

# -------------------------   LIB RUN   -----------------------------

SRC := $(wildcard ./$(SOURCE_DIR)/*.cpp)
OBJ := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir ${SRC}))

# running all commands without output (@ at the beginning)
$(LIB_RUN_NAME): $(OBJ)
	@$(CC) $^ -o $(BUILD_DIR)/$(LIB_RUN_NAME) $(CFLAGS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(BUILD_DIR)
	@$(CC) -c $< $(CFLAGS) -o $@ $(ASSERT_DEFINE)

perf: $(TEST_PERFOMANCE_NAME)
	$(BUILD_DIR)/$(TEST_PERFOMANCE_NAME)

perfomance: $(TEST_PERFOMANCE_NAME)
	$(BUILD_DIR)/$(TEST_PERFOMANCE_NAME)



run: $(LIB_RUN_NAME)
	$(BUILD_DIR)/$(LIB_RUN_NAME)





# # -------------------------   TEST PERFOMANCE     -----------------------------

OBJ_PERFOMANCE := $(patsubst %.cpp, $(BUILD_DIR)/PERFOMANCE_%.o, $(notdir ${SRC}))

# running all commands without output (@ at the beginning)
$(TEST_PERFOMANCE_NAME): $(OBJ_PERFOMANCE)
	@$(CC) $^ -o $(BUILD_DIR)/$(TEST_PERFOMANCE_NAME) $(CFLAGS) $(OPTIMIZE_FLAG) $(TEST_PERFOMANCE_DEFINE)

$(BUILD_DIR)/PERFOMANCE_%.o: $(SOURCE_DIR)/%.cpp $(BUILD_DIR)
	@$(CC) -c $< $(CFLAGS) $(OPTIMIZE_FLAG) -o $@ $(ASSERT_DEFINE) $(TEST_PERFOMANCE_DEFINE)





# -------------------------   HELPER TARGETS   ---------------------------

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
clean:
	rm -f $(BUILD_DIR)/*.o libRun


