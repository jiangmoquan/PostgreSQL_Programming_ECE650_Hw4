#include <iostream>
#include <pqxx/pqxx>

#include "exerciser.h"

using namespace std;
using namespace pqxx;


void DropTables(connection *C) {
  char * drop_sql = "DROP TABLE IF EXISTS PLAYER, TEAM, STATE, COLOR CASCADE;";

  work W(C);
  W.exec(drop_sql);
  W.commit();
  cout << "Exsiting tables have been dropped." << endl;
}








void CreateTables() {
  char * create_player_sql = "CREATE TABLE PLAYER(" \
  "PLAYER_ID    SERIAL  PRIMARY KEY," \
  "TEAM_ID      INT     REFERENCES TEAM(TEAM_ID)," \
  "UNIFORM_NUM  INT     NOT NULL," \
  "FIRST_NAME   TEXT    NOT NULL," \
  "LAST_NAME    TEXT    NOT NULL," \
  "MPG          REAL    NOT NULL," \ //?
  "PPG          REAL    NOT NULL," \ //?
  "RPG          REAL    NOT NULL," \ //?
  "APG          REAL    NOT NULL," \ //?
  "SPG          REAL    NOT NULL," \
  "BPG          REAL    NOT NULL);";

  char * create_team_sql = "CREATE TABLE TEAM(" \
  "TEAM_ID      SERIAL  PRIMARY KEY," \
  "NAME         TEXT    NOT NULL," \
  "STATE_ID     INT     REFERENCES STATE (STATE_ID)," \
  "COLOR_ID     INT     REFERENCES COLOR (COLOR_ID)," \
  "WINS         INT     NOT NULL," \
  "LOSSES       INT     NOT NULL);"; \

  char * create_state_sql = "CREATE TABLE STATE(" \
  "STATE_ID     SERIAL  PRIMARY KEY," \
  "NAME         TEXT    NOT NULL);";

  char * create_color_sql ="CREATE TABLE COLOR(" \
  "COLOR_ID     SERIAL  PRIMARY KEY," \
  "NAME         TEXT    NOT NULL);";

  work W(C);
  W.exec(create_player_sql);
  W.exec(create_team_sql);
  W.exec(create_state_sql);
  W.exec(create_color_sql);
  W.commit();

  cout << "Create tables successfully." << endl;
}


void LoadFiles() {

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


