#include <iostream>
#include <vector>

using namespace std;

auto MSS(const vector<int> &data) {
    if (data.size() == 0) {
        return make_pair(0, 0);
    }
    int maxGlobal = data[0], maxForNow = data[0], maxNonCont = data[0];
    for (int it = 1; it < data.size(); ++it) {
        const auto &curr = data[it];
        maxForNow = max(curr, maxForNow + curr);
        maxGlobal = max(maxGlobal, maxForNow);
        if (maxNonCont < 0) {
            if (curr > maxNonCont)
                maxNonCont = curr;
        } else {
            maxNonCont = max(maxNonCont, maxNonCont + curr);
        }
    }
    return make_pair(maxGlobal, maxNonCont);
}

int main(void) {
    int T = 0, N = 0, tmp = 0;
    vector<int> array;
    cin >> T;
    while (T-- > 0) {
        cin >> N;
        array.reserve(N);
        while (N-- > 0) {
            cin >> tmp;
            array.push_back(tmp);
        }
        auto sol = MSS(array);
        cout << sol.first << " " << sol.second << endl;
        array.clear();
    }
    return 0;
}
