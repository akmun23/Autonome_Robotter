#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include "CheckersDatabase.h"

void UpdateDatabaseFromTemp(){                                                  // Funktion til at tage den tabel gemt fra spillet
                                                                                // og indsætte den i databasen

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.exec("SELECT tempboard_id "                                           // Henter alle tempBoard_id fra Temp
               "FROM Temp");
    while (query.next()) {                                                      // Kører igennem alle tempBoard id
        AddBoard(query.value(0).toInt());                                       // Kalder AddBoard for alle de tempBoard id'er der er i Temp
    }

    query.exec("DELETE FROM Temp "
               "WHERE tempBoard_id >= 0");                                      // Sletter alle rækker i Temp

    return;
}

void AddBoard(int TempBoardID){                                                 // Funktion til at indsætte et board i databasen

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);


    std::string BoardStateInputtet;                                             // Deklarerer en string til at holde boardstate

    query.exec("Select BoardState "                                             // Henter boardstate fra Temp
               "FROM Temp "
               "WHERE tempBoard_id = " + QString::number(TempBoardID));
    query.first();                                                              // Det er kun 1 boardstate der matcher det boardstate fra temp
                                                                                // så derfor bruger vi first
    BoardStateInputtet = query.value(0).toString().toStdString();


    query.prepare("SELECT count(*) "                                            // Tæller hvor mange gange boardstate er i UniqueBoard
                  "FROM UniqueBoard "                                           // Mulighederne er 0 eller 1 gang
                  "Where BoardState = :BoardState");
    query.bindValue(":BoardState", QString::fromStdString(BoardStateInputtet));
    query.exec();
    query.first();

    if (query.value(0).toInt() == 1){                                           // Hvis boardstate er i UniqueBoard
        AddMove(TempBoardID);                                                   // Så skal den bare tilføje et move til det boardstate
        return;
    }
    else if (query.value(0).toInt() == 0){                                      // Hvis boardstate ikke er i UniqueBoard
        query.prepare("INSERT INTO UniqueBoard (BoardState) "                   // Så skal den tilføje boardstate til UniqueBoard
                      "VALUES (:BoardState)");
        query.bindValue(":BoardState", QString::fromStdString(BoardStateInputtet));
        query.exec();
        AddMove(TempBoardID);                                                   // Og derefter tilføje et move til det boardstate
        return;
    }
}

