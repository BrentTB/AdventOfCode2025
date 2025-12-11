#ifndef ALGORITHM_UTILS_HPP
#define ALGORITHM_UTILS_HPP

#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

using namespace std;

// AOCAlgorithms class for Advent of Code
// This class provides common algorithms and utilities for solving coding problems
namespace aoc
{
    class AOCAlgorithms
    {
    public:
        // Dijkstra's shortest path algorithm
        // Returns the shortest distances from start node to all reachable nodes
        // graph: adjacency list where graph[node] = vector of {neighbor, weight} pairs
        // start: starting node
        // Returns: map of node -> shortest distance from start
        template <typename T>
        map<T, long long> dijkstra(
            const map<T, vector<pair<T, long long>>> &graph,
            const T &start,
            map<T, vector<T>> *outPath = nullptr)
        {
            map<T, long long> distances;
            map<T, T> predecessor; // tracks best parent for path reconstruction
            priority_queue<
                pair<long long, T>,
                vector<pair<long long, T>>,
                greater<pair<long long, T>>>
                pq;

            // Initialize all nodes to infinity distance
            for (const auto &node : graph)
            {
                distances[node.first] = numeric_limits<long long>::max();
                // Also initialize all neighbors
                for (const auto &[neighbor, weight] : node.second)
                {
                    if (distances.find(neighbor) == distances.end())
                    {
                        distances[neighbor] = numeric_limits<long long>::max();
                    }
                }
            }

            // Ensure start node is initialized (even if not in graph keys)
            if (distances.find(start) == distances.end())
            {
                distances[start] = numeric_limits<long long>::max();
            }

            // Set start distance to 0
            distances[start] = 0;
            pq.push({0, start});

            while (!pq.empty())
            {
                auto [dist, node] = pq.top();
                pq.pop();

                // Skip if we've already found a shorter path
                if (dist > distances[node])
                    continue;

                // Check all neighbors
                if (graph.find(node) != graph.end())
                {
                    for (const auto &[neighbor, weight] : graph.at(node))
                    {
                        long long newDist = dist + weight;
                        if (distances.find(neighbor) != distances.end() && newDist < distances[neighbor])
                        {
                            distances[neighbor] = newDist;
                            if (outPath)
                            {
                                predecessor[neighbor] = node;
                            }
                            pq.push({newDist, neighbor});
                        }
                    }
                }
            }

            if (outPath)
            {
                outPath->clear();

                for (const auto &[target, distance] : distances)
                {
                    if (distance == numeric_limits<long long>::max())
                    {
                        continue; // unreachable node
                    }

                    vector<T> path;
                    T current = target;

                    // Walk backwards using predecessor map to rebuild path
                    while (true)
                    {
                        path.push_back(current);
                        auto it = predecessor.find(current);
                        if (current == start || it == predecessor.end())
                        {
                            break;
                        }
                        current = it->second;
                    }

                    reverse(path.begin(), path.end());
                    (*outPath)[target] = std::move(path);
                }
            }

            return distances;
        }

        // Combine overlapping or adjacent ranges
        // Takes a vector of pairs representing ranges [first, second] and combines overlapping ranges
        // The input ranges will be modified in place
        template <typename T>
        void combineRanges(vector<pair<T, T>> &ranges)
        {
            if (ranges.empty())
                return;

            bool changed = true;
            while (changed)
            {
                changed = false;
                for (size_t i = 0; i < ranges.size(); i++)
                {
                    for (size_t j = i + 1; j < ranges.size(); j++)
                    {
                        const pair<T, T> &range1 = ranges[i];
                        const pair<T, T> &range2 = ranges[j];

                        // overlapping range on the right
                        if (range2.first >= range1.first && range2.second >= range1.second && range2.first <= range1.second)
                        {
                            changed = true;
                            ranges[i].second = range2.second;
                            ranges.erase(ranges.begin() + j);
                            break;
                        }
                        // overlapping range on the left
                        else if (range2.first <= range1.first && range2.second <= range1.second && range2.second >= range1.first)
                        {
                            changed = true;
                            ranges[i].first = range2.first;
                            ranges.erase(ranges.begin() + j);
                            break;
                        }
                        // completely enclosed by range1
                        else if (range2.first >= range1.first && range2.second <= range1.second)
                        {
                            changed = true;
                            ranges.erase(ranges.begin() + j);
                            break;
                        }
                        // completely encloses range1
                        else if (range2.first <= range1.first && range2.second >= range1.second)
                        {
                            changed = true;
                            ranges[i] = range2;
                            ranges.erase(ranges.begin() + j);
                            break;
                        }
                    }
                    if (changed)
                    {
                        break;
                    }
                }
            }
        }

        // Greatest Common Divisor using Euclidean algorithm
        template <typename T>
        T gcd(T a, T b)
        {
            a = a < 0 ? -a : a;
            b = b < 0 ? -b : b;
            return b == 0 ? a : gcd(b, a % b);
        }

        // Least Common Multiple
        template <typename T>
        T lcm(T a, T b)
        {
            return a / gcd(a, b) * b;
        }

        // Split string by delimiter
        vector<string> splitString(const string &s, char delimiter)
        {
            vector<string> tokens;
            string token;
            istringstream tokenStream(s);
            while (getline(tokenStream, token, delimiter))
            {
                tokens.push_back(token);
            }
            return tokens;
        }

        // Compress grid points to remove unused coordinates
        template <typename T>
        vector<pair<T, T>> compressGridPoints(vector<pair<T, T>> &points)
        {
            T maxGridSize = 0;
            for (auto point : points)
            {
                maxGridSize = max(maxGridSize, point.first + 1);
                maxGridSize = max(maxGridSize, point.second + 1);
            }
            vector<bool> usedX(maxGridSize, false);
            vector<bool> usedY(maxGridSize, false);
            T numX = 1, numY = 1;
            vector<T> newNumsX(maxGridSize, 0), newNumsY(maxGridSize, 0);

            for (auto part : points)
            {
                usedX[part.first] = true;
                usedY[part.second] = true;
            }
            for (T i = 0; i < maxGridSize; i++)
            {
                if (usedX[i])
                {
                    newNumsX[i] = numX;
                    numX++;
                }
                if (usedY[i])
                {
                    newNumsY[i] = numY;
                    numY++;
                }
            }
            vector<pair<T, T>> partsSlim;
            for (auto part : points)
            {
                partsSlim.push_back({newNumsX[part.first], newNumsY[part.second]});
            }
            return partsSlim;
        }
    };

} // namespace aoc

#endif // ALGORITHM_UTILS_HPP
