#include <iostream>
#include <fstream>
#include <string>

int main(){
    std::ifstream inputFile("../src/day2/input.txt");

    if(!inputFile.is_open()){
        std::cerr << "ERROR IDIOT" << std::endl;
        return 1;
    }

    std::string line;
    int gameFinal = 0;

    while(std::getline(inputFile,line)){


    }

    inputFile.close();
}