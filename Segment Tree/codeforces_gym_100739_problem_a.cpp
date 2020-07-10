Reference : https://codeforces.com/gym/100739/problem/A

#include <bits/stdc++.h>

using namespace std;
#define DEBUG 0
const int nax = 1e5 + 5, mod = 4001;
struct s {
    int l;        // no of 1s from left, ie, in al, al ^ al+1, al ^ al+1 ^ al+2, ..., al ^ al+1 ^ ... ^ ar   
    int r;        // similar as above from right
    int xr;       // xor from al to ar
    int pxrsum;   // sum of xor pairs as asked in ques
    int start;
    int end;
    s() {
        l = r = xr = pxrsum = 0;
        start = end = -1;
    }
};

int n;
vector<int> arr(nax);
vector<vector<s>> st(10, vector<s>(2 * nax));

int sums(int a, int b) {
    return (a + b) % mod;
}

int muls(int a, int b) {
    return (a*b)%mod;
}

s combine(s a, s b) {
    s ret;
    if(a.start == -1) return b;
    if(b.start == -1) return a;
    int bl0 = b.end - b.start + 1 - b.l, ar0 = a.end - a.start + 1 - a.r;
    ret.l = a.l + (!a.xr ? b.l : bl0);
    ret.r = b.r + (!b.xr ? a.r : ar0);
    ret.xr = a.xr ^ b.xr;
    ret.pxrsum = sums(sums(sums(a.pxrsum, b.pxrsum), muls(a.r, bl0)), muls(b.l, ar0));
    ret.start = min(a.start, b.start);
    ret.end = max(b.end, a.end);
    return ret;
}

void build(int in) {
    for(int i = n-1;i>0;i--) {
        st[in][i] = combine(st[in][i<<1], st[in][(i<<1)|1]);
    }
}

void update(int in, int p) {
    for(p+=n;p>>=1;) st[in][p] = combine(st[in][p<<1], st[in][(p<<1)^1]);
}

int query(int in, int l, int r) {
    s lans, rans;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1) {
        if(l&1) lans = combine(lans, st[in][l++]);
        if(r&1) rans = combine(st[in][--r], rans);
        #if DEBUG
        cout <<  "in is " << in << ", l p sum is " << lans.pxrsum << ", r p sum is " << rans.pxrsum << endl;
        #endif
    }
    return combine(lans, rans).pxrsum;
}

int main() {
    int m, type, l, r;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int mask;
    for(int i = 0; i < 10; i++) {
        mask = 1 << i;
        #if DEBUG
        cout << "mask is " << mask << endl;
        #endif
        for(int j = 0; j < n; j++) {
            st[i][j+n].l = st[i][j+n].r = st[i][j+n].xr = st[i][j+n].pxrsum = ((arr[j] & mask) ? 1 : 0);
            #if DEBUG
            cout << ((arr[j] & mask) ? "1" : "0") << ' ';
            #endif
            st[i][j+n].start = st[i][j+n].end = j;
        }
        #if DEBUG
        cout << endl;
        #endif
        build(i);
    }
    while(m--) {
        cin >> type >> l >> r;
        if(type == 1) {
            l--;
            for(int i = 0; i < 10; i++) {
                mask = 1 << i;
                st[i][l+n].l = st[i][l+n].r = st[i][l+n].xr = st[i][l+n].pxrsum = ((r & mask) ? 1 : 0);
                update(i, l);
            }
        }
        else {
            l--;
            int ans = 0;
            for(int i = 0; i < 10; i++) {
                ans = sums(ans, muls(1<<i,query(i, l, r)));
            }
            cout << ans << endl;
        }
    }
    return 0;
}
