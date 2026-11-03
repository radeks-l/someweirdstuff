#include <iostream>
#include <vector>
#include <memory>

#include "../BigInt/BigInt.cpp"

std::shared_ptr<BigInt> fib(int N, std::vector<std::shared_ptr<BigInt>> &arr) {
    if (nullptr == arr[N]) {
        auto a = fib(N - 1, arr);
        auto b = fib(N - 1, arr);
        auto _2 = fib(N - 2, arr);
        auto pow = *a * *b;
        auto sum = *_2 + pow;
        arr[N] = std::make_shared<BigInt>(sum);
        return arr[N];
    } else {
        return arr[N];
    }
}

int main(void) {
    int t1 = 0, t2 = 1, N = 20;
    std::cin >> t1 >> t2 >> N;

    std::vector<std::shared_ptr<BigInt>> data(N + 1);
    data[0].reset(new BigInt(0));
    data[1].reset(new BigInt(t1));
    data[2].reset(new BigInt(t2));
    const auto solution = fib(N, data);
    std::cout << solution->toString() << std::endl;

    return 0;
}
