# C++ �ַ�������ʾ��

���ļ����� C++ ��׼�� `string` �ĳ�����������ͨ������ʾ��������ʾ��

## 1. �����������ʼ��  

C++ �ṩ���ַ�ʽ������ͳ�ʼ�� `string` ���͵ı�����  

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s1, s2 = "efg";   // �����ַ��� s1 �� s2��s2 ֱ�Ӹ�ֵ��
    cout << s2 << endl;

    string s("abc");         // ֱ�����ַ�����ʼ��
    string s3(s);            // ���������ַ��� s
    string S;
```
## 2. ��ȡ�����ַ���
ʹ�� `getline(cin, S)`` ��ȡ�������루�����ո�
```cpp
    getline(cin, S);  // �ӱ�׼�����ȡһ����
    cout << S << endl;
```
## 3. ��ȡ�ַ�������
��ȡ�ַ����ĳ��ȿ���ʹ�� `length()` �� `size()`��
```cpp
    cout << s.length() << endl;  // length() ��ȡ�ַ�������
    cout << s.size() << endl;    // size() Ҳ�������ַ���
```
## 4. ���ַ���ĩβ����ַ�
ʹ�� `push_back()`��`+=` �� `append()` ������ַ����ַ�����
```cpp
    s.push_back('d');  // ��ĩβ����ַ� 'd'
    s += 'e';          // ʹ�� += Ҳ��������ַ�
    s.append("fg");    // append() ��ĩβ׷���ַ���
    s = s + "hi";      // ֱ��ʹ�� + ��ƴ���ַ���
    s = "say:" + s;    // ������ǰ����ַ���
    cout << s << endl;
```
## 5. �����ַ������ַ���
ʹ�� `find()` �����ַ����е��Ӵ��������Ӵ�����ʼ�������Ҳ������� -1����
```cpp
    cout << s.find("ab", 1) << endl;  // ������ 1 ��ʼ���� "ab"
    cout << (int)s.find("ab", 4) << endl;  // ǿ��ת��Ϊ int���Ҳ������� -1
```
## 6. ��ȡ���ַ���
ʹ�� `substr(start, length)` ���ַ�������ȡ�Ӵ���
```cpp
    string s4(s.substr(4, 7));  // ������ 4 ��ʼ����ȡ 7 ���ַ�
    cout << s4 << endl;
```
## 7. �����ַ������ַ���
ʹ�� `insert()` ��ָ��λ�ò����ַ������ַ���
```cpp
    cout << s.insert(4, s4) << endl;      // ������ 4 �����ַ��� s4
    cout << s.insert(4, 2, 'a') << endl;  // ������ 4 ���� 2 �� 'a'
    cout << s.insert(4, "itself", 2, 4) << endl;  // �����ַ��� "itself" ������ 2 ��ʼ�� 4 ���ַ�
```
## 8. ɾ���ַ����еĲ�������
ʹ�� `erase(start, length)` ɾ��ָ����Χ���ַ���
```cpp
     cout << s.erase(4, 4) << endl;  // ������ 4 ��ʼɾ�� 4 ���ַ�
```
## 9. �滻�ַ����еĲ�������
ʹ�� `replace()` �滻ָ����Χ���ַ���
```cpp
    cout << s.replace(3, 3, " it:") << endl;  // ������ 3 ��ʼ�滻 3 ���ַ�
```
## 10. �������滻�ַ���
ʹ�� `replace(begin, end, new_string)` ͨ���������滻�������ݣ�
```cpp
    cout << s.replace(s.begin(), s.begin() + 7, "") << endl;  // ɾ��ǰ 7 ���ַ�
```
## 11. �ж��ַ����Ƿ�Ϊ��
ʹ�� `empty()` �ж��ַ����Ƿ�Ϊ�գ�
```cpp
    cout << s.empty() << endl;  // ����ַ���Ϊ�գ����� true��1��
```


