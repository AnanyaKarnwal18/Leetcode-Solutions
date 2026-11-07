
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        int n = servers.size();

        // Available servers: {weight, index}
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > available;

        // Busy servers: {freeTime, weight, index}
        priority_queue<
            tuple<long long,int,int>,
            vector<tuple<long long,int,int>>,
            greater<tuple<long long,int,int>>
        > busy;

        for(int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(tasks.size());

        long long time = 0;

        for(int j = 0; j < tasks.size(); j++) {

            // Current time cannot be earlier than task arrival
            time = max(time, (long long)j);

            // Release all servers that have become free
            while(!busy.empty() && get<0>(busy.top()) <= time) {

                auto [freeTime, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If all servers are busy, jump to earliest free time
            if(available.empty()) {

                time = get<0>(busy.top());

                while(!busy.empty() && get<0>(busy.top()) <= time) {

                    auto [freeTime, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Assign the task to the best available server
            auto [weight, index] = available.top();
            available.pop();

            ans[j] = index;

            // Server becomes free after processing this task
            busy.push({time + tasks[j], weight, index});
        }

        return ans;
    }
};
