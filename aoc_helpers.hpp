#ifndef AOC_HELPERS_HPP
#define AOC_HELPERS_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Helper module for Advent of Code file I/O operations
// This module provides a class to handle input files, write output files,
// and compare output with expected results.

namespace aoc {

// Helper class for Advent of Code file I/O operations
class Helper {
private:
    string partNum;
    string inputPrefix;
    string partFolder;
    string currentDir;
    int numInputs;

public:
    // Constructor: initializes configuration based on which part is being solved
    // part: 1 or 2 for part 1 or part 2
    // numInputs: optional, if provided, only reads the first numInputs input files
    Helper(int part, int numInputs = -1) : numInputs(numInputs) {
        this->partNum = to_string(part);
        currentDir = filesystem::current_path().string() + "/";
        inputPrefix = string("-p") + this->partNum;
        partFolder = "part" + this->partNum + "/";
    }

    // Read all input files from the current directory
    // Returns a vector of strings, each containing the full content of one input file
    // Files are named 1.in.txt, 2.in.txt, etc.
    vector<string> getInputFromFile() const {
        vector<string> inputs;
        int i = 1;
        while (true) {
            // If numInputs is specified, stop after reading that many files
            if (numInputs > 0 && i > numInputs) {
                break;
            }
            
            string filename = currentDir + to_string(i) + ".in.txt";
            ifstream file(filename);
            if (!file.is_open()) {
                break;
            }
            inputs.push_back("");
            string tmp;
            while (getline(file, tmp)) {
                inputs.back() += tmp + "\n";
            }
            file.close();
            i++;
        }
        cout << "Loaded " << to_string(inputs.size()) << " input files for part " << partNum << ".\n";
        return inputs;
    }

    // Write output to a file in the appropriate part folder
    // Output file is named <fileNumber>-p<partNum>.out.txt
    void writeOutputToFile(const string& output, int fileNumber) const {
        string filename = currentDir + partFolder + to_string(fileNumber) + inputPrefix + ".out.txt";
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open " << filename << " for writing.\n";
            return;
        }
        file << output;
        file.close();
        cout << "Wrote output to " << filename << "\n";
    }

    // Compare output file with expected file
    // Returns true if there are errors (mismatch), false if everything matches
    bool compareOutWithExpected(int fileNumber) const {
        string outFilename = currentDir + partFolder + to_string(fileNumber) + inputPrefix + ".out.txt";
        string expectedFilename = currentDir + partFolder + to_string(fileNumber) + inputPrefix + ".exp.txt";

        ifstream outFile(outFilename);
        ifstream expectedFile(expectedFilename);

        if (!outFile.is_open()) {
            cerr << "XXX: Error: Could not open " << outFilename << "\n";
            return true;
        }
        if (!expectedFile.is_open()) {
            cerr << "XXX: No .exp file found " << expectedFilename << "\n";
            cerr << "Output:\n";
            cerr << outFile.rdbuf() << "\n";
            return true;
        }

        string outContent, expectedContent;
        string outContentLine, expectedContentLine;
        int lineNumber = 1;
        bool compareFiles;
        while (true) {
            compareFiles = true;
            bool haveOut = static_cast<bool>(getline(outFile, outContentLine));
            bool haveExp = static_cast<bool>(getline(expectedFile, expectedContentLine));

            if (!haveOut && !haveExp)
                break; // both EOF, done

            if (!haveOut) {
                // expected has extra lines
                expectedContent += expectedContentLine + "\n";
                cout << "XXX: Expected has extra lines starting from line: " << to_string(lineNumber) << "\n";
                cout << "First extra line: " << expectedContentLine << "\n";
                // append remaining expected lines
                while (getline(expectedFile, expectedContentLine))
                    expectedContent += expectedContentLine + "\n";
                break;
            }

            if (!haveExp) {
                outContent += outContentLine + "\n";
                if (lineNumber == 1) {
                    cout << "***: No expected value given\n";
                    compareFiles = false;
                    break;
                }
                cout << "XXX: Output has extra lines starting from line: " << to_string(lineNumber) << "\n";
                cout << "First extra line: " << outContentLine << "\n";
                // append remaining out lines
                while (getline(outFile, outContentLine))
                    outContent += outContentLine + "\n";
                break;
            }

            // both lines present — compare
            outContent += outContentLine + "\n";
            expectedContent += expectedContentLine + "\n";
            if (outContentLine != expectedContentLine) {
                cout << "XXX: Difference found at line: " << to_string(lineNumber) << "\n";
                cout << "Output: " << outContentLine << "\n";
                cout << "Expected: " << expectedContentLine << "\n";
                break;
            }
            lineNumber++;
        }

        outFile.close();
        expectedFile.close();

        if (compareFiles) {
            if (outContent == expectedContent) {
                cout << "Output matches expected for file " << to_string(fileNumber) << ".\n";
                return false;
            } else {
                cout << "Output does NOT match expected for file " << to_string(fileNumber) << ".\n";
            }
        }
        return true;
    }
};

} // namespace aoc

#endif // AOC_HELPERS_HPP
