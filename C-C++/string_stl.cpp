//#include <bits/stdc++.h>VS������
#include<iostream>
#include<string>

using namespace std;


int main() {
	string s1, s2 = "efg";
	cout << s2 << endl;
	string s("abc");                          //����s����ֵ
	string s3(s);                             //����s���ݵ�s3
	string S;
	//�����ַ��� cin >> a
	getline(cin, S);                          //���������ַ���
	cout << S << endl;
	//����
	cout << s.length() << endl;               //length()�����ַ�������
	cout << s.size() << endl;                 //size()�����ַ������ȣ��б�����ã�
	//ĩβ����ַ�
	s.push_back('d'); s += 'e';               //push_back('�ַ�')��β����һ���ַ�
	s.append("fg");                           //append("�ַ���")��β����һ���ַ�
	s = s + "hi"; s = "say:" + s;             //C++���������ַ���ǰ������
	cout << s << endl;
	//�����ַ�������
	cout << s.find("ab", 1) << endl;           //find("�ַ�������",λ��)����λ�ã�0��ʼ��������ַ�������
	cout << (int)s.find("ab", 4) << endl;      //�Ҳ�������-1��ǿ��ת��int
	//��ȡ�ַ�������
	string s4(s.substr(4, 7));                //substr(��ʼλ��, ��ȡ����)
	cout << s4 << endl;
	//�����ַ�������
	cout << s.insert(4, s4) << endl;          //insert(λ��, �ַ�������)��λ�ò����ַ���
	cout << s.insert(4, 2, 'a') << endl;       //insert(λ��, ����N���ַ�)��λ�ò���N���ַ�
	cout << s.insert(4, "itself", 2, 4) << endl;//insert(λ��1, �ַ�����λ��2���ַ���m)��λ��1�����ַ�����λ��2���m���ַ���
	//ɾ��ĩβ�ַ�������
	cout << s.erase(4, 4) << endl;            //erase(λ��, ��������)�޲������������ȫ��������ʱ����λ���ϵ�
	//�滻�ַ���
	cout << s.replace(3, 3, " it:") << endl;   //replace(��ʼ�滻λ��, �滻�ַ���, �ַ���)
	//�������滻�ַ�replace(��ʼλ��, ����λ��, �ַ���)����λ�ö�Ϊ��������Ϊ[ )��ʽ
	cout << s.replace(s.begin(), s.begin() + 7, "") << endl;
	//�ж��Ƿ�Ϊ��
	cout << s.empty() << endl;










	return 0;

}