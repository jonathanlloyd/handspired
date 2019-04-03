all: build

.PHONY: build
build:
	@./scripts/build

.PHONY: run
run: build
	@./bin/game
