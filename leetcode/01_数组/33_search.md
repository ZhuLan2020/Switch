# 33. Search in Rotated Sorted Array, Medium
> Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
>
> (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

> You are given a target value to search. If found in the array return its index, otherwise return -1.
> 
> You may assume no duplicate exists in the array.
> 
> Your algorithm's runtime complexity must be in the order of O(log n).

> Example 1:
> 
> Input: nums = [4,5,6,7,0,1,2], target = 0
> 
> Output: 4
 
> Example 2:
> 
> Input: nums = [4,5,6,7,0,1,2], target = 3
> 
> Output: -1

## 解法1: 先找出target位置, 再二分查找
- 这是一种比较顺的思路
- 考虑到这个升序数组一定会分成两段, 先找出分界点的位置(判断条件: nums[n-1] > nums[n], 前一个值大于后一个值)
- 通过比较target与这两段数组的最小值(即第一个值), 可以确定target在哪一段
- 对这段数组进行二分查找, 寻找target, 找到了就好, 找不到说明不存在

``` cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() == 0)
        {
            return -1;
        }
        // 1. 确定目标值在前半段还是后半段, 然后更新[start, end]区间
        // 2. 在一段升序数组中使用二分法查找目标值
        int start = 0, end = nums.size()-1;
        if(target == nums[0])
        {
            return 0;
        }
        else if(target < nums[0]) // 目标值在后半段
        {
            for(size_t i = 1; i < nums.size(); i++)
            {
                if(!(target < nums[i])) // 找出分界点
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
                if(nums[0] > nums[i])// 找出分界点
                {
                    end = i-1;
                    break;
                }
            }
        }
        int res = -1; // 默认结果
        // 在一段升序数组中使用二分法查找目标值
        // 以下为二分法的典型写法, 需要熟练使用
        while(start <= end)
        {
            size_t mid = (start+end)/2;
            if(target == nums[mid])
            {
                res = mid;
                break;
            }
            else if(target > nums[mid])
            {
                start++;
            }
            else
            {
                end--;
            }
        }
        return res;
    }
};
```
- 极端情况下, 例如没有分界点, 完整的升序数组, O(n) = O(n) + O(logn) = O(n), 遍历+二分, 不满足题目O(logn) 的要求
- 解法2进行改进

## 解法2: 直接开始二分查找

``` cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() == 0)
        {
            return -1;
        }
        if(target == nums[0])
        {
            return 0;
        }

	// 不管分界点的位置, 直接整个数组开始二分查找
        int start = 0, end = nums.size()-1, res = -1;
        while(start <= end)
        {
            int mid = (start + end)/2;
            // 总共有这么几种情况:
            // 1.target == nums[mid], 找到了, 直接返回索引
            // 2.如果mid左侧有序(右侧有混乱)
            //    2.1 如果target在这段有序中, end位置左移
            //    2.2 如果target不在这段有序中, start位置右移
            // 3.如果mid右侧有序(左侧有混乱)
            //    3.1 如果target在这段有序中, start位置右移
            //    3.2 如果target在这段有序中, end位置左移
            // 直到最后start与end指向同一个位置, 结束
            if(nums[mid] == target)
            {
                res = mid;
                break;
            }
            // 判断是否在有序段中比较简单, 直接可以取最大值(最后那个)和最小值(最前面那个), 来比较, 不满足就是在无序段
            if(nums[start] <= nums[mid]) // 说明左侧是有序的
            {
                // 前面已经判断了nums[mid] == target, 所以这里取小于就行了
                if(nums[start] <= target and target < nums[mid]) // 如果target在这段有序段中
                {
                    end = mid-1;
                }
                else // 如果target在右侧无序段中
                {
                    start = mid+1;
                }
            }
            else // 如果右边是有序的(因为只有一个转折点, 所以左侧和右侧一定是有一段是有序的)
            {
                // 前面已经判断了nums[mid] == target, 所以这里取大于就行了
                if(nums[mid] < target and target <= nums[end]) // 如果target在这段有序段中
                {
                    start = mid+1;
                }
                else
                {
                    end = mid-1;
                }
            }
        }
        return res;
    }
};
```
- 由于一开始就使用二分查找, 没有去找分界点, 因此O(n) = O(logn)
- 主要是理清楚几种不同情况下, 怎么处理
