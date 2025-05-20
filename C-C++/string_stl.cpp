//#include <bits/stdc++.h>VS不可用
#include<iostream>
#include<string>

using namespace std;


int main() {
	string s1, s2 = "efg";
	cout << s2 << endl;
	string s("abc");                          //定义s并赋值
	string s3(s);                             //复制s内容到s3
	string S;
	//输入字符串 cin >> a
	getline(cin, S);                          //输入整行字符串
	cout << S << endl;
	//长度
	cout << s.length() << endl;               //length()返回字符串长度
	cout << s.size() << endl;                 //size()返回字符串长度（列表类可用）
	//末尾添加字符
	s.push_back('d'); s += 'e';               //push_back('字符')在尾部加一个字符
	s.append("fg");                           //append("字符串")在尾部加一个字符
	s = s + "hi"; s = "say:" + s;             //C++快速增加字符串前后内容
	cout << s << endl;
	//查找字符（串）
	cout << s.find("ab", 1) << endl;           //find("字符（串）",位置)，从位置（0开始）起查找字符（串）
	cout << (int)s.find("ab", 4) << endl;      //找不到返回-1需强制转换int
	//截取字符（串）
	string s4(s.substr(4, 7));                //substr(开始位置, 截取长度)
	cout << s4 << endl;
	//插入字符（串）
	cout << s.insert(4, s4) << endl;          //insert(位置, 字符（串）)从位置插入字符串
	cout << s.insert(4, 2, 'a') << endl;       //insert(位置, 次数N，字符)从位置插入N次字符
	cout << s.insert(4, "itself", 2, 4) << endl;//insert(位置1, 字符串，位置2，字符数m)从位置1插入字符串自位置2起的m个字符）
	//删除末尾字符（串）
	cout << s.erase(4, 4) << endl;            //erase(位置, 擦除数量)无擦除数量则后面全部，擦除时包括位置上的
	//替换字符串
	cout << s.replace(3, 3, " it:") << endl;   //replace(开始替换位置, 替换字符数, 字符串)
	//迭代器替换字符replace(开始位置, 结束位置, 字符串)两个位置都为迭代器，为[ )形式
	cout << s.replace(s.begin(), s.begin() + 7, "") << endl;
	//判断是否为空
	cout << s.empty() << endl;










	return 0;

}