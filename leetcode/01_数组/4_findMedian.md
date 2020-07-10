# 4. 寻找两个正序数组的中位数,困难

	给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。
	请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
	你可以假设 nums1 和 nums2 不会同时为空。

> 示例 1:
> nums1 = [1, 3]
> nums2 = [2]
> 则中位数是 2.0

> 示例 2:
> nums1 = [1, 2]
> nums2 = [3, 4]
> 则中位数是 (2 + 3)/2 = 2.5


## 解
- 归根结底,这个问题根据不同角度, 可以分解成两种小问题来解决
1. **寻找数组中第k个最小值**
2. **寻找拆分数组的合适位置**

## 解法1 寻找数组中第k个最小值
这个思路, 把原问题拆解成**寻找数组中第k个最小值**问题
- 偶数个时, 中位数 = (第k个最小值 + 第k+1个最小值) / 2, 其中 k= n/2
- 奇数个时, 中位数 = 第k个最小值, 其中 k = n/2 + 1
	- 皆为向下整除

### 解法1.1 一般通用法: 直接一个一个遍历
- 很直观, 就是直接找两个数组中中间小的那个值, 从第一个值开始,一个一个往后遍历,每一次排除一位
- 时间复杂度: O ( (m+n)/2 ), 也就是O(m+n)
- 空间复杂度: O(1), 无论是多长的数组, 都只用这几个局部变量
``` cpp
class Solution {
public:
    int findKthLittleNum(const vector<int>& nums1, const vector<int>& nums2, int k)
    {
        int m = nums1.size();
        int n = nums2.size();
        int aIndex = 0;
        int bIndex = 0;

        while(true)
        {
            if(aIndex == m) // nums1已经遍历完,剩下的直接在nums2中找就行
            {
                return nums2[bIndex + k-1];
            }
            else if(bIndex == n) // nums2已经遍历完,剩下的直接在nums1中找就行
            {
                return nums1[aIndex + k-1];
            }
            else if(k == 1) // 下一个最小的数,只要比较当前两个数组第一个值哪一个小就行了
            {
                return min(nums1[aIndex], nums2[bIndex]);
            }
            else // 一般情况
            {
                 // 从当前位置(aIndex或bIndex)往后移k/2,这里有一个减1,是因为下面的aIndex或bIndex已经加1了,即已经向后移了一位
                 // 此时,再向后移1位,实际上的索引就是 aIndex + 1-1
                 // 同理,再向后移动k/2位,实际上的索引就是 aIndex + k/2-1
                int newAIndex = min(aIndex + 1 - 1, m-1); // 判断会不会数组越界
                int newBIndex = min(bIndex + 1 - 1, n-1);

                if(nums1[newAIndex] <= nums2[newBIndex]) // nums1[newAIndex]小,排除nums1中k/2个值,并移动aIndex这个指针
                {
                    k = k-(newAIndex - aIndex + 1);// 当没有越界时,这句等价与 k = k-k/2,因为newAIndex = aIndex + k/2-1
                    //k = k-k/2;
                    aIndex = newAIndex + 1;
                }
                else // nums2[newAIndex]小,排除nums2中的值,并移动bIndex这个指针
                {
                    k = k-(newBIndex - bIndex + 1);// 当没有越界时,这句等价与 k = k-k/2,,因为newBIndex = bIndex + k/2-1
                    //k = k-k/2;
                    bIndex = newBIndex + 1;
                }
            }
        }
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();
        if(totalLength % 2 == 1)
        {
            return findKthLittleNum(nums1, nums2, totalLength/2+1);
        }
        else
        {
            return (findKthLittleNum(nums1, nums2, totalLength/2) + findKthLittleNum(nums1, nums2, totalLength/2+1)) / 2.0;
        }

    }
};

```
### 解法1.2 二分法: 一半一半遍历
- 一般来说, 看到带了==**log**==的时间复杂度, 应该马上联想到==**二分法**==
- 尤其是对于这种==**有序排列**==的数组, 也应该马上想到==**二分法**==
- 与解法一的异同:
	- 同: 都是从前往后遍历
	- 异: 每一次不是向后移1位然后排除1位, 而是每一次向后移 k/2位(找的是第k小的值),每一次排除k/2位
	- 相当于一个一个比的一种一般`抽象`情况
