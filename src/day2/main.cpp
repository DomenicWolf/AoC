#include <iostream>
#include <fstream>
#include <string>
#include <vector>


typedef struct{
    std::string color;
    int amount;
    int gameId;
} colorCombo;

colorCombo gTable[3] {
    {"red",12},
    {"green",13},
    {"blue",14}
};

int main(){
    std::ifstream inputFile("../src/day2/input.txt");

    if(!inputFile.is_open()){
        std::cerr << "ERROR IDIOT" << std::endl;
        return 1;
    }

    int lineNumber = 0;
    int gameFinal = 0;
    int powersSum = 0;

    std::string line;
    while(std::getline(inputFile,line)){
        std::string gameId = "";
        std::cout << line << std::endl;
        bool gameIdRange = true;
        std::vector<colorCombo> colorComboArray;
        std::string color = "";
        std::string amount = "";
        bool sectionRange = true;
        bool lastLine = false;
        for(int i = 5; i < line.size(); i++){
            //std::cout << line[i] << std::endl;
            if (gameIdRange and line[i] != ':') {
                gameId += line[i];
            }else if (line[i] == ':') {
                gameIdRange = false;
            }
            if(isdigit(line[i]) and !gameIdRange){
                std::string digitString(1, line[i]);
                // Convert the string to an integer and update amount
                amount += digitString;

            }
            else if(line[i] != ' ' and line[i] != ',' and line[i] != ';' and line[i] != ':' and !gameIdRange){
                color += line[i];
            }
            if(line[i] == ';' or line[i] == ','){
                colorCombo selection = {color,std::stoi(amount)};
                colorComboArray.push_back(selection);
                color = "";
                amount = "";
            }
            if(line[i] == ';' or line[i] == ',' and line.size() - i <= 8){
                lastLine = true;
            }
            if(lastLine and line.size() - i == 1){
                colorCombo selection = {color,std::stoi(amount)};
                colorComboArray.push_back(selection);
                color = "";
                amount = "";
            }
        }
        lineNumber++;
        // for(int i = 0; i < colorComboArray.size(); i++){
        //     std::cout << colorComboArray[i] << std::endl;
        // }
        //std::cout << colorComboArray << std::endl;
        std::cout << "Game: " << lineNumber;
        for (const auto &element : colorComboArray) {
            std::cout << " " << element.amount << " " << element.color << " ";
        }
        std::cout << std::endl;
        bool fail = false;
        int redLowest = -1;
        int greenLowest = -1;
        int blueLowest = -1;
        for (const auto &element : colorComboArray) {
            for(int i = 0; i < 3; i++){
                if(element.amount > gTable[i].amount and element.color == gTable[i].color){
                    std::cout << element.color << ": " << element.amount << '-' << gTable[i].color << ": " << gTable[i].amount << std::endl;
                    fail = true;    
                }
                if(gTable[i].color == element.color){
                    if (element.color == "red"){
                        if(redLowest == -1){
                            redLowest = element.amount;
                        }else if (element.amount > redLowest) {
                            redLowest = element.amount;
                        }
                    }
                    if (element.color == "green"){
                        if(greenLowest == -1){
                            greenLowest = element.amount;
                        }else if (element.amount > greenLowest) {
                            greenLowest = element.amount;
                        }
                    }
                    if (element.color == "blue"){
                        if(blueLowest == -1){
                            blueLowest = element.amount;
                        }else if (element.amount > blueLowest) {
                            std::cout << element.amount << blueLowest << std::endl;
                            blueLowest = element.amount;
                        }
                    }
                }
            }

        }
        if (!fail){
            gameFinal += std::stoi(gameId);
        }
        std::cout << redLowest << "redlowest" << blueLowest << greenLowest << std::endl;
        powersSum += (redLowest * blueLowest * greenLowest);
    }
    std::cout << gameFinal << std::endl;
    std::cout << powersSum << std::endl;
    inputFile.close();

    return 0;
}