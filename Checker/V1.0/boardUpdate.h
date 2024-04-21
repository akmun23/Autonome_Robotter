#pragma once
#ifndef BOARDUPDATE_H
#define BOARDUPDATE_H

#include <iostream>
#include <vector>

std::vector<std::vector<std::string>> startUp();

//Prints the board with input given by the vector boards
void checkerBoard(std::vector<std::vector<std::string>>& boards);
#endif // BOARDUPDATE_H
