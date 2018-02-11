#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int t, n;
bool visit[105], mat[105][105], firstVisit[105], output[105][105];

void bfs(int node, int stop) {	
	queue<int> q;
	q.push(node); visit[node] = true;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		if(v == stop) continue;
		for(int i = 0; i < n; i++) {
			if(mat[v][i] && !visit[i]) { q.push(i); visit[i] = true; }
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> t;
	for(int test_case = 1; test_case <= t; test_case++) {
		cin >> n;
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> mat[i][j];
		for(int i = 0; i < n; i++) visit[i] = false;
		bfs(0, -1);									// 0th node is the starting node
		for(int i = 0; i < n; i++) firstVisit[i] = visit[i];
		for(int i = 0; i < n; i++) {
			memset(visit, false, n * sizeof(bool));
			bfs(0, i);
			for(int j = 0; j < n; j++) {
				if(firstVisit[j] && !visit[j]) output[i][j] = true;
				else output[i][j] = false;
			}
			output[i][i] = firstVisit[i];
		}
		cout << "Case " << test_case << ':' << endl;
		for(int i = 0; i < n; i++) {
			cout << '+';
			for(int j = 0; j < 2 * n - 1; j++) cout << '-';
			cout << '+' << endl;
			cout << '|';
			for(int j = 0; j < n; j++) output[i][j] ? cout << "Y|" : cout << "N|";
			cout << endl;
		}	
		cout << '+';
		for(int j = 0; j < 2 * n - 1; j++) cout << '-';
		cout << '+' << endl;
	}
	return 0;
}
