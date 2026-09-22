class Solution {
public:

    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int n, k;
    vector<Node> seg;

    Node merge(Node &L, Node &R) {
        Node res;

        // Product of complete segment
        res.prod = (L.prod * R.prod) % k;

        // Prefixes which end inside left part
        for (int r = 0; r < k; r++) {
            res.cnt[r] += L.cnt[r];
        }

        // Prefixes which go through left and then into right
        for (int r = 0; r < k; r++) {
            int newRemainder = (L.prod * r) % k;
            res.cnt[newRemainder] += R.cnt[r];
        }

        return res;
    }

    Node makeNode(int value) {
        Node res;

        res.prod = value % k;

        // A single element forms one prefix
        res.cnt[res.prod] = 1;

        return res;
    }

    void build(vector<int>& nums, int idx, int l, int r) {

        if (l == r) {
            seg[idx] = makeNode(nums[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(nums, idx * 2, l, mid);
        build(nums, idx * 2 + 1, mid + 1, r);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, int value) {

        if (l == r) {
            seg[idx] = makeNode(value);
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(idx * 2, l, mid, pos, value);
        else
            update(idx * 2 + 1, mid + 1, r, pos, value);

        seg[idx] = merge(seg[idx * 2], seg[idx * 2 + 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {

        // Completely outside
        if (r < ql || l > qr) {
            return Node();
        }

        // Completely inside
        if (ql <= l && r <= qr) {
            return seg[idx];
        }

        int mid = (l + r) / 2;

        Node left = query(idx * 2, l, mid, ql, qr);
        Node right = query(idx * 2 + 1, mid + 1, r, ql, qr);

        /*
            Important:
            If one side is empty, return the other side.
        */

        bool leftEmpty = true;
        bool rightEmpty = true;

        for (int i = 0; i < k; i++) {
            if (left.cnt[i] != 0)
                leftEmpty = false;

            if (right.cnt[i] != 0)
                rightEmpty = false;
        }

        if (leftEmpty)
            return right;

        if (rightEmpty)
            return left;

        return merge(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k_,
        vector<vector<int>>& queries
    ) {

        k = k_;
        n = nums.size();

        seg.resize(4 * n);

        build(nums, 1, 0, n - 1);

        vector<int> ans;

        for (auto &q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            // Get information about nums[start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};