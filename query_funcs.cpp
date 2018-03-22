#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg) {
	work W(*C);
	stringstream add_sql;
	add_sql << "INSERT INTO PLAYER (TEAM_ID,UNIFORM_NUM,FIRST_NAME,LAST_NAME,MPG,PPG,RPG,APG,SPG,BPG) " \
		<< "VALUES (" << team_id << ", " << jersey_num << ", '" \
		<< W.esc(first_name) << "', '" << W.esc(last_name) << "', " << mpg << ", " << ppg << ", " \
		<< rpg << ", " << apg << ", " << spg << ", " << bpg << " );";

	W.exec(add_sql.str());
  	W.commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses) {
	work W(*C);
	stringstream add_sql;
	add_sql << "INSERT INTO TEAM (NAME,STATE_ID,COLOR_ID,WINS,LOSSES) " \
		<< "VALUES ('" << W.esc(name) << "', " << state_id << ", " \
		<< color_id << ", " << wins << ", " << losses << " );";

	W.exec(add_sql.str());
  	W.commit();
}


void add_state(connection *C, string name) {
	work W(*C);
	string add_sql = "INSERT INTO STATE (NAME) "
		"VALUES ('" + W.esc(name) + "' );";
	W.exec(add_sql);
  	W.commit();
}


void add_color(connection *C, string name) {
	work W(*C);
	string add_sql = "INSERT INTO COLOR (NAME) "
		"VALUES ('" + W.esc(name) + "' );";
	W.exec(add_sql);
  	W.commit();
}





void query1(connection *C,
	    	int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg) {

	try {
		nontransaction N(*C);
		stringstream sql;
		bool first_condition = true;
		
		sql << "SELECT * FROM PLAYER ";

		if (use_mpg) {
			sql << "WHERE MPG >= " << min_mpg << " AND MPG <= " << max_mpg << " ";
			first_condition = false;
		}

		if (use_ppg) {
			if (first_condition) {
				sql << "WHERE ";
			} else {
				sql << " AND ";
			}
			sql << " PPG >= " << min_ppg << " AND PPG <= " << max_ppg << " ";
			first_condition = false;
		}


		if (use_rpg) {
			if (first_condition) {
				sql << "WHERE ";
			} else {
				sql << " AND ";
			}
			sql << " RPG >= " << min_rpg << " AND RPG <= " << max_rpg << " ";
			first_condition = false;
		}

		if (use_apg) {
			if (first_condition) {
				sql << "WHERE ";
			} else {
				sql << " AND ";
			}
			sql << " APG >= " << min_apg << " AND APG <= " << max_apg << " ";
			first_condition = false;
		}

		if (use_spg) {
			if (first_condition) {
				sql << "WHERE ";
			} else {
				sql << " AND ";
			}
			sql << " SPG >= " << min_spg << " AND SPG <= " << max_spg << " ";
			first_condition = false;
		}

		if (use_bpg) {
			if (first_condition) {
				sql << "WHERE ";
			} else {
				sql << " AND ";
			}
			sql << " BPG >= " << min_bpg << " AND BPG <= " << max_bpg << " ";
			first_condition = false;
		}

		sql << ";";

		result r = N.exec(sql.str());


		cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" <<endl;
		for(result::const_iterator c = r.begin(); c!= r.end(); ++c){
			cout << c[0].as<int>() << " ";
			cout << c[1].as<int>() << " ";
			cout << c[2].as<int>() << " ";
			cout << c[3].as<string>() << " ";
			cout << c[4].as<string>() << " ";
			cout << c[5].as<int>() << " ";
			cout << c[6].as<int>() << " ";
			cout << c[7].as<int>() << " ";
			cout << c[8].as<int>() << " ";
			cout << setiosflags(ios::fixed) << setprecision(1) << c[9].as<double>() << " ";
			cout << setiosflags(ios::fixed) << setprecision(1) << c[10].as<double>() << endl;
		}
	} catch (const std::exception &e) {
    	cerr << e.what() << std::endl;
	}
}


void query2(connection *C, string team_color) {
	try {
		nontransaction N(*C);
		stringstream sql;
		sql << "SELECT TEAM.NAME " \
			<< "FROM TEAM, COLOR " \
			<< "WHERE TEAM.COLOR_ID=COLOR.COLOR_ID AND COLOR.NAME = '" << N.esc(team_color) << "';";

		result r = N.exec(sql.str());



		cout << "NAME" <<endl;
		for(result::const_iterator c = r.begin(); c != r.end(); ++c){
			cout << c[0].as<string>() <<endl;
		}

	} catch (const std::exception &e) {
    	cerr << e.what() << std::endl;
	}
}


void query3(connection *C, string team_name) {
	try {
		nontransaction N(*C);
		stringstream sql;
		sql << "SELECT FIRST_NAME, LAST_NAME " \
			<< "FROM PLAYER, TEAM " \
			<< "WHERE PLAYER.TEAM_ID = TEAM.TEAM_ID AND NAME ='"<< N.esc(team_name) <<"' " \
			<< "ORDER BY PPG DESC;";
		result r = N.exec(sql.str());

		cout << "FIRST_NAME LAST_NAME" <<endl;
		for(result::const_iterator c = r.begin(); c != r.end(); ++c) {
			cout << c[0].as<string>() << " " << c[1].as<string>() << endl;
		}


	} catch (const std::exception &e) {
    	cerr << e.what() << std::endl;
	}

}


void query4(connection *C, string team_state, string team_color) {
	try {
		nontransaction N(*C);
		stringstream sql;
		sql << "SELECT FIRST_NAME, LAST_NAME, UNIFORM_NUM " \
			<< "FROM PLAYER, TEAM, STATE, COLOR " \
			<< "WHERE PLAYER.TEAM_ID=TEAM.TEAM_ID AND TEAM.COLOR_ID=COLOR.COLOR_ID AND TEAM.STATE_ID=STATE.STATE_ID " \
			<< "AND STATE.NAME='"<< N.esc(team_state) <<"' AND COLOR.NAME='"<< N.esc(team_color) <<"';";

		result r = N.exec(sql.str());
		
		cout << "FIRST_NAME LAST_NAME UNIFORM_NUM" << endl;
		for(result::const_iterator c = r.begin(); c != r.end(); ++c) {
			cout << c[0].as<string>() << " " << c[1].as<string>() << " " << c[2].as<int>() << endl;
		}

	} catch (const std::exception &e) {
    	cerr << e.what() << std::endl;
	}


}


void query5(connection *C, int num_wins) {
	try {
		nontransaction N(*C);
		stringstream sql;
		sql << "SELECT FIRST_NAME, LAST_NAME, TEAM.NAME, WINS " \
			<< "FROM PLAYER, TEAM " \
			<< "WHERE PLAYER.TEAM_ID=TEAM.TEAM_ID AND WINS > " << num_wins << ";";

		result r = N.exec(sql.str());

		cout << "FIRST_NAME LAST_NAME NAME WINS" <<endl; 
		for(result::const_iterator c = r.begin(); c != r.end(); ++c) {
			cout << c[0].as<string>() << " " \
				 << c[1].as<string>() << " " \
				 << c[2].as<string>() << " " \
				 << c[3].as<int>() << endl;
		}

	} catch (const std::exception &e) {
    	cerr << e.what() << std::endl;
	}
}




