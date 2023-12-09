#include <iostream>
#include <fstream>
#include <string>

typedef struct {
    std::string str;
    int i;
} lookup_t;

lookup_t gTable[9] = {
    {std::string("one"),1},
    {std::string("two"),2},
    {std::string("three"),3},
    {std::string("four"),4},
    {std::string("five"),5},
    {std::string("six"),6},
    {std::string("seven"),7},
    {std::string("eight"),8},
    {std::string("nine"),9}
};

int match(std::string slice) {
    for(int i = 0; i < 9; i++) {
        if(!gTable[i].str.compare(0, gTable[i].str.length(), slice, 0, gTable[i].str.length())){
            return gTable[i].i;
        }
    }
    return -1;
}
int main() {
    std::ifstream inputFile("../src/day1/input.txt");

    if(!inputFile.is_open()){
        std::cerr << "ERROR IDIOT" << std::endl;
        return 1;
    }

    std::string line;
    int finalNumber = 0;
    int lineNumber = 1;

    while(std::getline(inputFile,line)){
        std::string first = "";
        std::string last = "";
        for (int i = 0; i < line.length(); i++) {
            if(isdigit(line[i]) and first == ""){
                first = line[i];
            }
            else if(match(line.substr(i)) != -1 and first == ""){
                first = std::to_string(match(line.substr(i)));
            }
            if(isdigit(line[i])){
                last = line[i];
            }
            else if(match(line.substr(i)) != -1){
                last = std::to_string(match(line.substr(i)));
            }
        }
        std::string combined = first + last;
        if(first != "" and last != ""){
            std::cout << "Line Number " << lineNumber << ": " << first << last << std::endl;
            finalNumber += std::stoi(combined);
            lineNumber++;
        }
        
    }
    std::cout << "Final Number: " << finalNumber << std::endl;
    inputFile.close();

    return 0;

}