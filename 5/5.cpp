#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>

void fillData(std::vector<std::pair<long long, long long>>& freshIngredientIntervals, std::vector<long long>& availableIngredients){
    std::ifstream file("5.txt");
    if(!file.is_open()){
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    while(!file.eof()){
        std::string line;
        std::getline(file, line);
        if(line.empty()){ //intervals ended
            break;
        }
        
        std::string::size_type pos = line.find('-');

        std::string from = line.substr(0, pos);
        std::string to = line.substr(pos + 1);


        freshIngredientIntervals.push_back(std::pair<long long, long long>(std::stoll(from), std::stoll(to)));
    }

    while(!file.eof()){
        std::string line;
        file >> line;

        availableIngredients.push_back(std::stoll(line));
    }

    file.close();
    return;
}

void part1(std::vector<std::pair<long long, long long>>& freshIngredientIntervals, std::vector<long long>& availableIngredients){
    int sum = 0;
    for(auto i : availableIngredients){
        for(auto interval : freshIngredientIntervals){
            if(i >= interval.first && i <= interval.second){
                sum++;
                break;
            }
        }
    }

    std::cout << "Part1 solution is: " << sum << std::endl;
}

void part2(std::vector<std::pair<long long, long long>> intervals){
    for(int i = 0; i < intervals.size(); i++){
        for(int j = 0; j < intervals.size(); j++){
            if(i == j) continue;
            if(intervals[i].first >= intervals[j].first && intervals[i].second <= intervals[j].second){ //teljesen benne van i j-ben
                intervals[i].first = 0;
                intervals[i].second = 0;
                break;
            }
            else if(intervals[i].first <= intervals[j].first && intervals[i].second >= intervals[j].first && intervals[i].second <= intervals[j].second){ //Balra kilóg
                intervals[i].second = intervals[j].first - 1;
            }
            else if(intervals[i].first >= intervals[j].first && intervals[i].second >= intervals[j].second && intervals[i].first <= intervals[j].second){ //Jobbra kilóg
                intervals[i].first = intervals[j].second + 1;
            }
        }
    }

    long long sum = 0;
    for(auto i : intervals){
        if(i.first == 0 && i.second == 0) continue;
        sum += (i.second - i.first) + 1;
    }

    std::cout << "Part2 solution is: " << sum << std::endl;
}

int main(){
    std::vector<std::pair<long long, long long>> freshIngredientIntervals;
    std::vector<long long> availableIngredients;

    fillData(freshIngredientIntervals, availableIngredients);
    part1(freshIngredientIntervals, availableIngredients);
    part2(freshIngredientIntervals);
}