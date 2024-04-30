#include "CheckersDatabase.h"

//////////////////////////////////////////////// Main databasen ///////////////////////////////////////////////////////////////////
void InsertMove(int board_id, QString Move, int PlayerID, float WinOrLoss){
    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);

    if (PlayerID == 1){
        query.prepare(  " INSERT INTO MovesP1"
                      " (board_id, Move, WinRate, WinCases, UseCases) "
                      " VALUES "
                      " (:board_id, :Move, :WinRate, :WinCases, 1)");
        query.bindValue(":board_id", board_id);
        query.bindValue(":Move", Move);
        query.bindValue(":WinRate", 50);        // Skal sættes til WinOrLoss * 100
        query.bindValue(":WinCases", 0.5);      // Skal sættes til WinOrLoss
        query.exec();
    }
    else if (PlayerID == 2){
        query.prepare(  " INSERT INTO MovesP2"
                      " (board_id, Move, WinRate, WinCases, UseCases) "
                      " VALUES "
                      " (:board_id, :Move, :WinRate, :WinCases, 1)");
        query.bindValue(":board_id", board_id);
        query.bindValue(":Move", Move);
        query.bindValue(":WinRate", 50);        // Skal sættes til WinOrLoss * 100
        query.bindValue(":WinCases", 0.5);      // Skal sættes til WinOrLoss
        query.exec();
    }
}

void HandleNewMoves(QString Move, int PlayerID, float WinOrLoss, int BoardID){
    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);

    if (PlayerID == 1){

        query.exec( " select Move "
                   " from MovesP1 "
                   " where board_id = " + QString::number(BoardID) );
        while (query.next()) {
            if (Move == query.value(0).toString()){
                UpdateMoveWinRate(Move, BoardID, WinOrLoss, PlayerID);
                return;
            }
        }
        InsertMove(BoardID, Move, PlayerID, WinOrLoss);
    }
    else if (PlayerID == 2){
        query.exec( " select Move "
                   " from MovesP2 "
                   " where board_id = " + QString::number(BoardID) );
        while (query.next()) {
            if (Move == query.value(0).toString()){
                UpdateMoveWinRate(Move, BoardID, WinOrLoss, PlayerID);
                return;
            }
        }
        InsertMove(BoardID, Move, PlayerID, WinOrLoss);
    }
}

void UploadTempToDatabase(int& UniqueBoardIDCounter, bool Toggle){

    if (Toggle == false){
        return;
    }
    else {
        QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
        QSqlQuery query = QSqlQuery(db);


        query.exec(" select UniqueBoard.board_id, Temp.tempBoard_id"     // Her finder vi alle de bræt der ikke er nye
                   " from Temp "
                   " left JOIN UniqueBoard "
                   " ON UniqueBoard.BoardState = Temp.BoardState"
                   " where UniqueBoard.BoardState IS NOT NULL;");                               // Her finder vi alle de bræt der er i uniqueboard ved at finde de bræt der ikke er lig null i boardstate efter join

        while (query.next()) {
            int BoardID = query.value(0).toInt();
            int TempBoardID = query.value(0).toInt();
            InserNewMoveToOldBoard(BoardID,TempBoardID);                                // Indsætter de nye træk i de gamle brætter

        }

        query.exec(" select Temp.tempBoard_id, Temp.BoardState"  // Her der finder vi alle de bræt der er nye
                   " from Temp "
                   " left JOIN UniqueBoard "
                   " ON UniqueBoard.BoardState = Temp.BoardState"
                   " where UniqueBoard.BoardState IS NULL");                           // Her finder vi alle de bræt der ikke er i uniqueboard ved at finde de bræt der er lig null i boardstate efter join
        while (query.next()) {
            int TempBoardID = query.value(0).toInt();
            QString BoardState = query.value(1).toString();
                                                                                        // Da dette er alle de nye ikke tjekkes for noget men bare indsættes
            InsertBoardToDatabase(BoardState);                                          // Indsætter brættet i uniqueboard

            InsertNewMoveToNewBoard(TempBoardID,UniqueBoardIDCounter);                         // Indsætter no moves i movesP1

            UniqueBoardIDCounter++;
        }
        return;
    }
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

void InsertNewMoveToNewBoard(int& TempBoardID, int& BoardID){    // funktion til at indsætte træk i MovesP1

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);


    query.prepare("select Move, PlayerID, WinOrLoss "
                  "from TempMoves "
                  "where tempBoard_id = :tempBoard_id");
    query.bindValue(":tempBoard_id", TempBoardID);
    query.exec();

    while (query.next()) {
        QString Move = query.value(0).toString();
        int PlayerID = query.value(1).toInt();
        float WinOrLoss = query.value(2).toDouble();

        if (PlayerID == 1){                                                         // Indsætter trækket i den rigtige spillers tabel
            InsertMove(BoardID, Move, PlayerID, WinOrLoss);

        }
        else if (PlayerID == 2){
            InsertMove(BoardID, Move, PlayerID, WinOrLoss);

        }
    }
}

