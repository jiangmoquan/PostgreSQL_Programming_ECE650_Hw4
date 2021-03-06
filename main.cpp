#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <sstream>
#include <fstream>
#include "exerciser.h"

using namespace std;
using namespace pqxx;


void DropTables(connection *C) {
  string drop_sql = "DROP TABLE IF EXISTS PLAYER, TEAM, STATE, COLOR CASCADE;";

  work W(*C);
  W.exec(drop_sql);
  W.commit();
  //cout << "Exsiting tables have been dropped." << endl;
}


void CreateTables(connection *C) {
  string create_player_sql = "CREATE TABLE PLAYER(" 
  "PLAYER_ID    SERIAL  PRIMARY KEY," 
  "TEAM_ID      INT     REFERENCES TEAM(TEAM_ID)," 
  "UNIFORM_NUM  INT     NOT NULL," 
  "FIRST_NAME   TEXT    NOT NULL," 
  "LAST_NAME    TEXT    NOT NULL," 
  "MPG          INT     NOT NULL,"  
  "PPG          INT     NOT NULL,"  
  "RPG          INT     NOT NULL,"  
  "APG          INT     NOT NULL,"  
  "SPG          REAL    NOT NULL," 
  "BPG          REAL    NOT NULL);";

  string create_team_sql = "CREATE TABLE TEAM(" 
  "TEAM_ID      SERIAL  PRIMARY KEY," 
  "NAME         TEXT    NOT NULL," 
  "STATE_ID     INT     REFERENCES STATE (STATE_ID)," 
  "COLOR_ID     INT     REFERENCES COLOR (COLOR_ID)," 
  "WINS         INT     NOT NULL," 
  "LOSSES       INT     NOT NULL);"; 

  string create_state_sql = "CREATE TABLE STATE(" 
  "STATE_ID     SERIAL  PRIMARY KEY," 
  "NAME         TEXT    NOT NULL);";

  string create_color_sql ="CREATE TABLE COLOR(" 
  "COLOR_ID     SERIAL  PRIMARY KEY," 
  "NAME         TEXT    NOT NULL);";

  work W(*C);
  W.exec(create_state_sql);
  W.exec(create_color_sql);
  W.exec(create_team_sql);
  W.exec(create_player_sql);
  W.commit();

  //cout << "Create tables successfully." << endl;
}


void LoadPlayerFile(connection *C) {
  ifstream ifs("player.txt", ifstream::in);
  string line;
  
  int id, team_id, uniform_num, mpg, ppg, rpg, apg;
  string first_name, last_name;
  double spg, bpg;

  while (getline(ifs, line)) {
    if (!line.empty()) {
      stringstream ss(line);
      ss >> id >> team_id >> uniform_num >> first_name >> last_name >> mpg >> ppg >> rpg >> apg >> spg >> bpg;
      add_player(C,team_id, uniform_num, first_name, last_name, mpg, ppg, rpg, apg, spg, bpg);
    }
  }

  ifs.close();
}


void LoadTeamFile(connection *C) {
  ifstream ifs("team.txt", ifstream::in);
  string line;
  
  int team_id, state_id, color_id, wins, losses;
  string name;

  while (getline(ifs, line)) {
    if (!line.empty()) {
      stringstream ss(line);
      ss >> team_id >> name >> state_id >> color_id >> wins >> losses;
      add_team(C, name, state_id, color_id, wins, losses);
    }
  }

  ifs.close();
}


void LoadStateFile(connection *C) {
  ifstream ifs("state.txt", ifstream::in);
  string line;
  
  int state_id;
  string name;

  while (getline(ifs, line)) {
    if (!line.empty()) {
      stringstream ss(line);
      ss >> state_id >> name;
      add_state(C, name);
    }
  }
  ifs.close();
}

void LoadColorFile(connection *C) {
  ifstream ifs("color.txt", ifstream::in);
  string line;
  
  int color_id;
  string name;

  while (getline(ifs, line)) {
    if (!line.empty()) {
      stringstream ss(line);
      ss >> color_id >> name;
      add_color(C, name);
    }
  }
  ifs.close();
}


void LoadFiles(connection *C) {
  LoadStateFile(C);
  LoadColorFile(C);
  LoadTeamFile(C);
  LoadPlayerFile(C);
  //cout << "Load files successfully." << endl;
}


int main (int argc, char *argv[]) {

  //Allocate & initialize a Postgres connection object
  connection *C;

  try {
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e) {
    cerr << e.what() << std::endl;
    return 1;
  }


  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files
  try {
    DropTables(C);
    CreateTables(C);
    LoadFiles(C);
  } catch (const std::exception &e) {
    cerr << e.what() << std::endl;
    return 1;    
  }



  exercise(C);


  //Close database connection
  C->disconnect();

  return 0;
}


