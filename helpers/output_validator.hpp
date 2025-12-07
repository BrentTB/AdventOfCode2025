#ifndef OUTPUT_VALIDATOR_HPP
#define OUTPUT_VALIDATOR_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

// OutputValidator class for Advent of Code
// This class handles writing output files, comparing with expected results,
// and tracking errors
namespace aoc
{

    class OutputValidator
    {
    private:
        std::string partNum;
        std::string inputPrefix;
        std::string partFolder;
        std::string currentDir;
        mutable int errorCount;

    public:
        // Constructor: initializes configuration based on which part is being solved
        // part: 1 or 2 for part 1 or part 2
        OutputValidator(int part) : errorCount(0)
        {
            this->partNum = std::to_string(part);
            currentDir = std::filesystem::current_path().string() + "/";
            inputPrefix = std::string("-p") + this->partNum;
            partFolder = "part" + this->partNum + "/";
        }

        // Write output to a file in the appropriate part folder
        // Output file is named <fileNumber>-p<partNum>.out.txt
        void writeOutputToFile(const std::string &output, int fileNumber) const
        {
            std::string filename = currentDir + partFolder + std::to_string(fileNumber) + inputPrefix + ".out.txt";
            std::ofstream file(filename);
            if (!file.is_open())
            {
                std::cerr << "Error: Could not open " << filename << " for writing.\n";
                return;
            }
            file << output;
            file.close();
            std::cout << "Wrote output to " << filename << "\n";
        }

        // Compare output file with expected file
        // Returns true if there are errors (mismatch), false if everything matches
        // Also increments internal error counter when errors are found
        bool compareOutWithExpected(int fileNumber) const
        {
            std::string outFilename = currentDir + partFolder + std::to_string(fileNumber) + inputPrefix + ".out.txt";
            std::string expectedFilename = currentDir + partFolder + std::to_string(fileNumber) + inputPrefix + ".exp.txt";

            std::ifstream outFile(outFilename);
            std::ifstream expectedFile(expectedFilename);

            if (!outFile.is_open())
            {
                std::cerr << "XXX: Error: Could not open " << outFilename << "\n";
                errorCount++;
                return true;
            }
            if (!expectedFile.is_open())
            {
                std::cerr << "XXX: No .exp file found " << expectedFilename << "\n";
                std::cerr << "Output:\n";
                std::cerr << outFile.rdbuf() << "\n";
                errorCount++;
                return true;
            }

            std::string outContent, expectedContent;
            std::string outContentLine, expectedContentLine;
            int lineNumber = 1;
            bool compareFiles;
            while (true)
            {
                compareFiles = true;
                bool haveOut = static_cast<bool>(std::getline(outFile, outContentLine));
                bool haveExp = static_cast<bool>(std::getline(expectedFile, expectedContentLine));

                if (!haveOut && !haveExp)
                    break; // both EOF, done

                if (!haveOut)
                {
                    // expected has extra lines
                    expectedContent += expectedContentLine + "\n";
                    std::cout << "XXX: Expected has extra lines starting from line: " << std::to_string(lineNumber) << "\n";
                    std::cout << "First extra line: " << expectedContentLine << "\n";
                    // append remaining expected lines
                    while (std::getline(expectedFile, expectedContentLine))
                        expectedContent += expectedContentLine + "\n";
                    break;
                }

                if (!haveExp)
                {
                    outContent += outContentLine + "\n";
                    if (lineNumber == 1)
                    {
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
                if (outContentLine != expectedContentLine)
                {
                    std::cout << "XXX: Difference found at line: " << std::to_string(lineNumber) << "\n";
                    std::cout << "Output:   " << outContentLine << "\n";
                    std::cout << "Expected: " << expectedContentLine << "\n";
                    break;
                }
                lineNumber++;
            }

            outFile.close();
            expectedFile.close();

            if (compareFiles)
            {
                if (outContent == expectedContent)
                {
                    std::cout << "Output matches expected for file " << std::to_string(fileNumber) << ".\n";
                    return false;
                }
                else
                {
                    std::cout << "Output does NOT match expected for file " << std::to_string(fileNumber) << ".\n";
                }
            }
            errorCount++;
            return true;
        }

        // Print error summary
        void printErrorSummary() const
        {
            if (errorCount > 0)
            {
                std::cout << "\nERROR: " << std::to_string(errorCount) << " input"
                     << (errorCount == 1 ? " was " : "s were ") << "incorrect\n";
            }
            else
            {
                std::cout << "\nSUCCESS: All inputs were correct\n";
            }
        }
    };

} // namespace aoc

#endif // OUTPUT_VALIDATOR_HPP
