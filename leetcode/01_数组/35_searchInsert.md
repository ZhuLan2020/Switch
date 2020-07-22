# 35. Search Insert Position, Easy
> Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
> 
> You may assume no duplicates in the array.
> 
> Example 1:
> 
> Input: [1,3,5,6], 5
> 
> Output: 2

> Example 2:
> 
> Input: [1,3,5,6], 2
> 
> Output: 1

> Example 3:
> 
> Input: [1,3,5,6], 7
> 
> Output: 4

> Example 4:
> 
> Input: [1,3,5,6], 0
> 
> Output: 0

## 解法: 二分法的又一种变体
- 与普通二分法相比, 多了一种可能找不到的情况
- 此时, 原来是返回-1, 现在是要返回这个值插入的位置, 也就是**第一个比这个值大的值原来的位置**
- 实际上这个位置, 就是start指针的最后位置
- 最后跳出while循环时, start指针在end右边一位, 此时指向的就是这个值的位置, 具体的, 可通过演算排演得到
``` cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if(nums.empty())
        {
            return 0;
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
        // 唯一的变化在这里
        // 如果没有找到, 就返回start指针的索引,就是这个第一个比目标值大的值的索引
        return (res == -1) ? start:res;
    }
};

```
## 简洁解法: 使用STL
- lower_bound(), 返回大于或等于val的第一个元素位置
- 其实底层代码也是用二分查找实现的, 因此仅仅适用于有序数列
``` cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    }
};
```

## 遗留
- STL中二分查找三兄弟: 待学习
	- lower_bound()
	- upper_bound()
	- binary_search())
