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

#define mapIter(map) \
    for (auto [key, val] : map)

auto aocAlg = AOCAlgorithms();

string p1(stringstream input)
{
    vpairll parts;
    string x;
    while (getline(input, x))
    {
        auto split = aocAlg.splitString(x, ',');
        parts.push_back({stol(split[0]), stol(split[1])});
    }

    ll maxSize = 0;
    fo(i, 0, parts.size() - 1)
    {
        fo(j, i + 1, parts.size())
        {
            ll size = (abs(parts[i].first - parts[j].first) + 1) * (abs(parts[i].second - parts[j].second) + 1);
            maxSize = max(maxSize, size);
        }
    }

    return to_string(maxSize);
}

bool isInside(bool **grid, map<pairll, bool> &visited, int gridSize, int x, int y)
{
    if (x == -1 || y == -1 || x == gridSize || y == gridSize)
    {
        return false;
    }
    if (grid[x][y])
        return true;
    if (!isInside(grid, visited, gridSize, x + 1, y) || !isInside(grid, visited, gridSize, x, y + 1))
        return false;
    return true;
}

void makeGridTrue(bool **grid, int x, int y)
{
    if (grid[x][y])
        return;

    grid[x][y] = true;
    makeGridTrue(grid, x + 1, y);
    makeGridTrue(grid, x - 1, y);
    makeGridTrue(grid, x, y + 1);
    makeGridTrue(grid, x, y - 1);
}

bool isAllInsideTrue(bool **grid, pairll start, pairll end)
{
    int minX = min(start.first, end.first);
    int maxX = max(start.first, end.first);
    int minY = min(start.second, end.second);
    int maxY = max(start.second, end.second);
    fo(x, minX, maxX + 1)
    {
        fo(y, minY, maxY + 1)
        {
            if (!grid[x][y])
                return false;
        }
    }
    return true;
}
string p2(stringstream input)
{
    vpairll parts;
    string x;
    print("start");
    while (getline(input, x))
    {
        auto split = aocAlg.splitString(x, ',');
        parts.push_back({stoll(split[0]), stoll(split[1])});
    }

    ll maxGridSize = 0;
    auto partsSlim = aocAlg.compressGridPoints(parts);

    foe(point, partsSlim)
    {
        maxGridSize = max(maxGridSize, point.first);
        maxGridSize = max(maxGridSize, point.second);
    }
    maxGridSize += 2;
    bool **grid = new bool *[maxGridSize];
    fo(i, 0, maxGridSize)
    {
        grid[i] = new bool[maxGridSize]();
    }

    print("setting grid");
    fo(i, 0, partsSlim.size() - 1)
    {
        int minX = min(partsSlim[i].first, partsSlim[i + 1].first);
        int maxX = max(partsSlim[i].first, partsSlim[i + 1].first);
        int minY = min(partsSlim[i].second, partsSlim[i + 1].second);
        int maxY = max(partsSlim[i].second, partsSlim[i + 1].second);
        fo(x, minX, maxX + 1)
        {
            fo(y, minY, maxY + 1)
            {
                grid[x][y] = true;
            }
        }
    }

    print("setting grid2");
    int minX = min(partsSlim[partsSlim.size() - 1].first, partsSlim[0].first);
    int maxX = max(partsSlim[partsSlim.size() - 1].first, partsSlim[0].first);
    int minY = min(partsSlim[partsSlim.size() - 1].second, partsSlim[0].second);
    int maxY = max(partsSlim[partsSlim.size() - 1].second, partsSlim[0].second);
    fo(x, minX, maxX + 1)
    {

        fo(y, minY, maxY + 1)
        {
            grid[x][y] = true;
        }
    }

    print("getting isInside");
    map<pairll, bool> visited;
    visited.clear();

    pairll start = {-1, -1};
    bool found = false;
    if (isInside(grid, visited, maxGridSize, partsSlim[0].first - 1, partsSlim[0].second - 1))
    {
        start = {partsSlim[0].first - 1, partsSlim[0].second - 1};
        found = true;
    }

    print(found);
    visited.clear();
    if (!found && isInside(grid, visited, maxGridSize, partsSlim[0].first + 1, partsSlim[0].second - 1))
    {
        start = {partsSlim[0].first + 1, partsSlim[0].second - 1};
        found = true;
    }

    print(found);
    visited.clear();
    if (!found && isInside(grid, visited, maxGridSize, partsSlim[0].first + 1, partsSlim[0].second + 1))
    {
        start = {partsSlim[0].first + 1, partsSlim[0].second + 1};
        found = true;
    }

    print(found);
    visited.clear();
    if (!found && isInside(grid, visited, maxGridSize, partsSlim[0].first - 1, partsSlim[0].second + 1))
    {
        start = {partsSlim[0].first - 1, partsSlim[0].second + 1};
        found = true;
    }

    print("makeGridTrue");
    makeGridTrue(grid, start.first, start.second);

    print("start");
    ll maxSize = 0;
    fo(i, 0, partsSlim.size() - 1)
    {
        fo(j, i + 1, partsSlim.size())
        {
            if (isAllInsideTrue(grid, partsSlim[i], partsSlim[j]))
            {
                ll size = (abs(parts[i].first - parts[j].first) + 1) * (abs(parts[i].second - parts[j].second) + 1);
                maxSize = max(maxSize, size);
            }
        }
    }

    return to_string(maxSize);
}

