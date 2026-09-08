class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,int> mp;
        for(int i=0;i<nums.size();i++){
            mp[nums[i]]++;
        }
        for(int i =0;i< nums.size();i++){
            auto it = mp.find(nums[i]);
            if(it != mp.end() && it->second>1){
                return true;
            }
        }
        return false;
    }
};