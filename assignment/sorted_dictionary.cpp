#include <algorithm>      // sort
#include <iostream>       // cin, cout, printf
#include <unordered_map>  // unordered_map
#include <vector>         // vector
using namespace std;

int main() {
  unordered_map<string, unsigned> dictionary;

  string word;

  while (cin >> word) {
/*
    if (dictionary.count(word) > 0) {
      dictionary[word] += 1;
    } else {
      dictionary[word] = 1;
    }
*/
    ++dictionary[word];
    //increment the value stored at key "word"
  }

  vector<pair<string, unsigned>> wordList;
  for (auto& t : dictionary) wordList.push_back(t);

  sort(wordList.begin(), wordList.end(), [](pair<string, unsigned> &x, pair<string, unsigned> &y) {
    return x.second > y.second;
  });

  for (auto& t : wordList) printf("%u:%s\n", t.second, t.first.c_str());
}
