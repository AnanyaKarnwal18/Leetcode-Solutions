#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, LOG, timer;
    vector<vector<int>> adj, up;
    vector<int> tin, tout, depth, bit;
    string s;

    void updateBIT(int idx, int val) {
        for (; idx <= n + 1; idx += idx & -idx) {
            bit[idx] ^= val;
        }
    }

    int queryBIT(int idx) {
        int res = 0;

        for (; idx > 0; idx -= idx & -idx) {
            res ^= bit[idx];
        }

        return res;
    }

    // Apply XOR to every Euler position in [l, r].
    void rangeUpdate(int l, int r, int val) {
        updateBIT(l, val);
        updateBIT(r + 1, val);
    }

    // Iterative DFS to avoid stack overflow.
    void dfs(int root) {
        vector<int> parent(n, -1);

        // {node, exiting}
        stack<pair<int, bool>> st;
        st.push({root, false});
        parent[root] = root;

        while (!st.empty()) {
            auto [u, exiting] = st.top();
            st.pop();

            if (exiting) {
                tout[u] = timer;
                continue;
            }

            tin[u] = ++timer;

            up[u][0] = parent[u];

            for (int j = 1; j < LOG; j++) {
                up[u][j] =
                    up[up[u][j - 1]][j - 1];
            }

            st.push({u, true});

            for (int v : adj[u]) {
                if (v == parent[u]) {
                    continue;
                }

                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push({v, false});
            }
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++) {
            if (diff & (1 << j)) {
                u = up[u][j];
            }
        }

        if (u == v) {
            return u;
        }

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }

    // XOR mask along the path from root to node u.
    int rootPathMask(int u) {
        return queryBIT(tin[u]);
    }

    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;
        this->s = s;
        timer = 0;

        adj.assign(n, {});

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        tin.assign(n, 0);
        tout.assign(n, 0);
        depth.assign(n, 0);

        LOG = 1;
        while ((1 << LOG) <= n) {
            LOG++;
        }

        up.assign(n, vector<int>(LOG, 0));

        // n + 2 allows the difference update at tout[u] + 1.
        bit.assign(n + 2, 0);

        dfs(0);

        // Initialize each node's contribution over its subtree.
        for (int u = 0; u < n; u++) {
            int mask = 1 << (s[u] - 'a');
            rangeUpdate(tin[u], tout[u], mask);
        }

        vector<bool> ans;

        for (const string &q : queries) {
            stringstream ss(q);

            string type;
            int u, v;

            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');

                // Remove old character from this subtree's
                // root-path XOR contributions.
                rangeUpdate(tin[u], tout[u], oldMask);

                s[u] = c;

                // Add the new character.
                rangeUpdate(tin[u], tout[u], newMask);
            } else {
                ss >> v;

                int w = lca(u, v);

                int mask =
                    rootPathMask(u) ^
                    rootPathMask(v) ^
                    (1 << (s[w] - 'a'));

                // A palindrome permutation can have
                // at most one character with odd frequency.
                ans.push_back(
                    (mask & (mask - 1)) == 0
                );
            }
        }

        return ans;
    }
};