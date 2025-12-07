#ifndef ALGORITHM_UTILS_HPP
#define ALGORITHM_UTILS_HPP

#include <algorithm>
#include <limits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// AlgorithmUtils class for Advent of Code
// This class provides common algorithms and utilities for solving coding problems
namespace aoc
{

    class AlgorithmUtils
    {
    public:
        // Dijkstra's shortest path algorithm
        // Returns the shortest distances from start node to all reachable nodes
        // graph: adjacency list where graph[node] = vector of {neighbor, weight} pairs
        // start: starting node
        // Returns: map of node -> shortest distance from start
        template <typename T>
        static std::unordered_map<T, long long> dijkstra(
            const std::unordered_map<T, std::vector<std::pair<T, long long>>> &graph,
            const T &start)
        {
            std::unordered_map<T, long long> distances;
            std::priority_queue<
                std::pair<long long, T>,
                std::vector<std::pair<long long, T>>,
                std::greater<std::pair<long long, T>>>
                pq;

            // Initialize all nodes to infinity distance
            for (const auto &node : graph)
            {
                distances[node.first] = std::numeric_limits<long long>::max();
                // Also initialize all neighbors
                for (const auto &[neighbor, weight] : node.second)
                {
                    if (distances.find(neighbor) == distances.end())
                    {
                        distances[neighbor] = std::numeric_limits<long long>::max();
                    }
                }
            }
            
            // Ensure start node is initialized (even if not in graph keys)
            if (distances.find(start) == distances.end())
            {
                distances[start] = std::numeric_limits<long long>::max();
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
                            pq.push({newDist, neighbor});
                        }
                    }
                }
            }

            return distances;
        }

        // Combine overlapping or adjacent ranges
        // Takes a vector of pairs representing ranges [first, second] and combines overlapping ranges
        // The input ranges will be modified in place
        template <typename T>
        static void combineRanges(std::vector<std::pair<T, T>> &ranges)
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
                        const std::pair<T, T> &range1 = ranges[i];
                        const std::pair<T, T> &range2 = ranges[j];

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

        // Add a range to a collection of ranges, merging if there's overlap
        // range: the new range to add
        // ranges: existing collection of ranges (will be modified and combined)
        template <typename T>
        static void addToRanges(const std::pair<T, T> &range, std::vector<std::pair<T, T>> &ranges)
        {
            ranges.push_back(range);
            combineRanges(ranges);
        }

        // Greatest Common Divisor using Euclidean algorithm
        template <typename T>
        static T gcd(T a, T b)
        {
            a = a < 0 ? -a : a;
            b = b < 0 ? -b : b;
            return b == 0 ? a : gcd(b, a % b);
        }

        // Least Common Multiple
        template <typename T>
        static T lcm(T a, T b)
        {
            return a / gcd(a, b) * b;
        }
    };

} // namespace aoc

#endif // ALGORITHM_UTILS_HPP
