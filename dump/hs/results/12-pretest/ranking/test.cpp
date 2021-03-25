#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
#define all(v) begin(v), end(v)
#define sz(v) (int)(v).size()
#define fi first
#define se second

bool is_prefix(string s, string p) {
  return sz(s) >= sz(p) and s.substr(0, sz(p)) == p;
}

int main(int argc, char const *argv[])
{
  // cin.sync_with_stdio(0); cin.tie(0);
  // cin.exceptions(cin.failbit);
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif
  int cnt = 0;
  string s;
  while(getline(cin, s)) {
    if(cnt % 13 == 0) {
      if(!is_prefix(s, "Name")) {
        cout << cnt+1 << endl;
        break;
      }
    }
    cnt++;
  }
  return 0;
}
/*
* use std::array instead of std::vector, if u can
* overflow?
* array bounds
*/