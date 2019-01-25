#include <regex> // regex
#include <iostream>
using namespace std;

int main() {
  while (true) {
    string line;
    getline(cin, line);
    // do things
    regex re("<a href=\"(.+?)\"(?: class=\"menulink\")?>(.+?)<\/a>");
    smatch match;
    if (regex_search(line, match, re) == true) {
      cout << match.str(2) << " --> " << match.str(1) << endl;
    }
  }
}
