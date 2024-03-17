#include <algorithm>
#include <cstdint>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;


int64_t SolveTask(vector<int64_t> c, int64_t K) {
    double minW = 0, maxW = 0;
    for (int64_t e : c) {
        maxW += e;
        if (e > minW)
            minW = e;
    }
    double currW, W;
    int64_t cK = K;
    while ((maxW - minW) > 1) {
        currW = (minW + maxW) / 2;
        W = currW;
        cK = K;
        for (int64_t e : c) {
            W -= e;
            if (W < 0) {
                cK--;
                W = currW - e;
            }
        }
        if (cK >= 0)
            maxW = currW;
        else
            minW = currW;
    }
    return ceil(minW);
}

int main() {
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");

    int64_t N, K;
    fin >> N >> K;

    vector<int64_t> c(N);
    for (int64_t& num : c)
        fin >> num;

    auto res = SolveTask(c, K-1);
    fout << res << "\n";
    return 0;
}
