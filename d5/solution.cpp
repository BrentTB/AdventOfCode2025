#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include "../aoc_helper.hpp"
#include "../aoc_algorithms.hpp"

using namespace std;
using namespace aoc;
#define ll long long
#define uint unsigned int
#define ull unsigned long long
// #define endl "\n"
#define elif else if
#define fo(i, a, b) for (ll i = a; i < (ll)b; i++)
#define foe(a, b) for (auto &a : b)
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
    vpairll fresh;
    vll nums;
    string x;
    bool onFresh = true;
    while (getline(input, x))
    {
        if (x == "")
        {
            onFresh = false;
            continue;
        }
        if (onFresh)
        {
            auto ind = x.find('-');
            fresh.push_back({stol(x.substr(0, ind)), stol(x.substr(ind + 1))});
        }
        else
        {
            nums.push_back(stol(x));
        }
    }

    ll numFresh = 0;
    foe(num, nums)
    {
        foe(val, fresh)
        {
            if (num >= val.first && num <= val.second)
            {
                numFresh++;
                break;
            }
        }
    }

    return to_string(numFresh);
}

string p2(stringstream input)
{
    auto aocAlg = AOCAlgorithms();
    vpairll fresh;
    vll nums;
    string x;
    bool onFresh = true;
    while (getline(input, x))
    {
        if (x == "")
        {
            onFresh = false;
            continue;
        }
        if (onFresh)
        {
            auto ind = x.find('-');
            fresh.push_back({stol(x.substr(0, ind)), stol(x.substr(ind + 1))});
        }
        else
        {
            nums.push_back(stol(x));
        }
    }

    aocAlg.combineRanges(fresh);

    ll numFresh = 0;
    foe(val, fresh)
    {
        numFresh += val.second - val.first + 1;
    }

    return to_string(numFresh);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    const int partNum = 2; // set to 2 for part 2

    AOCHelper helper(partNum);
    auto inputs = helper.getInputFromFile();

    for (int i = 1; i < inputs.size() + 1; i++)
    {
        auto input = inputs[i - 1];
        print("\n----- Input File " + to_string(input.second) + " -----");
        if (partNum == 1)
        {
            string out = p1(stringstream(input.first));
            helper.writeOutputToFile(out, input.second);
            helper.compareOutWithExpected(input.second);
        }
        else
        {
            string out = p2(stringstream(input.first));
            helper.writeOutputToFile(out, input.second);
            helper.compareOutWithExpected(input.second);
        }
    }

    helper.printErrorSummary();
}
