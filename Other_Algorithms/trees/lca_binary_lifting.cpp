#include <bits/stdc++.h>
using namespace std;

class LcaBinaryLifting {
    int n;
    int levels;
    vector<vector<int>> up;
    vector<int> depth;

  public:
    explicit LcaBinaryLifting(int vertices)
        : n(vertices), levels(1), depth(vertices, 0) {
        while ((1LL << levels) <= max(1, n))
            ++levels;
        up.assign(levels, vector<int>(n, 0));
    }

    void build(const vector<vector<int>> &tree, int root) {
        vector<int> parent(n, -1);
        queue<int> q;
        parent[root] = root;
        q.push(root);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            up[0][node] = parent[node];
            for (int child : tree[node]) {
                if (parent[child] != -1)
                    continue;
                parent[child] = node;
                depth[child] = depth[node] + 1;
                q.push(child);
            }
        }
        for (int level = 1; level < levels; ++level)
            for (int node = 0; node < n; ++node)
                up[level][node] = up[level - 1][up[level - 1][node]];
    }

    int kthAncestor(int node, int k) const {
        if (k < 0 || k > depth[node])
            return -1;
        for (int level = 0; level < levels; ++level)
            if ((k >> level) & 1)
                node = up[level][node];
        return node;
    }

    int lca(int a, int b) const {
        if (depth[a] < depth[b])
            swap(a, b);
        a = kthAncestor(a, depth[a] - depth[b]);
        if (a == b)
            return a;
        for (int level = levels - 1; level >= 0; --level) {
            if (up[level][a] != up[level][b]) {
                a = up[level][a];
                b = up[level][b];
            }
        }
        return up[0][a];
    }
};
