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

ll getDistance(const tuple<ll, ll, ll> &a, const tuple<ll, ll, ll> &b)
{
    return pow(get<0>(a) - get<0>(b), 2) + pow(get<1>(a) - get<1>(b), 2) + pow(get<2>(a) - get<2>(b), 2);
}
string p1(stringstream input, int inputNum)
{
    vector<tuple<ll, ll, ll>> ranges;
    vll circuit;
    string x;
    while (getline(input, x))
    {
        auto parts = AOCAlgorithms::splitString(x, ',');
        ranges.push_back({stoll(parts[0]), stoll(parts[1]), stoll(parts[2])});
        circuit.push_back(circuit.size());
    }

    vector<vector<ll>> distances(ranges.size(), vector<ll>(ranges.size()));

    // stores <distance, <from,to>>
    vector<pair<ll, pair<ll, ll>>> shortestDistances;
    fo(i, 0, ranges.size() - 1)
    {
        fo(j, i + 1, ranges.size())
        {
            distances[i][j] = getDistance(ranges[i], ranges[j]);
            shortestDistances.push_back({distances[i][j], {i, j}});
        }
    }
    print("");
    sort(shortestDistances.begin(), shortestDistances.end());

    vll numInCircuit(circuit.size(), 1);
    fo(i, 0, (inputNum == 1 ? 10 : 1000))
    {
        if (i == shortestDistances.size())
            break;
        int oldCircuit = circuit[shortestDistances[i].second.second];
        int newCircuit = circuit[shortestDistances[i].second.first];
        fo(j, 0, circuit.size())
        {
            if (circuit[j] == oldCircuit)
            {
                circuit[j] = newCircuit;
                numInCircuit[newCircuit] += 1;
                numInCircuit[oldCircuit] -= 1;
            }
        }
    }

    sort(numInCircuit.begin(), numInCircuit.end(), greater<ll>());

    return to_string(numInCircuit[0] * numInCircuit[1] * numInCircuit[2]);
}
string p2(stringstream input)
{
    vector<tuple<ll, ll, ll>> ranges;
    vll circuit;
    string x;
    while (getline(input, x))
    {
        auto parts = AOCAlgorithms::splitString(x, ',');
        ranges.push_back({stoll(parts[0]), stoll(parts[1]), stoll(parts[2])});
        circuit.push_back(circuit.size());
    }

    vector<vector<ll>> distances(ranges.size(), vector<ll>(ranges.size()));

    // stores distance, <from,to>
    vector<pair<ll, pair<ll, ll>>> shortestDistances;
    fo(i, 0, ranges.size() - 1)
    {
        fo(j, i + 1, ranges.size())
        {
            distances[i][j] = getDistance(ranges[i], ranges[j]);
            shortestDistances.push_back({distances[i][j], {i, j}});
        }
    }

    sort(shortestDistances.begin(), shortestDistances.end());

    vll numInCircuit(circuit.size(), 1);
    ll calc = 0;
    bool done = false;
    ll i = 0;
    while (!done)
    {
        int oldCircuit = circuit[shortestDistances[i].second.second];
        int newCircuit = circuit[shortestDistances[i].second.first];
        fo(j, 0, circuit.size())
        {
            if (circuit[j] == oldCircuit)
            {
                circuit[j] = newCircuit;
                numInCircuit[newCircuit] += 1;
                numInCircuit[oldCircuit] -= 1;

                if (numInCircuit[newCircuit] == circuit.size())
                {
                    calc = get<0>(ranges[shortestDistances[i].second.first]) * get<0>(ranges[shortestDistances[i].second.second]);
                    done = true;
                    break;
                }
            }
        }
        i++;
    }

    return to_string(calc);
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
        print("\n----- Input File " + to_string(i) + " -----");
        auto input = inputs[i - 1];
        string out = partNum == 1 ? p1(stringstream(input), i) : p2(stringstream(input));
        helper.writeOutputToFile(out, i);
        helper.compareOutWithExpected(i);
    }

    helper.printErrorSummary();
}
