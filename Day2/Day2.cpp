#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

int pospow(int b, int p)
{
    if (p == 0)
    {
        return 1;
    }
    else{
        return b*(pospow (b, p-1));
    }
}
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
std::string remove_char(std::string input, char delimeter)
{
    std::string::iterator pos = input.begin();
    std::string output;
    for (pos; pos<input.end(); pos++)
    {
        if(*pos != delimeter)
        {
            output+=*pos;
        }
    }
    return output;
}
std::string replace_char(std::string input, char target, char replacement)
{
    std::string::iterator pos = input.begin();
    std::string output;
    for (pos; pos<input.end(); pos++)
    {
        if(*pos!= target){
            output+=*pos;
        }
        else{
            output+=replacement;
        }
    }
    return output;
}
int string_to_int(std::string stringnum)
{
    int output =0;
    int size = stringnum.size();
    for (std::string::iterator pos = stringnum.begin(); pos<stringnum.end(); pos++)
    {
        output = output + (int(*pos-'0')) * pospow(10, size-1);
        size--;
    }
    return output;
}
void tester(std::string input, std::string delimeter)
{
    std::vector<std::string> result = split_string(input, delimeter);
    int i =0;
    std::cout<< result.size()<<std::endl;
    for (std::vector<std::string>::iterator pos = result.begin(); pos<result.end(); pos++)
    {
        i++;
    }

}
int main()
{
    std::vector<std::string> raw_input = readfile("/home/tim/Desktop/AOC/AdventOfCodeSolutions/Day2/input");
    std::vector<int> possible_games;
    std::map<std::string, int> max_colour = {
        {"red", 12},
        {"green", 13},
        {"blue", 14}
    };
    for (std::vector<std::string>::iterator line=raw_input.begin(); line<raw_input.end(); line++)
    {
        int game_id= string_to_int(*(split_string(*((split_string(*line, ":")).begin()), " ").end()-1));
        std::string games = *((split_string(*line, ":")).end()-1);
        games = replace_char(games, ';', ',');
        std::vector<std::string> draws = split_string(games, ",");
        for (std::vector<std::string>::iterator pos = draws.begin(); pos<draws.end(); pos++)
        {
            if (max_colour[*(split_string(*pos, " ").begin()+1)] < string_to_int(*(split_string(*pos, " ").begin())))
            {
                game_id = 0;
            }
        }
        possible_games.push_back(game_id);
    }
    int count=0;
    for (std::vector<int>::iterator loc= possible_games.begin(); loc < possible_games.end(); loc++)
    {
        count += *loc;
    } 
    std::cout<<"COUNT: " << count << std::endl;
    /* Part 2 */
    count =0;
    for (std::vector<std::string>::iterator line=raw_input.begin(); line<raw_input.end(); line++)
        {
            max_colour["red"] = 0;
            max_colour["green"] = 0;
            max_colour["blue"] = 0;

            std::string games = *((split_string(*line, ":")).end()-1);
            games = replace_char(games, ';', ',');
            std::vector<std::string> draws = split_string(games, ",");
            for (std::vector<std::string>::iterator pos = draws.begin(); pos<draws.end(); pos++)
            {
                if (max_colour[*(split_string(*pos, " ").begin()+1)] < string_to_int(*(split_string(*pos, " ").begin())))
                {
                    max_colour[*(split_string(*pos, " ").begin()+1)] = string_to_int(*(split_string(*pos, " ").begin()));
                }
            }
            count += max_colour["red"]*max_colour["green"]*max_colour["blue"];
        }
        std::cout<<"COUNT: " << count << std::endl;
      
}
