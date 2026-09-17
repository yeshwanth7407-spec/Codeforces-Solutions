/*
============================================================
Problem Name : Way Too Long Words
Problem ID   : 71A
Rating       : 800
Contest      : Codeforces Beta Round 65 (Div. 2)
Topic        : Strings
Date Solved  : 2026-09-17

Problem Statement:
Sometimes some words like "localization" or "internationalization" 
are so long that writing them many times is tiresome.
If a word's length is strictly more than 10 characters, replace it 
with an abbreviation: the first character, the number of omitted 
characters, and the last character.

Approach:
Check the length of the string:
- If length > 10: print s[0] + to_string(length - 2) + s.back()
- Otherwise: print the string unchanged.

Time Complexity  : O(1) per word
Space Complexity : O(1) auxiliary space
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    if (s.length() > 10) {
        cout << s.front() << s.length() - 2 << s.back() << "\n";
    } else {
        cout << s << "\n";
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