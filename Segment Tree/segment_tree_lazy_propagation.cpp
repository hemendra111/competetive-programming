#include <iostream>
#include <vector>

using namespace std;

enum OpType{
  Query,
  Update
};

class SegTree {
  vector<int> st, arr, lz;
  void build(int node, int s, int e);
  void update(int node, int s, int e, int l, int r, int val);
  int query(int node, int s, int e, int l, int r);
  int p(int i) {
    return i >> 1;
  }
  int lc(int i) {
    return i << 1;
  }
  int rc(int i) {
    return (i << 1) | 1;
  }
  int md(int l, int r) {
    return (l + r) >> 1;
  }
  void lazyupdate(int node, int s, int e) {
      if(lz[node]) {
          st[node] += (e - s + 1) * lz[node];
          if(s != e) {
            lz[lc(node)] += lz[node];
            lz[rc(node)] += lz[node];
          }
          lz[node] = 0;
      }
  }
public:
  explicit SegTree(const vector<int>& a) {
    arr = a;
    st.resize(arr.size() * 4, 0);
    lz.resize(arr.size() * 4, 0);
    build(1, 0, arr.size() - 1);
  }
  
  void update(int l, int r, int val) {
    update(1, 0, arr.size() - 1, l, r, val);
  }
  int query(int l, int r) {
    return query(1, 0, arr.size() - 1, l, r);
  }
};

void SegTree::build(int node, int s, int e) {
  if(s == e) {
    st[node] = arr[s];
    return;
  }
  int mid = md(s, e);
  build(lc(node), s, mid);
  build(rc(node), mid + 1, e);
  st[node] = st[lc(node)] + st[rc(node)];
  return;
}

void SegTree::update(int node, int s, int e, int l, int r, int val) {
  lazyupdate(node, s, e);
  if(s > r || e < l) return;
  if(l <= s && e <= r) {
    st[node] += (e - s + 1) * val;
    if(s != e) {
        lz[lc(node)] += val;
        lz[rc(node)] += val;
    }
    return;
  }
  int mid = md(s, e);
  update(lc(node), s, mid, l, r, val);
  update(rc(node), mid + 1, e, l, r, val);
  st[node] = st[lc(node)] + st[rc(node)];
  return;
}

int SegTree::query(int node, int s, int e, int l, int r) {
  if(s > r || e < l) return 0;
  lazyupdate(node, s, e);
  if(l <= s && e <= r) {
    return st[node];
  }
  int mid = md(s, e);
  int p1 = query(lc(node), s, mid, l, r);
  int p2 = query(rc(node), mid + 1, e, l, r);
  return p1 + p2;
}

int main() {
  int n, q, type, l, r, val;
  cin >> n;
  vector<int> arr(n);
  for(auto& x : arr) cin >> x;
  SegTree st(arr);
  cin >> q;
  while(q--) {
    cin >> type;
    switch(type) {
      case OpType::Query: {
        cin >> l >> r;
        cout << st.query(l, r) << endl;
        break;
      }
      case OpType::Update: {
        cin >> l >> r >> val;
        st.update(l, r, val);
        break;
      }
    }
  }
}
