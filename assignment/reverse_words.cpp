//Raphael Radna
//Karl Yerkes
//MAT-240B Winter '19
//Assignment 0

#include <iostream>
#include <string>
using namespace std;

int main() {

  while (true) {
    printf("Type a sentence (then hit return): ");
    string line;
    getline(cin, line);
    if (!cin.good()) {
      printf("Done\n");
      return 0;
    }

    int length = 0;
    while (true) {
      if (line[length] == '\0') break;
      length = 1 + length;
    }

    int space = 0;
    int lastSpace = -1;
    space = line.find(' ');
    while (space >= 0) {
      for (int i = space - 1; i > lastSpace; --i) {
        cout << line[i];
      }
    cout << ' ';
    lastSpace = space;
    space = line.find(' ', lastSpace + 1);
    }
    for (int i = length; i > lastSpace; --i) {
      cout << line[i];
    }
    cout << endl;
  }
}
