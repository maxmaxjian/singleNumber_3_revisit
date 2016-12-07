#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <iterator>
#include <algorithm>

class solution {
  public:
    std::vector<int> singleNumber(const std::vector<int> & nums) {
        int rs = std::accumulate(nums.begin(), nums.end(), 0, std::bit_xor<int>());
        // std::cout << "rs = " << rs << std::endl;
        int idx = 0;
        while (rs%2 == 0) {
            idx++;
            rs /= 2;
        }
        // std::cout << "idx = " << idx << std::endl;
        auto cpy = nums;
        auto it = std::partition(cpy.begin(), cpy.end(),
                               [&](int i){
                                   return getNthDigit(i, idx) == 0;
                               });
        std::cout << "After partitioning:\n";
        std::copy(cpy.begin(), cpy.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        
        std::vector<int> singleNums;
        singleNums.push_back(std::accumulate(cpy.begin(), it, 0, std::bit_xor<int>()));
        singleNums.push_back(std::accumulate(it, cpy.end(), 0, std::bit_xor<int>()));
        std::copy(singleNums.begin(), singleNums.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        
        return singleNums;
    }

  private:
    int getNthDigit(int num, int idx) {
        if (idx == 0)
            return num%2;
        else
            return getNthDigit(num/2, idx-1);
    }
};

int main() {
    std::vector<int> nums{1,2,1,3,2,5};

    solution soln;
    auto singles = soln.singleNumber(nums);
}
