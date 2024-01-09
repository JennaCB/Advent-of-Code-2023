#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void min_color_amount(std::string color, int color_value, int& current_color_min)
{
    if(color =="red" && color_value > current_color_min)
        current_color_min = color_value;
    else if (color =="green" && color_value > current_color_min)
        current_color_min = color_value;
    else if (color =="blue" && color_value > current_color_min)
        current_color_min = color_value;
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
        int min_red = 0;
        int min_green = 0;
        int min_blue = 0;

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

                    if(throw_away == "red")
                        min_color_amount(throw_away, amount, min_red);
                    else if(throw_away == "green")
                        min_color_amount(throw_away, amount, min_green);
                    else if(throw_away == "blue")
                        min_color_amount(throw_away, amount, min_blue);
                }
            }
        }

        int power_of_set = min_red * min_green * min_blue;

        sum = sum + power_of_set;
    }

    std::cout<<"Sum: "<<sum;
}