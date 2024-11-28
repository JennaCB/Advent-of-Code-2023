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

std::vector<pos> save_symbol_positions(const std::vector<std::vector<char>>& data, int i, int j)
{
    std::vector<pos> symbol_positions;

    if(i+1 < data.size())
    {
        if(j+1 < data[i].size())
            symbol_positions.push_back(pos{j+1, i+1});
        symbol_positions.push_back(pos{j, i+1});
        if(j != 0)
            symbol_positions.push_back(pos{j-1, i+1});
    }
    if(j != 0 && !isdigit(data[i][j-1]))
        symbol_positions.push_back(pos{j-1, i});
    if(i != 0)
    {
        if(j != 0)
            symbol_positions.push_back(pos{j-1, i-1});
        symbol_positions.push_back(pos{j, i-1});
        if(j+1 < data[i].size())
            symbol_positions.push_back(pos{j+1, i-1});
    }
    if(j+1 < data[i].size() && !isdigit(data[i][j+1]))
        symbol_positions.push_back(pos{j+1, i});

    return symbol_positions;
}

bool is_part(std::vector<std::vector<char>>& data, std::vector<pos>& symbol_positions)
{
    for(pos position : symbol_positions)
    {
        if(!isdigit(data[position.y][position.x]) && data[position.y][position.x] != '.') 
            return true;
    }
    return false;
}

int main(int argc, char* argv[])
{
    std::ifstream input(argv[1]);

    int sum = 0;

    std::vector<std::vector<char>> data = load_data(input);

    std::string potential_part;
    std::vector<pos> symbol_positions;

    for(std::size_t i = 0; i < data.size(); ++i) 
    {
        for(std::size_t j = 0; j < data[i].size(); ++j) 
        {
            if(isdigit(data[i][j]))
            {
                potential_part.push_back(data[i][j]);

                for(pos i : save_symbol_positions(data, i, j))
                    symbol_positions.push_back(i);
            }
            else
            {
                if(!potential_part.empty())
                {
                    if(is_part(data, symbol_positions))
                    {
                        sum = sum + std::stoi(potential_part);
                    }

                    potential_part.clear();
                    symbol_positions.clear();
                }
            }
        }
        if(!potential_part.empty())
        {
            if(is_part(data, symbol_positions))
            {
                sum = sum + std::stoi(potential_part);
            }

            potential_part.clear();
            symbol_positions.clear();
        }
    }

    std::cout<<"SUM: "<<sum;
}