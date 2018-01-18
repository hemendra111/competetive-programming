#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vi;

class FenwickTree {
private:
	vi ft;
	int LSOne(int x) { return (x & (-x)); }
public:
	FenwickTree(int n) { ft.assign(n + 1, 0); }           // init n + 1 zeros
	int rsq(int b) {
		int sum = 0;
		for(; b; b -= LSOne(b)) sum  += ft[b];        // ft[b] contains sum of cfs from (b - LSOne(b) + 1) to (b), iteration \
							      // is from leaf to root
		return sum;
	}
	int rsq(int a, int b) { return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }      // returns RSQ(a, b)
	int adjust(int k, int v) { for(; k < static_cast<int>(ft.size()); k += LSOne(k)) ft[k] += v; }   // n = ft.size() - 1, iterates \
													 //from root to leaf
};

int main() {
	int f[] = {2, 4, 5, 5, 6, 6, 6, 7, 7, 8, 9};          // m = 11
	FenwickTree ft(10);				      // declare a Fenwick Tree for range [1..10]	
	for(int i = 0; i < 11; i++) ft.adjust(f[i], 1);       // insert these scores manually one by one into an empty Fenwick Tree
							      // here each operation is increasing f[i](score at index i) by 1, O(mlogn)
	printf("%d\n", ft.rsq(1, 1)); 			      // 0 => ft[1] = 0
	printf("%d\n", ft.rsq(1, 2)); 			      // 1 => ft[2] = 1
	printf("%d\n", ft.rsq(1, 6)); 			      // 7 => ft[6] + ft[4] = 5 + 2 = 7
	printf("%d\n", ft.rsq(1, 10)); 			      // 11 => ft[10] + ft[8] = 1 + 10 = 11
	printf("%d\n", ft.rsq(3, 6)); 			      // 6 => rsq(1, 6) - rsq(1, 2) = 7 - 1
	ft.adjust(5, 2);                                      // update demo
	printf("%d\n", ft.rsq(1, 10)); 			      // now 13
	return 0;
}
