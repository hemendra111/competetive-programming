Reference : https://codeforces.com/contest/292/problem/E

#include <bits/stdc++.h>

using namespace std;

const int nax = 1e5 + 5, INF = 1e9 + 7;

vector<int> a(nax), b(nax), st(4 * nax), lazy(4 * nax, -1);

void build(int node, int s, int e) {
    if(s==e) {
        st[node] = -1;
        return;
    }
    int mid = (s + e) >> 1;
    build(2*node, s, mid);
    build(2*node + 1, mid + 1, e);
    return;
}

void update(int node, int s, int e, int l, int r, int posa) {
    int mid = (s + e) >> 1;
    if(lazy[node] != -1) {
        if(s != e) {
            lazy[2*node] = lazy[node];
            lazy[2*node + 1] = lazy[node] + (mid-s+1);
        }
        else {
            st[node] = lazy[node];
        }
        lazy[node] = -1;
    }
    if(l > e || r < s) {
        return;
    }
    if(l <= s && e <= r) {
        lazy[node] = posa + (max(l, s) - l);
        return;
    }
    update(2*node, s, mid, max(l,s), min(r,e), posa + (max(l, s) - l));
    update(2*node+1, mid+1, e, max(l,s), min(r,e), posa + (max(l, s) - l));
}

int query(int node, int s, int e, int pos) {
    if(pos < s || e < pos) return -INF;
    int mid = (s + e) >> 1;
    if(lazy[node] != -1) {
        if(s != e) {
            lazy[2*node] = lazy[node];
            lazy[2*node + 1] = lazy[node] + (mid-s+1);
        }
        else {
            st[node] = lazy[node];
        }
        lazy[node] = -1;
    }
    if(s==e) {
        if(st[node] == -1) {
            return b[pos];
        }
        else return a[st[node]];
    }
    if(pos <= mid) return query(2*node, s, mid, pos);
    else return query(2*node+1, mid+1, e, pos);
}

int main() {
    int n, m, xs, ys, k, type;
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    build(1,0,n-1);
    while(m--) {
        cin >> type;
        if(type == 1) {
            cin >> xs >> ys >> k;
            xs--, ys--;
            update(1, 0, n-1, ys, ys+k-1, xs);  // update(node, s, e, l, r, vala)
        }
        else {
            cin >> ys;
            //cout << type << ' ' << ys << endl;
            ys--;
            cout << query(1, 0, n-1, ys) << endl;  // query(node, s, e, pos)
        }
    }
    return 0;
}
