# 16_最接近的三数之和, Medium
> 给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。
>
> 假定每组输入只存在唯一答案。

> 示例：
>
> 输入：nums = [-1,2,1,-4], target = 1
> 
> 输出：2
> 
> 解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。


## 解法: 排序+双指针
- 与15题非常相似, 同样的, 如果暴力解, 就是三重for循环
- 这里同样是先排序, 然后用i遍历 + 双指针遍历
- O(n2), 同样是O(ologn) + O(n2) = O(n2) 

``` cpp
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end()); // 先做一步升序排序
        int res = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < nums.size(); i++)
        {
            if(i>0 and nums[i]==nums[i-1]) // 跳过i的重复, 直接i指针右移
            {
                continue;
            }
            int j = i+1; // j, 左指针
            int k = nums.size() - 1; // k, 右指针
            while(j < k) // 左指针和右指针同时移动, 直至两者重合
            {
                int sum = nums[i] + nums[j] + nums[k];
                res  = abs(sum - target) < abs(res - target) ? sum:res; // 取较小值
                if(sum > target) 
                {
                    k--; // 值太大,减小最大值,即左指针左移
                    while(j < k and nums[k+1]==nums[k]) k--; // 跳过k的重复, 直接左移
                }
                else if(sum < target) 
                {
                    j++; // 值太小,增大最小值,即右指针右移
                    while(j < k and nums[j-1]==nums[j]) j++;// 跳过j的重复, 直接右移
                }
                else
                {
                    return target; // 已经找到相等值了, 直接返回
                }
            }
        }
        return res;
    }
};
```
