#include "checkersdatabase.h"

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
        query.bindValue(":WinRate", WinOrLoss * 100);        // Skal sættes til WinOrLoss * 100
        query.bindValue(":WinCases", WinOrLoss);      // Skal sættes til WinOrLoss
        query.exec();
    }
    else if (PlayerID == 2){
        query.prepare(  " INSERT INTO MovesP2"
                      " (board_id, Move, WinRate, WinCases, UseCases) "
                      " VALUES "
                      " (:board_id, :Move, :WinRate, :WinCases, 1)");
        query.bindValue(":board_id", board_id);
        query.bindValue(":Move", Move);
        query.bindValue(":WinRate", WinOrLoss * 100);        // Skal sættes til WinOrLoss * 100
        query.bindValue(":WinCases", WinOrLoss);      // Skal sættes til WinOrLoss
        query.exec();
    }
}

void HandleNewMoves(QString Move, int PlayerID, float WinOrLoss, int BoardID){
    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);

    if (PlayerID == 1){

        query.prepare( " select Move "
                      " from MovesP1 "
                      " where board_id = :board_id "
                      " and Move = :Move");
        query.bindValue(":board_id", BoardID);
        query.bindValue(":Move", Move);
        query.exec();
        if (query.first()){
            UpdateMoveWinRate(Move, BoardID, WinOrLoss, PlayerID);
            return;
        }
        else{
            InsertMove(BoardID, Move, PlayerID, WinOrLoss);
        }
    }
    else if (PlayerID == 2){
        query.prepare(  " select Move "
                      " from MovesP2 "
                      " where board_id = :board_id "
                      " and Move = :Move");
        query.bindValue(":board_id", BoardID);
        query.bindValue(":Move", Move);
        query.exec();
        if (query.first()){
            UpdateMoveWinRate(Move, BoardID, WinOrLoss, PlayerID);
            return;
        }
        else{
            InsertMove(BoardID, Move, PlayerID, WinOrLoss);
        }
    }
}

