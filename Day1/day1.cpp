#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> readfile(std::string filepath)
{
    std::vector<std::string> filecontent;
    std::ifstream ifile(filepath);
    if (ifile.is_open())
    {
        std::string line;
        while (std::getline(ifile, line))
        {
            filecontent.push_back(line);
        }
    }
    ifile.close();
    return filecontent;
}
std::string parse_substring(std::string input, std::string num, std::string num_parsed)
{
    if(input.find(num) != std::string::npos)
    {
        input.replace(input.find(num), num.length(), num_parsed);
        input = parse_substring(input, num, num_parsed);
    }
    return input;
}
int main()
{
    std::vector<std::string> unparsed_filecontent = readfile("c:\\Users\\timot\\Desktop\\AdventOfCode\\Day1\\input.txt");
    std::vector<std::string>::iterator pos = unparsed_filecontent.begin();
    std::vector<std::string> string_nums = {"one", "o1e", "two", "t2o", "three", "t3e", "four", "f4r", "five", "f5e", "six",
    "s6x", "seven", "s7n", "eight", "e8t", "nine", "n9e"};
    std::vector<std::string> filecontent;
    while (pos < unparsed_filecontent.end())
    {
        std::string temp= *pos;
        for (int i=0; i<string_nums.size(); i+=2)
        {
            temp = parse_substring(temp, string_nums[i], string_nums[i+1]);
        }
        filecontent.push_back(temp); 
        pos++;
    }


    pos = filecontent.begin();
    int accumulator=0; 
    int first;
    int last;
    bool firstfound = false;
    while (pos < filecontent.end())
    {
        std::string current_line = *pos;
        std::string::iterator car = current_line.begin();
        first = 0;
        last = 0;
        firstfound=false;
        while (car < current_line.end())
        {
            if (std::isdigit(*car))
            {
                last = (int)*car - '0';
                if (!firstfound)
                {
                    firstfound = true;
                    first = (int) *car -'0';
                }
            }
            car++;
        }
        accumulator = accumulator + (10* first) + last;
        std::cout << *pos << " " << first << " "  << last << std::endl;
        pos++;

        std::cout << accumulator << std::endl;
    }
}