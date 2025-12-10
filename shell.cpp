#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <string>

int main()
{
    while (true)
    {
        std::cout << "$ ";

        std::string perintah;
        std::getline(std::cin, perintah);

        if (perintah.empty())
        {
            continue;
        }
        else if (perintah.find("type ") == 0)
        {
            std::vector<std::string> listPerintah = {"exit", "echo", "cd", "mkdir", "touch", "type"};
            std::string tipePerintah = perintah.substr(5);

            auto cariDiPerintah = std::find(listPerintah.begin(), listPerintah.end(), tipePerintah);
            if (cariDiPerintah != listPerintah.end())
            {
                std::cout << tipePerintah << " is a shell builtin" << std::endl;
            }
            else
            {
                std::cout << "bash: type: " << tipePerintah << ": not found" << std::endl;
            }
        }
        else if (perintah == "exit")
        {
            break;
        }
        else
        {
            std::cout << perintah << ": not found" << std::endl;
        }
    }
}