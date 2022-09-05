#include <cstdlib>
#include <time.h>
#include "Controller.h"

int main()
{
	srand(unsigned(time(NULL))); 	
	Controller controller;
	controller.run();

	return EXIT_SUCCESS;
}
