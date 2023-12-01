#include <iostream>
#include <fstream>
#include <vector>
#include <string>


int main()
{
    std::string filepath = "c:\\Users\\timot\\Desktop\\AdventOfCode\\Day1\\input.txt";
    std::ifstream ifile(filepath);
    std::vector<std::string> filecontent;
    if (ifile.is_open())
    {
        std::string line;
        std::vector<string> string_nums = {"one","two","three","four","five","six","seven","eight","nine","ten"};
        while (std::getline(ifile, line))
        {
            filecontent.push_back(line);
        }
    }
    ifile.close();
    std::vector<std::string>::iterator pos = filecontent.begin();
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