#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

void load_data(std::ifstream& source, std::vector<std::string>& data)
{
	std::string line;
	while(std::getline(source, line))
	{
		data.push_back(line);
	}
}

int main()
{
    std::ifstream data("day_1.txt");

	std::vector<std::string> text;

	int first_sum = 0;
	int second_sum = 0;

    load_data(data, text);

	std::vector<std::string> number_names{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "1", "2", "3", "4", "5", "6", "7", "8", "9"};


	for(std::string line : text)
	{
		std::string numbers;

		for(char potential_number : line)
		{
			if(std::isdigit(potential_number))
			{
				numbers = numbers + potential_number;
			}
		}
		std::string calibration_value_1 = std::string(1, numbers.front()) + numbers.back();
		first_sum = first_sum + std::stoi(calibration_value_1);


		// Solution for Part 2

		std::map<int, int> all_numbers;
		for(int i = 0; i < number_names.size(); i = i + 1)
		{
			std::string to_find = number_names[i];
			

			std::size_t current_position = line.find(number_names[i]);
			while(current_position <line.size())
			{
				std::size_t found_at = current_position;

				bool is_found = line.find(to_find) != std::string::npos;


				if(is_found)
				{
					if(to_find == "one")
					{
						all_numbers[found_at] = 1;
					}
					else if(to_find == "two")
					{
						all_numbers[found_at] = 2;
					}
					else if(to_find == "three")
					{
						all_numbers[found_at] = 3;
					}
					else if(to_find == "four")
					{
						all_numbers[found_at] = 4;
					}
					else if(to_find == "five")
					{
						all_numbers[found_at] = 5;
					}
					else if(to_find == "six")
					{
						all_numbers[found_at] = 6;
					}
					else if(to_find == "seven")
					{
						all_numbers[found_at] = 7;
					}
					else if(to_find == "eight")
					{
						all_numbers[found_at] = 8;
					}
					else if(to_find == "nine")
					{
						all_numbers[found_at] = 9;
					}
					else
					{
						all_numbers[found_at] = std::stoi(to_find);
					}
				}
				current_position = line.find(number_names[i], current_position + 1);
			}
		}
		std::string calibration_value_2 = std::to_string(all_numbers.begin() -> second) + std::to_string(all_numbers.rbegin() -> second);
		second_sum = second_sum + std::stoi(calibration_value_2);
	}
	std::cout<<"Sum Part 1: "<<first_sum<<'\n';
	std::cout<<"Sum Part 2: "<<second_sum;
}