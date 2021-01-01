#include <bits/stdc++.h>
#include<direct.h>

void zip_coder(std::vector<std::string>& files)
{
    std::string line;
    _mkdir("zip_result");

    for (const std::string &filename : files)
    {
        std::string dir_name = filename.substr(0, filename.find('.'));
        _mkdir(dir_name.c_str());
        _mkdir((dir_name + "\\split").c_str());
        _mkdir((dir_name + "\\unique").c_str());

        for (int i = 0; i < 10; i++)
        {
            std::ifstream file(filename);
            std::ofstream new_file(dir_name + "\\split\\" + std::to_string(i) + "-" + filename);

            while (std::getline(file, line))
            {
                if ((int) line.front() - 48 == i)
                {
                    new_file << line << std::endl;
                }
            }
            new_file.close();
        }
    }

    std::cout << "File Splitting Complete" << std::endl;

    for (const std::string &filename : files)
    {
        std::string dir_name = filename.substr(0, filename.find('.'));

        for (int i = 0; i < 10; i++)
        {
            std::set<int> zip_codes;
            std::ifstream file(dir_name + "\\split\\" + std::to_string(i) + "-" + filename);
            std::ofstream new_file(dir_name + "\\unique\\" + std::to_string(i) + "-unique-" + filename);

            for (const std::string &current_filename : files)
            {
                if (filename != current_filename)
                {
                    std::string current_dir = current_filename.substr(0, filename.find('.'));
                    std::ifstream current_file(current_dir + "\\split\\" + std::to_string(i) + "-" + current_filename);

                    while (std::getline(current_file, line))
                    {
                        zip_codes.insert(std::stoi(line.substr(0, 5)));
                    }
                    current_file.close();
                }
            }

            while (std::getline(file, line))
            {
                if (zip_codes.find(std::stoi(line.substr(0, 5))) == zip_codes.end())
                {
                    new_file << line << std::endl;
                }
            }
            file.close();
        }
    }

    std::cout << "Unique Value Extraction Complete" << std::endl;
}

int main()
{
    std::vector<std::string> files;
    files.emplace_back("zipcodestest.csv");
    files.emplace_back("zipcodestest2.csv");
    zip_coder(files);
}
