CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -MMD -MP
LDFLAGS  :=

TARGET := $(notdir $(CURDIR))
BIN    := $(TARGET)

OBJ_DIR := .build

TEST_TARGET := test_runner

SRCS := $(wildcard *.cpp)

TEST_SRCS     := test-main.cpp $(wildcard test-*.cpp)
TEST_OBJS     := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))
TEST_DEPS     := $(TEST_OBJS:.o=.d)

NON_MAIN_SRCS := $(filter-out main.cpp test-main.cpp $(wildcard test-*.cpp),$(SRCS))
NON_MAIN_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(NON_MAIN_SRCS))

MAIN_SRCS := $(filter-out test-main.cpp $(wildcard test-*.cpp),$(SRCS))
MAIN_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))

DEPS := $(patsubst %.cpp,$(OBJ_DIR)/%.d,$(SRCS))

.PHONY: build run test clean

build:
	@needs_build=0; \
	if [ ! -f $(BIN) ]; then needs_build=1; \
	else \
	  for src in $(MAIN_SRCS); do \
	    if [ "$$src" -nt "$(BIN)" ]; then needs_build=1; break; fi; \
	  done; \
	  if [ -d $(OBJ_DIR) ]; then \
	    for dep in $(OBJ_DIR)/*.d; do \
	      [ -f "$$dep" ] || continue; \
	      while read -r line; do \
	        f=$$(echo "$$line" | tr -d '\\' | tr ' ' '\n' | grep -v '\.o:' | grep '\.' | head -1); \
	        [ -n "$$f" ] && [ -f "$$f" ] && [ "$$f" -nt "$(BIN)" ] && needs_build=1 && break 2; \
	      done < "$$dep"; \
	    done; \
	  fi; \
	fi; \
	if [ $$needs_build -eq 1 ]; then \
	  $(MAKE) --no-print-directory $(BIN); \
	else \
	  echo "[BUILD] $(TARGET) is up to date"; \
	fi

run:
	@needs_build=0; \
	if [ ! -f $(BIN) ]; then needs_build=1; \
	else \
	  for src in $(MAIN_SRCS); do \
	    if [ "$$src" -nt "$(BIN)" ]; then needs_build=1; break; fi; \
	  done; \
	fi; \
	if [ $$needs_build -eq 1 ]; then \
	  $(MAKE) --no-print-directory $(BIN); \
	fi; \
	./$(BIN)

test: $(TEST_TARGET)
	@./$(TEST_TARGET)

clean:
	@if [ -f $(BIN) ]; then rm -f $(BIN); echo "[CLEAN] rm -f $(BIN)"; fi
	@if [ -f $(TEST_TARGET) ]; then rm -f $(TEST_TARGET); echo "[CLEAN] rm -f $(TEST_TARGET)"; fi
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR); echo "[CLEAN] rm -rf $(OBJ_DIR)"; fi

$(BIN): $(MAIN_OBJS) | $(OBJ_DIR)
	@echo "[LINK ] $(TARGET)"
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@echo "[BUILD] $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJS) $(NON_MAIN_OBJS) | $(OBJ_DIR)
	@echo "[LINK ] $(TEST_TARGET)"
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) -lboost_unit_test_framework

$(OBJ_DIR):
	@mkdir -p $@

-include $(DEPS)
-include $(TEST_DEPS)

