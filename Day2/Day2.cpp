#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
int main()
{
    std::string test = ",Testing,Commas,as,Delimeters,";
    std::vector<std::string> result = split_string(test, ",");
    int i =0;
    std::cout<< result.size()<<std::endl;
    for (std::vector<std::string>::iterator pos = result.begin(); pos<result.end(); pos++)
    {
        std::cout<<i << ": " << *pos <<std::endl;
        i++;
    }
}
