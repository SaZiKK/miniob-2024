BUILD_DIR:= build_debug

all: 
	@echo "Building..."
	@bash build.sh --make -j20

run: all
	@echo "Running..."
	@cd $(BUILD_DIR) && ./bin/observer -f ../etc/observer.ini -P cli

clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR)

.PHONY: all run clean