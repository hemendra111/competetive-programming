/* solved here using 2 pointer approach */
/* Note : can also be solved using binary search, take a1 in array and search for a2 in remaining array */
#include <iostream>
#include <algorithm>

using namespace std;

int arr[10005];

int main() {
	int n, l, r, m, a1, a2;
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	while(cin >> n) {
		for(int i = 0; i < n; i++) cin >> arr[i];
		cin >> m;
		sort(arr, arr + n);
		l = 0, r = n - 1;
		while(l < r) {
			if(arr[l] + arr[r] == m) {
				a1 = l;
				a2 = r;
				l++;
			}
			else if(arr[l] + arr[r] < m) l++;
			else r--;
		}
		cout <<  "Peter should buy books whose prices are " << arr[a1] << " and " << arr[a2] << '.' << endl << endl;
	}
	return 0;
}