bool isNoPartsInside(bool **grid, vpairll parts, pairll start, pairll end, ll gridSize)
{
    int minX = min(start.first, end.first);
    int maxX = max(start.first, end.first);
    int minY = min(start.second, end.second);
    int maxY = max(start.second, end.second);
    foe(part, parts)
    {
        if (part.first > minX && part.first < maxX && part.second > minY && part.second < maxY)
        {
            return false;
        }
    }

    // there shoulnd't be any borders inside the square
    fo(x, minX + 1, maxX)
    {
        fo(y, minY + 1, maxY)
        {
            if (grid[x][y])
                return false;
        }
    }

    // if I go in the direction the square would go, I should eventually find a border (not full proof, but should help)
    bool found = false;
    if (start.first < end.first)
    {
        fo(i, start.first + 1, gridSize)
        {
            if (grid[i][start.second])
            {
                found = true;
                continue;
            }
        }
        if (!found)
            return false;
        found = false;
        fo(i, 0, end.first)
        {
            if (grid[i][end.second])
            {
                found = true;
                continue;
            }
        }
        if (!found)
            return false;
        found = false;
    }
    else
    {
        fo(i, end.first + 1, gridSize)
        {
            if (grid[i][end.second])
            {
                found = true;
                continue;
            }
        }
        if (!found)
            return false;
        found = false;
        fo(i, 0, start.first)
        {
            if (grid[i][start.second])
            {
                found = true;
                continue;
            }
        }
        if (!found)
            return false;
        found = false;
    }

    if (start.second < end.second)
    {
        fo(i, start.second + 1, gridSize)
        {
            if (grid[start.first][i])
            {
                found = true;
                continue;
            }
        }
        if (!found)
            return false;
        found = false;
        fo(i, 0, end.second)
        {
            if (grid[end.first][i])
            {
                found = true;
                continue;
            }
        }
        if (!found)
            return false;
        found = false;
    }
    else
    {
        fo(i, end.second + 1, gridSize)
        {
            if (grid[end.first][i])
                found = true;
        }
        if (!found)
            return false;
        found = false;
        fo(i, 0, start.second)
        {
            if (grid[start.first][i])
                found = true;
        }
        if (!found)
            return false;
        found = false;
    }

    return true;
}
bool has3BordersTrue(bool **grid, pairll start, pairll end)
{
    int minX = min(start.first, end.first);
    int maxX = max(start.first, end.first);
    int minY = min(start.second, end.second);
    int maxY = max(start.second, end.second);

    // check one square vertical and horizontal to each part, in the right direction

    int trueCount = 0;

    if (start.first > start.second)
    {
        if (grid[start.first - 1][start.second])
            trueCount++;
        if (grid[start.first][start.second + 1])
            trueCount++;
    }
    else
    {
        if (grid[start.first + 1][start.second])
            trueCount++;
        if (grid[start.first][start.second - 1])
            trueCount++;
    }

    if (start.second > end.second)
    {
        if (grid[end.first + 1][end.second])
            trueCount++;
        if (grid[end.first][end.second - 1])
            trueCount++;
    }
    else
    {
        if (grid[end.first - 1][end.second])
            trueCount++;
        if (grid[end.first][end.second + 1])
            trueCount++;
    }

    return trueCount >= 3;
}

