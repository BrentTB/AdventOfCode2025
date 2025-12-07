#ifndef OUTPUT_VALIDATOR_HPP
#define OUTPUT_VALIDATOR_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// OutputValidator class for Advent of Code
// This class handles writing output files, comparing with expected results,
// and tracking errors
namespace aoc
{

    class OutputValidator
    {
    private:
        string partNum;
        string inputPrefix;
        string partFolder;
        string currentDir;
        int errorCount;

    public:
        // Constructor: initializes configuration based on which part is being solved
        // part: 1 or 2 for part 1 or part 2
        OutputValidator(int part) : errorCount(0)
        {
            this->partNum = to_string(part);
            currentDir = filesystem::current_path().string() + "/";
            inputPrefix = string("-p") + this->partNum;
            partFolder = "part" + this->partNum + "/";
        }

        // Write output to a file in the appropriate part folder
        // Output file is named <fileNumber>-p<partNum>.out.txt
        void writeOutputToFile(const string &output, int fileNumber) const
        {
            string filename = currentDir + partFolder + to_string(fileNumber) + inputPrefix + ".out.txt";
            ofstream file(filename);
            if (!file.is_open())
            {
                cerr << "Error: Could not open " << filename << " for writing.\n";
                return;
            }
            file << output;
            file.close();
            cout << "Wrote output to " << filename << "\n";
        }

        // Compare output file with expected file
        // Returns true if there are errors (mismatch), false if everything matches
        // Also increments internal error counter when errors are found
        bool compareOutWithExpected(int fileNumber)
        {
            string outFilename = currentDir + partFolder + to_string(fileNumber) + inputPrefix + ".out.txt";
            string expectedFilename = currentDir + partFolder + to_string(fileNumber) + inputPrefix + ".exp.txt";

            ifstream outFile(outFilename);
            ifstream expectedFile(expectedFilename);

            if (!outFile.is_open())
            {
                cerr << "XXX: Error: Could not open " << outFilename << "\n";
                errorCount++;
                return true;
            }
            if (!expectedFile.is_open())
            {
                cerr << "XXX: No .exp file found " << expectedFilename << "\n";
                cerr << "Output:\n";
                cerr << outFile.rdbuf() << "\n";
                errorCount++;
                return true;
            }

            string outContent, expectedContent;
            string outContentLine, expectedContentLine;
            int lineNumber = 1;
            bool compareFiles;
            while (true)
            {
                compareFiles = true;
                bool haveOut = static_cast<bool>(getline(outFile, outContentLine));
                bool haveExp = static_cast<bool>(getline(expectedFile, expectedContentLine));

                if (!haveOut && !haveExp)
                    break; // both EOF, done

                if (!haveOut)
                {
                    // expected has extra lines
                    expectedContent += expectedContentLine + "\n";
                    cout << "XXX: Expected has extra lines starting from line: " << to_string(lineNumber) << "\n";
                    cout << "First extra line: " << expectedContentLine << "\n";
                    // append remaining expected lines
                    while (getline(expectedFile, expectedContentLine))
                        expectedContent += expectedContentLine + "\n";
                    break;
                }

                if (!haveExp)
                {
                    outContent += outContentLine + "\n";
                    if (lineNumber == 1)
                    {
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
                if (outContentLine != expectedContentLine)
                {
                    cout << "XXX: Difference found at line: " << to_string(lineNumber) << "\n";
                    cout << "Output:   " << outContentLine << "\n";
                    cout << "Expected: " << expectedContentLine << "\n";
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
                    cout << "Output matches expected for file " << to_string(fileNumber) << ".\n";
                    return false;
                }
                else
                {
                    cout << "Output does NOT match expected for file " << to_string(fileNumber) << ".\n";
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
                cout << "\nERROR: " << to_string(errorCount) << " input"
                     << (errorCount == 1 ? " was " : "s were ") << "incorrect\n";
            }
            else
            {
                cout << "\nSUCCESS: All inputs were correct\n";
            }
        }
    };

} // namespace aoc

#endif // OUTPUT_VALIDATOR_HPP
