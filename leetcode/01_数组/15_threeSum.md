# 15_三数之和, Medium

> 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。
>
> 注意：答案中不可以包含重复的三元组。

> 示例：
>
> 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
>
> 满足要求的三元组集合为：
> [
>   [-1, 0, 1],
>   [-1, -1, 2]
>   ]


## 解法: 先排序, 再双指针
- 如果直接三重for循环, 就会是O(n3)
- 先做一步排序, 然后遍历第一个值
	- 为什么要排序? 为了避免重复, 人为强制最后输出的[a, b, c]中, a <= b <= c
- 同时遍历第2个值与第3个值, 一个从前往后, 一个从后往前, 直至两个指针碰面
``` cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        // 假设nums长度必定大于3
        sort(nums.begin(), nums.end()); // 先做一步升序排序
        for (int i = 0; i < nums.size(); i++)
        {
            if(nums[i] > 0) // 最小值已经大于0, 那么三数之和不可能等于0, 直接break
            {
                break;
            }
            if(i>0 and nums[i]==nums[i-1]) // 跳过i的重复, 直接i指针右移
            {
                continue;
            }
            int j = i+1; // j, 左指针
            int k = nums.size() - 1; // k, 右指针
            while(j < k) // 左指针和右指针同时移动, 直至两者重合
            {
                int sum = nums[i] + nums[j] + nums[k];
                if(sum > 0) k--; // 值太大,减小最大值,即左指针左移
                else if(sum < 0) j++; // 值太小,增大最小值,即右指针右移
                else // == 0
                {
                    res.push_back( {nums[i], nums[j], nums[k]} );
                    k--;
                    j++;
                    while( j < k and nums[k+1] == nums[k]) k--; // 跳过k的重复
                    while( j < k and nums[j-1] == nums[j]) j++; // 跳过j的重复
                }
            }
        }
        return res;
    }
};
```
- 时间复杂度
	- 排序, O(nlogn)
	- i的一轮遍历,  O(n)
	- 双指针遍历, O(n)
	- 最终的时间复杂度为: O(nlogn) + O(n)*O(n), 由于O(n2) 要比O(nlogn) 复杂, 因此最终的复杂度为O(n2)
- 空间复杂度: O(1)  
