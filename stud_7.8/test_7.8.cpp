#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        // �������Ϊ�ջ���ֻ��һ��Ԫ�أ���û�з���������һ����
        if (numbers.empty() || numbers.size() < 2) {
            return {}; // ���ؿյ�����
        }

        int left = 0; // ��ָ�������Ŀ�ʼλ��
        int right = numbers.size() - 1; // ��ָ��������ĩβλ��
        vector<int> result; // ���ڴ洢�����һ����������

        // ����ָ��С����ָ��ʱ����ѭ��
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                result.push_back(left + 1); // ����ָ���������ӵ����������+1��Ϊ��ĿҪ���±��1��ʼ
                result.push_back(right + 1); // ����ָ���������ӵ����������+1��Ϊ��ĿҪ���±��1��ʼ
                break; // �ҵ����������ѭ��
            }
            else if (sum < target) {
                left++; // �����С��Ŀ��ֵ���ƶ���ָ��
            }
            else {
                right--; // ����ʹ���Ŀ��ֵ���ƶ���ָ��
            }
        }

        return result; // ���ؽ������
    }
};

class Solution2 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // ʹ�� unordered_map ���洢����Ԫ�غͶ�Ӧ������
        unordered_map<int, int> indices;
        // ��������
        for (int i = 0; i < nums.size(); ++i) {
            // ����Ƿ����һ����ʹ������֮�͵��� target
            if (indices.count(target - nums[i])) {
                // ����ҵ����򷵻ص�ǰ������֮ǰ�洢������
                return { indices[target - nums[i]], i };
            }
            // ����ǰԪ�غ����������ϣ��
            indices[nums[i]] = i;
        }
        // ���û���ҵ����ʵĽ⣬���ؿ�����
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

    // ʹ��˫ָ�뷨�������֮������
    vector<vector<int>> threeSum(vector<int>& nums) {
        // �����������������ʵ��˫ָ���ǰ������
        sort(nums.begin(), nums.end());

        vector<vector<int>> res;  // �洢����������������Ԫ��
        int n = nums.size();  // ���鳤��

        // �������飬�̶���һ���� nums[i]
        for (int i = 0; i < n - 2; ++i) {
            // ȥ�أ������ظ��ĵ�һ������ȷ������в������ظ�����Ԫ��
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // ��֦1������̶��� nums[i] ���������������С�Ͷ����� nums[i]����ô���������Ͳ����ٿ����ˣ���Ϊ���ǵĺ�һ������� 0
            if (nums[i + 1] + nums[i + 2] > -nums[i]) break;

            // ��֦2������̶��� nums[i] ǰ��������������Ͷ�С�� nums[i]����ô��ǰ�����Ͳ����ٿ����ˣ���Ϊ���ǵĺ�һ����С�� 0
            if (nums[n - 1] + nums[n - 2] < -nums[i]) continue;

            // ��ʼ��˫ָ�룬l ָ��̶��� nums[i] ����һ������r ָ����������һ����
            int l = i + 1;
            int r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum == 0) {
                    // �ҵ���һ����Ϊ 0 ����Ԫ�飬������ӵ��������
                    res.push_back({ nums[i], nums[l], nums[r] });

                    // ȥ�أ������ظ��ĵڶ�������ȷ������в������ظ�����Ԫ��
                    l++;
                    while (l < r && nums[l] == nums[l - 1]) l++;

                    // ȥ�أ������ظ��ĵ���������ȷ������в������ظ�����Ԫ��
                    r--;
                    while (l < r && nums[r] == nums[r + 1]) r--;
                }
                else if (sum < 0) {
                    // �������֮��С�� 0����Ҫ���ӵڶ���������Ϊ�����Ѿ��������Կ��� l++
                    l++;
                }
                else {
                    // �������֮�ʹ��� 0����Ҫ���ٵ�����������Ϊ�����Ѿ��������Կ��� r--
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
        // ��ʼ����ָ�����ָ�룬���Ƕ�������ĵ�һ��Ԫ�ؿ�ʼ
        int fast = 0;
        int slow = 0;

        // ��һ����Ѱ�һ��е�һ����
        // ʹ�ÿ�ָ�����ָ��ķ�������ָ��ÿ������������ָ��ÿ����һ��
        do {
            fast = nums[nums[fast]]; // ��ָ��������������ȡ����ֵ��Ϊ��һ������
            slow = nums[slow];       // ��ָ����һ��
        } while (fast != slow); // �����ָ�������ָ�룬˵���ҵ��˻��е�һ����

        // ��ʼ����һ��ָ�룬������ĵ�һ��Ԫ�ؿ�ʼ
        int finder = 0;

        // �ڶ�����Ѱ�һ�����ڵ�
        // ���ָ�����ָ��ͬʱ������������������ٶ���ͬ
        // ����������ʱ�����ǻ�����ڵ�
        while (finder != slow) {
            finder = nums[finder]; // ���ָ����һ��
            slow = nums[slow];     // ��ָ������ߣ����ֺ�finder��ͬ���ٶ�
        }

        // ���ػ�����ڵ㣬���������ظ���Ԫ��
        return finder;
    }
};
int main() 
{
    test_1();

    return 0;
}