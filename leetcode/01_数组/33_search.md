
``` cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() == 0)
        {
            return -1;
        }
        int start = 0, end = nums.size()-1;
        if(target == nums[0])
        {
            return 0;
        }
        else if(target < nums[0]) // 目标值在后半段
        {
            for(size_t i = 1; i<nums.size(); i++)
            {
                if(!(target < nums[i]))
                {
                    start = i;
                    break;
                }
            }
        }
        else // 目标值在前半段
        {
            for (size_t i = 1; i < nums.size(); i++)
            {
                if(nums[0] > nums[i])
                {
                    end = i-1;
                    break;
                }
            }
        }
        int length = end-start+1;
        int res = -1;
        // 在一个升序数组里使用二分法查找目标值
        while(length >= 1)
        {
            size_t i = start+length/2;
            if(target == nums[i])
            {
                res = i;
                break;
            }
            else if(target > nums[i])
            {
                if(start==i)start++;
                else
                {
                    start = i;
                }
            }
            else
            {
                if(end==i)end--;
                else
                {
                     end = i;
                }
            }
            length = end-start+1;
        }
        return res;
    }
};
```
