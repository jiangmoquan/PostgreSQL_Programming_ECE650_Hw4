#include "exerciser.h"

void exercise(connection *C) {
	add_player(C, 7, 27, "Liang", "Zhang", 27, 17, 7, 7, 1.7, 0.7);
	add_team(C, "ZJU", 1, 5, 17, 1);
	add_state(C, "CA");
	add_color(C, "NAVY");
	add_color(C, "PLAIN");
	query1(C, 0, 35, 40,
			  1, 5,  15,
			  0, 2,  6,
			  1, 2,  5,
			  0, 0.1,0.6,
			  1, 0.3,0.7);
	query2(C, "DarkBlue");
	query3(C, "Duke");
	query4(C, "NC", "DarkBlue");
	query5(C, 10);
}
