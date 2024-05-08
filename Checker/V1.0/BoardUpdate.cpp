#include "boardUpdate.h"

std::vector<std::vector<std::string>> startUp(){
    std::vector<std::vector<std::string>> boards = {
        {"B ", "  ", "B ", "  ", "B ", "  ", "B ", "  "},
        {"  ", "B ", "  ", "B ", "  ", "B ", "  ", "B "},
        {"B ", "  ", "B ", "  ", "B ", "  ", "B ", "  "},
        {"  ", "1 ", "  ", "1 ", "  ", "1 ", "  ", "1 "},
        {"1 ", "  ", "1 ", "  ", "1 ", "  ", "1 ", "  "},
        {"  ", "R ", "  ", "R ", "  ", "R ", "  ", "R "},
        {"R ", "  ", "R ", "  ", "R ", "  ", "R ", "  "},
        {"  ", "R ", "  ", "R ", "  ", "R ", "  ", "R "}
    };

    //Print the initial board
    //std::cout << "Welcome to Checkers!" << std::endl;
    //std::cout << "Here is the board:" << std::endl;
    //checkerBoard(boards);
    //std::cout << std::endl;
    return boards;
}

//Prints the board with input given by the vector boards
void checkerBoard(std::vector<std::vector<std::string>>& boards){
    std::cout << " " << " "  << "1"  << "  "        << "2" << "  "         << "3"  << "  "        << "4"  << "  "        << "5"  << "  "        << "6"  << "  "        << "7"  << "  "        << "8"          << std::endl;
    std::cout << "A" << " "  << boards[0][0] << " " << boards[0][1] << " " << boards[0][2] << " " << boards[0][3] << " " << boards[0][4] << " " << boards[0][5] << " " << boards[0][6] << " " << boards[0][7] << std::endl;
    std::cout << "B" << " "  << boards[1][0] << " " << boards[1][1] << " " << boards[1][2] << " " << boards[1][3] << " " << boards[1][4] << " " << boards[1][5] << " " << boards[1][6] << " " << boards[1][7] << std::endl;
    std::cout << "C" << " "  << boards[2][0] << " " << boards[2][1] << " " << boards[2][2] << " " << boards[2][3] << " " << boards[2][4] << " " << boards[2][5] << " " << boards[2][6] << " " << boards[2][7] << std::endl;
    std::cout << "D" << " "  << boards[3][0] << " " << boards[3][1] << " " << boards[3][2] << " " << boards[3][3] << " " << boards[3][4] << " " << boards[3][5] << " " << boards[3][6] << " " << boards[3][7] << std::endl;
    std::cout << "E" << " "  << boards[4][0] << " " << boards[4][1] << " " << boards[4][2] << " " << boards[4][3] << " " << boards[4][4] << " " << boards[4][5] << " " << boards[4][6] << " " << boards[4][7] << std::endl;
    std::cout << "F" << " "  << boards[5][0] << " " << boards[5][1] << " " << boards[5][2] << " " << boards[5][3] << " " << boards[5][4] << " " << boards[5][5] << " " << boards[5][6] << " " << boards[5][7] << std::endl;
    std::cout << "G" << " "  << boards[6][0] << " " << boards[6][1] << " " << boards[6][2] << " " << boards[6][3] << " " << boards[6][4] << " " << boards[6][5] << " " << boards[6][6] << " " << boards[6][7] << std::endl;
    std::cout << "H" << " "  << boards[7][0] << " " << boards[7][1] << " " << boards[7][2] << " " << boards[7][3] << " " << boards[7][4] << " " << boards[7][5] << " " << boards[7][6] << " " << boards[7][7] << std::endl;
    std::cout << "-------------------------" << std::endl;
}

