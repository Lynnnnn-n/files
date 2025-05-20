# C++ 字符串操作示例

本文件介绍 C++ 标准库 `string` 的常见操作，并通过代码示例进行演示。

## 1. 变量定义与初始化  

C++ 提供多种方式来定义和初始化 `string` 类型的变量：  

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s1, s2 = "efg";   // 定义字符串 s1 和 s2（s2 直接赋值）
    cout << s2 << endl;

    string s("abc");         // 直接用字符串初始化
    string s3(s);            // 复制已有字符串 s
    string S;
```
## 2. 读取整行字符串
使用 `getline(cin, S)`` 读取整行输入（包括空格）
```cpp
    getline(cin, S);  // 从标准输入读取一整行
    cout << S << endl;
```
## 3. 获取字符串长度
获取字符串的长度可以使用 `length()` 或 `size()`：
```cpp
    cout << s.length() << endl;  // length() 获取字符串长度
    cout << s.size() << endl;    // size() 也可用于字符串
```
## 4. 向字符串末尾添加字符
使用 `push_back()`、`+=` 或 `append()` 来添加字符或字符串：
```cpp
    s.push_back('d');  // 在末尾添加字符 'd'
    s += 'e';          // 使用 += 也可以添加字符
    s.append("fg");    // append() 在末尾追加字符串
    s = s + "hi";      // 直接使用 + 号拼接字符串
    s = "say:" + s;    // 可以在前面加字符串
    cout << s << endl;
```
## 5. 查找字符或子字符串
使用 `find()` 查找字符串中的子串，返回子串的起始索引（找不到返回 -1）：
```cpp
    cout << s.find("ab", 1) << endl;  // 从索引 1 开始查找 "ab"
    cout << (int)s.find("ab", 4) << endl;  // 强制转换为 int，找不到返回 -1
```
## 6. 截取子字符串
使用 `substr(start, length)` 从字符串中提取子串：
```cpp
    string s4(s.substr(4, 7));  // 从索引 4 开始，截取 7 个字符
    cout << s4 << endl;
```
## 7. 插入字符或子字符串
使用 `insert()` 在指定位置插入字符串或字符：
```cpp
    cout << s.insert(4, s4) << endl;      // 在索引 4 插入字符串 s4
    cout << s.insert(4, 2, 'a') << endl;  // 在索引 4 插入 2 个 'a'
    cout << s.insert(4, "itself", 2, 4) << endl;  // 插入字符串 "itself" 从索引 2 开始的 4 个字符
```
## 8. 删除字符串中的部分内容
使用 `erase(start, length)` 删除指定范围的字符：
```cpp
     cout << s.erase(4, 4) << endl;  // 从索引 4 开始删除 4 个字符
```
## 9. 替换字符串中的部分内容
使用 `replace()` 替换指定范围的字符：
```cpp
    cout << s.replace(3, 3, " it:") << endl;  // 从索引 3 开始替换 3 个字符
```
## 10. 迭代器替换字符串
使用 `replace(begin, end, new_string)` 通过迭代器替换部分内容：
```cpp
    cout << s.replace(s.begin(), s.begin() + 7, "") << endl;  // 删除前 7 个字符
```
## 11. 判断字符串是否为空
使用 `empty()` 判断字符串是否为空：
```cpp
    cout << s.empty() << endl;  // 如果字符串为空，返回 true（1）
```


