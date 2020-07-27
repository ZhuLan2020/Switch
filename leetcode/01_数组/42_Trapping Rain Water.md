``` cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int sum = 0;
        int len = height.size()-1;
        // 不能在for循环条件中写成i<height.size()-1
        // 因为size()返回类型为非负的size_t,若数组为空，再减1就会变成一个很大的数，不该进循环而进循环了
        for(int i=1; i<len; i++)
        {
            int maxLeft = 0, maxRight = 0;
            for(int j=i-1; j>=0; j--)
            {   
                if(height[j] > maxLeft)
                    maxLeft = height[j];
            }
            for(int j=i+1; j<height.size(); j++)
            {
                if(height[j] > maxRight)
                    maxRight = height[j];
            }

            if(height[i] < maxRight and height[i] < maxLeft)
            {
                sum += min(maxRight, maxLeft) - height[i];
            }
        }
        return sum;
    }
};
```

``` cpp

class Solution {
public:
    int trap(vector<int>& height) {
        int sum = 0;
        int len = height.size()-1;
        vector<int> maxLeft  (height.size());
        vector<int> maxRight (height.size());
        // 不能在for循环条件中写成i<height.size()-1
        // 因为size()返回类型为非负的size_t,若数组为空，再减1就会变成一个很大的数，不该进循环而进循环了
        for(int i=1; i<len; i++)
        {
            maxLeft[i] = max(maxLeft[i-1], height[i-1]);
        }
        for(int i=len-1; i>=0; i--)
        {
            maxRight[i] = max(maxRight[i+1], height[i+1]);
        }

        for(int i=1; i<len; i++)
        {
            if(height[i] < maxRight[i] and height[i] < maxLeft[i])
            {
                sum += min(maxRight[i], maxLeft[i]) - height[i];
            }
        }
        return sum;
    }
};
```
