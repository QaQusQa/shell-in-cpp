#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <sstream>

std::string cariDiPath(const std::string &perintah);

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

            auto cariDiList = std::find(listPerintah.begin(), listPerintah.end(), tipePerintah);
            if (cariDiList != listPerintah.end())
            {
                std::cout << tipePerintah << " is a shell builtin" << std::endl;
            }
            else
            {
                std::string cariKePath = cariDiPath(tipePerintah);
                if (!cariKePath.empty())
                {
                    std::cout << tipePerintah << " is " << cariKePath << std::endl;
                }
                else
                {
                    std::cout << "bash: type: " << tipePerintah << ": not found" << std::endl;
                }
            }
        }
        else if (perintah.find("cd ") == 0)
        {
            std::string pindahDirektori = perintah.substr(3);
            std::cout << "cd command will be implemented soon" << std::endl;
        }
        else if (perintah.find("mkdir ") == 0)
        {
            std::string buatFolder = perintah.substr(6);
            std::cout << "mkdir command will be implemented soon" << std::endl;
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

std::string cariDiPath(const std::string &perintah)
{
    const char *path = std::getenv("PATH");
    if (!path)
    {
        return "";
    }

    std::string pathSebagaiString = path;

    std::stringstream ss(pathSebagaiString);
    std::vector<std::string> direktori;
    std::string alurDirektori;

    while (std::getline(ss, alurDirektori, ':'))
    {

        if (!alurDirektori.empty())
        {
            direktori.push_back(alurDirektori);
        }
    }

    for (const std::string dir : direktori)
    {
        std::string fullPath = dir + "/" + perintah;

        if (access(fullPath.c_str(), X_OK) == 0)
        {
            return fullPath;
        }
    }

    return "";
}