void UploadTempToDatabase(int& UniqueBoardIDCounter, bool Toggle){

    if (Toggle == false){
        return;
    }
    else {
        QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
        QSqlQuery query = QSqlQuery(db);

        query.exec(" select board_id, BoardState "
                   " from UniqueBoard "
                   " where BoardState in (select BoardState from Temp)");
        while (query.next()) {
            int BoardID = query.value(0).toInt();
            QString BoardState = query.value(1).toString();
            InserNewMoveToOldBoard(BoardID,BoardState);                                // Indsætter de nye træk i de gamle brætter

        }
        query.exec(" Select tempBoard_id, BoardState "
                   " from Temp "
                   " where BoardState not in (select BoardState from UniqueBoard)");
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


    query.prepare(  "select Move, PlayerID, WinOrLoss "
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

void InserNewMoveToOldBoard(int& BoardID, QString& BoardState){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);

    query.prepare(  "select tempBoard_id "
                  "from Temp "
                  "where BoardState = :BoardState");
    query.bindValue(":BoardState", BoardState);
    query.exec();
    query.first();
    int TempBoardID = query.value(0).toInt();
    query.prepare(  "select Move, PlayerID, WinOrLoss "
                  "from TempMoves "
                  "where tempBoard_id = :tempBoard_id");
    query.bindValue(":tempBoard_id", TempBoardID);
    query.exec();
    while (query.next()) {
        HandleNewMoves(query.value(0).toString(), query.value(1).toInt(), query.value(2).toFloat(),BoardID);
    }
}



void UpdateMoveWinRate(QString& Move, int& BoardID, float& WinOrLoss, int& PlayerId){  // funktion til at opdatere træk i MovesP1 eller MovesP2

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");
    QSqlQuery query = QSqlQuery(db);

    if (PlayerId == 1){
        query.prepare(" UPDATE MovesP1 "
                      " SET "
                      " WinCases = WinCases + :WinCases, "
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
        query.prepare(" UPDATE MovesP2 "
                      " SET "
                      " WinCases = WinCases + :WinCases, "
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

    query.prepare("SELECT board_id "                        // Hvis databasen kender brættet så skal den finde det rigtige board_id
                  "FROM UniqueBoard "
                  "WHERE BoardState = :BoardState");
    query.bindValue(":BoardState", QBoardState);
    query.exec();
    if (!query.first()){
        return "No moves";                                      // Hvis databasen ikke kender brættet så skal den returnere no moves
    }
    else{
        query.first();
        int BoardID = query.value(0).toInt();


        if (PlayerTurn == 1){                                   // Vælger den rigtige tabel ud fra hvilken spiller der skal trækkes for
            PlayersMoveDB = "MovesP1";
        }
        else if (PlayerTurn == 2){
            PlayersMoveDB = "MovesP2";
        }

        query.prepare(" SELECT Move, WinRate"                        // Finder det bedste move og returnere det
                      " FROM "+ PlayersMoveDB +
                      " WHERE board_id = " + QString::number(BoardID) + " "
                                                                        " ORDER BY WinRate DESC");
        query.exec();
        if(!query.first()){
            return "No moves";
        }
        else{

            query.first();
            std::string Move = query.value(0).toString().toStdString();
            int WinRate = query.value(1).toInt();
            if (WinRate < 15){
                return "No moves";
            }
            else{
                return Move;
            }
        }
    }
}

////////////////////////////////////////// Temp ting//////////////////////////////////////////////////////////////////////////////

void InsertToTemp(std::string& BoardState,std::string& Move,int& Counter,int PlayerId){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    QString QBoardState = QString::fromStdString(BoardState);
    QString QMove = QString::fromStdString(Move);
    int BoardID;

    query.prepare("Select tempBoard_id from Temp where BoardState = :BoardState");
    query.bindValue(":BoardState", QBoardState);
    query.exec();
    if (query.first()){
        BoardID = query.value(0).toInt();
        query.prepare(  "Select Move "
                      "from TempMoves "
                      "where tempBoard_id = :tempBoard_id "
                      "and Move = :Move");
        query.bindValue(":tempBoard_id", BoardID);
        query.bindValue(":Move", QMove);
        query.exec();
        if (!query.first()){

            query.prepare("INSERT INTO TempMoves "
                          "(tempBoard_id, Move, PlayerID) "
                          "VALUES "
                          "(:tempBoard_id, :Move, :PlayerID)");
            query.bindValue(":tempBoard_id", BoardID);
            query.bindValue(":Move", QMove);
            query.bindValue(":PlayerID", PlayerId);
            query.exec();
        }
        else{
            return;
        }
    }
    else{
        query.prepare(  " INSERT INTO Temp "                                           // Indsætter data i Temp
                      " (BoardState) "
                      " VALUES "
                      " (:BoardState)");
        query.bindValue(":BoardState", QBoardState);
        query.exec();

        query.prepare("Select tempBoard_id "
                      "from Temp "
                      "where BoardState = :BoardState");
        query.bindValue(":BoardState", QBoardState);
        query.exec();
        query.first();
        BoardID = query.value(0).toInt();
        query.prepare("INSERT INTO TempMoves "
                      "(tempBoard_id, Move, PlayerID) "
                      "VALUES "
                      "(:tempBoard_id, :Move, :PlayerID)");
        query.bindValue(":tempBoard_id", BoardID);
        query.bindValue(":Move", QMove);
        query.bindValue(":PlayerID", PlayerId);
        query.exec();
    }
}

void RefreshTempTable(){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    //Clear Temp
    query.exec("DELETE FROM Temp WHERE tempBoard_id >= 0");
    query.exec("DELETE FROM TempMoves WHERE tempBoard_id >= 0");
    query.exec("ALTER TABLE Temp AUTO_INCREMENT = 1");


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



