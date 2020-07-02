class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map < int, int > temp;
        for(int i = 0; i < nums.size(); i++)
        {
            int result = target - nums.at(i);
            if( temp.count(result) )
            {
                return { temp.find( result ) -> second, i };
            }
            temp.insert( make_pair( i, nums.at(i) ) ); 
        }
        return {};
    }
};