void AddMove(int& TempBoardID){                                                 // Funktion til at add move til et boardstate
                                                                                // Eller update winrate hvis move allerede er i Moves


    //Laver variabler til at holde data fra databasen
    int BoardID = 0;
    double WinChecker = 0;
    int PlayerID = 0;
    std::string NewMoveToCheck;
    std::string BoardState;
    std::vector<std::string> OldMoves;

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    if (TempBoardID == 0){                                                      // Hvis det er det første board i spillet
        return;                                                                 // så skal den ikke tilføje et move da den henter movet fra hvordan
    }                                                                           // man kom til det boardstate og der er ikke et move hen til startbrættet

    query.exec("Select WinOrLoss, PlayerID "                                              // Finder ud af om det move den skal tilføje
               "FROM Temp "                                                     // var et move fra spilleren der vandt ellet tabte
               "WHERE tempBoard_id = " + QString::number(TempBoardID));
    query.first();
    WinChecker = query.value(0).toDouble();
    PlayerID = query.value(1).toInt();

    query.exec("Select BoardState "                                             // Finder boardstate fra det board før det nuværende
               "FROM Temp "                                                     // da det er det boardstate rykket blev lavet på
               "WHERE tempBoard_id = " + QString::number(TempBoardID-1));
    query.first();
    BoardState = query.value(0).toString().toStdString();

    query.prepare("SELECT board_id "                                            // Finder board id fra det board som den skal tilføje et move til
                  "FROM UniqueBoard "
                  "WHERE BoardState = :boardState");
    query.bindValue(":boardState", BoardState.c_str());
    query.exec();
    query.first();
    BoardID = query.value(0).toInt();


    query.exec("Select Move "                                                   // Finder det move som blev lavet
               "FROM Temp "                                                     // for at komme til det nuværende boardstate
               "WHERE tempBoard_id = " + QString::number(TempBoardID));
    query.first();
    NewMoveToCheck = query.value(0).toString().toStdString();


    query.exec("SELECT count(Move) "                                            // Tæller hvor mange ryk der er lavet på det boardstate
               "FROM Moves "
               "WHERE board_id = " + QString::number(BoardID));
    query.first();
    int count = query.value(0).toInt();

    if (count == 0){                                                            // Hvis der ikke er nogen moves på det boardstate

        InsertToMove(BoardID, NewMoveToCheck, WinChecker, PlayerID);                         // Så skal den bare tilføje et move
        return;
    }
    else{                                                                       // Hvis der er moves på det boardstate

        std::string Move;
        bool UpdatedMove = false;

        query.exec(" SELECT Move "                                               // Så skal den kigge på alle moves på det boardstate
                   " FROM Moves "
                   " WHERE board_id = " + QString::number(BoardID) + " "
                   " And Player = " + QString::number(PlayerID));
        while (query.next()) {                                                  // Her kører den igennem alle moves på det boardstate
            Move = query.value(0).toString().toStdString();

            if (Move == NewMoveToCheck){                                           // Hvis det move der skal tilføjes allerede er i Moves

                UpdateMoveWinrate(BoardID, NewMoveToCheck, WinChecker, PlayerID);            // Så skal den opdatere winrate, wincases og usescases for det move
                UpdatedMove = true;                                             // Og sætte UpdatedMove til true så den ikke går ned i nedenstående
                return;
            }
        }
        if (UpdatedMove == false){                                              // hvis den har kørt ovenstående loop igennem og ikke fundet et match
                                                                                // så betyder det at movet ikke er gemt i forvejen.
            InsertToMove(BoardID, NewMoveToCheck, WinChecker, PlayerID);                     // Så derfor tilføjer vi det
            return;
        }
    }
}
void InsertToTemp(std::string& BoardState,                                      // Funktion til at indsætte data mellem hvert ryk ind i temp
                  std::string& Move,
                  int& Counter,
                  int PlayerId){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.prepare("INSERT INTO Temp "                                           // Indsætter data i Temp
                  "(tempBoard_id, BoardState, Move, PlayerID, WinOrLoss) "
                  "VALUES "
                  "(:tempBoard_id, :BoardState, :Move, :PlayerID, :WinOrLoss)");
    query.bindValue(":tempBoard_id", Counter);
    query.bindValue(":BoardState", QString::fromStdString(BoardState));
    query.bindValue(":Move", QString::fromStdString(Move));
    query.bindValue(":PlayerID", PlayerId);

    query.exec();

    Counter++;                                                                  // Øger counteren med 1 for at holde styr på id'erne
}


void InsertToMove(int& BoardID,                                                 // Funktion til at indsætte et move i Moves
                  std::string& MoveToCheck,
                  double& WinChecker,
                  int& PlayerID){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.prepare("INSERT INTO Moves "                                          // Tilføjer et move til tabellen ud fra inputtet
                  "(board_id, Move, WinRate, WinCases, UseCases, Player) "
                  "VALUES "
                  "(:board_id, :Move, :WinRate, :WinCases, 1, :Player)");
    query.bindValue(":board_id", BoardID);
    query.bindValue(":Move", MoveToCheck.c_str());
    query.bindValue(":WinRate", WinChecker*100);
    query.bindValue(":WinCases", WinChecker);
    query.bindValue(":Player", PlayerID);
    query.exec();
}

