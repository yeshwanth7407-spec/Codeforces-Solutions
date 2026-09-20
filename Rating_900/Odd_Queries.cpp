/*
============================================================
Problem Name: 1807D - Odd Queries
Rating      : 900
Contest     : Codeforces Round 859 (Div. 4)
Topic       : Prefix Sums / Parity / Math
Date Solved : 2026-09-20

Problem Statement:
Given an array `a` of n integers and q queries, each query consists 
of three integers l, r, and k. If all elements from index l to r 
(1-indexed) are temporarily replaced by k, determine whether the total 
sum of the resulting array is odd ("YES") or even ("NO").

Approach:
Prefix Sum with O(1) Parity Evaluation:
- Construct a 1-indexed prefix sum array `pref` where `pref[i] = pref[i-1] + a[i]`.
  Use 64-bit integers (`long long`) to prevent overflow.
- Total original array sum is given by `total_sum = pref[n]`.
- For each query (l, r, k):
  - Original sum of range [l, r] = `pref[r] - pref[l - 1]`.
  - Replaced sum of range [l, r] = `(r - l + 1) * k`.
  - New total sum = `total_sum - (pref[r] - pref[l - 1]) + ((r - l + 1) * k)`.
  - If `new_total_sum % 2 != 0`, output "YES", otherwise "NO".

Time Complexity  : O(n + q) per testcase
Space Complexity : O(n) auxiliary space for the prefix sum array
============================================================
*/

#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;

    vector<long long> pref(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long val;
        cin >> val;
        pref[i] = pref[i - 1] + val;
    }

    long long total_sum = pref[n];

    while (q--) {
        int l, r;
        long long k;
        cin >> l >> r >> k;

        long long original_range_sum = pref[r] - pref[l - 1];
        long long replaced_range_sum = (r - l + 1) * k;
        long long new_total_sum = total_sum - original_range_sum + replaced_range_sum;

        if (new_total_sum % 2 != 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
