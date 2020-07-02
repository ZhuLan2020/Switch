# 1_twoSum，简单

> 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
>
> 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

> 示例:
>
> 给定 nums = [2, 7, 11, 15], target = 9
>
> 因为 nums[0] + nums[1] = 2 + 7 = 9
>
> 所以返回 [0, 1]
>
> 需要注意：nums = [3, 3], target = 6，返回 [0, 1]

``` cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map < int, int > temp;
        for(int i = 0; i < nums.size(); i++)
        {
            int result = target - nums.at(i);
             // 判断目标值有没有已经在temp中
             // 如果有，直接输出索引
             // 如果没有，把当前值insert入temp中
            if( temp.find(result) != temp.end() )
            {         
                return { temp.find(result) -> second, i };
            }
            temp.insert( make_pair( nums.at(i), i ) ); 
        }
        return {};
    }
};
```
## 解法1：暴力解法，两重循环
``` cpp
for(int i = 0; i < nums.size(); i++)
{
    for(int j = i+1; j < nums.size(); j++)
    {
        if( nums.at(i) + nums.at(j) == target)
        {
            return { i,j };
        }
    }
}
return {};
```
1. O(N2)，1500ms, 7M
2. 耗时过长

## 解法2：Hash表

### 2.1 两轮循环
比较顺的想法应该是这样：
- 第一轮循环，把所有nums中的值放入map中
- 然后再一轮循环，使用temp.find(result)，寻找目标值
``` cpp
std::unordered_map < int, int > temp;
for(int i = 0; i < nums.size(); i++)
{
    temp.insert( make_pair( nums.at(i), i ) ); 
}
for(int i = 0; i < nums.size(); i++)
{
	int result = target - nums.at(i);
    if( temp.find(result) != temp.end() )
    {         
        return { i, temp.find(result) -> second };
    }
}
```
有两个问题：
1. 时间复杂度为 O(2N)，运行时间为20～24 ms
2. 对于[3,3] 6，这个测试用例，正确输出为[0,1]，实际输出为[1,0] ，主要是因为有重复值，而find方法输出的是第一个值
3. 内存消耗8.5M

### 2.2 一轮循环
- 先把前面的值insert进map，实际是使用了后面的值来判断
- 判断时部分值在map里，部分在外面，避免了[3,3] 6这种值重复问题
	- 所以输出时 i 在后面
``` cpp
std::map < int, int > temp;
for(int i = 0; i < nums.size(); i++)
{
    int result = target - nums.at(i);
     // 判断目标值有没有已经在temp中
     // 如果有，直接输出索引
     // 如果没有，把当前值insert入temp中
    if( temp.find(result) != temp.end() )
    {         
        return { temp.find(result) -> second, i };
    }
    temp.insert( make_pair( nums.at(i), i ) ); 
}
```
1. 时间复杂度为 O(N)，运行时间为12～20 ms，比两轮循环有所提升
2. 内存消耗与两轮相同，8.5M
### 2.3 把map改成unordered_map
- 由于是顺序无关
``` cpp
std::unordered_map < int, int > temp;
... ...
```
1. 时间复杂度为 O(N)，运行时间继续缩短至8～12 ms
2. 内存消耗不变

## 小结
实际上暴力解法和Hash表解法都是两重循环，区别在于vector的遍历寻找是 O(N)，而Hash表的是O(1)，所以引入Hash表能显著降低时间复杂度
