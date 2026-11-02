#include <iostream>
#include "../BigInt/BigInt.hpp"

using namespace std;

BigInt fib(int N, BigInt *arr) {
    if (false == arr[N].isValid()) {
        auto a = fib(N - 1, arr);
        auto b = fib(N - 1, arr);
        auto _2 = fib(N - 2, arr);
        auto pow = a*b;
        auto sum = _2 + pow;
        arr[N] = sum;
        //cout << "N: " << N << ", a: " << a.toString() << ", b: " << b.toString() << ", pow: " << pow.toString() << ", _2: " << _2.toString() << ", sum: " << sum.toString() <<endl;
        //std::cout << "invalid, N: " << N << ", " << arr[N].toString() << " pow: " << pow.toString() << " sum: " << sum.toString() << std::endl;
        return arr[N];
    } else {
        //std::cout << "valid, N: " << N << ", " << arr[N].toString() << std::endl;
        return arr[N];
    }
}

int main(void) {
    int t1 = 0, t2 = 1, N = 20;
    //std::cin >> t1 >> t2 >> N;
    //std::cout << "(" << t1 << ", " << t2 << ", " << N << ")" << std::endl;

    BigInt *data = new BigInt[N + 1]();
    data[0] = BigInt(0);
    data[1] = BigInt(t1);
    data[2] = BigInt(t2);
    fib(N, data);
    std::cout << data[N].toString() << std::endl;
    delete []data;
    return 0;
}
