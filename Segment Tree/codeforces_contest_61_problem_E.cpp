Problem link : https://codeforces.com/contest/61/problem/E

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void add(int p, int val, vector<int>& st) { // point update
    int n = st.size() >> 1;
    for(st[p += n] += val; p > 1; p >>= 1) st[p >> 1] = st[p] + st[p^1];
}

int query(int l, int r, vector<int>& st) { // range query
    int n = st.size() >> 1;
    int res = 0;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if(l & 1) res += st[l++];
        if(r & 1) res += st[--r];
    }
    return res;
}

// suf(ai) stores 1 so that it's contribution is taken for elements smaller than it on the left
// pref(ai) stores 1 so that it's contribution is taken for elements greater than it on the right

int main()
{
    int n, x;
    cin >> n;
    vector<int> pref(2 * n, 0), suf(2 * n, 0); 
    vector<pair<int, int>> temp(n);
    for(int i = 0; i < n; i++) {
        cin >> x;
        temp[i] = {x, i};
    }
    sort(temp.begin(), temp.end());
    //for(int i = 0; i < n; i++) {
      //  v[temp[i].second] = i;  // transforming array to range [0, n-1]
    //}
    add(temp[0].second, 1, pref);  // add 1 to pref of a0 (a0 < a1 < a2 ... < an-1)
    for(int i = 1; i < n; i++) add(temp[i].second, 1, suf);
    //cout << "v "; for(int i = 0; i < n; i++) cout << v[i] << ' '; cout << endl;
    //cout << "temp "; for(int i = 0; i < n; i++) cout << temp[i].second << ' '; cout << endl;
    ll ans = 0;
    for(int i = 1; i < n; i++) {
        //cout << "pref "; for(int i = 0; i < n; i++) cout << pref[i + n] << ' '; cout << endl;
        //cout << "suf "; for(int i = 0; i < n; i++) cout << suf[i + n] << ' '; cout << endl;
        ans += (ll)query(0, temp[i].second, suf) * query(temp[i].second + 1, n, pref); // suf[0, tab[i]) * pref[tab[i] + 1, n)
        add(temp[i].second, 1, pref);
        add(temp[i].second, -1, suf);
    }
    cout << ans;
    return 0;
}
