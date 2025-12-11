#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include "../aoc_classes/aoc_helper.hpp"
#include "../aoc_classes/aoc_algorithms.hpp"

using namespace std;
using namespace aoc;
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

bool hasFewerThanXNeighbours(const vstr &grid, int row, int col, int numNeighbours)
{
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    for (int dr = -1; dr <= 1; dr++)
    {
        for (int dc = -1; dc <= 1; dc++)
        {
            if (dr == 0 && dc == 0)
                continue; // skip self
            int newRow = row + dr;
            int newCol = col + dc;
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols)
            {
                if (grid[newRow][newCol] == '@')
                {
                    count++;
                    if (count >= numNeighbours)
                        return false;
                }
            }
        }
    }
    return true;
}
string p1(stringstream input)
{
    vstr lines;
    string x;
    while (getline(input, x))
    {
        lines.push_back(x);
    }

    ll count = 0;
    fo(i, 0, lines.size())
    {
        fo(j, 0, lines[i].size())
        {
            if (lines[i][j] == '@')
            {
                if (hasFewerThanXNeighbours(lines, i, j, 4))
                {
                    count++;
                }
            }
        }
    }

    return to_string(count);
}
string p2(stringstream input)
{

    vstr lines;
    string x;
    while (getline(input, x))
    {
        lines.push_back(x);
    }

    ll count = 0;
    bool changed = false;
    do
    {
        changed = false;
        fo(i, 0, lines.size())
        {
            fo(j, 0, lines[i].size())
            {
                if (lines[i][j] == '@')
                {
                    if (hasFewerThanXNeighbours(lines, i, j, 4))
                    {
                        count++;
                        lines[i][j] = '.';
                        changed = true;
                    }
                }
            }
        }
    } while (changed);

    return to_string(count);
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
