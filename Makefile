BUILD_DIR:= build_debug
DEBUG_DIR:= test/case
SRC_DIR := src
TEST:= basic


all: fmt gen
	@echo "Building..."
	@bash build.sh --make -j20

gen:
	@echo "Generating..."
	@cd src/observer/sql/parser/ && ./gen_parser.sh

run: all
	@echo "Running..."
	@cd $(BUILD_DIR) && ./bin/observer -f ../etc/observer.ini -P cli

clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR)

fmt:
	@echo "Formatting source files..."
	@find $(SRC_DIR) \( -name '*.c' -o -name '*.h' -o -name '*.cpp' -o -name '*.hpp' \) \
		-not \( -name 'lex_sql*' -o -name 'yacc_sql*' \) \
		-print0 | xargs -0 clang-format -i
	@echo "Formatting complete."

debug:
	@echo "Building debug..."
	@cd $(DEBUG_DIR) && python3 miniob_test.py --test-cases=primary-$(TEST)

.PHONY: all run clean fmt gen debug