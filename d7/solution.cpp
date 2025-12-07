#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include "../aoc_helpers.hpp"

using namespace std;
#define ll long long
#define uint unsigned int
#define ull unsigned long long
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
#define print(x) cout << (x) << "\n"
#define mod(a, b) ((a % b) + b) % b

template <typename T>
T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
template <typename T>
T lcm(T a, T b) { return a * b / gcd(a, b); }

#define printall(x)         \
    for (auto zz : x)       \
    {                       \
        cout << zz << "\n"; \
    }                       \
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

const bool part1 = false; // set to false for part 2

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
    vstr inputs;
    string x;
    while (getline(input, x))
    {
        inputs.push_back(x);
    }

    ll numSplit = 0;
    fo(i, 1, inputs.size())
    {
        fo(j, 0, inputs[i].size())
        {
            if (inputs[i - 1][j] == '|' || inputs[i - 1][j] == 'S')
            {
                if (inputs[i][j] == '.')
                {
                    inputs[i][j] = '|';
                }
                else if (inputs[i][j] == '^')
                {
                    numSplit++;
                    if (j > 0)
                    {
                        inputs[i][j - 1] = '|';
                    }
                    if (j < inputs[i].size() - 1)
                    {
                        inputs[i][j + 1] = '|';
                    }
                }
            }
        }
    }

    return to_string(numSplit);
}

ll recur(vstr inputs, int row, int col, map<pairint, ll> &memo)
{
    if (memo.find({row, col}) != memo.end())
        return memo[{row, col}];

    if (col < 0 || col >= inputs[0].size())
        return 0;

    if (row == inputs.size())
        return 1;

    if (inputs[row][col] == '^')
    {
        auto val = recur(inputs, row + 1, col - 1, memo) + recur(inputs, row + 1, col + 1, memo);
        memo[{row, col}] = val;
        return val;
    }
    return recur(inputs, row + 1, col, memo);
}

string p2(stringstream input)
{

    vstr inputs;
    string x;
    while (getline(input, x))
    {
        inputs.push_back(x);
    }

    // use memoization to speed up the path traversal.
    // Once we get to the same row and column we've been to before, we know how many paths the particle will end up taking
    map<pairint, ll> memo;
    return to_string(recur(inputs, 1, inputs[0].find('S'), memo));
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    aoc::Helper helper(part1);
    auto inputs = helper.getInputFromFile();
    int errors = 0;

    for (int i = 1; i < inputs.size() + 1; i++)
    {
        print("\n----- Input File " + to_string(i) + " -----");
        auto input = inputs[i - 1];
        if (part1)
        {
            string out = p1(stringstream(input));
            helper.writeOutputToFile(out, i);
            errors += helper.compareOutWithExpected(i);
        }
        else
        {
            string out = p2(stringstream(input));
            helper.writeOutputToFile(out, i);
            errors += helper.compareOutWithExpected(i);
        }
    }

    if (errors > 0)
    {
        print("\nERROR: " + to_string(errors) + " input" + (errors == 1 ? " was " : "s were ") + "incorrect");
    }
    else
    {
        print("\nSUCCESS: All inputs were correct");
    }
}
