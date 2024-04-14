#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include "CheckersDatabase.h"


//////////////////////////////////////////////// Main databasen ///////////////////////////////////////////////////////////////////
void UploadTempToDatabase(int& UniqueBoardIDCounter){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.exec(" select Temp.BoardState, Temp.Move, Temp.PlayerID, Temp.WinOrLoss"  // Her der finder vi alle de bræt der er nye
               " from Temp "
               " left JOIN UniqueBoard "
               " ON UniqueBoard.BoardState = Temp.BoardState"
               " where UniqueBoard.BoardState IS NULL;");                           // Her finder vi alle de bræt der ikke er i uniqueboard ved at finde de bræt der er lig null i boardstate efter join
    while (query.next()) {
        QString BoardState = query.value(0).toString();
        QString Move = query.value(1).toString();
        int PlayerID = query.value(2).toInt();
        double WinOrLoss = query.value(3).toDouble();
                                                                                    // Da dette er alle de nye ikke tjekkes for noget men bare indsættes
        InsertBoardToDatabase(BoardState);                                          // Indsætter brættet i uniqueboard

        if (PlayerID == 1){                                                         // Indsætter trækket i den rigtige spillers tabel
            InsertMoveToP1Database(Move, UniqueBoardIDCounter,WinOrLoss);
            UniqueBoardIDCounter++;
        }
        else if (PlayerID == 2){
            InsertMoveToP2Database(Move,UniqueBoardIDCounter,WinOrLoss);
            UniqueBoardIDCounter++;
        }

    }




    query.exec(" select UniqueBoard.board_id, Temp.Move, Temp.PlayerID, Temp.WinOrLoss"     // Her finder vi alle de bræt der ikke er nye
               " from Temp "
               " left JOIN UniqueBoard "
               " ON UniqueBoard.BoardState = Temp.BoardState"
               " where UniqueBoard.BoardState IS NOT NULL;");                               // Her finder vi alle de bræt der er i uniqueboard ved at finde de bræt der ikke er lig null i boardstate efter join

    while (query.next()) {
        int BoardID = query.value(0).toInt();
        QString Move = query.value(1).toString();
        int PlayerID = query.value(2).toInt();
        double WinOrLoss = query.value(3).toDouble();

                                                                                            // Da dette er kendte boards skal de ikke indsættes
                                                                                            // men der skal tjekkes om rykket skal opdateres hvis det er gammelt eller sættes ind hvis det er nyt

        if (PlayerID == 1){
            query.prepare(" SELECT Move "                                                   // Vælger alle moves den valgte player har lavet på det valgte board
                          " FROM MovesP1 "
                          " WHERE board_id = :board_id");
            query.bindValue(":board_id", BoardID);
            query.exec();
            bool MoveExists = false;
            while (query.next()) {
                if (query.value(0).toString() == Move){                                     // Tjekker om det nye move allerede er lavet
                    MoveExists = true;
                }
            }
            if (MoveExists == false){
                InsertMoveToP1Database(Move,BoardID,WinOrLoss);                             // Indsætter move hvis det ikke er lavet før
            }
            else{
                // Skal kommenteres ind når den skal trænes
                //UpdateMoveWinRate(Move,BoardID,WinOrLoss,PlayerID);                       // Opdaterer move hvis det er lavet før
            }

        }



        else if (PlayerID == 2){                                                            // Samme som ovenstående bare for player 2
            query.prepare(" SELECT Move "
                          " FROM MovesP2 "
                          " WHERE board_id = :board_id");
            query.bindValue(":board_id", BoardID);
            query.exec();
            bool MoveExists = false;
            while (query.next()) {
                if (query.value(0).toString() == Move){
                    MoveExists = true;
                }
            }
            if (MoveExists == false){
                InsertMoveToP2Database(Move,BoardID,WinOrLoss);
            }
            else{
                // Skal kommenteres ind når den skal trænes
                //UpdateMoveWinRate(Move,BoardID,WinOrLoss,PlayerID);
            }


        }

    }


    return;
}

