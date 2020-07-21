

``` cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.size() < 1)
        {
            return {-1,-1};
        }
        if(nums.size() == 1)
        {
            if(nums[0] == target)
            {
                return {0,0};
            }
            else
            {
                return {-1,-1};
            }
        }

        int start = 0, end = nums.size()-1, res = -1;

        while(start <= end)
        {
            int mid = start + (end-start)/2;
            if(target == nums[mid])
            {
                res = mid;
                break;
            }
            else if(target > nums[mid])
            {
                start = mid+1;
            }
            else if(target < nums[mid])
            {
                end = mid-1;
            }
        }
        if(res == -1)
        {
            return {-1,-1};
        }
        int first = (findFirst(nums, res) == -1)? res:findFirst(nums, res);
        int last =  (findLast(nums, res) == -1) ? res:findLast (nums, res);

        return {first, last};
    }

    int findFirst(vector<int>& nums, int mid)
    {
        int start = 0, end = mid-1, res = -1;
        int target = nums[mid];
        while(start <= end)
        {
            int mid = start + (end-start)/2;
            if(target > nums[mid])
            {
                start = mid+1;
            }
            else if(target < nums[mid])
            {
                end = mid-1;
            }
            else if(target == nums[mid])
            {
                end = mid-1;
            }
        }
        if(start > mid-1 or nums[start]!=target)
            return -1;
        return start;
    }
    int findLast(vector<int>& nums, int mid)
    {
        int start = mid+1, end = nums.size()-1, res = -1;
        int target = nums[mid];
        while(start <= end)
        {
            int mid = start + (end-start)/2;
            if(target > nums[mid])
            {
                start = mid+1;
            }
            else if(target < nums[mid])
            {
                end = mid-1;
            }
            else if(target == nums[mid])
            {
                start = mid+1;
            }
        }
        if(end < 0 or nums[end]!=target)
            return -1;
        return end;
    }
};


```
