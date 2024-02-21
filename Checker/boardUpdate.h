#ifndef BOARDUPDATE_H
#define BOARDUPDATE_H

#include <iostream>
#include <vector>
#include <string>

void checkerBoard(std::vector<std::string>& A, std::vector<std::string>& B, std::vector<std::string>& C, std::vector<std::string>& D, std::vector<std::string>& E, std::vector<std::string>& F, std::vector<std::string>& G, std::vector<std::string>& H){
    std::cout << " " << " "  << "1"  << "  "<< "2"  << "  "<< "3"  << "  "<< "4"  << "  "<< "5"  << "  "<< "6"  << "  "<< "7"  << "  "<< "8" << std::endl;
    std::cout << "A" << " "  << A[0] << " " << A[1] << " " << A[2] << " " << A[3] << " " << A[4] << " " << A[5] << " " << A[6] << " " << A[7] << std::endl;
    std::cout << "B" << " "  << B[0] << " " << B[1] << " " << B[2] << " " << B[3] << " " << B[4] << " " << B[5] << " " << B[6] << " " << B[7] << std::endl;
    std::cout << "C" << " "  << C[0] << " " << C[1] << " " << C[2] << " " << C[3] << " " << C[4] << " " << C[5] << " " << C[6] << " " << C[7] << std::endl;
    std::cout << "D" << " "  << D[0] << " " << D[1] << " " << D[2] << " " << D[3] << " " << D[4] << " " << D[5] << " " << D[6] << " " << D[7] << std::endl;
    std::cout << "E" << " "  << E[0] << " " << E[1] << " " << E[2] << " " << E[3] << " " << E[4] << " " << E[5] << " " << E[6] << " " << E[7] << std::endl;
    std::cout << "F" << " "  << F[0] << " " << F[1] << " " << F[2] << " " << F[3] << " " << F[4] << " " << F[5] << " " << F[6] << " " << F[7] << std::endl;
    std::cout << "G" << " "  << G[0] << " " << G[1] << " " << G[2] << " " << G[3] << " " << G[4] << " " << G[5] << " " << G[6] << " " << G[7] << std::endl;
    std::cout << "H" << " "  << H[0] << " " << H[1] << " " << H[2] << " " << H[3] << " " << H[4] << " " << H[5] << " " << H[6] << " " << H[7] << std::endl;
    std::cout << std::endl;
}

#endif // BOARDUPDATE_H
