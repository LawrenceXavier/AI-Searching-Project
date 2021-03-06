#include <cstdio>
#include <cstdlib>
#include "Geometry.h"
#include "AllObject.h"
#include "FindPath.h"

#define INPUT_FILE	"input.txt"

int main(int argc, char* argv[]) {
	AllObject allObj(INPUT_FILE);
	FindPath fd(&allObj);
	fd.search();
	fd.printOut("Output.html");
	return 0;
}
