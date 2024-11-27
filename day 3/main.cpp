#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct pos{
    int x, y;
};

std::vector<std::vector<char>> save_data(std::ifstream& input)
{
    std::vector<std::vector<char>> data;

    int line_counter = 0;

    std::string line;
    while(getline(input, line))
    {
        data.push_back(std::vector<char>());
        for(char i : line)
        {
            data[line_counter].push_back(i);
        }
        line_counter++;
    }

    return data;
}

void print_data(std::vector<std::vector<char>>& data)
{
    for(int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < data[i].size(); j++)
        {
            std::cout<<data[i][j]<<' ';
        }
        std::cout<<'\n';
    }
}

std::vector<pos> save_symbol_positions(std::vector<std::vector<char>>& data, int i, int j)
{
    std::vector<pos> symbol_positions;

    if(i != (data.size() - 1))
    {
        if(j != (data[i].size() - 1))
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
        if(j != (data[i].size() - 1))
            symbol_positions.push_back(pos{j+1, i-1});
    }
    if(j != (data[i].size() - 1) && !isdigit(data[i][j+1]))
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

    int sum;

    std::vector<std::vector<char>> data = save_data(input);

    std::string potential_part;
    std::vector<pos> symbol_positions;

    for(int i = 0; i < data.size(); i++) 
    {
        for(int j = 0; j < data[i].size(); j++) 
        {
            if(isdigit(data[i][j]))
            {
                potential_part.push_back(data[i][j]);

                std::vector<pos> temp = save_symbol_positions(data, i, j);
                for(pos i : temp)
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