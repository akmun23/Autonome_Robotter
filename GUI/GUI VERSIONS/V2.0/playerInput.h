#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
#include <iostream>
#include <string>
#include <vector>

bool playerMover(std::string playerStart, std::string playerMove, int playerTurn, std::vector<std::vector<std::string>> boards);

//Function to get the player's input
bool playerInput(std::string playerStart, std::string playerMove, std::vector<std::string> playerJump, int playerTurn, std::vector<std::vector<std::string>> boards) {
    bool valid = false; //If the move is valid
    bool check = false; //If the move is a jump
    bool jumpPossible = false; //If a jump is possible

    if(playerJump.size() > 0){
        jumpPossible = true;
    }

    std::string lowerCase; //Variable used to convert the player's input to lowercase
    std::string lowerCase2; //Variable used to convert the player's input to lowercase

    //Loop to get the player's input until a valid one is given
    while(!valid){

        //Checks if the input has the correct number of characters
        if(playerStart.length() != 2 || playerMove.length() != 2) {
            std::cout << "Invalid move. Please enter a move in the format A3." << std::endl;
            valid = false;
        } else {
            //Checks if the input is a jump while a jump is possible
            if(jumpPossible && valid){
                for (int i = 0; i < playerJump.size(); i+=2) {
                    //Makes it possible to write in both upper and lowerCase
                    lowerCase = playerJump[i];
                    lowerCase[0] = tolower(lowerCase[0]);
                    lowerCase2 = playerJump[i+1];
                    lowerCase2[0] = tolower(lowerCase2[0]);

                    //Checks if the input is a jump
                    if(!check){
                        if((playerStart == playerJump[i] || playerStart == lowerCase) && (playerMove == playerJump[i+1] || playerMove == lowerCase2)){
                            check = true;
                            valid = true;
                        } else {
                            valid = false;
                        }
                    }
                }
                if(!valid){
                    std::cout << "Invalid move. You must jump." << std::endl;
                } else {
                    // If the input was a jump, it goes on to check if the move is valid
                    valid = playerMover(playerStart, playerMove, playerTurn, boards);
                }
            } else {
                //If there were no jumps possible, it checks if the move is valid
                valid = playerMover(playerStart, playerMove, playerTurn, boards);
            }

        }
    }
    //Returns true if the move is valid, which it must be to break out of the while-loop
    return true;
}

#endif // PLAYERINPUT_H
