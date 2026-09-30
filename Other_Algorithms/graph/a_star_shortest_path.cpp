#include <bits/stdc++.h>
using namespace std;

struct WeightedEdge {
    int to;
    long long weight;
};

struct AStarResult {
    long long distance;
    vector<int> path;
};

// heuristic[node] must be admissible; weights must be non-negative.
optional<AStarResult> aStar(const vector<vector<WeightedEdge>> &graph,
                            const vector<long long> &heuristic, int source,
                            int target) {
    int n = graph.size();
    const long long inf = LLONG_MAX / 4;
    vector<long long> distance(n, inf);
    vector<int> parent(n, -1);
    using State = tuple<long long, long long, int>; // f, g, node
    priority_queue<State, vector<State>, greater<State>> queue;
    distance[source] = 0;
    queue.push({heuristic[source], 0, source});

    while (!queue.empty()) {
        auto [estimatedTotal, cost, node] = queue.top();
        queue.pop();
        if (cost != distance[node])
            continue;
        if (node == target)
            break;
        for (const WeightedEdge &edge : graph[node]) {
            if (cost > inf - edge.weight)
                continue;
            long long nextCost = cost + edge.weight;
            if (nextCost < distance[edge.to]) {
                distance[edge.to] = nextCost;
                parent[edge.to] = node;
                queue.push({nextCost + heuristic[edge.to], nextCost, edge.to});
            }
        }
    }
    if (distance[target] == inf)
        return nullopt;

    vector<int> path;
    for (int node = target; node != -1; node = parent[node])
        path.push_back(node);
    reverse(path.begin(), path.end());
    return AStarResult{distance[target], path};
}
