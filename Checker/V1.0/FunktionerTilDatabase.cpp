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
    std::string MoveToCheck;
    std::string BoardState;
    std::vector<std::string> OldMoves;

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    if (TempBoardID == 0){                                                      // Hvis det er det første board i spillet
        return;                                                                 // så skal den ikke tilføje et move da den henter movet fra hvordan
    }                                                                           // man kom til det boardstate og der er ikke et move hen til startbrættet

    query.exec("Select WinOrLoss "                                              // Finder ud af om det move den skal tilføje
               "FROM Temp "                                                     // var et move fra spilleren der vandt ellet tabte
               "WHERE tempBoard_id = " + QString::number(TempBoardID));
    query.first();
    WinChecker = query.value(0).toDouble();


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
    MoveToCheck = query.value(0).toString().toStdString();


    query.exec("SELECT count(Move) "                                            // Tæller hvor mange ryk der er lavet på det boardstate
               "FROM Moves "
               "WHERE board_id = " + QString::number(BoardID));
    query.first();
    int count = query.value(0).toInt();

    if (count == 0){                                                            // Hvis der ikke er nogen moves på det boardstate

        InsertToMove(BoardID, MoveToCheck, WinChecker);                         // Så skal den bare tilføje et move
        return;
    }
    else{                                                                       // Hvis der er moves på det boardstate

        std::string Move;
        bool UpdatedMove = false;

        query.exec("SELECT Move "                                               // Så skal den kigge på alle moves på det boardstate
                   "FROM Moves "
                   "WHERE board_id = " + QString::number(BoardID));
        while (query.next()) {                                                  // Her kører den igennem alle moves på det boardstate
            Move = query.value(0).toString().toStdString();

            if (Move == MoveToCheck){                                           // Hvis det move der skal tilføjes allerede er i Moves

                UpdateMoveWinrate(BoardID, MoveToCheck, WinChecker);            // Så skal den opdatere winrate, wincases og usescases for det move
                UpdatedMove = true;                                             // Og sætte UpdatedMove til true så den ikke går ned i nedenstående
                return;
            }
        }
        if (UpdatedMove == false){                                              // hvis den har kørt ovenstående loop igennem og ikke fundet et match
                                                                                // så betyder det at movet ikke er gemt i forvejen.
            InsertToMove(BoardID, MoveToCheck, WinChecker);                     // Så derfor tilføjer vi det
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
                  double& WinChecker){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.prepare("INSERT INTO Moves "                                          // Tilføjer et move til tabellen ud fra inputtet
                  "(board_id, Move, WinRate, WinCases, UseCases) "
                  "VALUES "
                  "(:board_id, :Move, :WinRate, :WinCases, 1)");
    query.bindValue(":board_id", BoardID);
    query.bindValue(":Move", MoveToCheck.c_str());
    query.bindValue(":WinRate", WinChecker*100);
    query.bindValue(":WinCases", WinChecker);
    query.exec();
}

void UpdateMoveWinrate(int& BoardID,                                            // Funktion til at opdatere et move i Moves
                       std::string& MoveToCheck,
                       double& WinChecker){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    // Opretter variabler
    double WinCases = 0;
    double UseCases = 0;
    double WinRate = 0;

    query.prepare("UPDATE Moves SET "                                           // Opdaterer WinCases og UseCases for det move
                  " WinCases = WinCases + :WinCases,"
                  " UseCases = UseCases + 1 "
                  " WHERE board_id = :board_id AND Move = :Move");
    query.bindValue(":WinCases", WinChecker);
    query.bindValue(":board_id", BoardID);
    query.bindValue(":Move", MoveToCheck.c_str());
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


void RefreshTemp(int& playerTurn){                                              // Funktion til at slette Temp og indsætte start board i Temp

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);


    query.exec("DELETE FROM Temp "                                              // Sletter alle rækker i Temp
               "WHERE tempBoard_id >= 0");
    query.prepare(  "INSERT INTO Temp "                                         // Indsætter start board i Temp
                  "(tempBoard_id, BoardState, PlayerID) "
                  "VALUES "
                  "(0, '22222222222211111111444444444444', :StartingPlayer)");
    query.bindValue(":StartingPlayer", playerTurn);
    query.exec();
}
