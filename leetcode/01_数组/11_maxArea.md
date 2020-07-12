# 11. 盛最多水的容器, Medium

> 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

> 说明：你不能倾斜容器，且 n 的值至少为 2。

 ![alt](https://aliyun-lc-upload.oss-cn-hangzhou.aliyuncs.com/aliyun-lc-upload/uploads/2018/07/25/question_11.jpg)

> 图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。

## 解法1：暴力两重for循环



## 解法2：双指针

- 对于一个数组[a~1~, a~2~, a~3~, ... ... a~i~]，长度为i，那么a1和ai组成的容器面积为min(a1, ai) * i
- 第二次移动指针时，必然需要移动的是这两个值中小的那个值的指针
  - 因为目标是要找到最大值
  - 如果小的不动，而去移动较大的值，那这个面积一定是越来越小的
    - 假设[x, y]，且x < y，y - x = i
    - 指向x的指针不变，指向y的指针--，此时变为[x, y']，且y' - x = j，显然 i = j + 1
       	1. 若 y < y'，则 **min(x, y) = x = min(x, y')**，而**j < i**，所以面积减小
       	2. 若 y >= y' 
           - 当 y' > x，与情况1相同， **min(x, y) = x = min(x, y')**
           - 当 y' < x，则 **min(x, y) = x > min(x, y')**，显然面积也是减小的
- 每一次移动一个指针，相当于形成了一个新的数组，继续重复以上步骤，即可比较出最大值
- 时间：O(n-1)，即为O(n)
- 空间：O(1)

``` cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size()-1;
        int length = right - left;
        int vol = min(height.at(left), height.at(right)) * length;

        while(right-left > 1){
            height.at(left) < height.at(right) ? left++ : right--;
            length = right - left;
            int temp = min(height.at(left), height.at(right)) * length;
            vol = max(temp, vol);
        }
        return vol;
    }
};
```

