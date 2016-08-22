//
// Created by Jordi Sanabria on 8/18/16.
//

#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string alphabet{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
    vector<string> words;
    unordered_set<string> dictionary;
    while (dictionary.size() < n) {
        string str;
        int length = rand() % 12 + 3;
        str.reserve(length);
        for (int i = 0; i < length; ++i)
        {
            str += alphabet[rand() % alphabet.length()];
        }
        if (dictionary.find(str) != dictionary.end()) {
            dictionary.insert(str);
            words.push_back(str);
        }
    }

    vector<string> finalStream;
    unordered_set<int> appeared;
    for (int i = 0; i < m; ++i) {
        int pos = rand() % words.size();

        if (appeared.find(pos) == appeared.end())
            appeared.insert(pos);
        finalStream.push_back(words[pos]);
    }

    cout << appeared.size() << ' ' << m << endl;

    for (auto x : finalStream) {
        cout << x << endl;
    }

    return 0;
}