#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
bool compare1(string a, string b) {
    return(a.length() > b.length());
}
bool compare2(string a, string b) {
    return(a < b);
}
int main() {
    int n;
    cin >> n;
    vector <string> a(2 * n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = n; i < 2 * n; i++)
        a[i] = a[i - n];
    vector<string>s1;
    sort(a.begin(), a.end(), compare2);
    string ab;
    cin >> ab;
    do {
        string s(ab);
        for (int i = 0; i < 2 * n - 1; i++) {
            for (int j = min(a[i + 1].length() - 1, a[i].length() - 1); j >= 1; j--) {
                if (s.length() >= j && s.substr(s.length() - j, j) == a[i + 1].substr(0, j)) {
                    s += a[i + 1].substr(j, a[i + 1].length());
                    break;
                }
            }
        }s1.push_back(s);
    } while (next_permutation(a.begin(), a.end()));
    sort(s1.begin(), s1.end(), compare1);
    auto it = s1.begin();
    string s3 = *it;
    cout << s3.length() << endl;

    return 0;
}