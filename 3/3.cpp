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

void solution(std::vector<std::string>& batteryBanks, int width){

    long long int sum = 0;

    for(std::string b : batteryBanks){
        std::string joltsStr;
        
        std::string::size_type lastIdx = -1;
        for(int i = 0; i < width; i++){
            joltsStr.push_back('\0');
            for(std::string::size_type j = lastIdx + 1; j < b.size() - (width - 1 - i); j++){
                if(b[j] > joltsStr[i]){
                    joltsStr[i] = b[j];
                    lastIdx = j;
                }
            } 
        }
        
        long long jolts = std::stoll(joltsStr);
        sum += jolts;
    }

    std::cout << "Solution for " << width << " width batteryBank is: " << sum << std::endl;
}

int main(){
    std::vector<std::string> batteryBanks;

    fillBatteryBanks(batteryBanks);
    solution(batteryBanks, 2);
    solution(batteryBanks, 12);

    return 0;
}