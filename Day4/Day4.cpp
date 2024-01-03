#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

struct scratchcard
{
    int game_id;
    std::vector<int> winning_nums;
    std::vector<int> player_nums;
    int matching_nums;
};
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
std::vector<int> strvec2intvec (std::vector<std::string> invec)
{
    std::vector<int> outvec;
    for (std::vector<std::string>::iterator pos = invec.begin(); pos < invec.end(); pos++)
    {
        outvec.push_back(std::stoi(*pos));
    }
    return outvec;
}
std::vector<std::string> split_string(std::string input, std::string delimeter)
{
    std::vector<std::string> tokens;
    std::string::iterator pos = input.begin();
    pos = input.begin();
    while(input.find(delimeter)!=std::string::npos)
    {
        pos = input.begin()+input.find(delimeter)+1;
        std::string token = std::string(input.begin(), pos-1);
        if (token!=delimeter && token != " " && token != "")
        {
            tokens.push_back(token);
        }
         input = std::string(pos, input.end());
    }
    if (input.size() >0)
    {
        tokens.push_back(input);
    }
    return tokens;
}
bool found_duplicate(int val, std::vector<int> vec)
{
    for (std::vector<int>::iterator pos = vec.begin(); pos < vec.end(); pos++)
    {
        if (val == *pos)
        {
            return true;
        }
    }
    return false;
}
int count_cards(std::vector<scratchcard> &cardlist, std::vector<scratchcard>::iterator cpos)
{
    int matching_nums = (*cpos).matching_nums;
    int total_cards =1;
    if (matching_nums == 0)
    {
        return 1;
    }
    else {
        while (matching_nums>0)
        {
            *cpos++;
            matching_nums -=1;
            total_cards +=count_cards(cardlist, cpos);
        }
    }
    return total_cards;
}
int main()
{
    int total_score=0;
    std::vector<std::string> raw_input = readfile("/home/tim/Desktop/AOC/AdventOfCodeSolutions/Day4/input");
    std::vector<scratchcard> parsed_input;
    for (std::vector<std::string>::iterator pos = raw_input.begin(); pos<raw_input.end(); pos++)
    {
        int game_id = stoi(split_string((split_string(*pos, ":")[0])," ")[1]);
        std::string winning_nums = split_string(split_string(*pos, ":")[1], "|")[0];
        std::string player_nums = split_string(*pos, "|")[1];

        scratchcard s;
        s.game_id=game_id;
        s.winning_nums = strvec2intvec (split_string(std::string(winning_nums.begin()+1, winning_nums.end()), " "));
        s.player_nums = strvec2intvec(split_string(std::string(player_nums.begin()+1, player_nums.end()), " "));
        s.matching_nums =1;
        parsed_input.push_back(s);
    }
    for (std::vector<scratchcard>::iterator pos = parsed_input.begin(); pos<parsed_input.end(); pos++)
    {
        double temp_score=0.5;
        scratchcard cur = *pos;
        for (std::vector<int>::iterator tpos = cur.player_nums.begin();  tpos<cur.player_nums.end(); tpos++)
        {
            if (found_duplicate (*tpos, cur.winning_nums))
            {
                temp_score*=2;
            }
        }    
        if (temp_score>0.5) total_score += temp_score;    
    }
    std::cout << total_score << std::endl;
    std::vector<scratchcard>::iterator npos = parsed_input.begin(); 
    for (std::vector<scratchcard>::iterator pos = parsed_input.begin(); pos<parsed_input.end(); pos++)
    {
        int score=0;
        scratchcard &cur = *pos;
        for (std::vector<int>::iterator tpos = cur.player_nums.begin();  tpos<cur.player_nums.end(); tpos++)
        {
            if (found_duplicate (*tpos, cur.winning_nums))
            {
                score+=1;
            }
        }    
        cur.matching_nums=score;
    }
    total_score =0;
    for (std::vector<scratchcard>::iterator pos = parsed_input.begin(); pos<parsed_input.end(); pos++)
    {
        total_score += count_cards(parsed_input, pos);
    }
    std::cout << "TOTAL SCORE: " << total_score << std::endl;

}