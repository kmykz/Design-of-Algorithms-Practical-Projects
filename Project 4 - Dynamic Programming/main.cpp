#include <iostream>
#include <vector>

using namespace std;
string s;
vector<int> v;
int k, n;
const int mod = 1e9 + 7;
int dp[100][100][2505];

void initialize_vector() {
    int numberOf1s = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            numberOf1s++;
            if (i == n - 1) {
                v.push_back(numberOf1s);
            }
        } else if (s[i] == '0') {
            v.push_back(numberOf1s);
            numberOf1s = 0;
        }
    }
}

// a function to calculate number of 1s in a string
int numberOf1s(string s) {
    int numberOf1s = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '1') {
            numberOf1s++;
        }
    }
    return numberOf1s;
}

int main() {
    cin >> s >> k;
    n = s.size();
    initialize_vector();
    int len = v.size();
    int maxCarry = numberOf1s(s);
    // dp [kodom sefr] [chan ta 1 dare miad] [chan ta amaliat darim]
//    int dp[len + 10][maxCarry + 2][2505];
    for (int i = 0; i <= maxCarry; i++) {
        dp[1][i][0] = 1;
        for (int j = 1; j <= 2500; ++j) {
            if (j > 0) dp[1][i][j] = 0;
        }
    }
    for (int i = 2; i <= len; ++i) {
        for (int j = 0; j <= maxCarry; ++j) {
            for (int l = 0; l <= 2500; ++l) {
                dp[i][j][l] = dp[i - 1][j][l];
                for (int t = 1; t <= v[i - 1]; t++) {
                    if(j + t <= maxCarry && l-t >= 0) {
                        dp[i][j][l] = (dp[i][j][l] + dp[i - 1][j + t][l - t]) % mod;
                    }
                }
                for (int t = 1; t <= j; ++t) {
                    dp[i][j][l] = (dp[i][j][l] + dp[i - 1][j - t][l]) % mod;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= min(k,2500); ++i) {
        ans = (ans + dp[len][0][i]) % mod;
    }
    return cout << ans , 0;
}
