#include <iostream>
#include <fstream>
#include <string>

struct Instruction {
    char direction;
    int value;
};

int fillInstructions(std::vector<Instruction>& instructions){
    std::ifstream file("1.txt");
    if(!file.is_open()){
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    while(!file.eof()){
        std::string line;
        file >> line;
        char dir = line[0];
        int num = std::stoi(line.substr(1));

        Instruction i = {
            .direction = dir,
            .value = num
        };
        instructions.push_back(i);
    }

    file.close();
    return 0;
}

void part1(std::vector<Instruction>& instructions){
    int pos = 50;
    int password = 0;

    for(Instruction i : instructions){
        char dir = i.direction;
        int num = i.value % 100;

        if(dir == 'L'){
            if(pos - num < 0){
                pos += 100;
            }
           pos -= num;
        }
        else if(dir == 'R'){
            if(pos + num > 99){
                pos -= 100;
            }
           pos += num;
        }
        else{
            return;
        }

        if(pos == 0){
            password++;
        }
    }

    std::cout << "Part1 Password is: " << password << std::endl;
}

void part2(std::vector<Instruction>& instructions){
    int pos = 50;
    int password = 0;

    for(Instruction i : instructions){
        char dir = i.direction;
        int num = i.value % 100;
        password += (int)i.value / 100;

        if(dir == 'L'){
            if(pos - num < 0){
                if(pos - num != 0 && pos != 0){ //(pos == 0): starting from 0
                    password++;
                }
                pos += 100;
            }
           pos -= num;
        }
        else if(dir == 'R'){
            if(pos + num > 99){
                if(pos + num != 100 && pos != 0){ //(pos + num == 100):turned to 0 (pos == 0): starting from 0
                    password++;
                }
                
                pos -= 100;
            }
           pos += num;
        }
        else{
            return;
        }

        if(pos == 0){
            password++;
        }
    }

    std::cout << "Part2 Password is: " << password << std::endl;
}

int main() {
    std::vector<Instruction> instructions;
    int retval = fillInstructions(instructions);
    if(retval != 0){
        return retval;
    }

    part1(instructions);
    part2(instructions);
    
    return 0;
}