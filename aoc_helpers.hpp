#ifndef AOC_HELPERS_HPP
#define AOC_HELPERS_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Helper module for Advent of Code file I/O operations
// This module provides functions to read input files, write output files,
// and compare output with expected results.

namespace aoc {

// Get the part-specific constants based on which part is being solved
struct PartConfig {
    string partNum;
    string inputPrefix;
    string partFolder;
    string currentDir;
    
    PartConfig(bool isPart1) {
        partNum = isPart1 ? "1" : "2";
        currentDir = filesystem::current_path().string() + "/";
        inputPrefix = string("-p") + partNum;
        partFolder = "part" + partNum + "/";
    }
};

// Read all input files from the current directory
// Returns a vector of strings, each containing the full content of one input file
// Files are named 1.in.txt, 2.in.txt, etc.
vector<string> getInputFromFile(const PartConfig& config, bool isPart1) {
    vector<string> inputs;
    int i = 1;
    while (true) {
        string filename = config.currentDir + to_string(i) + ".in.txt";
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
    cout << "Loaded " << to_string(inputs.size()) << " input files for " << (isPart1 ? "part 1." : "part 2.") << "\n";
    return inputs;
}

// Write output to a file in the appropriate part folder
// Output file is named <fileNumber>-p<partNum>.out.txt
void writeOutputToFile(const PartConfig& config, const string& output, int fileNumber) {
    string filename = config.currentDir + config.partFolder + to_string(fileNumber) + config.inputPrefix + ".out.txt";
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << " for writing." << endl;
        return;
    }
    file << output;
    file.close();
    cout << "Wrote output to " << filename << "\n";
}

// Compare output file with expected file
// Returns true if there are errors (mismatch), false if everything matches
bool compareOutWithExpected(const PartConfig& config, int fileNumber) {
    string outFilename = config.currentDir + config.partFolder + to_string(fileNumber) + config.inputPrefix + ".out.txt";
    string expectedFilename = config.currentDir + config.partFolder + to_string(fileNumber) + config.inputPrefix + ".exp.txt";

    ifstream outFile(outFilename);
    ifstream expectedFile(expectedFilename);

    if (!outFile.is_open()) {
        cerr << "XXX: Error: Could not open " << outFilename << endl;
        return true;
    }
    if (!expectedFile.is_open()) {
        cerr << "XXX: No .exp file found " << expectedFilename << endl;
        cerr << "Output:" << endl;
        cerr << outFile.rdbuf() << endl;
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
                cout << "***: No expected value given" << "\n";
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
            cout << "Output matches expected for file " << to_string(fileNumber) << "." << "\n";
            return false;
        } else {
            cout << "Output does NOT match expected for file " << to_string(fileNumber) << "." << "\n";
        }
    }
    return true;
}

} // namespace aoc

#endif // AOC_HELPERS_HPP
