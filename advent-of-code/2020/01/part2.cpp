#include <iostream>
#include <map>
#include <set>

int main() {
    std::set<int> nums;
    std::map<int, std::pair<int, int>> sums;
    int x;
    while (std::cin >> x) {
        int y = 2020 - x;
        if (sums.count(y) == 1) {
            auto p = sums[y];
            std::cout << x << " + " << p.first << " + " << p.second <<
                " = 2020" << std::endl;
            std::cout << x << " * " << p.first << " * " << p.second << " = " <<
                (x * p.first * p.second) << std::endl;
            break;
        } else {
            for (auto i = nums.begin(); i != nums.end(); ++i) {
                int s = x + *i;
                sums[s] = {x, *i};
            }
            nums.insert(x);
        }
    }
    return 0;
}
