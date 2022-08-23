#include <iostream>
#include <vector>

using namespace std;
string a[15];
int r[15];
vector<char> v;
int n, m;

bool is_ok(int index) {
    for (int i = 0; i < m; ++i) {
        int err = 0;
        for (int j = 0; j <= index; ++j) {
            if (a[i][j] != v[j]) {
                err++;
            }
        }
        if (err > r[i]) {
            return false;
        }
    }
    return true;
}

void print_vector() {
    for (int i = 0; i < v.size(); ++i) {
        cerr << v[i] << " ";
    }
    cerr << endl;
}

bool is_final_valid() {
    for (int i = 0; i < m; i++) {
        int err = 0;
        for (int j = 0; j < n; ++j) {
            if (a[i][j] != v[j]) {
                err++;
            }
        }
        if (err != r[i]) {
            return false;
        }
    }
//    print_vector();
    return true;
}

long long back_track(int index) {
//    print_vector();
    if (index == n - 1) {
        return is_final_valid() ? 1 : 0;
    }
    long long ans = 0;
    v.push_back('1');
    if (is_ok(index)) {
        ans += back_track(index + 1);
    }
    v.pop_back();
    v.push_back('0');
    if (is_ok(index)) {
        ans += back_track(index + 1);
    }
    v.pop_back();
    return ans;

}

int main() {

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> r[i];
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == '1') {
                a[i][j] = '0';
            } else {
                a[i][j] = '1';
            }
        }
    }
//    for (int i = 0; i < m; ++i) {
//        cout << a[i] << " " << r[i] << endl;
//    }
    cout << back_track(-1);

}
