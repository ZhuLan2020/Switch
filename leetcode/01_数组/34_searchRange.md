# 34.Find First and Last Position of Element in Sorted Array

> Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
>
> Your algorithm's runtime complexity must be in the order of O(log n).
>
> If the target is not found in the array, return [-1, -1].
>
> Example 1:
>
> Input: nums = [5,7,7,8,8,10], target = 8
>
> Output: [3,4]
>
> Example 2:
>
> Input: nums = [5,7,7,8,8,10], target = 6
>
> Output: [-1,-1]

## 解法：向左寻找 + 向右寻找

- 实际上用到了二分查找目标值的变体
- 一般的二分查找，找到目标值后就直接return了，如下：

``` cpp
// 正常版本的二分查找
int start = 0, end = nums.size()-1, res = -1;
while(start <= end)
{
    int mid = start + (end-start)/2;
    if(target == nums[gid])
    {
        res = mid;
        return res;
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
```

- 而这里，实际上需要做两个方法
  - 找到最左边的目标值
  - 找到最右边的目标值
  - 都是在二分查找上做的变体

### 向左寻找：找到最左边的目标值

``` cpp
int findFirst(vector<int>& nums, int target)
{
    int start = 0, end = nums.size()-1, res = -1;
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
            // 左边还有值 并且 左边第一个值仍然是目标值。此时仍然需要继续查找
            if(mid > 0 and nums[mid]==nums[mid-1]) 
            {
                // 注意这里的变化，即使找到了一个目标值也不退出，继续把范围缩小为[start, mid-1]继续查找，（因为[mid]已经找过了）
            	// 不断收拢右边界，往左找
                end = mid-1;
            } 
            else 
            {
                // 已经是第一个值了，或者左边第一个值不是目标值了，就可以停下了（因为是严格升序数列）
                res = mid;
                break;
            }
        }
    }
    
    return res;
}
```

### 向右寻找：找到最右边的目标值

``` cpp
int findLast(vector<int>& nums, int target)
{
    int start = 0, end = nums.size()-1, res = -1;
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
            // 右边还有值 并且 右边第一个值仍然是目标值。此时仍然需要继续查找
            if(mid < nums.size()-1 and nums[mid]==nums[mid+1]) 
            {
                // 同样是这里变了，即使找到了一个目标值也不退出，继续把范围缩小为[mid+1, end]继续查找（因为[mid]已经找过了）
            	// 不断收拢左边界，往右找
                start = mid+1;
            } 
            else 
            {
                res = mid;
                break;
            }
        }
    }
    return res;
}
```

可以发现，两种方向的方法只有在找到第一个目标值后，边界的收缩方向不同

- 向左寻找时，收拢右边界
- 向右寻找时，收拢左边界

``` cpp
// 左边还有值 并且 左边第一个值仍然是目标值。此时仍然需要继续查找
if(mid > 0 and nums[mid]==nums[mid-1]) 
{
    // 不断收拢右边界，往左找
    end = mid-1;
} 
else 
{
    res = mid;
    break;
}
*****************************************************************
// 右边还有值 并且 右边第一个值仍然是目标值。此时仍然需要继续查找
if(mid < nums.size()-1 and nums[mid]==nums[mid+1]) 
{
    // 不断收拢左边界，往右找
    start = mid+1;
} 
else 
{
    res = mid;
    break;
}
```

## 最终解法

其实就是向左寻找+向右寻找的组合而已：

``` cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty())
        {
            return {-1,-1};
        }

        int first = (findFirst(nums, target) == -1)? -1:findFirst(nums, target);
        int last =  (findLast(nums, target) == -1) ? -1:findLast (nums, target);

        return {first, last};
    }

    int findFirst(vector<int>& nums, int target)
    {
        int start = 0, end = nums.size()-1, res = -1;
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
                if(mid > 0 and nums[mid]==nums[mid-1]) 
                {
                    end = mid-1;
                } 
                else 
                {
                    res = mid;
                    break;
                }
            }
        }
        return res;
    }
    
    int findLast(vector<int>& nums, int target)
    {
        int start = 0, end = nums.size()-1, res = -1;
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
                if(mid < nums.size()-1 and nums[mid]==nums[mid+1]) 
                {
                    start = mid+1;
                } 
                else 
                {
                    res = mid;
                    break;
                }
            }
        }
        return res;
    }
};
```

