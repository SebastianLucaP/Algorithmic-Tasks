#include <fstream>
#include <vector>

using namespace std;
// Partea recursiva a algoritmului DFS
void DFS_RECURSIVE(int node, vector<int>& p, vector<int>& dfs,
                   vector<int> adj[], vector<int>& pos, vector<int>& pos2,
                   int& position, int& timestamp, vector<int>& start,
                   vector<int>& finish) {
    dfs.push_back(node);
    start[node] = timestamp++;
    pos[node] = position;
    pos2[position] = node;
    for (auto neigh : adj[node])
        if (p[neigh] == 0) {
            p[neigh] = node;
            DFS_RECURSIVE(neigh, p, dfs, adj, pos, pos2, ++position,
                          timestamp, start, finish);
        }
    finish[node] = timestamp - 1;
}
// Algoritm DFS
void DFS(int node, int N, vector<int>& dfs, vector<int> adj[],
         vector<int>& pos, vector<int>& pos2, vector<int>& start,
         vector<int>& finish) {
    static constexpr int NMAX = (int)1e5+5;
    // Vector de parinti
    vector<int> p(NMAX);
    for (int i = 1; i <= N; i++)
        p[i] = 0;

    int position = 1, timestamp = 0;
    DFS_RECURSIVE(1, p, dfs, adj, pos, pos2, position, timestamp,
                  start, finish);
}

int main() {
    // Citire date de intrare
    ifstream fin("magazin.in");
    ofstream fout("magazin.out");
    static constexpr int NMAX = (int)1e5+5;
    int N, Q;
    vector<int> adj[NMAX];
    fin >> N >> Q;
    for (int i = 1, x; i < N; i++) {
        fin >> x;
        adj[x].push_back(i+1);
    }
    vector<pair <int, int>> DE;
    DE.emplace_back(0, 0);
    for (int i = 1, x, y; i <= Q; i++) {
        fin >> x >> y;
        DE.emplace_back(x, y);
    }
    fin.close();
    vector<int> dfs, pos(NMAX), pos2(NMAX), start(NMAX), finish(NMAX);
    dfs.push_back(0);
    DFS(1, N, dfs, adj, pos, pos2, start, finish);
    // Calcularea depozitelor care vor primi coletele
    for (int i = 1; i <= Q; i++) {
        int node = DE[i].first, nrq = DE[i].second;
        if (finish[node] - start[node] < nrq)
            fout << -1 << "\n";
        else
            fout<<pos2[pos[node] + nrq]<< "\n";
    }
    fout.close();
    return 0;
}
