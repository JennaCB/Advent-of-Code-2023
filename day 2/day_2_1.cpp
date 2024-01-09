#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool color_max_exceeded(std::string color, int amount)
{
    int red_max = 12;
    int green_max = 13;
    int blue_max = 14;

    if(color == "red" && amount <= red_max)
        return false;
    else if(color == "green" && amount <= green_max)
        return false;
    else if(color == "blue" && amount <= blue_max)
        return false;

    return true;
}

int main()
{
    std::vector<std::string> combinations;

    std::ifstream data("day_2.txt");

    std::string line;

    int sum = 0;


    while(std::getline(data, line))
    {
        size_t pos = line.find(':');
        line.erase(0, pos + 1);
        combinations.push_back(line);
    }

    for(int i = 0; i < combinations.size(); i = i + 1)
    {
        std::istringstream stream(combinations[i]);
        while(std::getline(stream, line, ';'))
        {
            std::string something;
            std::istringstream actual(line);
            while(std::getline(actual, something, ','))
            {
                std::stringstream stream2(something);
                int amount;
                while(stream2 >> amount)
                {
                    std::string throw_away;
                    stream2 >> throw_away;

                    if(color_max_exceeded(throw_away, amount))
                    {
                        combinations.at(i) = "False";
                    }
                }
            }
        }
    }

    for(int i = 0; i < combinations.size(); i = i + 1)
    {
        if(combinations[i] != "False")
        {
            sum = sum + i + 1;
        }
    }

    std::cout<<"Sum: "<<sum<<'\n';
}