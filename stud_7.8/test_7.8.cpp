#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        // 如果数组为空或者只有一个元素，则没有符合条件的一对数
        if (numbers.empty() || numbers.size() < 2) {
            return {}; // 返回空的向量
        }

        int left = 0; // 左指针从数组的开始位置
        int right = numbers.size() - 1; // 右指针从数组的末尾位置
        vector<int> result; // 用于存储结果的一对数的索引

        // 当左指针小于右指针时继续循环
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                result.push_back(left + 1); // 将左指针的索引添加到结果向量，+1因为题目要求下标从1开始
                result.push_back(right + 1); // 将右指针的索引添加到结果向量，+1因为题目要求下标从1开始
                break; // 找到结果后跳出循环
            }
            else if (sum < target) {
                left++; // 如果和小于目标值，移动左指针
            }
            else {
                right--; // 如果和大于目标值，移动右指针
            }
        }

        return result; // 返回结果向量
    }
};

class Solution2 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 使用 unordered_map 来存储数组元素和对应的索引
        unordered_map<int, int> indices;
        // 遍历数组
        for (int i = 0; i < nums.size(); ++i) {
            // 检查是否存在一个数使得两数之和等于 target
            if (indices.count(target - nums[i])) {
                // 如果找到，则返回当前索引和之前存储的索引
                return { indices[target - nums[i]], i };
            }
            // 将当前元素和索引存入哈希表
            indices[nums[i]] = i;
        }
        // 如果没有找到合适的解，返回空向量
        return {};
    }
};

void test_1()
{
    Solution2 solution;
    std::vector<int> nums = { 2, 7, 11, 15 };
    int target = 9;
    std::vector<int> result = solution.twoSum(nums, target);
    if (!result.empty()) {
        std::cout << "Indices are: [";
        for (int i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            if (i < result.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
    else {
        std::cout << "No solution found!" << std::endl;
    }
}

class Solution3 {
public:

    // 使用双指针法解决三数之和问题
    vector<vector<int>> threeSum(vector<int>& nums) {
        // 对数组进行排序，这是实现双指针的前提条件
        sort(nums.begin(), nums.end());

        vector<vector<int>> res;  // 存储所有满足条件的三元组
        int n = nums.size();  // 数组长度

        // 遍历数组，固定第一个数 nums[i]
        for (int i = 0; i < n - 2; ++i) {
            // 去重：跳过重复的第一个数，确保结果中不会有重复的三元组
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // 剪枝1：如果固定数 nums[i] 后面的两个数的最小和都大于 nums[i]，那么后续的数就不用再考虑了，因为它们的和一定会大于 0
            if (nums[i + 1] + nums[i + 2] > -nums[i]) break;

            // 剪枝2：如果固定数 nums[i] 前面的两个数的最大和都小于 nums[i]，那么当前的数就不用再考虑了，因为它们的和一定会小于 0
            if (nums[n - 1] + nums[n - 2] < -nums[i]) continue;

            // 初始化双指针，l 指向固定数 nums[i] 的下一个数，r 指向数组的最后一个数
            int l = i + 1;
            int r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum == 0) {
                    // 找到了一个和为 0 的三元组，将其添加到结果集中
                    res.push_back({ nums[i], nums[l], nums[r] });

                    // 去重：跳过重复的第二个数，确保结果中不会有重复的三元组
                    l++;
                    while (l < r && nums[l] == nums[l - 1]) l++;

                    // 去重：跳过重复的第三个数，确保结果中不会有重复的三元组
                    r--;
                    while (l < r && nums[r] == nums[r + 1]) r--;
                }
                else if (sum < 0) {
                    // 如果三数之和小于 0，需要增加第二个数，因为数组已经排序，所以可以 l++
                    l++;
                }
                else {
                    // 如果三数之和大于 0，需要减少第三个数，因为数组已经排序，所以可以 r--
                    r--;
                }
            }
        }

        return res;
    }
};

class Solution4 {
public:
    int findDuplicate(vector<int>& nums) {
        // 初始化快指针和慢指针，它们都从数组的第一个元素开始
        int fast = 0;
        int slow = 0;

        // 第一步，寻找环中的一个点
        // 使用快指针和慢指针的方法，快指针每次走两步，慢指针每次走一步
        do {
            fast = nums[nums[fast]]; // 快指针先走两步，再取它的值作为下一个索引
            slow = nums[slow];       // 慢指针走一步
        } while (fast != slow); // 如果快指针等于慢指针，说明找到了环中的一个点

        // 初始化另一个指针，从数组的第一个元素开始
        int finder = 0;

        // 第二步，寻找环的入口点
        // 这个指针和慢指针同时从数组的起点出发，但速度相同
        // 当它们相遇时，就是环的入口点
        while (finder != slow) {
            finder = nums[finder]; // 这个指针走一步
            slow = nums[slow];     // 慢指针继续走，保持和finder相同的速度
        }

        // 返回环的入口点，即数组中重复的元素
        return finder;
    }
};
int main() 
{
    test_1();

    return 0;
}