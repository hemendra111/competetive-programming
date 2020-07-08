// Reference : https://codeforces.com/blog/entry/18051

#include <iostream>
#include <vector>

using namespace std;

enum OpType{
  Query,
  Update
};

void build(vector<int>& st) {
    int n = st.size() >> 1;
    for(int i = n - 1; i > 0; i--) {
        st[i] = st[i << 1] + st[(i << 1) | 1];
    }
    return;
}

int query(vector<int>& st, int l, int r) {
    int n = st.size() >> 1;
    int ans = 0;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ans += st[l++];
        if(r & 1) ans += st[--r];
    }
    return ans;
}

void update(vector<int>& st, int pos, int val) {
    int n = st.size() >> 1;
    for(st[pos += n] = val; pos > 1; pos >>= 1) {
        st[pos >> 1] = st[pos] + st[pos ^ 1]; 
    }
    return;
}

//for range query and single element update

int main() {
  int n, q, type, l, r, val, pos;
  cin >> n;
  vector<int> st(2 * n, 0);
  for(int i = 0; i < n; i++) cin >> st[n + i];
  build(st);
  cin >> q;
  while(q--) {
    cin >> type;
    switch(type) {
      case OpType::Query: {
        cin >> l >> r;
        cout << query(st, l, r) << endl;
        break;
      }
      case OpType::Update: {
        cin >> pos >> val;
        update(st, pos, val);
        break;
      }
    }
  }
}
