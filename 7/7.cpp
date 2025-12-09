#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void fillInput(std::vector<std::string>& input){
    std::ifstream file("7_test.txt");
    if(!file.is_open()){
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    while(!file.eof()){
        std::string line;
        std::getline(file, line);
        
        input.push_back(line);
    }

    file.close();
    return;
}

bool isUnique(std::vector<std::pair<int, int>> vec, std::pair<int, int> element){
    for(auto v : vec){
        if(v.first == element.first && v.second == element.second){
            return false;
        }
    }
    return true;
}

void part1(std::vector<std::string> input){
    long sum = 0;
    std::vector<std::pair<int, int>> positions;
    for(int i = 0; i < input[0].size(); i++){
        if(input[0][i] == 'S'){
            positions.push_back(std::pair<int, int>(1, i));
            break;
        }
    }
    for(int row = 1; row < input.size(); row++){
        std::vector<std::pair<int, int>> newPositions;
        for(int i = 0; i < positions.size(); i++){

            for(int col = 0; col < input[row].size(); col++){
                if(input[row][col] == '^' && positions[i].first == row && positions[i].second == col){
                    bool splitted = false;
                    if(col != 0 && row != input.size() - 1){
                        if(isUnique(newPositions, std::pair<int, int>(row + 1, col - 1))){
                            newPositions.push_back(std::pair<int, int>(row + 1, col - 1));
                            std::cout << "Keetéesik a " << positions[i].first << " " << positions[i].second << std::endl;
                            splitted = true;
                        }
                        
                    }
                    if(col != input[row].size() - 1 && row != input.size() - 1){
                        if(isUnique(newPositions, std::pair<int, int>(row + 1, col + 1))){
                            newPositions.push_back(std::pair<int, int>(row + 1, col + 1));
                            std::cout << "Keetéesik a " << positions[i].first << " " << positions[i].second << std::endl;
                            splitted = true;
                        }
                    }
                    if(splitted) sum++;
                }
                else if (positions[i].first == row && positions[i].second == col){
                    if(row != input.size() - 1){
                        if(isUnique(newPositions, std::pair<int, int>(positions[i].first + 1, positions[i].second))){
                            newPositions.push_back(std::pair<int, int>(positions[i].first + 1, positions[i].second));
                            std::cout << "Lefele megy a " << positions[i].first << " " << positions[i].second << std::endl;
                        }
                    } 
                }
            }

            
        }
        positions = newPositions;
        std::cout << "------------------" << std::endl;
        for(auto p : positions){
            std::cout << p.first << " " << p.second << std::endl;
        }
        std::cout << "------------------" << std::endl;
    }

    std::cout << "Part1 solution is: " << sum << std::endl;
}

int main(){
    std::vector<std::string> input;

    fillInput(input);
    part1(input);
}