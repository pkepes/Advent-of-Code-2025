#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("1.txt");
    if(!file.is_open()){
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    int pos = 50;
    int password = 0;

    while(!file.eof()){
        std::string line;
        file >> line;
        
        char dir = line[0];
        int num = std::stoi(line.substr(1));
        num %= 100;

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
            return 1;
        }

        if(pos == 0){
            password++;
        }
    }

    std::cout << "Password is: " << password << std::endl;

    file.close();
    return 0;
}