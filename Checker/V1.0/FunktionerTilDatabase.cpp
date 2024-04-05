#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include "CheckersDatabase.h"


void AddBoard(std::string& NewBoardState, std::string& OldBoardState, int& TempBoardID){                                                 // Funktion til at indsætte et board i databasen

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.prepare("SELECT count(*) "                                            // Tæller hvor mange gange boardstate er i UniqueBoard
                  "FROM UniqueBoard "                                           // Mulighederne er 0 eller 1 gang
                  "Where BoardState = :BoardState");
    query.bindValue(":BoardState", QString::fromStdString(NewBoardState));
    query.exec();
    query.first();

    if (query.value(0).toInt() == 1){                                           // Hvis boardstate er i UniqueBoard
        AddMove(TempBoardID, OldBoardState);                                                   // Så skal den bare tilføje et move til det boardstate

        return;
    }
    else if (query.value(0).toInt() == 0){                                      // Hvis boardstate ikke er i UniqueBoard
        query.prepare("INSERT INTO UniqueBoard (BoardState) "                   // Så skal den tilføje boardstate til UniqueBoard
                      "VALUES (:BoardState)");
        query.bindValue(":BoardState", QString::fromStdString(NewBoardState));
        query.exec();
        AddMove(TempBoardID, OldBoardState);                                                   // Og derefter tilføje et move til det boardstate

        return;
    }
}

void AddMove(int& TempBoardID, std::string& OldBoardState){                                                 // Funktion til at add move til et boardstate
    // Eller update winrate hvis move allerede er i Moves


    //Laver variabler til at holde data fra databasen
    int BoardID = 0;
    int PlayerID = 0;
    std::string NewMoveToCheck;
    std::vector<std::string> OldMoves;

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    if (OldBoardState == "Start"){                                                      // Hvis det er det første board i spillet
        return;                                                                 // så skal den ikke tilføje et move da den henter movet fra hvordan
    }                                                                           // man kom til det boardstate og der er ikke et move hen til startbrættet

    query.exec("Select PlayerID, Move "                                              // Finder ud af om det move den skal tilføje
               "FROM Temp "                                                     // var et move fra spilleren der vandt ellet tabte
               "WHERE tempBoard_id = " + QString::number(TempBoardID));
    query.first();
    PlayerID = query.value(0).toInt();
    NewMoveToCheck = query.value(1).toString().toStdString();



    query.prepare("SELECT board_id "                                            // Finder board id fra det board som den skal tilføje et move til
                  "FROM UniqueBoard "
                  "WHERE BoardState = :boardState");
    query.bindValue(":boardState", OldBoardState.c_str());
    query.exec();
    query.first();
    BoardID = query.value(0).toInt();

    query.prepare("UPDATE Temp SET oldboard_id = :board_id WHERE tempboard_id = :tempboard_id");
    query.bindValue(":board_id", BoardID);
    query.bindValue(":tempboard_id", TempBoardID);
    query.exec();

    query.exec("SELECT count(Move) "                                            // Tæller hvor mange ryk der er lavet på det boardstate
               "FROM Moves "
               "WHERE board_id = " + QString::number(BoardID));
    query.first();
    int count = query.value(0).toInt();

    if (count == 0){                                                            // Hvis der ikke er nogen moves på det boardstate

        InsertToMove(BoardID, NewMoveToCheck, PlayerID);                         // Så skal den bare tilføje et move
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

                //UpdateMoveWinrate(BoardID, NewMoveToCheck, PlayerID);            // Så skal den opdatere winrate, wincases og usescases for det move
                UpdatedMove = true;                                             // Og sætte UpdatedMove til true så den ikke går ned i nedenstående
                return;
            }
        }
        if (UpdatedMove == false){                                              // hvis den har kørt ovenstående loop igennem og ikke fundet et match
            // så betyder det at movet ikke er gemt i forvejen.
            InsertToMove(BoardID, NewMoveToCheck, PlayerID);                     // Så derfor tilføjer vi det
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
}


void InsertToMove(int& BoardID,                                                 // Funktion til at indsætte et move i Moves
                  std::string& MoveToCheck,
                  int& PlayerID){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.prepare("INSERT INTO Moves "                                          // Tilføjer et move til tabellen ud fra inputtet
                  "(board_id, Move, WinRate, WinCases, UseCases, Player) "
                  "VALUES "
                  "(:board_id, :Move, :WinRate, :WinCases, 0, :Player)");
    query.bindValue(":board_id", BoardID);
    query.bindValue(":Move", MoveToCheck.c_str());
    query.bindValue(":WinRate", 50);
    query.bindValue(":WinCases", 0);
    query.bindValue(":Player", PlayerID);
    query.exec();
}

void UpdateMoveWinrate(int& AmountOfMoves){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    // Opretter variabler
    double WinChecker = 0;
    int PlayerID = 0;
    std::string NewMoveToCheck;
    int OldBoardID = 0;
    double WinCases = 0;
    double UseCases = 0;
    double WinRate = 0;

                                                        // var et move fra spilleren der vandt ellet tabte
    for (int i = 1; i < AmountOfMoves; ++i){
        query.prepare("Select WinOrLoss, PlayerID, Move, oldboard_id "                                              // Finder ud af om det move den skal tilføje
                   "FROM Temp "
                   "WHERE tempBoard_id = :tempBoard_id");
        query.bindValue(":tempBoard_id", i);
        query.exec();
        query.first();
        WinChecker = query.value(0).toDouble();
        PlayerID = query.value(1).toInt();
        NewMoveToCheck = query.value(2).toString().toStdString();
        OldBoardID = query.value(3).toInt();

        query.prepare("UPDATE Moves SET "                                           // Opdaterer WinCases og UseCases for det move
                      " WinCases = WinCases + :WinCases,"
                      " UseCases = UseCases + 1, "
                      " WinRate = (WinCases/UseCases)*100"
                      " WHERE board_id = :board_id "
                      " AND Move = :Move"
                      " AND Player = :Player");
        query.bindValue(":WinCases", WinChecker);
        query.bindValue(":board_id", OldBoardID);
        query.bindValue(":Move", NewMoveToCheck.c_str());
        query.bindValue(":Player", PlayerID);
        query.exec();
    }
}

std::string MovePlayer(std::string& BoardState,
                       int& PlayerTurn){             // Funktion til at lave et move

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);


    query.prepare("SELECT count(*)"
                  "FROM UniqueBoard "
                  "WHERE BoardState = :output");
    query.bindValue(":output", QString::fromStdString(BoardState));
    query.exec();
    query.first();
    if (query.value(0).toInt() == 0){
        return "No moves";
    }
    else{
        query.prepare("SELECT board_id "
                      "FROM UniqueBoard "
                      "WHERE BoardState = :output");
        query.bindValue(":output", QString::fromStdString(BoardState));
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
