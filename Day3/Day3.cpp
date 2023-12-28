#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
std::vector<std::string> file2vec(std::string filepath)
{
    std::vector<std::string> filecontent;
    std::ifstream ifile(filepath);
    if (ifile.is_open())
    {
        std::string line;
        while (std::getline(ifile, line))
        {
            filecontent.push_back("." + line + ".");
        }
    }
    ifile.close();
    return filecontent;
}
bool part_num(std::string str)
{
    for (std::string::iterator pos=str.begin(); pos< str.end(); pos ++)
    {
        if (!isdigit(*pos) && *pos != '.')
        {
            return true;
        }
    }
    return false;
}
int main()
{
    std::vector<std::string> raw_input = file2vec("/home/tim/Desktop/AOC/AdventOfCodeSolutions/Day3/input");
    std::vector<std::string>::iterator pos = raw_input.begin();
    std::string line1 = *pos;
    std::string t(line1.end()-line1.begin(), '.');
    raw_input.insert(raw_input.begin(), t);
    raw_input.insert(raw_input.end(), t);
    int sum =0;
    std::vector<std::string> part_nums; 
    *pos++;
    for (std::vector<std::string>::iterator nloc = raw_input.begin()+1; nloc<raw_input.end()-1; nloc++)
    {
        std::string targetline = *nloc;
        std::string prevline = *(nloc -1);
        std::string nextline = *(nloc+1);
        std::string::iterator scan_start, scan_end;
        bool scanning_num = false;
        for (std::string::iterator cpos = targetline.begin()+1; cpos < targetline.end()-1; cpos++)
        {
            if (isdigit(*cpos))
            {
                std::string::iterator start_num = cpos-1;
                std::string num ="";
                while (isdigit(*cpos))
                {
                    num+= *cpos; 
                    *cpos++;
                }
                std::string::iterator end_num = cpos+1;

                std::string test_str = std::string(start_num, end_num);
                int start_index = start_num-targetline.begin();
                int end_index = end_num-targetline.begin();
                test_str = std::string(prevline.begin()+start_index, prevline.begin()+end_index) + std::string(start_num,  end_num) + std::string(nextline.begin()+start_index, nextline.begin()+end_index);
                if (part_num(test_str))
                {
                    part_nums.push_back(num);
                }
                else{

                }
            } 
        }
    }
    for (pos=part_nums.begin(); pos<part_nums.end(); pos++)
    {
        sum += std::stoi(*pos);
    }
    std::cout << "Sum of all part nums: " << sum << std::endl;

    for (std::vector<std::string>::iterator nloc = raw_input.begin()+1; nloc<raw_input.end()-1; nloc++)
    {
        
    }

}