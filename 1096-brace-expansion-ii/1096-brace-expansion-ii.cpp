class Solution {
public:

    set<string> merge(set<string> a, set<string> b) {
        set<string> res;

        for (string x : a) {
            for (string y : b) {
                res.insert(x + y);
            }
        }

        return res;
    }

    set<string> parse(string &s, int &i) {

        set<string> res;
        set<string> cur = {""};

        while (i < s.size() && s[i] != '}') {

            if (s[i] == ',') {
                // Union
                for (string x : cur)
                    res.insert(x);

                cur = {""};
                i++;
            }

            else if (s[i] == '{') {
                // Parse inside braces
                i++;  // skip '{'

                set<string> inside = parse(s, i);

                i++;  // skip '}'

                // Concatenate current with inside
                cur = merge(cur, inside);
            }

            else {
                // Single character
                set<string> letter = {string(1, s[i])};

                cur = merge(cur, letter);

                i++;
            }
        }

        // Add last part
        for (string x : cur)
            res.insert(x);

        return res;
    }

    vector<string> braceExpansionII(string expression) {

        int i = 0;

        set<string> ans = parse(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};