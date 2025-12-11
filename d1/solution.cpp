#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../aoc_helper.hpp"
#include "../aoc_algorithms.hpp"

using namespace std;
using namespace aoc;
#define ll long long
#define uint unsigned int
#define ull unsigned long long
// #define endl "\n"
#define elif else if
#define fo(i, a, b) for (int i = a; i < (int)b; i++)
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

#define printall2d(x)         \
    for (auto zz : x)         \
    {                         \
        for (auto qq : zz)    \
        {                     \
            cout << qq << ""; \
        }                     \
        cout << "\n";         \
    }

string p1(stringstream input)
{
    vector<int> all;

    string x;
    while (getline(input, x))
    {
        if (x[0] == 'L')
        {
            all.push_back(-stoi(x.substr(1)));
        }
        else
        {
            all.push_back(stoi(x.substr(1)));
        }
    }

    int totalNum = 50;
    int count = 0;
    for (auto num : all)
    {
        totalNum = (totalNum + num + 1000) % 100;
        if (totalNum == 0)
        {
            count++;
        }
    }

    return to_string(count);
}
string p2(stringstream input)
{
    vector<int> all;

    string x;
    while (getline(input, x))
    {
        if (x[0] == 'L')
        {
            all.push_back(-stoi(x.substr(1)));
        }
        else
        {
            all.push_back(stoi(x.substr(1)));
        }
    }

    int totalNum = 50;
    int count = 0;
    for (auto num : all)
    {
        for (int i = 0; i < abs(num); i++)
        {
            if (num > 0)
            {
                totalNum = (totalNum + 1) % 100;
            }
            else
            {
                totalNum = (totalNum - 1 + 100) % 100;
            }
            if (totalNum == 0)
            {
                count++;
            }
        }
    }

    return to_string(count);
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
