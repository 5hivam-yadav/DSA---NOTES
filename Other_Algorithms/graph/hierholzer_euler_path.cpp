#include <bits/stdc++.h>
using namespace std;

// Directed Euler trail. Returns an empty vector if degree/path checks fail.
vector<int> directedEulerPath(int vertices,
                              const vector<pair<int, int>> &edges) {
    if (edges.empty())
        return {};
    vector<vector<int>> graph(vertices);
    vector<int> inDegree(vertices, 0), outDegree(vertices, 0);
    for (auto [from, to] : edges) {
        graph[from].push_back(to);
        ++outDegree[from];
        ++inDegree[to];
    }

    int start = -1;
    int starts = 0;
    int ends = 0;
    for (int node = 0; node < vertices; ++node) {
        int difference = outDegree[node] - inDegree[node];
        if (difference == 1) {
            start = node;
            ++starts;
        } else if (difference == -1) {
            ++ends;
        } else if (difference != 0) {
            return {};
        }
    }
    if (!((starts == 1 && ends == 1) || (starts == 0 && ends == 0)))
        return {};
    if (start == -1) {
        for (int node = 0; node < vertices; ++node)
            if (outDegree[node] > 0) {
                start = node;
                break;
            }
    }

    vector<int> nextEdge(vertices, 0);
    vector<int> stack{start};
    vector<int> path;
    while (!stack.empty()) {
        int node = stack.back();
        if (nextEdge[node] < (int)graph[node].size()) {
            stack.push_back(graph[node][nextEdge[node]++]);
        } else {
            path.push_back(node);
            stack.pop_back();
        }
    }
    if ((int)path.size() != (int)edges.size() + 1)
        return {};
    reverse(path.begin(), path.end());
    return path;
}
