#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <climits>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// FileReader class for Advent of Code
// This class handles reading input files from the filesystem
namespace aoc
{

    class FileReader
    {
    private:
        string currentDir;
        int numInputs;

    public:
        // Constructor
        // numInputs: optional, if provided, only reads the first numInputs input files
        FileReader(int numInputs = -1) : numInputs(numInputs)
        {
            currentDir = filesystem::current_path().string() + "/";
        }

        // Read all input files from the current directory
        // Returns a vector of strings, each containing the full content of one input file
        // Files are named 1.in.txt, 2.in.txt, etc.
        vector<string> getInputFromFile(int partNum) const
        {
            vector<string> inputs;

            // If numInputs is -1, read until file not found; otherwise read exactly numInputs files
            int limit = (numInputs == -1) ? INT_MAX : numInputs;

            for (int i = 1; i <= limit; i++)
            {
                string filename = currentDir + to_string(i) + ".in.txt";
                ifstream file(filename);
                if (!file.is_open())
                {
                    break;
                }
                inputs.push_back("");
                string tmp;
                while (getline(file, tmp))
                {
                    inputs.back() += tmp + "\n";
                }
                file.close();
            }
            cout << "Loaded " << to_string(inputs.size()) << " input files for part " << to_string(partNum) << ".\n";
            return inputs;
        }
    };

} // namespace aoc

#endif // FILE_READER_HPP
