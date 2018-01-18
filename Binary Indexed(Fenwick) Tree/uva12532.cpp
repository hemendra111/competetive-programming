#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;

const int MAXSIZE = 100005;

class FenwickTree{
private:
	vi ft;
	int LSOne(int k) { return (k & (-k)); }
	int rsq(int k) { 
		int sum = 0;
		for(; k; k -= LSOne(k)) {
			sum += ft[k];
		} 
		return sum;
	 }
public:
	FenwickTree(int n) { ft.assign(n + 1, 0); }
	int rsq(int a, int b) { return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }
	void adjust(int k, int v) { 
		for(; k < static_cast<int>(ft.size()); k += LSOne(k)) {
			ft[k] += v;
		}
	}
};

int main() {
	int n, k, f[MAXSIZE], a, b, index, val, count;
	char c;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while(cin >> n) {
		cin >> k;
		FenwickTree ftplus(n + 1), ftminus(n + 1), ftzero(n + 1);   // indexing is 1 to n
		for(int i = 1; i <= n; i++) {
			cin >> f[i];
			f[i] = (f[i] > 0 ? 1 : (f[i] == 0 ? 0 : -1));
			switch(f[i]) {
			case  1:
				ftplus.adjust(i, 1);
				break;	
			case  0:
				ftzero.adjust(i, 1);
				break;	
			case -1:
				ftminus.adjust(i, 1);
				break;	
			}
		}
		while(k--) {
			cin >> c;
			if(c == 'C') {
				cin >> index >> val;
				val = (val > 0 ? 1 : (val == 0 ? 0 : -1));
				switch (val) {
				case  1:
					if(f[index] == 0) ftzero.adjust(index, -1);
					else if(f[index] == -1) ftminus.adjust(index, -1);
					if(f[index] != 1) { ftplus.adjust(index, 1); f[index] = 1; } 	
					break;
				case  0:
					if(f[index] == 1) ftplus.adjust(index, -1);
					else if(f[index] == -1) ftminus.adjust(index, -1);
					if(f[index] != 0) { ftzero.adjust(index, 1); f[index] = 0; } 	
					break;
				case -1:
					if(f[index] == 0) ftzero.adjust(index, -1);
					else if(f[index] == 1) ftplus.adjust(index, -1);
					if(f[index] != -1) { ftminus.adjust(index, 1); f[index] = -1; } 	
					break;
				}
			}
			else if(c == 'P') {
				cin >> a >> b;
				if(ftzero.rsq(a, b)) { cout << '0'; }
				else {
					ftminus.rsq(a, b) % 2 ? cout << '-' : cout << '+';
				}
			}
		}
		cout << endl;
	}
	return 0;
}
