#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include "../aoc_helpers.hpp"
#include "../helpers/algorithm_utils.hpp"

using namespace std;
using namespace aoc;
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

#define printall(x)        \
    for (auto zz : x)      \
    {                      \
        cout << zz << " "; \
    }                      \
    cout << "\n";

#define printalln(x)        \
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

string p1(stringstream input)
{
    string x;
    while (getline(input, x))
    {
    }

    ll val = 0;
    return to_string(val);
}
string p2(stringstream input)
{
    string x;
    while (getline(input, x))
    {
    }

    ll val = 0;
    return to_string(val);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    const int partNum = 1; // set to 2 for part 2

    AOCHelper helper(partNum);
    auto inputs = helper.getInputFromFile();

    for (int i = 1; i < inputs.size() + 1; i++)
    {
        print("\n----- Input File " + to_string(i) + " -----");
        auto input = inputs[i - 1];
        if (partNum == 1)
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

    helper.printErrorSummary();
}
