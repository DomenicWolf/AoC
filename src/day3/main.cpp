#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>


//track the top, current and bottom line, when moved down, replace shift varialbes containting top,current,bottom
// track numbers and symbols on each line, and which line their on, might need to create struct or something to 
// watch out for duplicate nubmer which touch multiple symbols

typedef struct {
    int value;
    std::vector<int> idx;
} number_idx;

int main(){
    std::ifstream inputFile("../src/day3/input.txt");

    if(!inputFile.is_open()){
        std::cerr << "ERROR IDIOT" << std::endl;
        return 1;
    }

    bool isFull = false;

    int finalNumber = 0;
    std::vector<int> finalNumbersArray;

    std::vector<int> topLineNumber;
    std::vector<int> topLineSymbols;

    std::vector<int> bottomLineNumber;
    std::vector<int> bottomLineSymbols;

    std::vector<int> topLineValue;
    std::vector<int> bottomLineValue;

    std::vector<number_idx> topValueIdxPairs; 
    std::vector<number_idx> bottomValueIdxPairs;

    std::string line;
    while(std::getline(inputFile,line)){
        bool isTopDigit = false;
        std::string topNumberHolder = "";

        bool isBottomDigit = false;
        std::string bottomNumberHolder = "";

        number_idx currentNumber;
        number_idx bottomNumber;

        for(int i = 0; i < line.size(); i++){
            //std::cout << "Crying: " << topLineNumber[0] << std::endl;
            if(!isFull){
                if(isdigit(line[i]) and !isTopDigit){
                    topLineNumber.push_back(i);
                    isTopDigit = true;
                    topNumberHolder += line[i];
                    currentNumber.idx.push_back(i);
                }
                else if (isTopDigit and isdigit(line[i])){
                    topNumberHolder += line[i];
                    currentNumber.idx.push_back(i);
                }
                else if(isTopDigit and !isdigit(line[i])){
                    //std::cout << line[i] << " " << topNumberHolder << std::endl;
                    isTopDigit = false;
                    topLineValue.push_back(std::stoi(topNumberHolder));
                    currentNumber.value = std::stoi(topNumberHolder);
                    topValueIdxPairs.push_back(currentNumber);
                    topNumberHolder = "";
                }
                else if(!isdigit(line[i]) and line[i] != '.'){
                    topLineSymbols.push_back(i);
                }
                if(i + 1 == line.size() and topNumberHolder != "" and isdigit(line[i])){
                    topNumberHolder += line[i];
                    currentNumber.idx.push_back(i);
                    currentNumber.value = std::stoi(topNumberHolder);
                    topLineValue.push_back(std::stoi(topNumberHolder));
                    topValueIdxPairs.push_back(currentNumber);
                }
            }
            if (line.size() - 1 == i and !isFull){
                isFull = true;
                continue;
            }
           
            if(isFull){
                if(isdigit(line[i]) and !isBottomDigit){
                    //std::cout << "test" << i << std::endl;
                    bottomLineNumber.push_back(i);
                    isBottomDigit = true;
                    bottomNumberHolder += line[i];
                    bottomNumber.idx.push_back(i);
                }
                else if(isBottomDigit and isdigit(line[i])){
                    bottomNumberHolder += line[i];
                    bottomNumber.idx.push_back(i);
                }
                else if(isBottomDigit and !isdigit(line[i])){
                    //std::cout << line[i] << " " << bottomNumberHolder << std::endl;
                    isBottomDigit = false;
                    bottomLineValue.push_back(std::stoi(bottomNumberHolder));
                    bottomNumber.value = std::stoi(bottomNumberHolder);
                    bottomValueIdxPairs.push_back(bottomNumber);
                    bottomNumberHolder = "";
                }
                else if(!isdigit(line[i]) and line[i] != '.'){
                    bottomLineSymbols.push_back(i);
                }
                if(i + 1 == line.size() and bottomNumberHolder != "" and isdigit(line[i])){
                    //bottomNumberHolder += line[i];
                    bottomLineValue.push_back(std::stoi(bottomNumberHolder));
                    bottomNumber.idx.push_back(i);
                    bottomNumber.value = std::stoi(bottomNumberHolder);
                    bottomValueIdxPairs.push_back(bottomNumber);
                    std::cout << "I DONT KNOW MAN" << bottomNumberHolder << std::endl;
                }
                if (  bottomNumberHolder != ""){
                    if(stoi(bottomNumberHolder) > 1000){
                        
                    }
                    
                }
                
            }
             //std::cout << "test" << bottomNumber.value << std::endl;
        }
        if(bottomLineNumber.size() > 0){
            
            for(int i = 0; i < topLineSymbols.size(); i++){
                for(int j = 0; j < topValueIdxPairs.size(); j++){
                    bool added = true;
                    
                    if(topLineSymbols[i] <= topValueIdxPairs[j].idx[topValueIdxPairs[j].idx.size()] and topLineSymbols[i] >= topValueIdxPairs[j].idx[0]){
                        finalNumbersArray.push_back(topValueIdxPairs[j].value);
                        added = true;
                    }
                    else if (topLineSymbols[i] == topValueIdxPairs[j].idx[0] - 1){
                        finalNumbersArray.push_back(topValueIdxPairs[j].value);
                        added = true;
                    }
                    else if(topLineSymbols[i] == topValueIdxPairs[j].idx[topValueIdxPairs[j].idx.size() + 1]){
                        finalNumbersArray.push_back(topValueIdxPairs[j].value);
                        added = true;
                    }
                

                    if(bottomLineSymbols[i] >= topValueIdxPairs[j].idx[0] and bottomLineSymbols[i] <= topValueIdxPairs[j].idx[topValueIdxPairs[j].idx.size()] and added == true){
                        finalNumbersArray.push_back(topValueIdxPairs[j].value);
                    }
                    else if (bottomLineSymbols[i] == topValueIdxPairs[j].idx[0] - 1){
                        finalNumbersArray.push_back(topValueIdxPairs[j].value);
                        added = true;
                    }
                    else if(bottomLineSymbols[i] == topValueIdxPairs[j].idx[topValueIdxPairs[j].idx.size() + 1]){
                        finalNumbersArray.push_back(topValueIdxPairs[j].value);
                        added = true;
                    }
                }
            }

            for(int i = 0; i < topLineSymbols.size(); i++){
                for(int j = 0; j < bottomValueIdxPairs.size(); j++){
                    bool added = true;
                    if(bottomValueIdxPairs[j].value >= 961){
                        //std::cout << "ONE THING AFTER ANOTHER" << bottomValueIdxPairs[j].value << std::endl;
                    }
                    
                    if(topLineSymbols[i] <= bottomValueIdxPairs[j].idx[bottomValueIdxPairs[j].idx.size()] and topLineSymbols[i] >= bottomValueIdxPairs[j].idx[0]){
                        finalNumbersArray.push_back(bottomValueIdxPairs[j].value);
                        added = true;
                    }
                    else if (topLineSymbols[i] == bottomValueIdxPairs[j].idx[0] - 1){
                        finalNumbersArray.push_back(bottomValueIdxPairs[j].value);
                        added = true;
                    }
                    else if(topLineSymbols[i] == bottomValueIdxPairs[j].idx[bottomValueIdxPairs[j].idx.size() + 1]){
                        finalNumbersArray.push_back(bottomValueIdxPairs[j].value);
                        added = true;
                    }
                

                    if(bottomLineSymbols[i] >= bottomValueIdxPairs[j].idx[0] and bottomLineSymbols[i] <= bottomValueIdxPairs[j].idx[bottomValueIdxPairs[j].idx.size()] and added == true){
                        finalNumbersArray.push_back(bottomValueIdxPairs[j].value);
                    }
                    else if (bottomLineSymbols[i] == bottomValueIdxPairs[j].idx[0] - 1){
                        finalNumbersArray.push_back(bottomValueIdxPairs[j].value);
                        added = true;
                    }
                    else if(bottomLineSymbols[i] == bottomValueIdxPairs[j].idx[bottomValueIdxPairs[j].idx.size() + 1]){
                        finalNumbersArray.push_back(bottomValueIdxPairs[j].value);
                        added = true;
                    }
                }
            } 

        }

        if(bottomLineNumber.size() > 0){

            topLineNumber.assign(bottomLineNumber.begin(),bottomLineNumber.end());
            topLineSymbols.assign(bottomLineSymbols.begin(),bottomLineSymbols.end());

            bottomLineNumber.erase(bottomLineNumber.begin(),bottomLineNumber.end());
            bottomLineSymbols.erase(bottomLineSymbols.begin(),bottomLineSymbols.end());

            topLineValue.assign(topLineValue.begin(),topLineValue.end());
            bottomLineValue.erase(bottomLineValue.begin(),bottomLineValue.end());

            //std::cout << "WhAT THE FCUK" << currentNumber.value << " IDX: " << currentNumber.idx[0] << std::endl;
            number_idx newBottom;
            currentNumber = bottomNumber;
            bottomNumber = newBottom;
        }
        



        //std::cout << "new line" << std::endl;
    }
    int highest = -1;
    for(int i = 0; i < finalNumbersArray.size(); i++){
        //std::cout << finalNumbersArray.size() << std::endl;
        //std::cout << "Looped element" << finalNumbersArray[i] << std::endl;
        if(finalNumbersArray[i] >= 961){
            std::cout << "SO CLOSE " << finalNumbersArray[i] << std::endl;
        }
        if(highest == -1){
            highest = finalNumbersArray[i];
        }else if (finalNumbersArray[i] > highest){
            highest = finalNumbersArray[i];
            std::cout << "fake news: " << finalNumbersArray[i] << std::endl;
        }
    }
    std::cout << "HIGHEST: " << highest << std::endl;
    for(int i = 0; i < finalNumbersArray.size(); i++){
        finalNumber += finalNumbersArray[i];
    }
    std::cout << "Final Number: " << finalNumber << std::endl;
    return 0;
}