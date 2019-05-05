//Base64 encode and decode
//Authour:Michael Jiang
//Sun May 5 18:56:09 DST 2019

#include "cstdio"
#include "string"
#include "iostream"

using namespace std;

char bin_temp[4096];//存放二进制代码
int bin_len = 0;
int str_len = 0;

//Base64 编码表
char table[]{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};
void to_bin(string str)
{
	int char_index = 8;
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		char c = *it;
		int offset = 0;
		while (c)
		{
			if (c % 2 == 0)
				bin_temp[char_index - offset] = 0;
			else
				bin_temp[char_index - offset] = 1;
			c /= 2;
			offset++;
		}
		bin_len = char_index;
		char_index += 8;
	}
	str_len = str.length();
}

void to_bin(int str[])
{
	int char_index = 6;
	for (int i = 0; i < str_len; i++)
	{
		char c = str[i];
		int offset = 0;
		while (c)
		{
			if (c % 2 == 0)
				bin_temp[char_index - offset] = 0;
			else
				bin_temp[char_index - offset] = 1;
			c /= 2;
			offset++;
		}
		bin_len = char_index;
		char_index += 6;
	}
}

//编码
string encode(string str) 
{
	int index = 6;
	string out = "";//Base64 编码结果
	to_bin(str);//将输入的字符串转成二进制存放再bin_temp[]中
	for (int i = 1; i <= bin_len; i += 6)
	{
		int index = 5;
		int c = 0;
		for (int j = i; j <= i+5; j++)
		{
			c+=bin_temp[j] * pow(2, index--);
		}
		out += table[c];
	}

	//求出末尾 = 的个数
	int s = str_len % 3;
	if (s)
	{
		for (int i = 0; i < 3 - s; i++)
			out += "=";
	}
	return out;
}

int find_code(char c)
{
	for (int i = 0; i < 64; i++)
	{
		if (table[i] == c)
			return i;
	}
	return -1;
}

//解码
string decode(string s)
{
	int temp[2048];
	char c;
	int i = 0;
	string str = "";
	for (string::iterator it = s.begin(); it != s.end(); it++)
	{
		if (*it != '=')
		{
			str += *it;
		}
	}
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		c = find_code(*it);
		temp[i++] = c;
	}
	str_len = i;
	to_bin(temp);
	string out = "";
	for (int i = 1; i <= bin_len; i += 8)
	{
		int index = 7;
		char c = 0;
		for (int j = i; j <= i + 7; j++)
		{
			c += bin_temp[j] * pow(2, index--);
		}
		out += c;
	}
	return out;
}

int main()
{
	string in = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
	string out = encode(in);
	cout <<"原始字符串："<<in << endl;
	cout <<"Base64编码："<<out << endl;
	cout << "Base64解码: "<<decode(out);
}