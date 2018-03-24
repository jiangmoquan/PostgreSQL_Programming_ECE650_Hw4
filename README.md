# PostgreSQL_Programming_ECE650_Hw4

Overview
In this assignment, you will build a PostgreSQL database. The relation schemas (tables) of the database will be provided, along with the database values. You will implement:
1. A C++ program to read text files containing the entries (rows) for each table, and build the database by creating each table and adding entries.
2. A C++ library (set of functions) which will provide an interface for a program to interact with the database (e.g. add rows to the tables and query for certain information).
The database relates to ACC basketball teams, and will allow queries to discover information about things like player statistics, team attributes, etc. The database will have 4 tables, specified as follows (an underlined attribute indicates the primary key for the table):
PLAYER (PLAYER_ID, TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG)
TEAM (TEAM_ID, NAME, STATE_ID, COLOR_ID, WINS, LOSSES)
STATE (STATE_ID, NAME)
COLOR (COLOR_ID, NAME)

Several skeleton files, and database table information files are provided to get you started. The following describes each file:
• Database source text files: player.txt, team.txt, state.txt, color.txt. These files contain table-like information for each entry and each attribute that should be inserted into the respective database table.
• main.cpp: The main function. Here you should implement code which will setup the database on each execution of the program. Specifically, it should drop (if needed) and add each table to the database (named ACC_BBALL), and then read information from the source text files and add rows to each table as appropriate.
      
• query_funcs.h and query_funcs.cpp: Here you will implement functions to interact with the database (add new entries and print the results of 5 different queries specified below). You may add new functions to these files if desired (you don’t have to), but you should not change the definitions of the existing functions.
• exerciser.h and exerciser.cpp: Here you can add code in the exercise() function to test your query functions. The exercise() function is called from main() after the database is initialized.
• Makefile: Will compile all source files into an executable program named “test”

Your task is to do the following:
• Create a PostgreSQL database named ACC_BBALL
• Create a user for the ACC_BBALL database named “postgres” with password
“passw0rd” (see the postgresql.ppt charts for how to set the password of the postgres
user.
• Implement support in main.cpp to connect (as user ‘postgres') to the ACC_BBALL
database and initialize its tables and data. Of course, usually a database will live persistently, but for the purposes of evaluating the submissions, the program should re- create the database every time. You should drop tables that may already exist (e.g. from prior runs of your test) before creating an initializing the tables in the program.
• Implement the following query functions:
o query1():showallattributesofeachplayerwithaveragestatisticsthatfall
between the min and max (inclusive) for each enabled statistic
o query2():showthenameofeachteamwiththeindicateduniformcolor
o query3():showthefirstandlastnameofeachplayerthatplaysfortheindicated
team, ordered from highest to lowest ppg (points per game)
o query4():showfirstname,lastname,andjerseynumberofeachplayerthat
plays in the indicated state and wears the indicated uniform color
o query5():showfirstnameandlastnameofeachplayer,andteamnameand
number of wins for each team that has won more than the indicated number of
games
o ImportantNote:Eachqueryfunctionshouldprintitsoutput.Theformatofthis
output should be as follows. The first row of output should contain each field name (separated by a single space character. The next rows of output should contain the values returned from the query, each also separated by a single space. The field name and each row of output should appear one line after the next.
• You may test your database and query functions by adding calls to the query functions inside the exerciser() function. For the purposes of grading assignments, we will replace the exerciser.cpp file with a new one that will test a variety of query calls.
