#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <sstream>
#include <filesystem>
#include <sys/wait.h>
#include <fstream>

namespace fs = std::filesystem;

std::string cariDiPath(const std::string &kataPerintah);
int eksekusiFile(const std::string &fullPath, const std::vector<std::string> &daftarKata);

int main()
{
    while (true)
    {
        std::cout << "$ ";

        std::string inputUser;
        if (!std::getline(std::cin, inputUser))
        {
            std::cout << "\n";
            break;
        };

        std::stringstream ss(inputUser);
        std::string kata;
        std::vector<std::string> daftarKata;

        while (ss >> kata)
        {
            if (!kata.empty())
            {
                daftarKata.push_back(kata);
            }
        }
        if (daftarKata.empty())
        {
            continue;
        }
        std::string kataPerintah = daftarKata[0];

        if (kataPerintah == "type")
        {
            std::vector<std::string> listTipePerintah = {"exit", "echo", "cd", "mkdir", "touch", "type", "mv"};

            if (daftarKata.size() < 2)
            {
                std::cout << "Inputmu kurang panjang!!! Panjangin woy!!" << std::endl;
                continue;
            }
            std::string tipePerintah = daftarKata[1];

            auto cariDiList = std::find(listTipePerintah.begin(), listTipePerintah.end(), tipePerintah);
            if (cariDiList != listTipePerintah.end())
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
        else if (kataPerintah == "cd")
        {
            if (daftarKata.size() < 2)
            {
                std::cout << "Inputmu kurang panjang!!! Panjangin woy!!" << std::endl;
                continue;
            }

            else if (chdir(daftarKata[1].c_str()) != 0)
            {
                std::cout << "changing directory error" << std::endl;
            }
        }
        else if (kataPerintah == "mkdir")
        {
            if (daftarKata.size() < 2)
            {
                std::cout << "Inputmu kurang panjang!!! Panjangin woy!!" << std::endl;
                continue;
            }

            for (int i = 1; i < daftarKata.size(); ++i)
            {
                fs::create_directory(daftarKata[i]);
            }
        }
        else if (kataPerintah == "echo")
        {
            for (int i = 1; i < daftarKata.size(); ++i)
            {
                std::cout << daftarKata[i] << " ";
            }
            std::cout << std::endl;
        }
        else if (kataPerintah == "touch")
        {
            for (int i = 1; i < daftarKata.size(); ++i)
            {
                std::ofstream buatFile(daftarKata[i]);
            }
        }
        else if (kataPerintah == "exit")
        {
            break;
        }
        else
        {
            std::string fullPath = cariDiPath(kataPerintah);

            if (fullPath.empty())
            {
                std::cout << kataPerintah << ": not founded" << std::endl;
            }
            else
            {
                eksekusiFile(fullPath, daftarKata);
            }
        }
    }
    return 0;
}

std::string cariDiPath(const std::string &kataPerintah)
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
        std::string fullPath = dir + "/" + kataPerintah;

        if (access(fullPath.c_str(), X_OK) == 0)
        {
            return fullPath;
        }
    }
    return "";
}

int eksekusiFile(const std::string &fullPath, const std::vector<std::string> &daftarKata)
{

    std::vector<char *> parameter;
    for (const auto &d : daftarKata)
    {
        parameter.push_back(const_cast<char *>(d.c_str()));
    }
    parameter.push_back(nullptr);

    pid_t eksekusiFile = fork();

    if (eksekusiFile == 0)
    {
        execvp(fullPath.c_str(), parameter.data());
        perror("execvp error boss");
        exit(1);
    }
    else if (eksekusiFile > 0)
    {
        waitpid(eksekusiFile, nullptr, 0);
    }
    else
    {
        perror("fork error woy");
    }
    return 0;
}