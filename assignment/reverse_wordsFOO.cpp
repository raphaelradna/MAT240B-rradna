
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

    // put your code here

    //how many lines?
    int length = 0;
    while (true) {
      if (line[length] == '\0') break;
      length = 1 + length;
    }

    //how many words?
    int words = 0;
    char last = ' ';
    int wordLength = 0;
    int offset = 0;
    int cursor = 0;

// main scope
    for (int i = 0; i < length; ++i) {
      if (line[i] != ' ') {
        ++wordLength;
        }
        else {
          //cout << i << endl;
          //cout << wordLength << ' ' << offset << ' ';
          cursor = offset + wordLength - 1;
          //cout << cursor << endl;
          offset += wordLength + 1;
          for (int j = cursor; j >= offset; --j) {
            cout << line[j];
          }
          wordLength = 0;
        }
    }
    //cout << wordLength << ' '<< offset << ' ';
    cursor = offset + wordLength - 1;
    //cout << cursor << endl;
    offset += wordLength + 1;
    for (int j = cursor; j >= offset; --j) {
      cout << line[j];
    }
    wordLength = 0;
    cout << endl;
    //for (int i = cursor; i > offset; --i) {
      //cout << line[i] << endl;

      //  words++;
      //}

/*
    for (int i = length; i >= 0; --i) {
      cout << line[i];
    }
    cout << endl;
*/

/*
    for (int i = 0; i < length; ++i) {
      //???
      //if (line[i] != ' ' && last == ' ') {
      //  words++;
      //}
      if (line[i] != ' ') {
        wordLength++;} else {
          //printf("%d\n", wordLength);
          for (int i = wordLength; i >= offset; --i) {
            cout << line[i];
            //printf("%c", line[i]);
          }
          cout << ' ';
          offset += wordLength;
          wordLength = 0;
      }
      last = line[i];

    }
    cout << endl;

*/

    //printf("%d\n", wordLength);
    //for (int i = wordLength; i >= offset; --i) {
      //cout << line[i];
    //}

    //reverse
    //printf("it has %d words\n", words);
  }
}
