class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges,
                     string labels, int k) {

        vector<vector<pair<int, int>>> adj(n);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
        }

        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dist(
            n, vector<long long>(k + 1, INF)
        );

        // {cost, node, consecutive character count}
        using State = tuple<long long, int, int>;

        priority_queue<State, vector<State>, greater<State>> pq;

        // Starting node contributes its label.
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [cost, u, count] = pq.top();
            pq.pop();

            if (cost != dist[u][count]) {
                continue;
            }

            for (auto &[v, w] : adj[u]) {
                int newCount;

                if (labels[u] == labels[v]) {
                    newCount = count + 1;
                } else {
                    newCount = 1;
                }

                if (newCount > k) {
                    continue;
                }

                long long newCost = cost + w;

                if (newCost < dist[v][newCount]) {
                    dist[v][newCount] = newCost;
                    pq.push({newCost, v, newCount});
                }
            }
        }

        long long ans = INF;

        for (int count = 1; count <= k; count++) {
            ans = min(ans, dist[n - 1][count]);
        }

        return ans == INF ? -1 : static_cast<int>(ans);
    }
};
