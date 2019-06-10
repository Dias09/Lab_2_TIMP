#include "Cipher.h"
using namespace std;

modAlphaCipher::modAlphaCipher(const string& skey)
{
	for (unsigned i=0; i<numAlpha.size(); i++) {
		alphaNum[numAlpha[i]]=i;
	}
	wstring wskey = towstr(skey);
	key = convert(getValidKey(wskey));;
}

string modAlphaCipher::encrypt(const string& open_text)
{
	wstring open_wtext = towstr (open_text);
	vector<int> work = convert(getValidOpenText(open_wtext));
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
string modAlphaCipher::decrypt(const string& cipher_text)
{
	wstring cipher_wtext = towstr (cipher_text);
	vector<int> work = convert(getValidCipherText(cipher_wtext));
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
inline vector<int> modAlphaCipher::convert(const wstring& ws)
{
	vector<int> result;
	for(auto wc:ws) {
		result.push_back(alphaNum[wc]);
	}
	return result;
}

inline string modAlphaCipher::convert(const vector<int>& v)
{
	wstring wresult;
	for(auto i:v) {
		wresult.push_back(numAlpha[i]);
	}
	string result = fromwstr(wresult);
	return result;
}

wstring modAlphaCipher::towstr(const string& s)
{
	locale loc("ru_RU.UTF-8");
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	wstring ws = codec.from_bytes(s);
	return ws;
}

string modAlphaCipher::fromwstr(const wstring& ws)
{
	locale loc("ru_RU.UTF-8");
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	string s = codec.to_bytes(ws);
	return s;
}

inline wstring modAlphaCipher::getValidKey(const wstring & ws)
{
	locale loc("ru_RU.UTF-8");
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	if (ws.empty())
		throw cipher_error("Введите ключ");
	wstring tmp(ws);
	for (auto & wc:tmp) {
		if (!isalpha(wc, loc)) {
			string s = fromwstr(ws);
			throw cipher_error(string("Недопустимый ключ ")+s);
		}
		if (islower(wc, loc))
			wc = toupper(wc, loc);
	}
	return tmp;
}

inline wstring modAlphaCipher::getValidOpenText (const wstring & ws)
{
	locale loc("ru_RU.UTF-8");
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	wstring tmp;
	for (auto wc:ws) {
		if (isalpha(wc, loc)) {
			if (islower(wc,loc))
				tmp.push_back(toupper(wc,loc));
			else
				tmp.push_back(wc);
		}
	}
	if (tmp.empty())
		throw cipher_error("Пустой открытый текст");
	return tmp;
}

inline wstring modAlphaCipher::getValidCipherText(const wstring & ws)
{
	locale loc("ru_RU.UTF-8");
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	if (ws.empty())
		throw cipher_error("Введите зашифрованный текст");
	for (auto wc:ws) {
		if (!isupper(wc, loc)) {
			string s = fromwstr(ws);
			throw cipher_error(string("Недопустимый зашифрованный текст ")+s);
		}
	}
	return ws;
}
