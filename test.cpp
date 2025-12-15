#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

std::string eksekusifile(const std::string )

int main()
{

    /*fs::path pathFile = "./folder";

    std::cout << pathFile.filename() << std::endl;
    std::cout << pathFile.extension() << std::endl;
    std::cout << pathFile.parent_path() << std::endl;
    std::cout << pathFile.replace_extension() << std::endl;

    if (!fs::exists(pathFile))
    {
        std::cout << "File not founded" << std::endl;
    }
    else
    {
        std::cout << "File been found!!!" << std::endl;
    }
    */
    std::string perintah;
    std::getline(std::cin, perintah);

    std::string kata = perintah;

    std::stringstream ss(kata);
    std::vector<std::string> kumpulanKata;
    std::string hasilParsing;

    while (std::getline(ss, hasilParsing, ' '))
    {
        if (!hasilParsing.empty())
        {
            kumpulanKata.push_back(hasilParsing);
        }
    }

    std::string eksekusi = 
    return 0;
}