#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <climits>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// FileReader class for Advent of Code
// This class handles reading input files from the filesystem
namespace aoc
{

    class FileReader
    {
    private:
        std::string currentDir;
        std::vector<int> inputNums;

    public:
        // Constructor
        // inputs: optional, if provided, only reads the inputs specified in the vector
        FileReader(std::vector<int> inputNums = {}) : inputNums(inputNums)
        {
            currentDir = std::filesystem::current_path().string() + "/";
        }

        // Read all input files from the current directory
        // Returns a vector of strings, each containing the full content of one input file
        // Files are named 1.in.txt, 2.in.txt, etc.
        std::vector<std::pair<std::string, int>> getInputFromFile(int partNum) const
        {
            std::vector<std::pair<std::string, int>> inputs;

            int index = 0;
            while (true)
            {
                int i;
                if (inputNums.size() > 0)
                {
                    if (index >= (int)inputNums.size())
                    {
                        break;
                    }
                    i = inputNums[index];
                }
                else
                {
                    i = index + 1;
                }
                std::string filename = currentDir + std::to_string(i) + ".in.txt";
                std::ifstream file(filename);
                if (!file.is_open())
                {
                    break;
                }
                inputs.push_back({"", i});
                std::string tmp;
                while (std::getline(file, tmp))
                {
                    inputs.back().first += tmp + "\n";
                }
                file.close();
                index++;
            }
            std::cout << "Loaded " << std::to_string(inputs.size()) << " input files for part " << std::to_string(partNum) << ".\n";
            return inputs;
        }
    };

} // namespace aoc

#endif // FILE_READER_HPP
