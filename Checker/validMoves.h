#ifndef VALIDMOVES_H
#define VALIDMOVES_H

#include <iostream>
#include<vector>
#include<string>
#include "playerInput.h"

bool jumpPossible(int playerTurn, std::vector<std::string>& A, std::vector<std::string>& B, std::vector<std::string>& C, std::vector<std::string>& D, std::vector<std::string>& E, std::vector<std::string>& F, std::vector<std::string>& G, std::vector<std::string>& H, std::vector<std::string>& playerJump) {
    int check = -1;
    int j = 0;
    bool jump = false;
    playerJump = {};

    for(int i = 0; i < 64; i++){
        if(i%8 == 0){
            check++;
            j = 0;
        }
        if(check == 0){
            if(A[j] == "B " && playerTurn == 1 || A[j] == "BK" && playerTurn == 1){
                if((j < 6 && B[j+1] == "R " && C[j+2] == "1 ") || (j < 6 && B[j+1] == "RK" && C[j+2] == "1 ")){
                    playerJump.push_back("A" + std::to_string(j+1));
                    playerJump.push_back("C" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && B[j-1] == "R " && C[j-2] == "1 ") || (j > 1 && B[j-1] == "RK" && C[j-2] == "1 ")){
                    playerJump.push_back("A" + std::to_string(j+1));
                    playerJump.push_back("C" + std::to_string(j-1));
                    jump = true;
                }
            } else if(A[j] == "RK" && playerTurn == 1){
                if((j < 6) && (B[j+1] == "B " && C[j+2] == "1 ") || (j < 6 && B[j+1] == "BK" && C[j+2] == "1 ")){
                    playerJump.push_back("A" + std::to_string(j+1));
                    playerJump.push_back("C" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && B[j-1] == "B " && C[j-2] == "1 ") || ((j > 1) && B[j-1] == "BK" && C[j-2] == "1 ")){
                    playerJump.push_back("A" + std::to_string(j+1));
                    playerJump.push_back("C" + std::to_string(j-1));
                    jump = true;
                }
            }
        } else if(check == 1){
            if(B[j] == "B " && playerTurn == 1 || B[j] == "BK" && playerTurn == 1){
                if((j < 6 && C[j+1] == "R " && D[j+2] == "1 ") || (j < 6 && C[j+1] == "RK" && D[j+2] == "1 ")){
                    playerJump.push_back("B" + std::to_string(j+1));
                    playerJump.push_back("D" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && C[j-1] == "R " && D[j-2] == "1 ") || (j > 1 && C[j-1] == "RK" && D[j-2] == "1 ")){
                    playerJump.push_back("B" + std::to_string(j+1));
                    playerJump.push_back("D" + std::to_string(j-1));
                    jump = true;
                }
            } else if(B[j] == "RK" && playerTurn == 1){
                if((j < 6) && (C[j+1] == "B " && D[j+2] == "1 ") || (j < 6 && C[j+1] == "BK" && D[j+2] == "1 ")){
                    playerJump.push_back("B" + std::to_string(j+1));
                    playerJump.push_back("D" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && C[j-1] == "B " && D[j-2] == "1 ") || ((j > 1) && C[j-1] == "BK" && D[j-2] == "1 ")){
                    playerJump.push_back("B" + std::to_string(j+1));
                    playerJump.push_back("D" + std::to_string(j-1));
                    jump = true;
                }
            }

        } else if(check == 2){
            if(C[j] == "B " && playerTurn == 1 || C[j] == "BK" && playerTurn == 1){
                if(j < 6 && D[j+1] == "R " && E[j+2] == "1 " || (j < 6 && D[j+1] == "RK" && E[j+2] == "1 ")){
                    playerJump.push_back("C" + std::to_string(j+1));
                    playerJump.push_back("E" + std::to_string(j+3));
                    jump = true;
                }
                if(j > 1 && D[j-1] == "R " && E[j-2] == "1 " || (j > 1 && D[j-1] == "RK" && E[j-2] == "1 ")){
                    playerJump.push_back("C" + std::to_string(j+1));
                    playerJump.push_back("E" + std::to_string(j-1));
                    jump = true;
                }
                if((C[j] == "BK" && j < 6 && B[j+1] == "R " && A[j+2] == "1 ") || (C[j] == "BK" && j < 6 && B[j-1] == "RK" && A[j-2] == "1 ")){
                    playerJump.push_back("C" + std::to_string(j+1));
                    playerJump.push_back("A" + std::to_string(j+3));
                    jump = true;
                }
                if((C[j] == "BK" && j < 6 && B[j-1] == "R " && A[j-2] == "1 ") || (C[j] == "BK" && j < 6 && B[j-1] == "RK" && A[j-2] == "1 ")){
                    playerJump.push_back("C" + std::to_string(j+1));
                    playerJump.push_back("A" + std::to_string(j-1));
                }

            } else if(C[j] == "R " && playerTurn == 2 || C[j] == "RK" && playerTurn == 2){
                if((j < 6 && B[j+1] == "B " && A[j+2] == "1 ") || (j < 6 && B[j+1] == "BK" && A[j+2] == "1 ")){
                    playerJump.push_back("C" + std::to_string(j+1));
                    playerJump.push_back("A" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && B[j-1] == "B " && A[j-2] == "1 ") || (j > 1 && B[j-1] == "BK" && A[j-2] == "1 ")){
                    playerJump.push_back("C" + std::to_string(j+1));
                    playerJump.push_back("A" + std::to_string(j-1));
                    jump = true;
                }
                if((C[j] == "RK" && j < 6 && D[j+1] == "B " && E[j+2] == "1 ") || (C[j] == "RK" && j < 6 && D[j+1] == "BK" && E[j+2] == "1 ")){
                    playerJump.push_back("C" + std::to_string(j+1));
                    playerJump.push_back("E" + std::to_string(j+3));
                    jump = true;
                }
                if((C[j] == "RK" && j < 6 && D[j-1] == "B " && E[j-2] == "1 ") || (C[j] == "RK" && j < 6 && D[j-1] == "BK" && E[j-2] == "1 ")){
                    playerJump.push_back("C" + std::to_string(j+1));
                    playerJump.push_back("E" + std::to_string(j-1));
                    jump = true;
                }
            }
        } else if(check == 3){
            if(D[j] == "B " && playerTurn == 1 || D[j] == "BK" && playerTurn == 1){
                if(j < 6 && E[j+1] == "R " && F[j+2] == "1 " || (j < 6 && E[j+1] == "RK" && F[j+2] == "1 ")){
                    playerJump.push_back("D" + std::to_string(j+1));
                    playerJump.push_back("F" + std::to_string(j+3));
                    jump = true;
                }
                if(j > 1 && E[j-1] == "R " && F[j-2] == "1 " || (j > 1 && E[j-1] == "RK" && E[j-2] == "1 ")){
                    playerJump.push_back("D" + std::to_string(j+1));
                    playerJump.push_back("F" + std::to_string(j-1));
                    jump = true;
                }
                if((D[j] == "BK" && j < 6 && C[j+1] == "R " && B[j+2] == "1 ") || (D[j] == "BK" && j < 6 && C[j-1] == "RK" && B[j-2] == "1 ")){
                    playerJump.push_back("D" + std::to_string(j+1));
                    playerJump.push_back("B" + std::to_string(j+3));
                    jump = true;
                }
                if((D[j] == "BK" && j < 6 && C[j-1] == "R " && B[j-2] == "1 ") || (D[j] == "BK" && j < 6 && C[j-1] == "RK" && B[j-2] == "1 ")){
                    playerJump.push_back("D" + std::to_string(j+1));
                    playerJump.push_back("B" + std::to_string(j-1));
                }

            } else if(D[j] == "R " && playerTurn == 2 || D[j] == "RK" && playerTurn == 2){
                if((j < 6 && C[j+1] == "B " && B[j+2] == "1 ") || (j < 6 && C[j+1] == "BK" && B[j+2] == "1 ")){
                    playerJump.push_back("D" + std::to_string(j+1));
                    playerJump.push_back("B" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && C[j-1] == "B " && B[j-2] == "1 ") || (j > 1 && C[j-1] == "BK" && B[j-2] == "1 ")){
                    playerJump.push_back("D" + std::to_string(j+1));
                    playerJump.push_back("B" + std::to_string(j-1));
                    jump = true;
                }
                if((D[j] == "RK" && j < 6 && E[j+1] == "B " && F[j+2] == "1 ") || (D[j] == "RK" && j < 6 && E[j+1] == "BK" && F[j+2] == "1 ")){
                    playerJump.push_back("D" + std::to_string(j+1));
                    playerJump.push_back("F" + std::to_string(j+3));
                    jump = true;
                }
                if((D[j] == "RK" && j < 6 && E[j-1] == "B " && F[j-2] == "1 ") || (D[j] == "RK" && j < 6 && E[j-1] == "BK" && F[j-2] == "1 ")){
                    playerJump.push_back("D" + std::to_string(j+1));
                    playerJump.push_back("F" + std::to_string(j-1));
                    jump = true;
                }
            }
        } else if(check == 4){
            if(E[j] == "B " && playerTurn == 1 || E[j] == "BK" && playerTurn == 1){
                if(j < 6 && F[j+1] == "R " && G[j+2] == "1 " || (j < 6 && F[j+1] == "RK" && G[j+2] == "1 ")){
                    playerJump.push_back("E" + std::to_string(j+1));
                    playerJump.push_back("G" + std::to_string(j+3));
                    jump = true;
                }
                if(j > 1 && F[j-1] == "R " && G[j-2] == "1 " || (j > 1 && F[j-1] == "RK" && G[j-2] == "1 ")){
                    playerJump.push_back("E" + std::to_string(j+1));
                    playerJump.push_back("G" + std::to_string(j-1));
                    jump = true;
                }
                if((E[j] == "BK" && j < 6 && D[j+1] == "R " && C[j+2] == "1 ") || (E[j] == "BK" && j < 6 && D[j-1] == "RK" && C[j-2] == "1 ")){
                    playerJump.push_back("E" + std::to_string(j+1));
                    playerJump.push_back("C" + std::to_string(j+3));
                    jump = true;
                }
                if((E[j] == "BK" && j < 6 && D[j-1] == "R " && C[j-2] == "1 ") || (E[j] == "BK" && j < 6 && D[j-1] == "RK" && C[j-2] == "1 ")){
                    playerJump.push_back("E" + std::to_string(j+1));
                    playerJump.push_back("C" + std::to_string(j-1));
                }

            } else if(E[j] == "R " && playerTurn == 2 || E[j] == "RK" && playerTurn == 2){
                if((j < 6 && D[j+1] == "B " && C[j+2] == "1 ") || (j < 6 && D[j+1] == "BK" && C[j+2] == "1 ")){
                    playerJump.push_back("E" + std::to_string(j+1));
                    playerJump.push_back("C" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && D[j-1] == "B " && C[j-2] == "1 ") || (j > 1 && D[j-1] == "BK" && C[j-2] == "1 ")){
                    playerJump.push_back("E" + std::to_string(j+1));
                    playerJump.push_back("C" + std::to_string(j-1));
                    jump = true;
                }
                if((E[j] == "RK" && j < 6 && F[j+1] == "B " && G[j+2] == "1 ") || (E[j] == "RK" && j < 6 && F[j+1] == "BK" && G[j+2] == "1 ")){
                    playerJump.push_back("E" + std::to_string(j+1));
                    playerJump.push_back("G" + std::to_string(j+3));
                    jump = true;
                }
                if((E[j] == "RK" && j < 6 && F[j-1] == "B " && G[j-2] == "1 ") || (E[j] == "RK" && j < 6 && F[j-1] == "BK" && G[j-2] == "1 ")){
                    playerJump.push_back("E" + std::to_string(j+1));
                    playerJump.push_back("G" + std::to_string(j-1));
                    jump = true;
                }
            }
        } else if(check == 5){
            if(F[j] == "B " && playerTurn == 1 || F[j] == "BK" && playerTurn == 1){
                if(j < 6 && G[j+1] == "R " && H[j+2] == "1 " || (j < 6 && G[j+1] == "RK" && H[j+2] == "1 ")){
                    playerJump.push_back("F" + std::to_string(j+1));
                    playerJump.push_back("H" + std::to_string(j+3));
                    jump = true;
                }
                if(j > 1 && G[j-1] == "R " && H[j-2] == "1 " || (j > 1 && G[j-1] == "RK" && H[j-2] == "1 ")){
                    playerJump.push_back("F" + std::to_string(j+1));
                    playerJump.push_back("H" + std::to_string(j-1));
                    jump = true;
                }
                if((F[j] == "BK" && j < 6 && E[j+1] == "R " && D[j+2] == "1 ") || (F[j] == "BK" && j < 6 && E[j-1] == "RK" && D[j-2] == "1 ")){
                    playerJump.push_back("F" + std::to_string(j+1));
                    playerJump.push_back("D" + std::to_string(j+3));
                    jump = true;
                }
                if((F[j] == "BK" && j < 6 && E[j-1] == "R " && D[j-2] == "1 ") || (F[j] == "BK" && j < 6 && E[j-1] == "RK" && D[j-2] == "1 ")){
                    playerJump.push_back("F" + std::to_string(j+1));
                    playerJump.push_back("D" + std::to_string(j-1));
                }

            } else if(F[j] == "R " && playerTurn == 2 || F[j] == "RK" && playerTurn == 2){
                if((j < 6 && E[j+1] == "B " && D[j+2] == "1 ") || (j < 6 && E[j+1] == "BK" && D[j+2] == "1 ")){
                    playerJump.push_back("F" + std::to_string(j+1));
                    playerJump.push_back("D" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && E[j-1] == "B " && D[j-2] == "1 ") || (j > 1 && E[j-1] == "BK" && D[j-2] == "1 ")){
                    playerJump.push_back("F" + std::to_string(j+1));
                    playerJump.push_back("D" + std::to_string(j-1));
                    jump = true;
                }
                if((F[j] == "RK" && j < 6 && G[j+1] == "B " && H[j+2] == "1 ") || (F[j] == "RK" && j < 6 && G[j+1] == "BK" && H[j+2] == "1 ")){
                    playerJump.push_back("F" + std::to_string(j+1));
                    playerJump.push_back("H" + std::to_string(j+3));
                    jump = true;
                }
                if((F[j] == "RK" && j < 6 && G[j-1] == "B " && H[j-2] == "1 ") || (F[j] == "RK" && j < 6 && G[j-1] == "BK" && H[j-2] == "1 ")){
                    playerJump.push_back("F" + std::to_string(j+1));
                    playerJump.push_back("H" + std::to_string(j+3));
                    jump = true;
                }

            }
        } else if(check == 6){
            if(G[j] == "R " && playerTurn == 2 || G[j] == "RK" && playerTurn == 2){
                if((j < 6 && F[j+1] == "B " && E[j+2] == "1 ") || (j < 6 && F[j+1] == "BK" && E[j+2] == "1 ")){
                    playerJump.push_back("G" + std::to_string(j+1));
                    playerJump.push_back("E" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && F[j-1] == "B " && E[j-2] == "1 ") || (j > 1 && F[j-1] == "BK" && E[j-2] == "1 ")){
                    playerJump.push_back("G" + std::to_string(j+1));
                    playerJump.push_back("E" + std::to_string(j-1));
                    jump = true;
                }
            } else if(G[j] == "BK" && playerTurn == 1){
                if((j < 6) && (F[j+1] == "R " && E[j+2] == "1 ") || (j < 6 && F[j+1] == "RK" && E[j+2] == "1 ")){
                    playerJump.push_back("G" + std::to_string(j+1));
                    playerJump.push_back("E" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && F[j-1] == "R " && E[j-2] == "1 ") || ((j > 1) && F[j-1] == "RK" && E[j-2] == "1 ")){
                    playerJump.push_back("G" + std::to_string(j+1));
                    playerJump.push_back("E" + std::to_string(j-1));
                    jump = true;
                }
            }
        } else if(check == 7){
            if(H[j] == "R " && playerTurn == 2 || H[j] == "RK" && playerTurn == 2){
                if((j < 6 && G[j+1] == "B " && F[j+2] == "1 ") || (j < 6 && G[j+1] == "BK" && F[j+2] == "1 ")){
                    playerJump.push_back("H" + std::to_string(j+1));
                    playerJump.push_back("F" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && G[j-1] == "B " && F[j-2] == "1 ") || (j > 1 && G[j-1] == "BK" && F[j-2] == "1 ")){
                    playerJump.push_back("H" + std::to_string(j+1));
                    playerJump.push_back("F" + std::to_string(j-1));
                    jump = true;
                }
            } else if(H[j] == "BK" && playerTurn == 1){
                if((j < 6) && (G[j+1] == "R " && F[j+2] == "1 ") || (j < 6 && G[j+1] == "RK" && F[j+2] == "1 ")){
                    playerJump.push_back("H" + std::to_string(j+1));
                    playerJump.push_back("F" + std::to_string(j+3));
                    jump = true;
                }
                if((j > 1 && G[j-1] == "R " && F[j-2] == "1 ") || ((j > 1) && G[j-1] == "RK" && F[j-2] == "1 ")){
                    playerJump.push_back("H" + std::to_string(j+1));
                    playerJump.push_back("F" + std::to_string(j-1));
                    jump = true;
                }
            }
        }
        j++;
    }

    if(jump){
        return true;
    } else {
        return false;
    }
}

