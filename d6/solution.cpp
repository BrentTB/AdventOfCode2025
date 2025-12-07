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
#define print(x) cout << (x) << "\n";
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

string p1(stringstream input)
{
    vstr lines;
    string x;
    while (getline(input, x))
    {
        lines.push_back(x);
    }

    int numCols = 0;

    foe(character, lines[lines.size() - 1])
    {

        if (character == '*' || character == '+')
        {
            numCols++;
        }
    }

    v(vll) data(numCols);
    v(char) sign(numCols);

    fo(i, 0, lines.size())
    {
        int colIdx = 0;
        stringstream ss(lines[i]);
        string num;
        while (ss >> num)
        {
            if (i == lines.size() - 1)
            {
                sign[colIdx] = num[0];
            }
            else
            {

                data[colIdx].push_back(stol(num));
            }
            colIdx++;
        }
    }

    ll totalSum = 0;
    fo(i, 0, numCols)
    {
        ll colVal = 0;
        if (sign[i] == '*')
        {
            colVal = 1;
        }

        foe(val, data[i])
        {
            if (sign[i] == '*')
            {
                colVal *= val;
            }
            else if (sign[i] == '+')
            {
                colVal += val;
            }
        }
        totalSum += colVal;
    }

    return to_string(totalSum);
}
string p2(stringstream input)
{
    vstr lines;
    string x;
    while (getline(input, x))
    {
        lines.push_back(x);
    }

    vll vals;
    ll totalSum = 0;
    rfo(i, 0, lines[0].size())
    {
        vals.push_back(0);
        fo(j, 0, lines.size())
        {
            if (lines[j][i] == '*')
            {
                ll prod = 1;
                foe(val, vals)
                {
                    // this code adds extra 0's to the val array, so just ignore them when multiplying
                    if (val == 0)
                        continue;
                    prod *= val;
                }
                vals.clear();
                totalSum += prod;
            }
            else if (lines[j][i] == '+')
            {
                ll sum = 0;
                foe(val, vals)
                {
                    sum += val;
                }
                vals.clear();
                totalSum += sum;
            }
            else if (lines[j][i] != ' ')
            {
                vals[vals.size() - 1] = vals[vals.size() - 1] * 10 + (lines[j][i] - '0');
            }
        }
    }

    return to_string(totalSum);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    const int partNum = 2; // set to 2 for part 2

    aoc::Helper helper(partNum);
    auto inputs = helper.getInputFromFile();
    int errors = 0;

    for (int i = 1; i < inputs.size() + 1; i++)
    {
        print("\n----- Input File " + to_string(i) + " -----");
        auto input = inputs[i - 1];
        if (partNum == 1)
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
