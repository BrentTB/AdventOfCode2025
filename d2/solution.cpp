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
#define rfo(i, b, a) for (int i = a - 1; i >= b; i--)
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

#define printall(x)         \
    for (auto zz : x)       \
    {                       \
        cout << zz << "\n"; \
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

    vpairll range;
    string x;
    while (getline(input, x, ','))
    {
        range.push_back({stoll(x.substr(0, x.find('-'))), stoll(x.substr(x.find('-') + 1))});
    }

    ll sum = 0;
    foe(zz, range)
    {
        fo(i, zz.first, zz.second + 1)
        {
            string s = to_string(i);
            if (s.length() % 2 == 0 && s.substr(0, s.length() / 2) == s.substr(s.length() / 2))
            {
                sum += i;
            }
        }
    }

    return to_string(sum);
}
string p2(stringstream input)
{

    vpairll range;
    string x;
    while (getline(input, x, ','))
    {
        range.push_back({stoll(x.substr(0, x.find('-'))), stoll(x.substr(x.find('-') + 1))});
    }

    ll sum = 0;
    foe(zz, range)
    {
        fo(i, zz.first, zz.second + 1)
        {
            string s = to_string(i);
            regex r1("^(.*)\\1+$");
            if (regex_match(s, r1))
            {
                sum += i;
            }
        }
    }

    return to_string(sum);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    aoc::PartConfig config(part1);
    auto inputs = aoc::getInputFromFile(config);
    int errors = 0;

    for (int i = 1; i < inputs.size() + 1; i++)
    {
        print("\n----- Input File " + to_string(i) + " -----");
        auto input = inputs[i - 1];
        if (part1)
        {
            string out = p1(stringstream(input));
            aoc::writeOutputToFile(config, out, i);
            errors += aoc::compareOutWithExpected(config, i);
        }
        else
        {
            string out = p2(stringstream(input));
            aoc::writeOutputToFile(config, out, i);
            errors += aoc::compareOutWithExpected(config, i);
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
