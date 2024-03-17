#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int task1(int n, int m, int x, vector <int>& p, vector <vector <int> >& g) {
	vector <vector <int> > dp(m + 1, vector <int> (x*n + 1, 0));

	for (int cost = 0; cost <= x*n; cost++)
		dp[0][cost] = 0;
	for (int i = 1; i <= m; i++) {
		int nota = 0;
		for(int j = 0; j < n; j++) {
				nota += g[j][i-1];
		}
		for (int cost = 0; cost <= x*n; cost++) {
			dp[i][cost] = dp[i-1][cost];

			if(cost - p[i-1] >= 0) {
				int sol = dp[i-1][cost - p[i-1]] + nota;
				dp[i][cost] = max(dp[i][cost], sol);
			}
		}
	}
	return dp[m][x*n];
}
int task2(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	vector <vector <int> > gc(n, vector <int> (2*m, 0));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			gc[i][j] = gc[i][j+m] = g[i][j];
		}
	}
	vector <int> pc(2*m, 0);
	for(int i = 0; i < m; ++i) {
		pc[i] = pc[i+m] = p[i];
	}
	vector <vector <int> > dp(2*m + 1, vector <int> (x*n + 1, 0));

	for (int cost = 0; cost <= x*n; cost++)
		dp[0][cost] = 0;
	for (int i = 1; i <= 2*m; i++) {
		int nota = 0;
		for(int j = 0; j < n; j++) {
				nota += gc[j][i-1];
		}
		for (int cost = 0; cost <= x*n; cost++) {
			dp[i][cost] = dp[i-1][cost];

			if(cost - pc[i-1] >= 0) {
				int sol = dp[i-1][cost - pc[i-1]] + nota;
				dp[i][cost] = max(dp[i][cost], sol);
			}
		}
	}
	return dp[2*m][x*n];
}

int task3(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	vector <vector <int> > gc(n, vector <int> (2*m, 0));
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			gc[i][j] = gc[i][j+m] = g[i][j];
		}
	}
	vector <int> pc(2*m, 0);
	for(int i = 0; i < m; ++i) {
		pc[i] = pc[i+m] = p[i];
	}
	vector < vector <vector <int> > > dp(2*m + 1,
										 vector <vector <int> >(x*n + 1,
										 vector <int>(n+1, 0)));
	for (int cost = 0; cost <= x*n; cost++)
		dp[0][cost][0] = 0;
	for (int i = 1; i <= 2*m; i++) {
		int nota = 0;
		for(int j = 0; j < n; j++) {
				nota += gc[j][i-1];
		}
		for (int cost = 0; cost <= x*n; cost++) {
			for(int k = 1; k <= n; k++) {
				dp[i][cost][k] = dp[i-1][cost][k];

				if(cost - pc[i-1] >= 0) {
					int sol = dp[i-1][cost - pc[i-1]][k-1] + nota;
					dp[i][cost][k] = max(dp[i][cost][k], sol);
				}
			}
		}
	}
	return dp[2*m][x*n][n];
}

int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
