#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

void fillMap(std::vector<std::vector<bool>>& map){
    std::ifstream file("4.txt");
    if(!file.is_open()){
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    while(!file.eof()){
        std::string line;
        file >> line;
        std::vector<bool> row;
        
        for(char c : line){
            if(c == '.') row.push_back(false);
            else if(c == '@') row.push_back(true);
            else std::cerr << "Error reading the file" << std::endl;
        }

        map.push_back(row);

    }

    file.close();
    return;  
}

//GPT:((
std::vector<std::pair<int, int>> getNeighbours(const std::vector<std::vector<bool>>& map, int x, int y) {

    std::vector<std::pair<int, int>> n;

    int width  = map[0].size();
    int height = map.size();

    auto add = [&](int nx, int ny){
        if(nx >= 0 && nx < width && ny >= 0 && ny < height)
            n.emplace_back(nx, ny);
    };

    for(int dy = -1; dy <= 1; ++dy){
        for(int dx = -1; dx <= 1; ++dx){
            if(dx == 0 && dy == 0)
                continue;

            add(x + dx, y + dy);
        }
    }

    return n;
}


bool hasMoreThanNNeighbours(std::vector<std::vector<bool>>& map, int x, int y, int N = 4){
    std::vector<std::pair<int, int>> neighbours = getNeighbours(map, x, y);

    int count = 0;

    for(auto p : neighbours){
        if(map[p.second][p.first] == true){
            count++;
        }
    }

    return !(count >= N);
}

void part1(std::vector<std::vector<bool>>& map){
    int count = 0;

    for(int y = 0; y < map.size(); y++){
        for(int x = 0; x < map[y].size(); x++){
            if(map[y][x] == false){
                continue;
            }
            if(hasMoreThanNNeighbours(map, x, y, 4) == true){
                count++;
            }
        }
    }

    std::cout << "Part1 solution is: " << count << std::endl;
}

//Very inefficient but works
void part2(std::vector<std::vector<bool>>& map){
    int count = 0;
    bool foundRemovable;
    
    do{
        foundRemovable = false;
        for(int y = 0; y < map.size(); y++){
            for(int x = 0; x < map[y].size(); x++){
                if(map[y][x] == false){
                    continue;
                }
                if(hasMoreThanNNeighbours(map, x, y, 4) == true){
                    count++;
                    foundRemovable = true;
                    map[y][x] = false;
                }
            }
        }
    }
    while(foundRemovable);
    std::cout << "Part2 solution is: " << count << std::endl;
}

int main(){
    std::vector<std::vector<bool>> map;
    fillMap(map);
    part1(map);
    part2(map);

    return 0;
}