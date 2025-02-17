#include <gtest/gtest.h>
#include <vector>

/*The function takes as input a vector and an index.
The value of the indexed position is deleted and the remaining
values are shifted in-place of the removed value*/
void FillInPosition(std::vector<int>& vec, size_t index, int val);

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        size_t element_counter = 0;
        for (size_t i = 0; i < nums.size(); i++) {
            if (nums[i] == val) {
                FillInPosition(nums, i, val);
            }
            else {
                element_counter++;
            }
        }

        return element_counter;
    }
};

void FillInPosition(std::vector<int>& vec, size_t index, int val)
{
    bool found_new = 0;

   
    for (size_t j = index + 1; j < vec.size(); j++) {
        if (vec[j] != val && !found_new) {
           //New value
            vec[index] = vec[j];
            found_new = 1;
        }
        else if (found_new) {
            vec[j - 1] = vec[j];
        }
    }
}

//TESTING------------------------------------------

class TestVector : public ::testing::Test {
protected:
    std::vector<int> nums{ 0, 1, 1, 1, 2, 3, 4, 5 };
    std::vector<int> nums_answer{ 0, 1, 1, 3, 4, 5 };
    std::vector<int> nums_answer_2{ 0, 2, 3, 4, 5 };
    int val;
    int index;
    Solution sol;

    void SetUp() override {
        val = 1;
        index = 2;
    }
};

TEST_F(TestVector, fill_in_position) {
    FillInPosition(nums, 1, 1);
    FillInPosition(nums, 2, 1);
    FillInPosition(nums, 3, 1);
    EXPECT_EQ(nums, nums_answer_2);
}

TEST_F(TestVector, remove_element) {
    sol.removeElement(nums, val);
    EXPECT_EQ(nums, nums_answer_2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}