// #include <bits/stdc++.h>
// #include <vector>
// #include <unordered_map>
// using namespace std;

// int evaluateTerm(string &term, unordered_map<char, int> &mp)
// {
//     int value = 1;
//     int product = mp[term.length() - 1];
//     for (int i = term.length() - 2; i >= 0; i--)
//     {
//         product += pow(10, value++) * mp[term[i]];
//     }
//     return product;
// }

// bool backtrack(int i, string unique, unordered_map<char, int> &mp, vector<string> &words, string result)
// {
//     if (i == unique.size())
//     {
//         int value1 = evaluateTerm(words[0], mp);
//         int value2 = evaluateTerm(words[1], mp);
//         int value3 = evaluateTerm(result, mp);
//         return value1 + value2 == value3;
//     }

//     char ch = unique[i];
//     for (int j = 0; j <= 9; j++)
//     {
//         if (mp.find(ch) == mp.end())
//         {
//             mp[ch] = j;
//             if (backtrack(i+1, unique, mp, words, result))
//             {
//                 return true;
//             }
//             mp.erase(ch);
//         }
//     }

//     return false;
// }

// void solve(int i, string unique, unordered_map<char, int> &mp, vector<string> &words, string result)
// {
//     if (backtrack(i, unique, mp, words, result))
//     {
//         cout << "Solution found:" << endl;
//         for (char letter : unique)
//         {
//             cout << letter << " = " << mp[letter] << endl;
//         }
//     }
//     else
//     {
//         cout << "No solution found." << endl;
//     }
// }
// int main()
// {
//     vector<string> words = {"SEND", "MORE"};
//     string result = "MONEY";
//     unordered_map<char, int> mp;
//     string unique = "";

//     for (string s : words)
//     {
//         for (int i = 0; i < s.length(); i++)
//         {
//             char ch = s[i];
//             if (isalpha(ch))
//             {
//                 unique += ch;
//             }
//         }
//     }

//     for (int i = 0; i < result.length(); i++)
//     {
//         char ch = result[i];
//         if (isalpha(ch))
//         {
//             unique += ch;
//         }
//     }

//     solve(0, unique, mp, words, result);

//     return 0;
// }

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <set>
using namespace std;

int evaluateTerm(const string &term, const unordered_map<char, int> &mp) {
    int value = 0;
    for (char ch : term) {
        value = value * 10 + mp.at(ch);
    }
    return value;
}

bool backtrack(int i, const set<char> &uniqueLetters, unordered_map<char, int> &mp, vector<bool> &used, const vector<string> &words, const string &result) {
    if (i == uniqueLetters.size()) {
        int value1 = evaluateTerm(words[0], mp);
        int value2 = evaluateTerm(words[1], mp);
        int value3 = evaluateTerm(result, mp);
        return value1 + value2 == value3;
    }

    char currentLetter = *next(uniqueLetters.begin(), i);
    for (int digit = 0; digit <= 9; digit++) {
        if (!used[digit]) {
            mp[currentLetter] = digit;
            used[digit] = true;
            if (backtrack(i + 1, uniqueLetters, mp, used, words, result)) {
                return true;
            }
            used[digit] = false;
            mp[currentLetter] = -1; // Reset the assignment
        }
    }
    return false;
}

void solve(const vector<string> &words, const string &result) {
    unordered_map<char, int> mp;
    set<char> uniqueLetters;
    for (const string &s : words) {
        for (char ch : s) {
            if (isalpha(ch) && uniqueLetters.find(ch) == uniqueLetters.end()) {
                uniqueLetters.insert(ch);
            }
        }
    }
    for (char ch : result) {
        if (isalpha(ch) && uniqueLetters.find(ch) == uniqueLetters.end()) {
            uniqueLetters.insert(ch);
        }
    }

    vector<bool> used(10, false); // Indicates if a digit is used
    if (backtrack(0, uniqueLetters, mp, used, words, result)) {
        cout << "Solution found:" << endl;
        for (char letter : uniqueLetters) {
            cout << letter << " = " << mp[letter] << endl;
        }
    } else {
        cout << "No solution found." << endl;
    }
}

int main() {
    vector<string> words = {"SEND", "MORE"};
    string result = "MONEY";
    solve(words, result);
    return 0;
}
