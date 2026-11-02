#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    long int n = 0, m = 0;
    long int a = 0, b = 0;
    long long k = 0;
    long int max = 0;

    cin >> n >> m;

    long long *arr = new long long[n + 1]();

    while (m-- > 0) {
        cin >> a >> b >> k;

        arr[a] += k;
        arr[b+1] -= k;
    }

    for (long int i = 0; i < n + 1; ++i) {
        if (max + arr[i] > max)
            max += arr[i];
    }

    cout << max;

    return 0;
}

