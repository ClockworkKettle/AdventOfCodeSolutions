#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <queue>
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
bool contains_part_num(std::string str)
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
bool ratio_found(std::string str)
{
    bool innum = false;
    int count = 0;
    for (std::string::iterator pos = str.begin(); pos<str.end(); pos++)
    {
        
        if (isdigit(*pos)&& !innum)
        {
            count++;
            innum=true;
        }
        else if (!isdigit(*pos))
        {
            innum=false;
        }      
    }
    return (count > 1);
}
std::string get_full_num(std::string &line, std::string::iterator pos)
{
    std::string::iterator start_pos, end_pos;

    for (std::string::iterator numpos = pos; numpos>line.begin(); numpos--)
    {
        if (isdigit(*numpos))
        {
            start_pos = numpos;
        }
        else
        {
            break;
        }
    }
        for (std::string::iterator numpos = pos; numpos<line.end(); numpos++)
    {
        if (isdigit(*numpos))
        {
            end_pos = numpos+1;
        }
        else
        {
            break;
        }
    }
    return (std::string(start_pos, end_pos));
}
std::queue<std::string> get_gear_nums(int i_start, std::queue<std::string> lines)
{
    int nums_found = 0;
    std::queue<std::string> s;
    bool innum = false;
    std::string cur_line = lines.front();
    std::string::iterator cpos = cur_line.begin()+i_start;
    while(!lines.empty())
    {
        if(cpos > cur_line.begin()+i_start+2 || cpos < cur_line.begin()+i_start)
        {
        lines.pop();
        cur_line = lines.front();            
        cpos = cur_line.begin()+i_start;
        innum=false;
        }
        else if (isdigit(*cpos) && !innum)
        {
            s.push(get_full_num(cur_line, cpos));
            nums_found++;
            innum = true;
            cpos++;
            
        }
        else if(isdigit(*cpos) && innum)
        {
            cpos++;
        }
        else if(!isdigit(*cpos) && innum)
        {
            innum=false;
            cpos++;
        }
        else{
            cpos++;
        }
    }
    return s;
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
                if (contains_part_num(test_str))
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
    /*
            Part 2 
    */
    sum=0;
    for (std::vector<std::string>::iterator nloc = raw_input.begin()+1; nloc<raw_input.end()-1; nloc++)
    {
        std::string cur_line = *nloc;
        std::string prev_line = *(nloc-1);
        std::string next_line = *(nloc+1);

        for (std::string::iterator cloc = cur_line.begin(); cloc < cur_line.end(); cloc++ )
        {

            if (*cloc == '*')
            {
                int start = cloc - cur_line.begin()-1;
                std::string test_str = std::string(prev_line.begin()+start, prev_line.begin()+start+3)+"."
                +std::string(cur_line.begin()+start, cur_line.begin()+start+3)+"."
                +std::string(next_line.begin()+start, next_line.begin()+start+3);
                std::queue<std::string> test_lines;
                test_lines.push(prev_line);
                test_lines.push(cur_line);
                test_lines.push(next_line);


                // if ratio found, we know there are two numbers, get start and end of both nums and divide first by last.
                if (ratio_found(test_str))
                {
                  std::queue<std::string> nums= get_gear_nums(start, test_lines);
                  std::string num1 = nums.front();
                  nums.pop();
                  std::string num2 = nums.front();

                  sum += stoi(num1)*stoi(num2);
                }
            }
        }
        
    }
    std::cout << "SUM: " << sum << std::endl;

}