#pragma once

#include "CLI.h"


int main() {
	initHeapMonitor();

	CLI* cli = new CLI();

	while (cli->behAplikacie());

	delete cli;

	return 0;

}
