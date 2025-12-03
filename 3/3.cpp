#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void fillBatteryBanks(std::vector<std::string>& batteryBanks){
    std::ifstream file("3.txt");
    if(!file.is_open()){
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    while(!file.eof()){
        std::string line;
        file >> line;

        batteryBanks.push_back(line);
    }

    file.close();
    return;
}

void part1(std::vector<std::string>& batteryBanks){

    int sum = 0;

    for(std::string b : batteryBanks){
        char first = b[0];
        std::string::size_type firstIdx = 0;
        char second = '\0';

        for(std::string::size_type i = 0; i < b.size() - 1; i++){
            if(b[i] > first){
                first = b[i];
                firstIdx = i;
            }
        }

        for(std::string::size_type i = firstIdx + 1; i < b.size(); i++){
            if(b[i] > second){
                second = b[i];
            }
        }
        
        int jolts = ((int)first - (int)'0') * 10 + ((int)second - (int)'0');
        sum += jolts;
    }

    std::cout << "Part1 solution is: " << sum << std::endl;
}

int main(){
    std::vector<std::string> batteryBanks;

    fillBatteryBanks(batteryBanks);
    part1(batteryBanks);

    return 0;
}