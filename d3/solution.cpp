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
    }

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

    vstr banks;
    string x;
    while (getline(input, x))
    {
        banks.push_back(x);
    }
    ll sum = 0;
    foe(bank, banks)
    {
        ll largest = bank[bank.length() - 1] - '0', second = 0;
        ll previousLarge = 0;

        rfo(i, 0, bank.length() - 1)
        {
            int val = bank[i] - '0';
            if (10 * val + largest > previousLarge)
            {
                second = max(second, largest);
                largest = val;
                previousLarge = 10 * largest + second;
            }
        }
        sum += previousLarge;
    }

    return to_string(sum);
}
ll getTotalSize(vll sizes)
{
    ll total = 0;
    foe(size, sizes)
    {
        total = total * 10 + size;
    }
    return total;
}

string p2(stringstream input)
{
    int numBat = 12;
    vstr banks;
    string x;
    while (getline(input, x))
    {
        banks.push_back(x);
    }
    ll sum = 0;
    foe(bank, banks)
    {
        vll sizes(numBat, 0);
        fo(i, bank.length() - numBat, bank.length())
        {
            sizes[i - (bank.length() - numBat)] = bank[i] - '0';
        }

        ll previousLarge = getTotalSize(sizes);

        rfo(i, 0, bank.length() - numBat)
        {
            int val = bank[i] - '0';

            bool skipUsed = false;
            // get the new total bettery value. We can skip one number, so we want to skip the first number that can be bigger
            vll tmp(numBat, 0);
            fo(i, 0, numBat - 1)
            {
                if (!skipUsed && sizes[i] < sizes[i + 1])
                {
                    tmp[i + 1] = sizes[i + 1];
                    skipUsed = true;
                }
                else
                {
                    int index = skipUsed ? i + 1 : i;
                    tmp[i + 1] = sizes[index];
                }
            }
            tmp[0] = val;

            if (getTotalSize(tmp) > previousLarge)
            {
                previousLarge = getTotalSize(tmp);
                sizes = tmp;
            }
        }
        sum += previousLarge;
    }

    return to_string(sum);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    aoc::Helper helper(part1);
    auto inputs = helper.getInputFromFile();

    for (int i = 1; i < inputs.size() + 1; i++)
    {
        print("\n----- Input File " + to_string(i) + " -----");
        auto input = inputs[i - 1];
        if (part1)
        {
            string out = p1(stringstream(input));
            helper.writeOutputToFile(out, i);
            helper.compareOutWithExpected(i);
        }
        else
        {
            string out = p2(stringstream(input));
            helper.writeOutputToFile(out, i);
            helper.compareOutWithExpected(i);
        }
    }
}
