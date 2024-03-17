#include <climits>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
using namespace std;
// Functie auxiliara pentru calcularea context switch-urilor utilizand
// sortare topologica
void AUX_TSORT(vector<list<int>> adj, vector<int> ind, vector<int> set,
               int& CT, queue<int> q1, queue<int> q2, int set1) {
    while (!q1.empty() || !q2.empty()) {
        while (!q1.empty()) {
            int node = q1.front();
            q1.pop();
            for (int deg : adj[node])
                ind[deg]--;
            for (auto neigh : adj[node]) {
                if (!ind[neigh]) {
                    if (set[neigh] == set1)
                        q1.push(neigh);
                    else
                        q2.push(neigh);
                }
            }
        }
        if (q1.empty() && !q2.empty())
            CT++;
        while (!q2.empty()) {
            int node = q2.front();
            q2.pop();
            for (int deg : adj[node])
                ind[deg]--;
            for (auto neigh : adj[node]) {
                if (!ind[neigh]) {
                    if (set[neigh] == set1)
                        q1.push(neigh);
                    else
                        q2.push(neigh);
                }
            }
        }
        if (!q1.empty() && q2.empty())
            CT++;
    }
}
// Sortare topologica utilizand BFS cu 2 cozi
void TSort(vector<list<int>> adj, vector<int> ind, vector<int> set, int N,
           int& CT) {
    static constexpr int NMAX = (int)1e5+5;
    vector<int> d(NMAX);
    for (int i = 1; i <= N; i++) {
        d[i] = INT_MAX;
    }

    queue<int> q1, q2;

    for (int i = 1; i <= N; i++)
        if (!ind[i]) {
            d[i] = 0;
            if (set[i] == 1)
                q1.push(i);
            else
                q2.push(i);
        }
    // Calculare context switch-uri prin sortarea topologica
    int CT1 = 0, CT2 = 0;
    AUX_TSORT(adj, ind, set, CT1, q1, q2, 1);

    AUX_TSORT(adj, ind, set, CT2, q2, q1, 2);
    CT = min(CT1, CT2);
}

int main() {
    // Citire date de intrare
    ifstream fin("supercomputer.in");
    ofstream fout("supercomputer.out");
    static constexpr int NMAX = (int)1e5+5;
    int N, M;
    fin >> N >> M;
    vector<int> set(NMAX);
    for (int i = 1, x; i<= N; i++) {
        fin >> x;
        set[i] = x;
    }
    vector<list<int>> adj(NMAX);
    vector<int> ind(NMAX, 0);
     for (int i = 1, x, y; i <= M; i++) {
        fin >> x >> y;
        adj[x].push_back(y);
        ind[y]++;
    }
    int CT = 0;
    TSort(adj, ind, set, N, CT);
    fout<< CT;
    return 0;
}
