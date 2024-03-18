#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>


int main()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("IndsætDatabase navn");
    db.setUserName("INDSÆT navn");  // Change to username
    db.setPassword("Indsæt password!");  // Change to password
    db.open();

    QSqlQuery query;

    //query.exec("ALTER TABLE UniqueBoard ADD BoardState CHAR(255)");

    //query.exec("ALTER TABLE UniqueBoard DROP COLUMN description");

    //query.exec("ALTER TABLE UniqueBoard RENAME COLUMN task_id to board_id");

    query.exec("SELECT * FROM UniqueBoard");
    while (query.next()) {
        int BoardID = query.value(0).toInt();
        QString BoardState = query.value(1).toString();
        qDebug() << "BoardID:" << BoardID << "BoardState:" << BoardState;
    }



    std::string str2;
    std::cout << "What is the boardstate u want to save";
    std::cin >> str2;

    std::vector<std::string> OldBoardState;
    OldBoardState.clear();

    query.exec("SELECT BoardState FROM UniqueBoard");
    while (query.next()) {
        std::string BoardState = query.value(0).toString().toStdString();
        OldBoardState.push_back(BoardState);
    }


    if (OldBoardState.size() == 0){
        int newBoardID = OldBoardState.size()+1;
        query.prepare("INSERT INTO UniqueBoard ( board_id, BoardState) "
                      "VALUES (:board_id, :BoardState)");
        query.bindValue(":board_id", newBoardID);
        query.bindValue(":BoardState", str2.c_str());
        query.exec();
    }
    else{
        for (int i = 0; i <= OldBoardState.size(); i++) {
            if (str2 == OldBoardState[i].c_str()) {
                std::cout << "BoardState is already stored" << std::endl << std::endl;
                return 1;

            }

            else if (i == OldBoardState.size()){
                int newBoardID = OldBoardState.size()+1;
                query.prepare("INSERT INTO UniqueBoard ( board_id, BoardState) "
                              "VALUES (:board_id, :BoardState)");
                query.bindValue(":board_id", newBoardID);
                query.bindValue(":BoardState", str2.c_str());
                query.exec();
            }
        }
    }

    query.exec("SELECT * FROM UniqueBoard");
    while (query.next()) {
        int BoardID = query.value(0).toInt();
        QString BoardState = query.value(1).toString();
        qDebug() << "BoardID:" << BoardID << "BoardState:" << BoardState;
    }

    query.exec("DELETE FROM UniqueBoard WHERE board_id >= 4");




    return 0;
}