void UpdateMoveWinrate(int& BoardID,                                            // Funktion til at opdatere et move i Moves
                       std::string& MoveToCheck,
                       double& WinChecker,
                       int& PlayerID){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    // Opretter variabler
    double WinCases = 0;
    double UseCases = 0;
    double WinRate = 0;

    query.prepare("UPDATE Moves SET "                                           // Opdaterer WinCases og UseCases for det move
                  " WinCases = WinCases + :WinCases,"
                  " UseCases = UseCases + 1 "
                  " WHERE board_id = :board_id "
                  " AND Move = :Move"
                  " AND Player = :Player");
    query.bindValue(":WinCases", WinChecker);
    query.bindValue(":board_id", BoardID);
    query.bindValue(":Move", MoveToCheck.c_str());
    query.bindValue(":Player", PlayerID);
    query.exec();


    query.prepare("SELECT Wincases, UseCases FROM Moves "                       // Finder de opdaterede Wincases og UseCases for det move
                  " WHERE board_id = :board_id AND Move = :Move");
    query.bindValue(":board_id", BoardID);
    query.bindValue(":Move", MoveToCheck.c_str());
    query.exec();

    query.first();
    WinCases = query.value(0).toDouble();
    UseCases = query.value(1).toDouble();

    WinRate = (WinCases/UseCases)*100;                                          // Finder WinRate ud fra WinCases og UseCases

    query.prepare("UPDATE Moves SET "                                           // Opdaterer WinRate for det move med den nye WinRate
                  " WinRate = ROUND(:WinRate,2)"
                  " WHERE board_id = :board_id AND Move = :Move");
    query.bindValue(":WinRate", WinRate);
    query.bindValue(":board_id", BoardID);
    query.bindValue(":Move", MoveToCheck.c_str());
    query.exec();
}

std::string MovePlayer(std::vector<std::vector<std::string>>& BoardState,
                int& PlayerTurn){             // Funktion til at lave et move

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    std::string output;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(BoardState[i][j] == "1 "){
                output += "1";
            } else if(BoardState[i][j] == "B "){
                output += "2";
            } else if(BoardState[i][j] == "BK"){
                output += "3";
            } else if(BoardState[i][j] == "R "){
                output += "4";
            } else if(BoardState[i][j] == "RK"){
                output += "5";
            }
        }
    }

    query.prepare("SELECT count(*)"
                  "FROM UniqueBoard "
                  "WHERE BoardState = :output");
    query.bindValue(":output", QString::fromStdString(output));
    query.exec();
    query.first();
    if (query.value(0).toInt() == 0){
        return "No moves";
    }
    else{
        query.prepare("SELECT board_id "
                      "FROM UniqueBoard "
                      "WHERE BoardState = :output");
        query.bindValue(":output", QString::fromStdString(output));
        query.exec();
        query.first();
        int BoardID = query.value(0).toInt();

        query.exec(" SELECT count(*)"
                   " FROM Moves "
                   " WHERE board_id = " + QString::number(BoardID) + " "
                   " And Player = " + QString::number(PlayerTurn) + " "
                   " ORDER BY WinRate DESC");
        query.first();
        if(query.value(0).toInt() == 0){
            return "No moves";
        }
        else{
            query.exec(" SELECT Move "
                       " FROM Moves "
                       " WHERE board_id = " + QString::number(BoardID) + " "
                       " And Player = " + QString::number(PlayerTurn) + " "
                       " ORDER BY WinRate DESC");
            query.first();
            std::string Move = query.value(0).toString().toStdString();
            return Move;

        }

    }


}
void RefreshTempTable(int& playerTurn){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    //Clear Temp og sætter start board ind
    query.exec("DELETE FROM Temp WHERE tempBoard_id >= 0");
    query.prepare(  "INSERT INTO Temp (tempBoard_id, BoardState, PlayerID) "
                  "VALUES (0, '22222222222211111111444444444444', :StartingPlayer)");
    query.bindValue(":StartingPlayer", playerTurn);
    query.exec();
    return;
}

bool CheckDuplicateMoves(std::string& BoardState, std::string& MoveToCheck, int& PlayerId){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.prepare(" SELECT count(tempboard_id) "                                // Tjekker om trækket allerede er lavet i det her spil
                  " FROM Temp "
                  " WHERE Move = :MoveMade"
                  " AND BoardState = :board"
                  " AND PlayerID = :PlayerId");
    query.bindValue(":MoveMade", QString::fromStdString(MoveToCheck));
    query.bindValue(":board", QString::fromStdString(BoardState));
    query.bindValue(":PlayerId", PlayerId);
    query.exec();

    query.first();
    if (query.value(0).toInt() == 0){
        return true;                                                            // Hvis trækket ikke er lavet i det her spil
    }
    else{
        return false;                                                           // Hvis trækket er lavet i det her spil
    }
}
