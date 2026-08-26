class Solution {
private:
    static bool comparator(pair<int,char> p1, pair<int,char> p2) {
        return p1.first > p2.first;
    }

public:
    string frequencySort(string s) {

        pair<int,char> freq[256];

        for(int i = 0; i < 256; i++) {
            freq[i] = {0, (char)i};
        }

        for(char ch : s) {
            freq[(unsigned char)ch].first++;
        }

        sort(freq, freq + 256, comparator);

        string ans;

        for(int i = 0; i < 256; i++) {
            if(freq[i].first > 0) {

                for(int j = 0; j < freq[i].first; j++) {
                    ans.push_back(freq[i].second);
                }

            }
        }

        return ans;
    }
};