bool pieceJump(std::string playerStart, std::string playerMove, int playerTurn, std::vector<std::string>& A, std::vector<std::string>& B, std::vector<std::string>& C, std::vector<std::string>& D, std::vector<std::string>& E, std::vector<std::string>& F, std::vector<std::string>& G, std::vector<std::string>& H){
    int row = playerStart[1] - '0';
    int row2 = playerMove[1] - '0';
    int row3 = row2 + (row-row2)/2 - 1;
    char column;

    column = playerStart[0]-((playerStart[0]-playerMove[0])/2);

    if(column == 'A'|| column == 'a'){
        if(A[row3] == "R " && playerTurn == 1 || A[row3] == "RK" && playerTurn == 1){
            return true;
        } else if(A[row3] == "B " && playerTurn == 2 || A[row3] == "BK" && playerTurn == 2){
            return true;
        } else {
            return false;
        }
    } else if(column == 'B' || column == 'b'){
        if(B[row3] == "R " && playerTurn == 1 || B[row3] == "RK" && playerTurn == 1){
            B[row3] = "1 ";
            return true;
        } else if(B[row3] == "B " && playerTurn == 2 || B[row3] == "BK" && playerTurn == 2){
            B[row3] = "1 ";
            return true;
        } else {
            return false;
        }
    } else if(column == 'C' || column == 'c'){
        if(C[row3] == "R " && playerTurn == 1 || C[row3] == "RK" && playerTurn == 1){
            C[row3] = "1 ";
            return true;
        } else if(C[row3] == "B " && playerTurn == 2 || C[row3] == "BK" && playerTurn == 2){
            C[row3] = "1 ";
            return true;
        } else {
            return false;
        }
    } else if(column == 'D' || column == 'd'){
        if(D[row3] == "R " && playerTurn == 1 || D[row3] == "RK" && playerTurn == 1){
            D[row3] = "1 ";
            return true;
        } else if(D[row3] == "B " && playerTurn == 2 || D[row3] == "BK" && playerTurn == 2){
            D[row3] = "1 ";
            return true;
        } else {
            return false;
        }
    } else if(column == 'E' || column == 'e'){
        if(E[row3] == "R " && playerTurn == 1 || E[row3] == "RK" && playerTurn == 1){
            E[row3] = "1 ";
            return true;
        } else if(E[row3] == "B " && playerTurn == 2 || E[row3] == "BK" && playerTurn == 2){
            E[row3] = "1 ";
            return true;
        } else {
            return false;
        }
    } else if(column == 'F' || column == 'f'){
        if(F[row3] == "R " && playerTurn == 1 || F[row3] == "RK" && playerTurn == 1){
            F[row3] = "1 ";
            return true;
        } else if(F[row3] == "B " && playerTurn == 2 || F[row3] == "BK" && playerTurn == 2){
            F[row3] = "1 ";
            return true;
        } else {
            return false;
        }
    } else if(column == 'G' || column == 'g'){
        if(G[row3] == "R " && playerTurn == 1 || G[row3] == "RK" && playerTurn == 1){
            G[row3] = "1 ";
            return true;
        } else if(G[row3] == "B " && playerTurn == 2 || G[row3] == "BK" && playerTurn == 2){
            G[row3] = "1 ";
            return true;
        } else {
            return false;
        }
    } else if(column == 'H' || column == 'h'){
        if(H[row3] == "R " && playerTurn == 1 || H[row3] == "RK" && playerTurn == 1){
            return true;
        } else if(H[row3] == "B " && playerTurn == 2 || H[row3] == "BK" && playerTurn == 2){
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool moreMoveCheck(std::vector<std::string>& playerJump, std::string& playerMove) {
    std::string lowerCase;
    bool check;

    for (int i = 0; i < playerJump.size(); i += 2) {
        lowerCase = playerJump[i];
        lowerCase[0] = tolower(lowerCase[0]);
        if(playerMove == playerJump[i] || playerMove == lowerCase){
            return true;
        }
    }

    return false;
}

bool isValid(std::string playerStart, std::string playerMove, int playerTurn, std::vector<std::string>& A, std::vector<std::string>& B, std::vector<std::string>& C, std::vector<std::string>& D, std::vector<std::string>& E, std::vector<std::string>& F, std::vector<std::string>& G, std::vector<std::string>& H, int& redPieces, int& blackPieces, std::vector<std::string>& playerJump) {
    int row = playerStart[1] - '0';
    int row2 = playerMove[1] - '0';
    int check;
    bool king = false;

    if(playerStart == playerMove){
        std::cout << "Invalid move. Please enter a move that is not the same as your starting position." << std::endl;
        return false;
    }

    if(playerTurn % 2 == 0){
        check = -1;
    } else {
        check = 1;
    }

    if(playerStart[0] == 'A' || playerStart[0] == 'a'){
        if(A[playerStart[1]-'0'-1] == "BK" || A[playerStart[1]-'0'] == "RK"){
            king = true;
        }
    } else if(playerStart[0] == 'B' || playerStart[0] == 'b'){
        if(B[playerStart[1]-'0'-1] == "BK" || B[playerStart[1]-'0'] == "RK"){
            king = true;
        }
    } else if(playerStart[0] == 'C' || playerStart[0] == 'c'){
        if(C[playerStart[1]-'0'-1] == "BK" || C[playerStart[1]-'0'] == "RK"){
            king = true;
        }
    } else if(playerStart[0] == 'D' || playerStart[0] == 'd'){
        if(D[playerStart[1]-'0'-1] == "BK" || D[playerStart[1]-'0'] == "RK"){
            king = true;
            std::cout << "Hej" << std::endl;
        }
    } else if(playerStart[0] == 'E' || playerStart[0] == 'e'){
        if(E[playerStart[1]-'0'-1] == "BK" || E[playerStart[1]-'0'] == "RK"){
            king = true;
        }
    } else if(playerStart[0] == 'F' || playerStart[0] == 'f'){
        if(F[playerStart[1]-'0'-1] == "BK" || F[playerStart[1]-'0'] == "RK"){
            king = true;
        }
    } else if(playerStart[0] == 'G' || playerStart[0] == 'g'){
        if(G[playerStart[1]-'0'-1] == "BK" || G[playerStart[1]-'0'] == "RK"){
            king = true;
        }
    } else if(playerStart[0] == 'H' || playerStart[0] == 'h'){
        if(H[playerStart[1]-'0'-1] == "BK" || H[playerStart[1]-'0'] == "RK"){
            king = true;
        }
    }

    if(playerStart[0] == playerMove[0] || playerStart[1] == playerMove[1]) {
        std::cout << "Invalid move. Please enter a move that is diagonal." << std::endl;
        return false;
    }

    if(isupper(playerStart[0])){
        if(playerStart[0] < 'A' || playerStart[0] > 'H') {
            std::cout << "Invalid move. Please enter a letter between A and H." << std::endl;
            return false;
        }
    } else {
        if(playerStart[0] < 'a' || playerStart[0] > 'h') {
            std::cout << "Invalid move. Please enter a letter between a and h." << std::endl;
            return false;
        }
    }

    if(isupper(playerMove[0])){
        if(playerMove[0] < 'A'|| playerMove[0] > 'H') {
            std::cout << "Invalid move. Please enter a letter between A and H." << std::endl;
            return false;
        }
    } else {
        if(playerMove[0] < 'a' || playerMove[0] > 'h') {
            std::cout << "Invalid move. Please enter a letter between a and h." << std::endl;
            return false;
        }
    }

    if(row == 0 || row > 8 || row2 < 1 || row2 > 8){
        std::cout << "Invalid move. Please enter a number between 1 and 8." << std::endl;
        return false;
    }

    if(!king){
        if(abs(row2-row) != 1 || (playerMove[0]-'0')-(playerStart[0]-'0') != check){
            if(abs(row2-row) == 2 && (playerMove[0]-'0')-(playerStart[0]-'0') == 2*check){ //Der mangler tjek for RK og BK her!
                if(pieceJump(playerStart, playerMove, playerTurn, A, B, C, D, E, F, G, H)){
                    if(playerTurn == 1){
                        redPieces--;
                        if(redPieces == 0){
                            gameEnd = true;
                        }
                    } else {
                        blackPieces--;
                        if(blackPieces == 0){
                            gameEnd = true;
                        }
                    }
                    moreMove = true;
                    return true;
                }
            }
            std::cout << "Invalid move. Please enter a move that is only one square away." << std::endl;
            return false;
        }
    } else {
        if(abs(row2-row) != 1 || abs((playerMove[0]-'0')-(playerStart[0]-'0')) != 1){
            if(abs(row2-row) == 2 && abs((playerMove[0]-'0')-(playerStart[0]-'0')) == 2){ //Der mangler tjek for RK og BK her!
                if(pieceJump(playerStart, playerMove, playerTurn, A, B, C, D, E, F, G, H)){
                    if(playerTurn == 1){
                        redPieces--;
                        if(redPieces == 0){
                            gameEnd = true;
                        }
                    } else {
                        blackPieces--;
                        if(blackPieces == 0){
                            gameEnd = true;
                        }
                    }
                    moreMove = true;
                    return true;
                }
            }
            std::cout << "Invalid move. Please enter a move that is only one square away." << std::endl;
            return false;
        }
    }

    return true;
}

bool movePossible(bool jumpPossible, int playerTurn, std::vector<std::string>& A, std::vector<std::string>& B, std::vector<std::string>& C, std::vector<std::string>& D, std::vector<std::string>& E, std::vector<std::string>& F, std::vector<std::string>& G, std::vector<std::string>& H){
    int check = 0;
    int j = 0;

    if(jumpPossible){
        return true;
    }

    for(int i = 0; i < 64; i++){
        if(i%8 == 0 && i != 0){
            check++;
            j = 0;
        }
        if(j > 0 && j < 7){
            if(check == 0){
                if(A[j] == "B " && playerTurn == 1){
                    if((B[j+1] == "1 " || B[j-1] == "1 ")){
                        return true;
                    }
                }
            } else if(check == 1){
                if(B[j] == "B " && playerTurn == 1){
                    if(C[j+1] == "1 " || C[j-1] == "1 "){
                        return true;
                    }
                } else if(B[j] == "R " && playerTurn == 2){
                    if(A[j+1] == "1 " || A[j-1] == "1 "){
                        return true;
                    }
                }
            } else if(check == 2){
                if(C[j] == "B " && playerTurn == 1){
                    if(D[j+1] == "1 " || D[j-1] == "1 "){
                        return true;
                    }
                } else if(C[j] == "R " && playerTurn == 2){
                    if(B[j+1] == "1 " || B[j-1] == "1 "){
                        return true;
                    }
                }
            } else if(check == 3){
                if(D[j] == "B " && playerTurn == 1){
                    if(E[j+1] == "1 " || E[j-1] == "1 "){
                        return true;
                    }
                } else if(D[j] == "R " && playerTurn == 2){
                    if(C[j+1] == "1 " || C[j-1] == "1 "){
                        return true;
                    }
                }
            } else if(check == 4){
                if(E[j] == "B " && playerTurn == 1){
                    if(F[j+1] == "1 " || F[j-1] == "1 "){
                        return true;
                    }
                } else if(E[j] == "R " && playerTurn == 2){
                    if(D[j+1] == "1 " || D[j-1] == "1 "){
                        return true;
                    }
                }
            } else if(check == 5){
                if(F[j] == "B " && playerTurn == 1){
                    if(G[j+1] == "1 " || G[j-1] == "1 "){
                        return true;
                    }
                } else if(F[j] == "R " && playerTurn == 2){
                    if(E[j+1] == "1 " || E[j-1] == "1 "){
                        return true;
                    }
                }
            } else if(check == 6){
                if(G[j] == "B " && playerTurn == 1){
                    if(H[j+1] == "1 " || H[j-1] == "1 "){
                        return true;
                    }
                } else if(G[j] == "R " && playerTurn == 2){
                    if(F[j+1] == "1 " || F[j-1] == "1 "){
                        return true;
                    }
                }
            } else if(check == 7){
                if(H[j] == "R " && playerTurn == 2){
                    if(G[j+1] == "1 " || G[j-1] == "1 "){
                        return true;
                    }
                }
            }
        }
        j++;

    }
    return false;
}

bool promotion(std::vector<std::string>& A, std::vector<std::string>& H, int playerTurn){
    if(playerTurn == 1){
        for(int i = 0; i < 8; i++){
            if(H[i] == "B "){
                H[i] = "BK";
            }
        }
    } else {
        for(int i = 0; i < 8; i++){
            if(A[i] == "R "){
                A[i] = "RK";
            }
        }
    }
    ;
}

bool playerMover(std::string& playerStart, std::string& playerMove, std::vector<std::string>& A, std::vector<std::string>& B, std::vector<std::string>& C, std::vector<std::string>& D, std::vector<std::string>& E, std::vector<std::string>& F, std::vector<std::string>& G, std::vector<std::string>& H, int playerTurn, int& redPieces, int& blackPieces, std::vector<std::string>& playerJump, int tries) {
    bool validMove1 = false;
    bool validMove2 = false;
    int row;
    int row2;
    std::vector<std::string> piece;
    bool jump;
    bool move;
    bool check = false;



    if(playerTurn == 1){
        piece = {"B ", "BK"};
    } else {
        piece = {"R ", "RK"};
    }

    while(!check) {
        jump = jumpPossible(playerTurn, A, B, C, D, E, F, G, H, playerJump);
        move = movePossible(jump, playerTurn, A, B, C, D, E, F, G, H);
        check = playerInput(jump, playerStart, playerMove, playerJump, playerTurn, move, tries);
        tries++;
    }

    if(gameEnd){
        ;
    }

    if(!isValid(playerStart, playerMove, playerTurn, A, B, C, D, E, F, G, H, redPieces, blackPieces, playerJump)){
        return false;
    }

    while(!validMove1){
        row = playerStart[1] - '0' - 1;
        if(playerStart[0] == 'A' || playerStart[0] == 'a') {
            if(A[row] != piece[0] && A[row] != piece[1]) {
                std::cout << "Invalid move. Please enter a square containing one of your pieces." << std::endl;
                return false;
            } else {
                validMove1 = true;
                piece[0] = A[row];
                A[row] = "1 ";
            }
        } else if(playerStart[0] == 'B' || playerStart[0] == 'b') {
            if(B[row] != piece[0] && B[row] != piece[1]) {
                std::cout << "Invalid move. Please enter a square containing one of your pieces." << std::endl;
                return false;
            } else {
                validMove1 = true;
                piece[0] = B[row];
                B[row] = "1 ";
            }
        } else if(playerStart[0] == 'C' || playerStart[0] == 'c') {
            if(C[row] != piece[0] && C[row] != piece[1]) {
                std::cout << "Invalid move. Please enter a square containing one of your pieces." << std::endl;
                std::cout << playerStart[0] << playerMove[0] << std::endl;
                return false;
            } else {
                validMove1 = true;
                piece[0] = C[row];
                C[row] = "1 ";
            }
        } else if(playerStart[0] == 'D' || playerStart[0] == 'd') {
            if(D[row] != piece[0] && D[row] != piece[1]) {
                std::cout << "Invalid move. Please enter a square containing one of your pieces." << std::endl;
                return false;
            } else {
                validMove1 = true;
                piece[0] = D[row];
                D[row] = "1 ";
            }
        } else if(playerStart[0] == 'E' || playerStart[0] == 'e') {
            if(E[row] != piece[0] && E[row] != piece[1]) {
                std::cout << "Invalid move. Please enter a square containing one of your pieces." << std::endl;
                return false;
            } else {
                validMove1 = true;
                piece[0] = E[row];
                E[row] = "1 ";
            }
        } else if(playerStart[0] == 'F' || playerStart[0] == 'f') {
            if(F[row] != piece[0] && F[row] != piece[1]) {
                std::cout << "Invalid move. Please enter a square containing one of your pieces." << std::endl;
                return false;
            } else {
                validMove1 = true;
                piece[0] = F[row];
                F[row] = "1 ";
            }
        } else if(playerStart[0] == 'G' || playerStart[0] == 'g') {
            if(G[row] != piece[0] && G[row] != piece[1]) {
                std::cout << "Invalid move. Please enter a square containing one of your pieces." << std::endl;
                return false;
            } else {
                validMove1 = true;
                piece[0] = G[row];
                G[row] = "1 ";
            }
        } else if(playerStart[0] == 'H' || playerStart[0] == 'h') {
            if(H[row] != piece[0] && H[row] != piece[1]) {
                std::cout << "Invalid move. Please enter a square containing one of your pieces." << std::endl;
                return false;
            } else {
                validMove1 = true;
                piece[0] = H[row];
                H[row] = "1 ";
            }
        }
    }

    while(!validMove2){
        row2 = playerMove[1] - '0' - 1;
        if(playerMove[0] == 'A' || playerMove[0] == 'a') {
            if(A[row2] != "1 ") {
                std::cout << "Invalid move. Please enter a square that isnt occupied." << std::endl;
                return false;
            } else {
                validMove2 = true;
                A[row2] = piece[0];
            }
        } else if(playerMove[0] == 'B' || playerMove[0] == 'b') {
            if(B[row2] != "1 ")  {
                std::cout << "Invalid move. Please enter a square that isnt occupied."<< std::endl;
                return false;
            } else {
                validMove2 = true;
                B[row2] = piece[0];
            }
        } else if(playerMove[0] == 'C' || playerMove[0] == 'c') {
            if(C[row2] != "1 ")  {
                std::cout << "Invalid move. Please enter a square that isnt occupied." << std::endl;
                return false;
            } else {
                validMove2 = true;
                C[row2] = piece[0];
            }
        } else if(playerMove[0] == 'D' || playerMove[0] == 'd') {
            if(D[row2] != "1 ")  {
                std::cout << "Invalid move. Please enter a square that isnt occupied." << std::endl;
                return false;
            } else {
                validMove2 = true;
                D[row2] = piece[0];
            }
        } else if(playerMove[0] == 'E' || playerMove[0] == 'e') {
            if(E[row2] != "1 ")  {
                std::cout << "Invalid move. Please enter a square that isnt occupied." << std::endl;
                return false;
            } else {
                validMove2 = true;
                E[row2] = piece[0];
            }
        } else if(playerMove[0] == 'F' || playerMove[0] == 'f') {
            if(F[row2] != "1 " )  {
                std::cout << "Invalid move. Please enter a square that isnt occupied." << std::endl;
                return false;
            } else {
                validMove2 = true;
                F[row2] = piece[0];
            }
        } else if(playerMove[0] == 'G' || playerMove[0] == 'g') {
            if(G[row2] != "1 " )  {
                std::cout << "Invalid move. Please enter a square that isnt occupied." << std::endl;
                return false;
            } else {
                validMove2 = true;
                G[row2] = piece[0];
            }
        } else if(playerMove[0] == 'H' || playerMove[0] == 'h') {
            if(H[row2] != "1 " )  {
                std::cout << "Invalid move. Please enter a square that isnt occupied."<< (playerMove[0]-'0') << " " << (playerStart[0]-'0') << std::endl;
                return false;
            } else {
                validMove2 = true;
                H[row2] = piece[0];
            }
        }
    }

    if(promotion(A, H, playerTurn)){
        moreMove = false;
        return true;
    }

    jumpPossible(playerTurn, A, B, C, D, E, F, G, H, playerJump);

    if(moreMoveCheck(playerJump, playerMove)){
        moreMove = true;
    } else {
        moreMove = false;
    }

    return true;

}
#endif // VALIDMOVES_H
