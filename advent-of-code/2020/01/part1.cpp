#include <iostream>
#include <set>

int main() {
    std::set<int> nums;
    int x;
    while (std::cin >> x) {
        int y = 2020 - x;
        if (nums.count(y) == 1) {
            std::cout << x << " + " << y << " = 2020" << std::endl;
            std::cout << x << " * " << y << " = " << (x * y) << std::endl;
            break;
        } else {
            nums.insert(x);
        }
    }
    return 0;
}
