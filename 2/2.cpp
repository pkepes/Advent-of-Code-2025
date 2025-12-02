#include <iostream>
#include <vector>
#include <fstream>
#include <string>


struct idInterval{
    long long int from;
    long long int to;
};

int fillIdIntervals(std::vector<idInterval>& idIntervals){
    std::ifstream file("2.txt");
    if(!file.is_open()){
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    while(!file.eof()){
        std::string line;
        std::getline(file, line, ',');
        
        std::string::size_type pos = line.find('-');

        std::string from = line.substr(0, pos);
        std::string to = line.substr(pos + 1);

        idInterval i = {
            .from = std::stoll(from),
            .to = std::stoll(to)
        };

        idIntervals.push_back(i);

    }

    file.close();
    return 0;
}

void part1(std::vector<idInterval> idIntervals){

    long long int sum = 0;

    for(idInterval i : idIntervals){

        for(long long iter = i.from; iter <= i.to; iter++){
            std::string s = std::to_string(iter);
            if(s.size() % 2 != 0){
                continue;
            }

            std::string subsLower = s.substr(0, (int)s.size() / 2);
            std::string subsHigher = s.substr(s.size() / 2);

            if(subsLower == subsHigher){
                sum += iter;
            }
            
        }
    }
    std::cout << "Part1 solution is: " << sum << std::endl;
}

int main(){
    std::vector<idInterval> idIntervals;
    fillIdIntervals(idIntervals);

    part1(idIntervals);

    return 0;
}