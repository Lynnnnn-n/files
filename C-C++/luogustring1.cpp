#include<iostream>
#include<string>
using namespace std;
int main() {
    string s;
    cin >> s;
    char s1;
    int result = 0, i;
    for (i = 0; i < s.length(); i++) {
		s1 = s[i];
		s[i] = ' ';
        if (s.find(s1) == string::npos) {
            result = 1;
            break;
        }
		s[i] = s1;
    }
    if (!result) {
        cout << "no" << endl;
        return 0;
    }
    cout << s1 << endl;
    return 0;
}