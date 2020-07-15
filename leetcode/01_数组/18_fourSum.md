# 18_四数之和, Medium
> 给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 
> 的值与 target 相等？找出所有满足条件且不重复的四元组。

> 注意：
>
> 答案中不可以包含重复的四元组。

> 示例：
> 
> 给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。
> 
> 满足要求的四元组集合为：
>
> [
  >[-1,  0, 0, 1],
  >[-2, -1, 1, 2],
 > [-2,  0, 0, 2]
> ]
## 解法: 同样是排序+双指针
- 与三数之和的解法几乎相同, 只是在最外面再加一层循环
- 稍微需要注意的是, 在判重时, 前两个指针的不同
- 暴力解法是四重循环, 就是 O(n4)
- 这种方法就是O(nlogn) + O(n)*O(n)*O(n), 也就是 O(n3)

``` cpp

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end()); // 先做一步升序排序
        vector<vector<int>> res;
        if(nums.size() < 4)return res;
        for (int i = 0; i < nums.size()-3; i++)
        {
            if(i > 0 and nums[i]==nums[i-1]) // 跳过i的重复, 直接i指针右移
            {
                continue;
            }
            for(int j = i+1; j < nums.size()-2; j++)
            {
                if(j > i+1 and nums[j]==nums[j-1]) // 跳过j的重复, 直接j指针右移, 注意这里是 j > i+1, 而不是 j > 1
                {
                    continue;
                }
                int m = j + 1; // m, 左指针
                int n = nums.size() - 1; // n, 右指针
                while( m < n)
                {
                    int sum = nums[i] + nums[j] + nums[m] + nums[n];
                    // 大于或者小于两种情况没有考虑避开重复值,因为即是重复了也就是多比较一次而已, 不会在结果中输出,这里就没有处理.
                    // 只有在相等时,才会去判断是否重复
                    if(sum > target) n--;
                    else if(sum < target) m++;
                    else
                    {
                        res.push_back({nums[i], nums[j], nums[m], nums[n]});
                        n--;
                        m++;
                        while( m < n and nums[n] == nums[n+1]) n--;
                        while( m < n and nums[m] == nums[m-1]) m++;
                    } 
                }
            }
        }
        return res;
    }
};
```
