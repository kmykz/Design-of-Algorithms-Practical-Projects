#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;
vector<pair<int, int>> p;
int a, b;

int brute_force_solve(int l, int r) {
    int ans = 1e9;
    for (int i = l; i < r; ++i) {
        for (int j = i + 1; j < r; ++j) {
            int deltaX = p[j].first - p[i].first;
            int deltaY = p[j].second - p[i].second;
            ans = min(ans, deltaX * deltaX + deltaY * deltaY);
        }
    }
    //cout << l << " " << r << " " << ans << endl;
    return ans;
}

int solve(int l, int r) {
    vector<pair<int, int>> strips;
    if (r - l < 4) return brute_force_solve(l, r);
    int mid = (l + r) / 2;
    int ans = min(solve(l, mid), solve(mid, r));
    float rad = sqrt(ans);
    int start = lower_bound(p.begin() + l, p.begin() + r, make_pair(int(p[mid].first - rad), p[mid].second)) - p.begin();
    int t = start;
    while (t < r && t < mid + rad + 1) {
        strips.push_back({p[t].second, p[t].first});
        t++;
    }
    sort(strips.begin(), strips.end());
    for (int i = 0; i < strips.size(); ++i) {
        for (int j = 1; j <= 7; j++) {
            if (i + j >= strips.size()) break;
            int deltaX = strips[i].first - strips[i + j].first;
            int deltaY = strips[i].second - strips[i + j].second;
            ans = min(ans, deltaX * deltaX + deltaY * deltaY);
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        p.push_back({abs(a), abs(b)});
    }
    sort(p.begin(), p.end());
    cout << solve(0, n) << endl;
}
