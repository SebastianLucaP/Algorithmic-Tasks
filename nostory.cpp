/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <vector>

using namespace std;

int64_t SolveTask1(vector<int>& a, vector<int>& b) {
    long sum = 0;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<int>());
    for (int i = 0 ; i < a.size(); i++)
        sum+= max(a[i], b[i]);
    return sum;
}

int64_t SolveTask2(vector<int>& a, vector<int>& b, int moves) {
    long sum = 0;
    for (int i = 0; i < a.size(); i++)
        if (a[i] < b[i])
            swap(a[i], b[i]);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<int>());
    for (int i = 0; i < a.size(); i++)
        if (a[i] < b[i] && moves) {
            sum += b[i];
            moves--;
        } else {
            sum += a[i];
        }
    return sum;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
    fout << res << "\n";
    return 0;
}
