# 41. First Missing Positive

> Given an unsorted integer array, find the smallest missing positive integer.
>
> Example 1:
> 
> Input: [1,2,0]
> 
>Output: 3

>Example 2:
>
>Input: [3,4,-1,1]
>
>Output: 2

>Example 3:
>
>Input: [7,8,9,11,12]
>
>Output: 1

>Note:
>
>Your algorithm should run in O(n) time and uses constant extra space.

## 解法1: 标记法
- 按照要求, 时间复杂度必须是O(n), 空间复杂度为O(1)
- 算法思路如下:
	1. 遍历, 把所有非正值原地改为n+1(超过n的值不用管, 输出一定是小于等于n的)
	2. 遍历, 

``` cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if(nums.empty())
        {
            return 1;
        }
        // 1. 把所有小于等于0的数原地改成n+1
        // 2. 遍历每一个小于n+1的数, 把nums中对应位置的数标记为负数(比如找到一个3, 就把nums[3-1]也就是nums[2]给标记成负数, 原来的值取负)
        // 3. 遍历整个数组, 找到第一个正整数, 其所在索引为k, 那么这个缺失值就是 k+1
        // 4. 默认缺失值为 n+1
        int n = nums.size();
        int res = n+1;// 默认缺失值

        for(auto &num:nums)
        {
            if(num <= 0)
            {
                num = n+1;
            }
        }
        for(int i = 0; i < n; i++)
        {
            // 注意这里可能出现负数,导致越界
            // 因为前面的值如果找到,可能会把后面的值改为负数,所以需要取绝对值,避免nums[i]是一个负数
            int temp = abs(nums[i]);
            if(temp < n+1)
            {
                nums[temp-1] = -abs(nums[temp-1]);
            }
        }
        for(int i=0; i < n; i++)
        {
            if(nums[i] > 0)
            {
                res = i+1;
                break;
            }
        }
        return res;
    }
};
```

## 解法2: 交换法

``` cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if(nums.empty())
        {
            return 1;
        }
        // 1.把当前值交换到对应索引的正确位置, 使用while循环对着当前位置持续交换至不能换为止
        // 2.遍历,找到第一个不在正确位置的值
        int n = nums.size();
        int res = n+1;// 默认缺失值

        for(int i=0; i<n; i++)
        {
            // while停止条件
            // 1. 当前值不在范围内[1,n]; 
            // 2. 当前值与待交换值相等(此时交换会陷入死循环)
            while(nums[i] > 0 and nums[i] < n+1 and nums[nums[i]-1] != nums[i]!)
            {
                swap(nums[i], nums[nums[i]-1]);
            }
        }
        
        for(int i=0; i < n; i++)
        {
            // 找到第一个不在正确位置的值
            if(nums[i]!=i+1)
            {
                res = i+1;
                break;
            }
        }
        return res;
    }
};


```
