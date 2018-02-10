#include <iostream>
#include <cmath>

using namespace std;

#define LOG 0

const int INF = 1e9 + 7;

int t, n, m, b, edgelist[11][2], dp[11][2050];

inline int dist(int from, int to) {
	return abs(edgelist[from][0] - edgelist[to][0]) + abs(edgelist[from][1] - edgelist[to][1]);
}

int tsp(int pos, int mask) {                                                 // mask represents set of visited cities till this point
#if LOG
	cout << "pos and mask are " << pos << ", " << mask << endl;
	cout << "Initial tsp " << dp[pos][mask] << endl;
#endif
	if(mask == ((1 << (b + 1)) - 1)) return dp[pos][mask] = dist(pos, 0);
	if(dp[pos][mask] != INF) return dp[pos][mask];	
	for(int nxt = 0; nxt <= b; nxt++) {
		if(pos != nxt && !(mask & (1 << nxt))) {
			int temp = dist(pos, nxt) + tsp(nxt, mask | (1 << nxt));
			if(temp < dp[pos][mask]) dp[pos][mask] = temp;
		}
	}
#if LOG
	cout << "pos and mask are " << pos << ", " << mask << endl;
	cout << "Final tsp " << dp[pos][mask] << endl;
#endif
	return dp[pos][mask];
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> t;
	while(t--) {
		cin >> n >> m;
		cin >> edgelist[0][0] >> edgelist[0][1];
		cin >> b;
		for(int i = 1; i <= b; i++) cin >> edgelist[i][0] >> edgelist[i][1];
		for(int i = 0; i <= b; i++) for(int j = 0; j <= pow(2, b + 1); j++) dp[i][j] = INF;
		cout << "The shortest path has length " << tsp(0, 1) << endl;
	}
	return 0;
}
