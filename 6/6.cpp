#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <sstream>

enum class Rule {
    RULE_ADD,
    RULE_MULTIPLY
};

struct Dataset{
    Rule rule;
    std::vector<int> numbers;
};

void fillDataPart1(std::vector<std::vector<int>>& numbers, std::vector<Rule>& rules){
    std::ifstream file("6.txt");
    if(!file.is_open()){
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    while(!file.eof()){
        std::string line;
        std::getline(file, line);

        if(line[0] == '*' || line[0] == '+'){
            std::istringstream iss(line);
            char c;
            while(iss >> c){
                if(c == '*') rules.push_back(Rule::RULE_MULTIPLY);
                else if(c == '+') rules.push_back(Rule::RULE_ADD);
            }
        }
        else{
            std::vector<int> row;
            std::istringstream iss(line);
            int n;
            while (iss >> n) {
                row.push_back(n);
            }
            numbers.push_back(row);
        }
    }

    file.close();
    return;
}

void fillDataPart2(std::vector<std::vector<int>>& numbers, std::vector<Rule>& rules){
    std::ifstream file("6.txt");
    if(!file.is_open()){
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::vector<std::string> lines;

    while(!file.eof()){
        std::string line;
        std::getline(file, line);
        lines.push_back(line);
    }

    file.close();

    std::string ruleLine = lines.back();
    lines.pop_back();

    //Err check
    int length = lines[0].size();
    for(auto l : lines){
        if(l.size() != length){
            std::cerr << "Failed to parse" << std::endl;
            return;
        }
    }
    if(ruleLine.size() != length){
        std::cerr << "Failed to parse" << std::endl;
        return;
    }

    std::vector<int> oneOperation;
    Rule r;
    for(long idx = 0; idx < length; idx++){

        //check end of operation
        bool endOfOperation = true;
        for(auto l : lines){
            if(l[idx] != ' '){
                endOfOperation = false;
                break;
            }
        }
        if(endOfOperation){
            numbers.push_back(oneOperation);
            oneOperation.clear();
            rules.push_back(r);
            continue;
        }

        if(ruleLine[idx] != ' '){
            if(ruleLine[idx] == '*'){
                r = Rule::RULE_MULTIPLY;
            }
            else if(ruleLine[idx] == '+'){
                r = Rule::RULE_ADD;
            }
        }

        int num = 0;
        bool alreadyAdded = false;
        for(auto l : lines){
            char c = l[idx];
            if(c == ' ' && num != 0){ //kész szám
                oneOperation.push_back(num);
                alreadyAdded = true;
                break;
            }
            else if(c != ' '){
                num *= 10;
                num += ((int)c - (int)'0');
            }
        }

        if(!alreadyAdded){
            oneOperation.push_back(num);
        }

    }

    rules.push_back(r);
    numbers.push_back(oneOperation);

    return;
}

void part1(std::vector<std::vector<int>> numbers, std::vector<Rule> rules){
    if(numbers.size() == 0) return;

    long long sum = 0;
    for(int col = 0; col < numbers[0].size(); col++){
        if(rules[col] == Rule::RULE_MULTIPLY){
            long long productPart = 1;
            for(int row = 0; row < numbers.size(); row++){
                productPart *= numbers[row][col];
            }
            sum += productPart;
        }
        else if(rules[col] == Rule::RULE_ADD){
            long long sumPart = 0;
            for(int row = 0; row < numbers.size(); row++){
                sumPart += numbers[row][col];
            }
            sum += sumPart;
        }
    }

    std::cout << "Part1 solution is " << sum << std::endl;
}

void part2(std::vector<std::vector<int>> numbers, std::vector<Rule> rules){
    long long sum = 0;
    
    for(int i = 0; i < numbers.size(); i++){
        if(rules[i] == Rule::RULE_MULTIPLY){
            long long productPart = 1;
            for(int j = 0; j < numbers[i].size(); j++){
                productPart *= numbers[i][j];
            }
            sum += productPart;
        }
        else if(rules[i] == Rule::RULE_ADD){
            long long sumPart = 0;
            for(int j = 0; j < numbers[i].size(); j++){
                sumPart += numbers[i][j];
            }
            sum += sumPart;
        }
    }

    std::cout << "Part2 solution is " << sum << std::endl;
}

int main(){
    std::vector<std::vector<int>> numbers;
    std::vector<Rule> rules;

    fillDataPart1(numbers, rules);
    part1(numbers, rules);
    numbers.clear();
    rules.clear();
    fillDataPart2(numbers, rules);
    part2(numbers, rules);
}