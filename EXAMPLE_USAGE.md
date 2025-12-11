# Helper Classes Usage Examples

## AOCAlgorithms

### Dijkstra's Shortest Path

```cpp
#include "../aoc_algorithms.hpp"

// Create a graph as adjacency list
// Type, T, can be anything to identify nodes

auto aocAlg = AOCAlgorithms();

std::unordered_map<int, std::vector<std::pair<int, long long>>> graph;
graph[0] = {{1, 4}, {2, 1}};  // Node 0 connects to node 1 (weight 4) and node 2 (weight 1)
graph[1] = {{3, 1}};           // Node 1 connects to node 3 (weight 1)
graph[2] = {{1, 2}, {3, 5}};   // Node 2 connects to nodes 1 and 3
graph[3] = {};                 // Node 3 has no outgoing edges

// Find shortest paths from node 0
auto distances = aocAlg.dijkstra(graph, 0);

// distances[0] = 0, distances[1] = 3, distances[2] = 1, distances[3] = 4
```

### Combining Overlapping Ranges

```cpp
#include "../aoc_algorithms.hpp"

auto aocAlg = AOCAlgorithms();

// Combine overlapping or adjacent ranges
std::vector<std::pair<int, int>> ranges = {{1, 5}, {3, 8}, {10, 15}, {12, 20}};
aocAlg.combineRanges(ranges);
// Result: {{1, 8}, {10, 20}}
```

### Adding a Range to Existing Ranges

```cpp
#include "../aoc_algorithms.hpp"

auto aocAlg = AOCAlgorithms();

std::vector<std::pair<int, int>> ranges = {{1, 5}, {10, 15}};
aocAlg.addToRanges({3, 12}, ranges);
// Result: range {3, 12} is added/merged with existing ranges
```

### GCD and LCM

```cpp
#include "../aoc_algorithms.hpp"

auto aocAlg = AOCAlgorithms();

int a = 12, b = 8;
int result_gcd = aocAlg.gcd(a, b);  // 4
int result_lcm = aocAlg.lcm(a, b);  // 24
```

## FileReader and OutputValidator

See `aoc_helpers.hpp` for the combined Helper class that uses both:

```cpp
#include "../aoc_helper.hpp"

int main()
{
    const int partNum = 1;
    aoc::AOCHelper helper(partNum);

    // Read input files
    auto inputs = helper.getInputFromFile();

    // Process and write output
    for (int i = 1; i < inputs.size() + 1; i++)
    {
        auto input = inputs[i - 1];
        string out = processInput(input.first);
        helper.writeOutputToFile(out, input.second);
        helper.compareOutWithExpected(input.second);
    }

    // Print summary
    helper.printErrorSummary();
}
```
