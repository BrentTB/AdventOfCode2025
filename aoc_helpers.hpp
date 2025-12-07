#ifndef AOC_HELPERS_HPP
#define AOC_HELPERS_HPP

#include "helpers/file_reader.hpp"
#include "helpers/output_validator.hpp"

// Helper module for Advent of Code file I/O operations
// This module provides a Helper class that combines FileReader and OutputValidator
// for backward compatibility with existing code.

namespace aoc
{

    // Helper class for Advent of Code file I/O operations
    // This is a convenience wrapper around FileReader and OutputValidator
    class Helper
    {
    private:
        int partNum;
        FileReader fileReader;
        OutputValidator validator;

    public:
        // Constructor: initializes configuration based on which part is being solved
        // part: 1 or 2 for part 1 or part 2
        // numInputs: optional, if provided, only reads the first numInputs input files
        Helper(int part, int numInputs = -1)
            : partNum(part), fileReader(numInputs), validator(part)
        {
        }

        // Read all input files from the current directory
        // Returns a vector of strings, each containing the full content of one input file
        // Files are named 1.in.txt, 2.in.txt, etc.
        std::vector<std::string> getInputFromFile() const
        {
            return fileReader.getInputFromFile(partNum);
        }

        // Write output to a file in the appropriate part folder
        // Output file is named <fileNumber>-p<partNum>.out.txt
        void writeOutputToFile(const std::string &output, int fileNumber) const
        {
            validator.writeOutputToFile(output, fileNumber);
        }

        // Compare output file with expected file
        // Returns true if there are errors (mismatch), false if everything matches
        // Also increments internal error counter when errors are found
        bool compareOutWithExpected(int fileNumber) const
        {
            return validator.compareOutWithExpected(fileNumber);
        }

        // Print error summary
        void printErrorSummary() const
        {
            validator.printErrorSummary();
        }
    };

} // namespace aoc

#endif // AOC_HELPERS_HPP
