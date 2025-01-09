#include "bits/stdc++.h"
using namespace std;

#define all(x) (x).begin(), (x).end()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

template<class T1, class T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[";
    for (int i = 0; i < v.size(); i++) {
        if (i) os << ", ";
        os << v[i];
    }
    return os << "]";
}

/***************************************************************************************/

class Solution {
private:

public:
    Solution() {}
    ~Solution() {}

    void solve(int times) {
        while (times--) {
            this->solve();
        }
    } 

    void solve() {
        
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Solution sol;
    int t = 1;
    cin >> t;  // Uncomment this line if the problem does not need to execute multiple times
    sol.solve(t);

    return 0;
}