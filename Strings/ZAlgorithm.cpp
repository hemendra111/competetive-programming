Reference : https://codeforces.com/blog/entry/3107

Z array : Z[i] represents max j strating from 0 such that string S[i+j] == S[j]
Invariant : [L, R] => 1 <= L <= i <= R with max R such that [L, R] is a prefix substring

void zalgo(string s) {
  int sz = s.length();
  vector<int> z(sz);
  z[0] = sz;
  int l = 0, r = 0;
  for(int i = 0; i < sz; i++) {
    if(i > R) {
      l = r = i;
      while(r < sz && s[r-l] == s[r]) r++;        // comparing s[0]... with s[i]...
      z[i] = r-l; r--;
    }
    else {                                        // z[k] >= min(z[k], r-i+1) s[i].. matches s[k]... for atleast r-i+1 characters
      int k = i - l;
      if(z[k] < r-i+1) {                          // z[i] = z[k]
        z[i] = z[k];
      }
      else {                                      // z[k] >= r-i+1, z[i] can be more than r-i+1, check s[i]... matches s[r] and so on..., r will increase
        l = i;
        while(r < sz && s[r-l]==s[r]) r++;
        z[i] = r-l; r--;
      }
    }
  }
}

int main() {
  string s = "somestringssssrrrfefqsomestr";
  zalgo(s);
  return 0;
}
