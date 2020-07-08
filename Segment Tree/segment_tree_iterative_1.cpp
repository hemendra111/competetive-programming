#include <iostream>
#include <vector>

using namespace std;

enum OpType{
  Query,
  Update
};

// point query, range update

void build(vector<int>& st) {
    int n = st.size() >> 1;
    for(int i = n - 1; i > 0; i--) {
        st[i] = st[i << 1] + st[(i << 1) | 1];
    }
    return;
}

int query(vector<int>& st, int pos) {
    int n = st.size() >> 1;
    int ans = 0;
    for(pos += n; pos > 0; pos >>= 1) {
        ans += st[pos];
    }
    return ans;
}

void update(vector<int>& st, int l, int r, int val) {
    int n = st.size() >> 1;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if(l & 1) st[l++] += val;
        if(r & 1) st[--r] += val;
    }
    return;
}

void push(vector<int>& st) {                  // to get values of arr
  for (int i = 1; i < (st.size() >> 1); ++i) {
    st[i << 1] += st[i];
    st[i << 1 | 1] += st[i];
    st[i] = 0;
  }
}

int main() {
  int n, q, type, l, r, val, pos;
  cin >> n;
  vector<int> st(2 * n, 0);
  for(int i = 0; i < n; i++) cin >> st[n + i];
  //build(st);
  cin >> q;
  while(q--) {
    cin >> type;
    switch(type) {
      case OpType::Query: {
        cin >> pos;
        cout << query(st, pos) << endl;
        break;
      }
      case OpType::Update: {
        cin >> l >> r >> val;
        update(st, l, r, val);
        break;
      }
    }
  }
}



/* sample input
5
1 2 3 4 5
5
0 3
1 1 4 5
0 3
1 1 4 2
0 3
*/