void InsertBoardToDatabase(QString& BoardState){                                // funktion til at indsætte bræt i uniqueboard

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.prepare(" INSERT INTO UniqueBoard "
                  " (BoardState) "
                  " VALUES "
                  " (:BoardState)");
    query.bindValue(":BoardState", BoardState);
    query.exec();
    return;
}
void InsertMoveToP1Database(QString& Move, int& BoardID, double& WinOrLoss){    // funktion til at indsætte træk i MovesP1

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);

    query.prepare(  " INSERT INTO MovesP1"
                  " (board_id, Move, WinRate, WinCases, UseCases) "
                  " VALUES "
                  " (:board_id, :Move, :WinRate, :WinCases, 1)");
    query.bindValue(":board_id", BoardID);
    query.bindValue(":Move", Move);
    query.bindValue(":WinRate", 50);        // Skal sættes til WinOrLoss * 100
    query.bindValue(":WinCases", 0.5);      // Skal sættes til WinOrLoss
    query.exec();
}
void InsertMoveToP2Database(QString& Move, int& BoardID, double& WinOrLoss){    // funktion til at indsætte træk i MovesP2

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);

    query.prepare(  " INSERT INTO MovesP2"
                  " (board_id, Move, WinRate, WinCases, UseCases) "
                  " VALUES "
                  " (:board_id, :Move, :WinRate, :WinCases, 1)");
    query.bindValue(":board_id", BoardID);
    query.bindValue(":Move", Move);
    query.bindValue(":WinRate", 50);        // Skal sættes til WinOrLoss * 100
    query.bindValue(":WinCases", 0.5);      // Skal sættes til WinOrLoss
    query.exec();
}
void UpdateMoveWinRate(QString& Move, int& BoardID, double& WinOrLoss, int& PlayerId){  // funktion til at opdatere træk i MovesP1 eller MovesP2

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);

    if (PlayerId == 1){
        query.prepare(" UPDATE MovesP1"
                      " SET "
                      " WinCases = WinCases + :WinCases,"
                      " UseCases = UseCases + 1, "
                      " WinRate = (WinCases/UseCases)*100"
                      " WHERE board_id = :board_id "
                      " AND Move = :Move");
        query.bindValue(":WinCases", WinOrLoss);
        query.bindValue(":board_id", BoardID);
        query.bindValue(":Move", Move);
        query.exec();
    }
    else if (PlayerId == 2){
        query.prepare(" UPDATE MovesP2"
                      " SET "
                      " WinCases = WinCases + :WinCases,"
                      " UseCases = UseCases + 1, "
                      " WinRate = (WinCases/UseCases)*100"
                      " WHERE board_id = :board_id "
                      " AND Move = :Move");
        query.bindValue(":WinCases", WinOrLoss);
        query.bindValue(":board_id", BoardID);
        query.bindValue(":Move", Move);
        query.exec();
    }


}






std::string MovePlayer(std::string& BoardState,int& PlayerTurn){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);

    QString PlayersMoveDB;


    QString QBoardState = QString::fromStdString(BoardState);

    query.prepare(  " SELECT count(*)"                          // Tjekker om databasen kender brættet der er givet
                    " FROM UniqueBoard "
                    " WHERE BoardState = :BoardState");
    query.bindValue(":BoardState", QBoardState);
    query.exec();
    query.first();
    if (query.value(0).toInt() == 0){
        return "No moves";                                      // Hvis databasen ikke kender brættet så skal den returnere no moves
    }
    else{
        query.prepare("SELECT board_id "                        // Hvis databasen kender brættet så skal den finde det rigtige board_id
                      "FROM UniqueBoard "
                      "WHERE BoardState = :BoardState");
        query.bindValue(":BoardState", QBoardState);
        query.exec();
        query.first();
        int BoardID = query.value(0).toInt();


        if (PlayerTurn == 1){                                   // Vælger den rigtige tabel ud fra hvilken spiller der skal trækkes for
            PlayersMoveDB = "MovesP1";
        }
        else if (PlayerTurn == 2){
            PlayersMoveDB = "MovesP2";
        }

        // Den her der tjekker om et move er der skal måske slettes da der ikke burde være en situation hvor et move ikke er der
        query.prepare(" SELECT count(*)"
                   " FROM " + PlayersMoveDB +
                   " WHERE board_id = " + QString::number(BoardID) + " "
                   " ORDER BY WinRate DESC");
        query.exec();
        query.first();
        if(query.value(0).toInt() == 0){
            return "No moves";
        }
        else{
            query.prepare(" SELECT Move"                        // Finder det bedste move og returnere det
                       " FROM "+ PlayersMoveDB +
                       " WHERE board_id = " + QString::number(BoardID) + " "
                       " ORDER BY WinRate DESC");
            query.exec();
            query.first();
            std::string Move = query.value(0).toString().toStdString();
            return Move;
        }

    }


}












////////////////////////////////////////// Temp ting//////////////////////////////////////////////////////////////////////////////

void InsertToTemp(std::string& BoardState,std::string& Move,int& Counter,int PlayerId){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.prepare(  " INSERT INTO Temp "                                           // Indsætter data i Temp
                  " (tempBoard_id, BoardState, Move, PlayerID, WinOrLoss) "
                  " VALUES "
                  " (:tempBoard_id, :BoardState, :Move, :PlayerID, :WinOrLoss)");
    query.bindValue(":tempBoard_id", Counter);
    query.bindValue(":BoardState", QString::fromStdString(BoardState));
    query.bindValue(":Move", QString::fromStdString(Move));
    query.bindValue(":PlayerID", PlayerId);

    query.exec();
    Counter++;
}





void RefreshTempTable(int& playerTurn){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    //Clear Temp og sætter start board ind
    query.exec("DELETE FROM Temp WHERE tempBoard_id >= 0");

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



void insertAlphaBetaToTemp(std::vector<std::vector<std::string>>& tempBoard, std::string& MoveMade, int& tempPlayer, int& CounterForTempTable){
    std::string output;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(tempBoard[i][j] == "1 "){
                output += "1";
            } else if(tempBoard[i][j] == "B "){
                output += "2";
            } else if(tempBoard[i][j] == "BK"){
                output += "3";
            } else if(tempBoard[i][j] == "R "){
                output += "4";
            } else if(tempBoard[i][j] == "RK"){
                output += "5";
            }
        }
    }

    std::string* outputPtr = &output;
    std::string* MoveMadePtr = &MoveMade;


    if (CheckDuplicateMoves(output, MoveMade, tempPlayer)){
        InsertToTemp(*outputPtr, *MoveMadePtr, CounterForTempTable, tempPlayer);  // Indsætter rykket hvis det ikke er en kopi af et move den allerede har lavet i spillet
    }
}

