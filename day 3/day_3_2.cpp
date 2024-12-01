#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct pos{
    int x, y;
};

std::vector<std::vector<char>> load_data(std::ifstream& input)
{
    std::vector<std::vector<char>> data;

    std::string line;
    while(getline(input, line))
    {
        data.push_back(std::vector<char>(line.begin(), line.end()));
    }

    return data;
}

void print_data(const std::vector<std::vector<char>>& data)
{
    for(std::size_t i = 0; i < data.size(); ++i)
    {
        for(std::size_t j = 0; j < data[i].size(); ++j)
        {
            std::cout<<data[i][j]<<' ';
        }
        std::cout<<'\n';
    }
}

std::vector<pos> search_for_parts(const std::vector<std::vector<char>>& data, int i, int j)
{
    std::vector<pos> part_positions;

    for(int index: {i-1, i+1})
    {
        if(isdigit(data[index][j]))
            part_positions.push_back(pos{j, index});
        else
        {
            if(isdigit(data[index][j-1]))
                part_positions.push_back(pos{j-1, index});
            if(isdigit(data[index][j+1]))
                part_positions.push_back(pos{j+1, index});
        }
    }

    if(isdigit(data[i][j-1]))
        part_positions.push_back(pos{j-1, i});

    if(isdigit(data[i][j+1]))
        part_positions.push_back(pos{j+1, i});

    return part_positions;
}

std::string determine_whole_part(const std::vector<std::vector<char>>& data, const pos& part_position)
{
    std::string part;
    
    part.push_back(data[part_position.y][part_position.x]);
    
    for(int x = part_position.x + 1; isdigit(data[part_position.y][x]); ++x)
        part.push_back(data[part_position.y][x]);
    for(int x = part_position.x - 1; isdigit(data[part_position.y][x]); --x)
        part.insert(0, 1, data[part_position.y][x]);

    return part;
}

int main(int argc, char* argv[])
{
    std::ifstream input(argv[1]);

    int sum = 0;

    std::vector<std::vector<char>> data = load_data(input);

    for(std::size_t i = 0; i < data.size(); ++i)
    {
        for(std::size_t j = 0; j <data[i].size(); ++j)
        {
            if(data[i][j] == '*')
            {
                std::vector<pos> part_positions = search_for_parts(data, i, j);
                if(part_positions.size() == 2)
                {
                    std::string part_1 = determine_whole_part(data, part_positions[0]);
                    std::string part_2 = determine_whole_part(data, part_positions[1]);

                    int gear_ratio = std::stoi(part_1) * std::stoi(part_2);

                    sum = sum + gear_ratio;
                }
            }
        }
    }

    std::cout<<"SUM: "<<sum;
}