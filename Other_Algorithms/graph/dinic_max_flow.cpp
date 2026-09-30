#include <bits/stdc++.h>
using namespace std;

class Dinic {
    struct Edge {
        int to;
        int reverseIndex;
        long long capacity;
    };

    vector<vector<Edge>> graph;
    vector<int> level;
    vector<int> nextEdge;

    bool buildLevels(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (const Edge &edge : graph[node]) {
                if (edge.capacity > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[node] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[sink] != -1;
    }

    long long sendFlow(int node, int sink, long long flow) {
        if (node == sink)
            return flow;
        for (int &i = nextEdge[node]; i < (int)graph[node].size(); ++i) {
            Edge &edge = graph[node][i];
            if (edge.capacity == 0 || level[edge.to] != level[node] + 1)
                continue;
            long long pushed =
                sendFlow(edge.to, sink, min(flow, edge.capacity));
            if (pushed == 0)
                continue;
            edge.capacity -= pushed;
            graph[edge.to][edge.reverseIndex].capacity += pushed;
            return pushed;
        }
        return 0;
    }

  public:
    explicit Dinic(int vertices)
        : graph(vertices), level(vertices), nextEdge(vertices) {}

    void addEdge(int from, int to, long long capacity) {
        int forwardIndex = graph[from].size();
        int reverseIndex = graph[to].size();
        if (from == to)
            ++reverseIndex;
        graph[from].push_back({to, reverseIndex, capacity});
        graph[to].push_back({from, forwardIndex, 0});
    }

    long long maxFlow(int source, int sink) {
        if (source == sink)
            return 0;
        long long flow = 0;
        while (buildLevels(source, sink)) {
            fill(nextEdge.begin(), nextEdge.end(), 0);
            while (long long pushed = sendFlow(source, sink, LLONG_MAX))
                flow += pushed;
        }
        return flow;
    }
};