// this function was my attempt when p2() was too slow. It does give the correct answer for my input,
// but I'm not sure if it's correct for all inputs.
string p2_2(stringstream input)
{
    vpairll parts;
    string x;
    ll maxGridSize = 0;
    print("start");
    while (getline(input, x))
    {
        auto split = aocAlg.splitString(x, ',');
        parts.push_back({stoll(split[0]), stoll(split[1])});
        maxGridSize = max(maxGridSize, stoll(split[0]));
        maxGridSize = max(maxGridSize, stoll(split[1]));
    }
    maxGridSize += 2;

    print("here");
    bool **grid = new bool *[maxGridSize];
    fo(i, 0, maxGridSize)
    {
        grid[i] = new bool[maxGridSize]();
    }

    print("setting grid");
    fo(i, 0, parts.size() - 1)
    {
        int minX = min(parts[i].first, parts[i + 1].first);
        int maxX = max(parts[i].first, parts[i + 1].first);
        int minY = min(parts[i].second, parts[i + 1].second);
        int maxY = max(parts[i].second, parts[i + 1].second);
        fo(x, minX, maxX + 1)
        {
            fo(y, minY, maxY + 1)
            {
                grid[x][y] = true;
            }
        }
    }

    print("setting grid2");
    int minX = min(parts[parts.size() - 1].first, parts[0].first);
    int maxX = max(parts[parts.size() - 1].first, parts[0].first);
    int minY = min(parts[parts.size() - 1].second, parts[0].second);
    int maxY = max(parts[parts.size() - 1].second, parts[0].second);
    fo(x, minX, maxX + 1)
    {

        fo(y, minY, maxY + 1)
        {
            grid[x][y] = true;
        }
    }

    // 3/4 of the lines next to the grid must be true, and there must be no parts on the inside
    print("start");
    ll maxSize = 0;
    fo(i, 0, parts.size() - 1)
    {
        fo(j, i + 1, parts.size())
        {
            ll size = (abs(parts[i].first - parts[j].first) + 1) * (abs(parts[i].second - parts[j].second) + 1);
            if (size < maxSize)
                continue;
            if (has3BordersTrue(grid, parts[i], parts[j]) && isNoPartsInside(grid, parts, parts[i], parts[j], maxGridSize))
            {
                print("found one: " + to_string(i) + ", " + to_string(j));
                print(to_string(size));
                maxSize = max(maxSize, size);
            }
        }
    }

    return to_string(maxSize);
}

int main()
{
    const int partNum = 2; // set to 2 for part 2

    AOCHelper helper(partNum);
    auto inputs = helper.getInputFromFile();

    for (int i = 1; i < inputs.size() + 1; i++)
    {
        auto input = inputs[i - 1];
        print("\n----- Input File " + to_string(input.second) + " -----");
        string out = partNum == 1 ? p1(stringstream(input.first)) : p2(stringstream(input.first));
        helper.writeOutputToFile(out, input.second);
        helper.compareOutWithExpected(input.second);
    }

    helper.printErrorSummary();
}