void InserNewMoveToOldBoard(int& BoardID, int& TempBoardID){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);


    query.exec("select Move, PlayerID, WinOrLoss "
               "from TempMoves "
               "where tempBoard_id = " + QString::number(TempBoardID));
    while (query.next()) {
        HandleNewMoves(query.value(0).toString(), query.value(1).toInt(), query.value(2).toFloat(),BoardID);
    }
}



void UpdateMoveWinRate(QString& Move, int& BoardID, float& WinOrLoss, int& PlayerId){  // funktion til at opdatere træk i MovesP1 eller MovesP2

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);
    /*
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
    }*/

    if (PlayerId == 1){
        query.prepare(" UPDATE MovesP1"
                      " SET "
                      " UseCases = UseCases + 1,"
                      " WinRate = WinRate - 1"
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
                      " UseCases = UseCases + 1,"
                      " WinRate = WinRate - 1"
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

    bool DuplicateBoard = false;
    bool DuplicateMove = false;
    int BoardID;
    QString BoardStateFromTemp;

    query.exec("Select * from Temp");
    while (query.next()) {
        BoardStateFromTemp = query.value(1).toString();
        if (BoardStateFromTemp == BoardState.c_str()){
            DuplicateBoard = true;
            BoardID = query.value(0).toInt();
            break;
        }
    }
    if (DuplicateBoard == true){
        query.prepare("Select Move "
                   "from TempMoves "
                   "where tempBoard_id = :tempBoard_id");
        query.bindValue(":tempBoard_id", BoardID);
        if (!query.exec()){

            query.prepare("INSERT INTO TempMoves "
                          "(tempBoard_id, Move, PlayerID) "
                          "VALUES "
                          "(:tempBoard_id, :Move, :PlayerID)");
            query.bindValue(":tempBoard_id", BoardID);
            query.bindValue(":Move", QString::fromStdString(Move));
            query.bindValue(":PlayerID", PlayerId);
            query.exec();
        }
        else{
            while (query.next()) {
                if (query.value(0).toString().toStdString() == Move){
                    DuplicateMove = true;
                }
            }
        }


        if (DuplicateMove == true){
            return;
        }
        else{
            query.prepare("INSERT INTO TempMoves "
                          "(tempBoard_id, Move, PlayerID) "
                          "VALUES "
                          "(:tempBoard_id, :Move, :PlayerID)");
            query.bindValue(":tempBoard_id", BoardID);
            query.bindValue(":Move", QString::fromStdString(Move));
            query.bindValue(":PlayerID", PlayerId);
            query.exec();
        }

    }
    else{
        query.prepare(  " INSERT INTO Temp "                                           // Indsætter data i Temp
                      " (tempBoard_id, BoardState) "
                      " VALUES "
                      " (:tempBoard_id, :BoardState)");
        query.bindValue(":tempBoard_id", Counter);
        query.bindValue(":BoardState", QString::fromStdString(BoardState));

        query.exec();

        query.prepare("INSERT INTO TempMoves "
                      "(tempBoard_id, Move, PlayerID) "
                      "VALUES "
                      "(:tempBoard_id, :Move, :PlayerID)");
        query.bindValue(":tempBoard_id", Counter);
        query.bindValue(":Move", QString::fromStdString(Move));
        query.bindValue(":PlayerID", PlayerId);
        query.exec();
        Counter++;

    }


}

void RefreshTempTable(){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    //Clear Temp
    query.exec("DELETE FROM Temp WHERE tempBoard_id >= 0");
    query.exec("DELETE FROM TempMoves WHERE tempBoard_id >= 0");

    return;
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
    InsertToTemp(*outputPtr, *MoveMadePtr, CounterForTempTable, tempPlayer);  // Indsætter rykket hvis det ikke er en kopi af et move den allerede har lavet i spillet

}




///////////////////////////////////////////////// Ting til simu //////////////////////////////////////////////////////

void LoadSimVectors(std::vector<int>& Player1SimChoise,std::vector<int>& Player2SimChoise){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.exec("select MoveChoise from SimMovesP1");
    while (query.next()) {
        Player1SimChoise.push_back(query.value(0).toInt());
    }

    query.exec("select MoveChoise from SimMovesP2");
    while (query.next()) {
        Player2SimChoise.push_back(query.value(0).toInt());
    }
}

void IncreaseSimu(const int& drawChecker, bool &AlreadyIncreased, std::vector<int> &Player1SimChoise){


    if(AlreadyIncreased == true){
        return;
    }
    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.prepare("UPDATE SimMovesP1 set MoveChoise = MoveChoise+1 WHERE MoveDepth = :GameDepth");
    query.bindValue(":GameDepth", drawChecker);
    query.exec();
    query.prepare("UPDATE SimMovesP1 set MoveChoise = 0 WHERE MoveDepth > :GameDepth");
    query.bindValue(":GameDepth", drawChecker);
    query.exec();

    Player1SimChoise.clear();

    query.exec("select MoveChoise from SimMovesP1");
    while (query.next()) {
        Player1SimChoise.push_back(query.value(0).toInt());
    }

    AlreadyIncreased = true;

}

void IncreaseOponentSimu(const int& drawChecker, std::vector<int> &Player2SimChoise){
    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);


    query.prepare("UPDATE SimMovesP2 set MoveChoise = MoveChoise+1 WHERE MoveDepth = :GameDepth");
    query.bindValue(":GameDepth", drawChecker+2);
    query.exec();
    query.prepare("UPDATE SimMovesP2 set MoveChoise = 0 WHERE MoveDepth < :GameDepth");
    query.bindValue(":GameDepth", drawChecker+2);
    query.exec();

    Player2SimChoise.clear();

    query.exec("select MoveChoise from SimMovesP2");
    while (query.next()) {
        Player2SimChoise.push_back(query.value(0).toInt());
    }

}



void DeleteWrongMove(std::vector<std::vector<std::string>>& tempBoard, std::string& MoveMade, int& tempPlayer){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

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

    query.prepare("Select board_id from UniqueBoard where BoardState = :BoardState");
    query.bindValue(":BoardState",QString::fromStdString(output));
    query.exec();
    query.first();
    int board_id = query.value(0).toInt();

    if (tempPlayer == 1){
        query.prepare("DELETE FROM MovesP1 WHERE board_id = :board_id AND Move = :Move");
        query.bindValue(":board_id", board_id);
        query.bindValue(":Move", QString::fromStdString(MoveMade));
        query.exec();
    }
    else if (tempPlayer == 2){
        query.prepare("DELETE FROM MovesP2 WHERE board_id = :board_id AND Move = :Move");
        query.bindValue(":board_id", board_id);
        query.bindValue(":Move", QString::fromStdString(MoveMade));
        query.exec();
    }

}


