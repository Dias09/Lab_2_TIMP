#pragma once
#include <vector>
#include <string>
#include <codecvt>
#include <locale>
#include <map>
using namespace std;
class modAlphaCipher
{
private:
	wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	map <wchar_t,int> alphaNum;
	vector <int> key; 
	vector<int> convert(const wstring& ws);
	string convert(const vector<int>& v);
	wstring getValidKey(const wstring & ws);
	inline wstring getValidOpenText(const wstring & ws);
	inline wstring getValidCipherText(const wstring & ws);
public:
	modAlphaCipher()=delete;
	modAlphaCipher(const string& skey);
	string encrypt(const string& open_text);
	string decrypt(const string& cipher_text);
	wstring towstr(const string& s);
	string fromwstr(const wstring& ws);
};

class cipher_error: public invalid_argument
{
public:
	explicit cipher_error (const string& what_arg):invalid_argument(what_arg) {}
	explicit cipher_error (const char* what_arg):invalid_argument(what_arg) {}
};
