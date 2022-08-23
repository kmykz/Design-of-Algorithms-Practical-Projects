#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
const int N = 100005;
int a[N], p[N], s[N], all[N];
set<int> s1, s2;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        all[a[i]] = 1;
    }
    for (int i = 1; i <= 2 * n; ++i) {
        if (all[i] == 0) {
            s1.insert(i);
            s2.insert(i);
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        auto t = s1.upper_bound(a[i]);
        if (t == s1.end()) {
            p[i] = cnt;
            s1.erase(s1.begin());
        } else {
            p[i] = ++cnt;
            s1.erase(t);
        }
    }
    cnt = 0;
    for (int i = n - 1; i >= 0; --i) {
        auto t = s2.lower_bound(a[i]);
        if (t == s2.begin()) {
            s2.erase(--s2.end());
            s[i] = cnt;
        } else {
            t--;
            s2.erase(t);
            s[i] = ++cnt;
        }
    }
    int ans = s[0];
    for (int i = 0; i < n; ++i) {
        ans = max(ans, p[i] + s[i+1]);
    }
    cout << ans << endl;

}


