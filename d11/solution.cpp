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

int bfs(map<string, vstr> &graph, const string &start, const string &end)
{
    map<string, bool> visited;
    queue<pair<string, int>> q;
    q.push({start, 0});
    visited[start] = true;

    ll count = 0;
    while (!q.empty())
    {
        auto [node, dist] = q.front();
        q.pop();

        if (node == end)
        {
            count++;
            continue;
        }

        for (const auto &neighbor : graph[node])
        {
            q.push({neighbor, dist + 1});
        }
    }

    return count;
}

ll dfs(map<string, vstr> &graph, const string &node, const string &end, map<pair<string, vstr>, ll> &mem, vstr required)
{
    if (node == end)
    {
        return required.empty() ? 1 : 0;
    }
    if (mem.find({node, required}) != mem.end())
    {
        return mem[{node, required}];
    }
    if (find(required.begin(), required.end(), node) != required.end())
    {
        required.erase(remove(required.begin(), required.end(), node), required.end());
    }

    ll count = 0;
    for (const auto &neighbor : graph[node])
    {
        count += dfs(graph, neighbor, end, mem, required);
    }

    mem[{node, required}] = count;
    return count;
}

string p1(stringstream input)
{
    string x;
    map<string, vstr> graph;
    map<string, vstr> backward;
    while (getline(input, x))
    {
        string start = x.substr(0, 3);
        auto parts = aocAlg.splitString(x.substr(4), ' ');
        graph.insert({start, parts});

        fo(i, 0, parts.size())
        {
            if (backward.find(parts[i]) == backward.end())
            {
                backward.insert({parts[i], vstr()});
            }
            backward[parts[i]].push_back(start);
        }
    }

    string start = "you", end = "out";
    return to_string(bfs(graph, start, end));
}
string p2(stringstream input)
{
    string x;
    map<string, vstr> graph;
    map<string, vstr> backward;
    while (getline(input, x))
    {
        string start = x.substr(0, 3);
        auto parts = aocAlg.splitString(x.substr(5), ' ');
        graph.insert({start, parts});

        fo(i, 0, parts.size())
        {
            if (backward.find(parts[i]) == backward.end())
            {
                backward.insert({parts[i], vstr()});
            }
            backward[parts[i]].push_back(start);
        }
    }

    string start = "svr",
           end = "out";
    map<pair<string, vstr>, ll> mem;
    vstr required;
    required.push_back("fft");
    required.push_back("dac");
    return to_string(dfs(graph, start, end, mem, required));
}

int main()
{
    // ios::sync_with_stdio(0);
    // cin.tie(0);

    const int partNum = 1; // set to 2 for part 2

    AOCHelper helper(partNum, {1, 3});
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
