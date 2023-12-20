#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> split_string(std::string input, std::string delimeter)
{
    std::vector<std::string> tokens;
    std::string::iterator pos = input.begin();
    pos = input.begin();

    while(input.find(delimeter))
    {
        tokens.push_back(pos, input.substr(input.find(delimeter)));
        pos = input.begin()+input.find(delimeter);
        input = std::string(pos, input.end());
    }
    return tokens;


}
int main()
{
    std::string test = "Testing space as a delimeter";
    std::vector<std::string> result = split_string(test, " ");
    for (std::vector<std::string>::iterator pos = result.begin(); pos<result.end(); pos++)
    {   
        std::cout<<*pos << std::endl;
    }
}
