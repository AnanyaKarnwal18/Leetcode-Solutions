class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        bool odd = false, even = false;

        for(int i = 0; i < nums1.size(); i++) {
            if(nums1[i] % 2 == 0)
                even = true;
            else
                odd = true;
        }

        
        if(!odd || !even)
            return true;

        int mn = *min_element(nums1.begin(), nums1.end());

        if(mn % 2 == 1)
            return true;

        
        return false;
    }
};