#include "exerciser.h"

void exercise(connection *C) {
	query1(C, 0, 35, 40,
	 	  0, 10,  15,
		  0, 3,  6,
		  0, 2,  5,
		  0, 0.2,0.6,
	          0, 0.7,0.3);
	        query1(C, 0, 35, 40,
                  1, 10,  15,
                  0, 3,  6,
                  0, 2,  5,
                  0, 0.2,0.6,
                  0, 0.7,0.3);
	query2(C, "DarkBlue");
	query3(C, "");
	query4(C, "NC", "DarkBlue");
	query5(C, 9);
}
