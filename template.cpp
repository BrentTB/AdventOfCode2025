#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;
#define ll long long
#define uint unsigned int
#define ull unsigned long long
// #define endl "\n"
#define elif else if
#define fo(i, a, b) for (ll i = a; i < (ll)b; i++)
#define foe(a, b) for (auto a : b)
#define rfo(i, b, a) for (ll i = a - 1; i >= b; i--)
#define v(i) vector<i>
#define vll vector<long long>
#define vint vector<int>
#define vstr vector<string>
#define pairll pair<long long, long long>
#define pairint pair<int, int>
#define vpairll vector<pair<long long, long long>>
#define vpairint vector<pair<int, int>>
#define print(x) cout << x << "\n"
#define mod(a, b) ((a % b) + b) % b

template <typename T>
T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
template <typename T>
T lcm(T a, T b) { return a * b / gcd(a, b); }

#define printall(x)        \
    for (auto zz : x)      \
    {                      \
        cout << zz << " "; \
    }                      \
    cout << "\n";

#define printallpair(x)            \
    for (auto zz : x)              \
    {                              \
        cout << zz.first << " ";   \
        cout << zz.second << "\n"; \
    }

#define printall2d(x)          \
    for (auto zz : x)          \
    {                          \
        for (auto qq : zz)     \
        {                      \
            cout << qq << " "; \
        }                      \
        cout << "\n";          \
    }

const bool part1 = true; // set to false for part 2

// TODO: Extract this into a reusable module
const string partNum = part1 ? "1" : "2";
const string currentDir = filesystem::current_path().string() + "/";
const string inputPrefix = string("-p") + partNum;
const string partFolder = "part" + partNum + "/";

v(string) getInputFromFile()
{
    v(string) inputs;
    int i = 1;
    while (true)
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
        i++;
    }
    print("Loaded " + to_string(inputs.size()) + " input files for " + (part1 ? "part 1." : "part 2."));
    return inputs;
}

void writeOutputToFile(const string &output, int fileNumber)
{
    string filename = currentDir + partFolder + to_string(fileNumber) + inputPrefix + ".out.txt";
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open " << filename << " for writing." << endl;
        return;
    }
    file << output;
    file.close();
    print("Wrote output to " + filename);
}

void compareOutWithExpected(int fileNumber)
{
    string outFilename = currentDir + partFolder + to_string(fileNumber) + inputPrefix + ".out.txt";
    string expectedFilename = currentDir + partFolder + to_string(fileNumber) + inputPrefix + ".exp.txt";

    ifstream outFile(outFilename);
    ifstream expectedFile(expectedFilename);

    if (!outFile.is_open())
    {
        cerr << "XXX: Error: Could not open " << outFilename << endl;
        return;
    }
    if (!expectedFile.is_open())
    {
        cerr << "XXX: No .exp file found " << expectedFilename << endl;
        cerr << "Output:" << endl;
        cerr << outFile.rdbuf() << endl;
        return;
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
            print("XXX: Expected has extra lines starting from line: " + to_string(lineNumber));
            print("First extra line: " + expectedContentLine);
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
                print("***: No expected value given");
                compareFiles = false;
                break;
            }
            print("XXX: Output has extra lines starting from line: " + to_string(lineNumber));
            print("First extra line: " + outContentLine);
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
            print("XXX: Difference found at line: " + to_string(lineNumber));
            print("Output: " + outContentLine);
            print("Expected: " + expectedContentLine);
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
            print("Output matches expected for file " + to_string(fileNumber) + ".");
        }
        else
        {
            print("Output does NOT match expected for file " + to_string(fileNumber) + ".");
        }
    }
}

/* File names:

1.in.txt        -- input file for test case 1
1-p1.out.txt    -- output file for part 1 of test case 1
1-p1.exp.txt    -- expected output file for part 1 of test case 1
1-p2.out.txt    -- output file for part 2 of test case 1
1-p2.exp.txt    -- expected output file for part 2 of test case 1
...

2.in.txt
2-p1.out.txt
2-p1.exp.txt
2-p2.out.txt
2-p2.exp.txt
...
*/

string p1(stringstream input)
{

    string x;
    while (getline(input, x))
    {
    }

    return "";
}
string p2(stringstream input)
{

    string x;
    while (getline(input, x))
    {
    }

    return "";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    auto inputs = getInputFromFile();

    for (int i = 1; i < inputs.size() + 1; i++)
    {
        print("\n----- Input File " + to_string(i) + " -----");
        auto input = inputs[i - 1];
        if (part1)
        {
            string out = p1(stringstream(input));
            writeOutputToFile(out, i);
            compareOutWithExpected(i);
        }
        else
        {
            string out = p2(stringstream(input));
            writeOutputToFile(out, i);
            compareOutWithExpected(i);
        }
    }
}
