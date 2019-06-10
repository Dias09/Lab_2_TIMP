#include <iostream>
#include <cctype>
#include "Cipher.h"
using namespace std;
int main(int argc, char **argv)
{
	int key;
	string text;
	unsigned op;
	do {
		try {
			cout << "Выберите операцию (0-выход, 1-зашифровать, 2-расшифровать): ";
			cin >> op;
			if (op > 2)
				cout<<"Недопустимая операция\n";
			else if (op > 0) {
				cout << "Шифратор готов. Введите текст: ";
				cin >> text;
				cout << "Введите ключ: ";
				cin >> key;
				Cipher cipher(key, text);
				if (op==1) {
					cout << "Зашифрованный текст: " << cipher.encrypt(text) << endl;
				} else {
					cout << "Расшифрованный текст: " << cipher.decrypt(text) << endl;
				}
			}
		} catch (const Error & e) {
			cerr << "Ошибка: " << e.what() << endl;
		}
	} while (op != 0);
	return 0;
}
