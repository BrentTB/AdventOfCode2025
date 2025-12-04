# AoC 2025

This is my solutions to the 2025 Advent of Code

## Solution.cpp

- The `solution.cpp` file contains the c++ solution. You control whether it truns for part 1 or 2 with a boolean flag at the top of the code.
- This file will automatically read in the input, run your part1/part2 code, write the ouput to a file, and compare your output with the expected output
- It outputs whether your solution was correct, if incorrect it will tell you which line had the inconsistency. It also tells you if your output/expected file has extra lines
- This was run with `c++20`

## Template.cpp

- The template is used to create the base solution file for each day.
- To see the specific code used for part 1 and part 2, look for the following functions:

```
string p1(stringstream input){...}
string p2(stringstream input){...}
```

- These functions return a string to be written to an output file once computed

## Folder structure

For some day, `dayNumber`:

- d<dayNumber>
  - 1.in.txt - input file 1
  - 2.in.txt - input file 2
  - part1
    - 1-p1.exp.txt - expected solution for input 1 part 1
    - 2-p1.exp.txt - expected solution for input 2 part 1
  - part2
    - 1-p2.exp.txt - expected solution for input 1 part 2
    - 2-p2.exp.txt - expected solution for input 2 part 2
  - solution.cpp - solution c++ file

Note: Only the solution file was committed in this repo

- The created output files are compared against the "expected solution" files above, giving you a way to automtically check your code when you know the output for some input (such as the input 1, which comes with a solution).
- This can also be used to create and automatically run small test cases outside of the 2 given inputs

### Creating the files

- You can run `./create-day-template <dayNumber>` for some day, to create the file structure listed above
- If you would like more than 2 input files (such as to write your own test cases), you can run `./create-day-template <dayNumber> <numInputs>`
  - Note: This will not overwrite any existing txt files, or your `solution.cpp` file.
- The `solution.cpp` will automatically run with the new inputs after they are created