- O ( log(m+n) )
- O (1)
``` cpp
class Solution {
public:
    int findKthLittleNum(const vector<int>& nums1, const vector<int>& nums2, int k)
    {
        int m = nums1.size();
        int n = nums2.size();
        int aIndex = 0;
        int bIndex = 0;

        while(true)
        {
            if(aIndex == m) // nums1已经遍历完,剩下的直接在nums2中找就行
            {
                return nums2[bIndex + k-1];
            }
            else if(bIndex == n) // nums2已经遍历完,剩下的直接在nums1中找就行
            {
                return nums1[aIndex + k-1];
            }
            else if(k == 1) // 下一个最小的数,只要比较当前两个数组第一个值哪一个小就行了
            {
                return min(nums1[aIndex], nums2[bIndex]);
            }
            else // 一般情况
            {
                 // 从当前位置(aIndex或bIndex)往后移k/2,这里有一个减1,是因为下面的aIndex或bIndex已经加1了,即已经向后移了一位
                 // 此时,再向后移1位,实际上的索引就是 aIndex + 1-1
                 // 同理,再向后移动k/2位,实际上的索引就是 aIndex + k/2-1
                int newAIndex = min(aIndex + k/2-1, m-1); // 判断会不会数组越界
                int newBIndex = min(bIndex + k/2-1, n-1);

                if(nums1[newAIndex] <= nums2[newBIndex]) // nums1[newAIndex]小,排除nums1中k/2个值,并移动aIndex这个指针
                {
                    k = k-(newAIndex - aIndex + 1);// 当没有越界时,这句等价与 k = k-k/2,因为newAIndex = aIndex + k/2-1
                    //k = k-k/2;
                    aIndex = newAIndex + 1;
                }
                else // nums2[newAIndex]小,排除nums2中的值,并移动bIndex这个指针
                {
                    k = k-(newBIndex - bIndex + 1);// 当没有越界时,这句等价与 k = k-k/2,,因为newBIndex = bIndex + k/2-1
                    //k = k-k/2;
                    bIndex = newBIndex + 1;
                }
            }
        }
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();
        if(totalLength % 2 == 1)
        {
            return findKthLittleNum(nums1, nums2, totalLength/2+1);
        }
        else
        {
            return (findKthLittleNum(nums1, nums2, totalLength/2) + findKthLittleNum(nums1, nums2, totalLength/2+1)) / 2.0;
        }

    }
};
```
- 解法1与解法2的唯一区别在于,每次是向后移一位,还是移k/2位
- 由于是有序数列,所以可以使用二分法,直接向后移k/2来比较
- 如果是无序数列,那就只能按照解法1,一个一个比过来了

## 解法3
- 根据数学中中位数的定义,可以把数组分成左右两部分
``` cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        int m = nums1.size();
        int n = nums2.size();
        if(m > n)
        {
            return (findMedianSortedArrays(nums2, nums1));
        }
        int left = 0, right = m;
        int aMax = 0, bMin = 0;

        while(left <= right)
        {
            int i = (left + right)/2;
            int j = (m + n + 1)/2 - i;

            int mim1 = (i == 0 ? INT_MIN : nums1[i-1]);
            int mi   = (i == m ? INT_MAX : nums1[i]);
            int mjm1 = (j == 0 ? INT_MIN : nums2[j-1]);
            int mj   = (j == n ? INT_MAX : nums2[j]);

            if(mim1 <= mj)
            {
                aMax = max(mim1, mjm1);
                bMin = min(mi, mj);
                left = i+1;
            }
            else
            {
                right = i-1;
            }
        }

        if((m+n)%2 == 0)
        {
            return (aMax+bMin)/2.0;
        }
        else
        {
            return aMax;
        }
    }
};
```
