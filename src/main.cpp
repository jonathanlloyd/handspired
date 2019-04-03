#include <iostream>
#include <stdio.h>

#include "Logger.h"

using namespace handspired;

int main() {
	Logger * const logger = new Logger(LOGGER_DEBUG);
	logger->debugf("Some number: %d", 10);
	logger->info("Normal line");
	return 0;
}
