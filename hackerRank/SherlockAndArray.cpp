#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const char *yes = "YES";
const char *no = "NO";

int main() {
    int tests = 0, N = 0, temp = 0;
    vector<int> data;
    cin >> tests;
    while (tests-- > 0) {
        unsigned int cumsum = 0;
        bool found = false;
        int rightSum, leftSum;
        int it;
        data.clear();
        cin >> N;
        for (int i = 0; i < N; ++i) {
            cin >> temp;
            data.push_back(temp);
        }
        if (1 == N) {
            found = true;
            goto PRINT_SOL;
        }
        transform(data.begin(), data.end(), data.begin(), [&cumsum](int d) {
            cumsum += d;
            return cumsum;
        });
        it = 1;
        while (it < (N - 1)) {
            rightSum = cumsum - data[it];
            leftSum = data[it - 1];
            if (rightSum == leftSum) {
                found = true;
                break;
            } else if (rightSum < leftSum) {
                break;
            }
            it++;
        }
PRINT_SOL:
        if (found)
            cout << yes << endl;
        else
            cout << no << endl;
    }
    return 0;
}

