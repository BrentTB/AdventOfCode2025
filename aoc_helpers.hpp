#ifndef AOC_HELPERS_HPP
#define AOC_HELPERS_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Helper module for Advent of Code file I/O operations
// This module provides functions to read input files, write output files,
// and compare output with expected results.

namespace aoc {

// Get the part-specific constants based on which part is being solved
struct PartConfig {
    std::string partNum;
    std::string inputPrefix;
    std::string partFolder;
    std::string currentDir;
    
    PartConfig(bool isPart1) {
        partNum = isPart1 ? "1" : "2";
        currentDir = std::filesystem::current_path().string() + "/";
        inputPrefix = std::string("-p") + partNum;
        partFolder = "part" + partNum + "/";
    }
};

// Read all input files from the current directory
// Returns a vector of strings, each containing the full content of one input file
// Files are named 1.in.txt, 2.in.txt, etc.
std::vector<std::string> getInputFromFile(const PartConfig& config) {
    std::vector<std::string> inputs;
    int i = 1;
    while (true) {
        std::string filename = config.currentDir + std::to_string(i) + ".in.txt";
        std::ifstream file(filename);
        if (!file.is_open()) {
            break;
        }
        inputs.push_back("");
        std::string tmp;
        while (std::getline(file, tmp)) {
            inputs.back() += tmp + "\n";
        }
        file.close();
        i++;
    }
    std::cout << "Loaded " << std::to_string(inputs.size()) << " input files for part " << config.partNum << ".\n";
    return inputs;
}

// Write output to a file in the appropriate part folder
// Output file is named <fileNumber>-p<partNum>.out.txt
void writeOutputToFile(const PartConfig& config, const std::string& output, int fileNumber) {
    std::string filename = config.currentDir + config.partFolder + std::to_string(fileNumber) + config.inputPrefix + ".out.txt";
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for writing.\n";
        return;
    }
    file << output;
    file.close();
    std::cout << "Wrote output to " << filename << "\n";
}

// Compare output file with expected file
// Returns true if there are errors (mismatch), false if everything matches
bool compareOutWithExpected(const PartConfig& config, int fileNumber) {
    std::string outFilename = config.currentDir + config.partFolder + std::to_string(fileNumber) + config.inputPrefix + ".out.txt";
    std::string expectedFilename = config.currentDir + config.partFolder + std::to_string(fileNumber) + config.inputPrefix + ".exp.txt";

    std::ifstream outFile(outFilename);
    std::ifstream expectedFile(expectedFilename);

    if (!outFile.is_open()) {
        std::cerr << "XXX: Error: Could not open " << outFilename << "\n";
        return true;
    }
    if (!expectedFile.is_open()) {
        std::cerr << "XXX: No .exp file found " << expectedFilename << "\n";
        std::cerr << "Output:\n";
        std::cerr << outFile.rdbuf() << "\n";
        return true;
    }

    std::string outContent, expectedContent;
    std::string outContentLine, expectedContentLine;
    int lineNumber = 1;
    bool compareFiles;
    while (true) {
        compareFiles = true;
        bool haveOut = static_cast<bool>(std::getline(outFile, outContentLine));
        bool haveExp = static_cast<bool>(std::getline(expectedFile, expectedContentLine));

        if (!haveOut && !haveExp)
            break; // both EOF, done

        if (!haveOut) {
            // expected has extra lines
            expectedContent += expectedContentLine + "\n";
            std::cout << "XXX: Expected has extra lines starting from line: " << std::to_string(lineNumber) << "\n";
            std::cout << "First extra line: " << expectedContentLine << "\n";
            // append remaining expected lines
            while (std::getline(expectedFile, expectedContentLine))
                expectedContent += expectedContentLine + "\n";
            break;
        }

        if (!haveExp) {
            outContent += outContentLine + "\n";
            if (lineNumber == 1) {
                std::cout << "***: No expected value given\n";
                compareFiles = false;
                break;
            }
            std::cout << "XXX: Output has extra lines starting from line: " << std::to_string(lineNumber) << "\n";
            std::cout << "First extra line: " << outContentLine << "\n";
            // append remaining out lines
            while (std::getline(outFile, outContentLine))
                outContent += outContentLine + "\n";
            break;
        }

        // both lines present — compare
        outContent += outContentLine + "\n";
        expectedContent += expectedContentLine + "\n";
        if (outContentLine != expectedContentLine) {
            std::cout << "XXX: Difference found at line: " << std::to_string(lineNumber) << "\n";
            std::cout << "Output: " << outContentLine << "\n";
            std::cout << "Expected: " << expectedContentLine << "\n";
            break;
        }
        lineNumber++;
    }

    outFile.close();
    expectedFile.close();

    if (compareFiles) {
        if (outContent == expectedContent) {
            std::cout << "Output matches expected for file " << std::to_string(fileNumber) << ".\n";
            return false;
        } else {
            std::cout << "Output does NOT match expected for file " << std::to_string(fileNumber) << ".\n";
        }
    }
    return true;
}

} // namespace aoc

#endif // AOC_HELPERS_HPP
