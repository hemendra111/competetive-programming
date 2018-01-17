#include <iostream>
#include <cstring>

using namespace std;

const int MAXSIZE = 502405;

enum Type {none, one, zero, inverse};

class SegmentTree {
private:
	int arr[MAXSIZE], st[4 * MAXSIZE], lazy[4 * MAXSIZE], size;

	int left(int p) { return 2 * p; }
	int right(int p) { return 2 * p + 1; }
	void build(int p, int l, int r) {
		if(l == r) st[p] = arr[l];
		else {
			int mid = (l + r) / 2;
			build(left(p), l , mid);
			build(right(p), mid + 1, r);
			st[p] = st[left(p)] + st[right(p)];
		}
	}
	int query(int p, int l, int r, int i, int j) {
		if(i > r || j < l) return 0;
		switch (lazy[p]) {
		case none:
			break;
		case one:
			st[p] = (r - l + 1);
			if(r != l) {
				lazy[left(p)] = lazy[right(p)] = lazy[p];
			}
			break;
		case zero:
			st[p] = 0;
			if(r != l) {
				lazy[left(p)] = lazy[right(p)] = lazy[p];
			}
			break;
		case inverse:
			st[p] = r - l + 1 - st[p];
			if(r != l) {
				switch (lazy[left(p)]) {
				case none:
					lazy[left(p)] = lazy[p];
					break;
				case one:
					lazy[left(p)] = zero;
					break;
				case zero:
					lazy[left(p)] = one;
					break;
				case inverse:
					lazy[left(p)] = none;
					break;
				}
				switch (lazy[right(p)]) {
				case none:
					lazy[right(p)] = lazy[p];
					break;
				case one:
					lazy[right(p)] = zero;
					break;
				case zero:
					lazy[right(p)] = one;
					break;
				case inverse:
					lazy[right(p)] = none;
					break;
				}
			}
			break;
		}
		lazy[p] = none;
		if(l >= i && j >= r) {
			return st[p];
		}
		int mid = (l + r) / 2;	
		int p1 = query(left(p), l, mid, i, j);
		int p2 = query(right(p), mid + 1, r, i, j);
		return (p1 + p2);
	}
	void update(int p, int l, int r, int i, int j, Type t) {
		/* update is done before checking for range overlapping unlike in query function as the values of children in 
		segment tree are used to compute value of parent in segment tree(see last line of update function) */
		switch (lazy[p]) {
		case none:
			break;
		case one:
			st[p] = (r - l + 1);
			if(r != l) {
				lazy[left(p)] = lazy[right(p)] = lazy[p];
			}
			break;
		case zero:
			st[p] = 0;
			if(r != l) {
				lazy[left(p)] = lazy[right(p)] = lazy[p];
			}
			break;
		case inverse:
			st[p] = r - l + 1 - st[p];
			if(r != l) {
				switch (lazy[left(p)]) {
				case none:
					lazy[left(p)] = lazy[p];
					break;
				case one:
					lazy[left(p)] = zero;
					break;
				case zero:
					lazy[left(p)] = one;
					break;
				case inverse:
					lazy[left(p)] = none;
					break;
				}
				switch (lazy[right(p)]) {
				case none:
					lazy[right(p)] = lazy[p];
					break;
				case one:
					lazy[right(p)] = zero;
					break;
				case zero:
					lazy[right(p)] = one;
					break;
				case inverse:
					lazy[right(p)] = none;
					break;
				}
			}
			break;
		}
		lazy[p] = none;
		if(i > r || j < l) return;
		if(i <= l && r <= j) {
			switch(t) {
			case none:
				break;
			case one:
				st[p] = r - l + 1;
				if(r != l) {
					lazy[left(p)] = lazy[right(p)] = one;
				}
				break;
			case zero:
				st[p] = 0;
				if(r != l) {
					lazy[left(p)] = lazy[right(p)] = zero;
				}
				break;
			case inverse:
				st[p] = r - l + 1 - st[p];
				if(r != l) {
					switch (lazy[left(p)]) {
					case none:
						lazy[left(p)] = inverse;
						break;
					case one:
						lazy[left(p)] = zero;
						break;
					case zero:
						lazy[left(p)] = one;
						break;
					case inverse:
						lazy[left(p)] = none;
						break;
					}
					switch (lazy[right(p)]) {
					case none:
						lazy[right(p)] = inverse;
						break;
					case one:
						lazy[right(p)] = zero;
						break;
					case zero:
						lazy[right(p)] = one;
						break;
					case inverse:
						lazy[right(p)] = none;
						break;
					}
				}
				break;
			}
			return;
		}
		int mid = (l + r) / 2;
		update(left(p), l, mid, i, j, t);
		update(right(p), mid + 1, r, i, j, t);
		st[p] = st[left(p)] + st[right(p)];	
	}

public:
	SegmentTree(int ar[], int sz) : size(sz) {
		for(int i = 0; i < size; i++) arr[i] = ar[i];
		for(int i = 0; i < 4 * size; i++) { lazy[i] = none; st[i] = 0; }
		build(1, 0, size - 1);
	}
	int query(int i, int j) { return query(1, 0, size - 1, i, j); }
	void update(int i, int j, Type t) { update(1, 0, size - 1, i, j, t); }
};

int main() {
	int t, m, n, size, arr[MAXSIZE], q, qno, a1, a2;
	char s[55], c;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> t;
	for(int i = 1; i <= t; i++) {
		size = 0, qno = 1;
		cin >> m;
		while(m--) {
			cin >> n;
			cin >> s;
			for(int k = 0; k < n; k++) {
				for(int j = size; j < size + strlen(s); j++) {
					arr[j] = s[j - size] - '0';
				}
				size += strlen(s);
			}
		}
		SegmentTree st(arr, size);
		cin >> q;
		cout << "Case " << i << ':' << endl;
		while(q--) {
			cin >> c >> a1 >> a2;
			switch(c) {
			case 'F':
				st.update(a1, a2, one);
				break;
			case 'E':
				st.update(a1, a2, zero);
				break;
			case 'I':
				st.update(a1, a2, inverse);
				break;
			case 'S':
				cout << 'Q' << qno << ": " << st.query(a1, a2) << endl;
				qno++;
				break;
			}
		}
	} 
	return 0;
}
