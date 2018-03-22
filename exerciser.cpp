#include "exerciser.h"

void exercise(connection *C) {
	query1(C, 0, 35, 40,
	 	  1, 10,  15,
		  1, 3,  6,
		  1, 2,  5,
		  1, 0.2,0.6,
	          1, 0.3,0.7);
	query2(C, "DarkBlue");
	query3(C, "");
	query4(C, "NC", "DarkBlue");
	query5(C, 9);
}
