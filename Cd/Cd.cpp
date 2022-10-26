//Створіть імітацію входу в систему, що буде запитувати пароль і виводити запрошення тільки у
//випадку збігу введеного пароля з заздалегідь визначеним у програмі, а у випадку помилки виводити
//повідомлення про помилку і прохання повторити введення.Після 3 помилок програма повинна вивести
//повідомлення про спробу несанкціонованого доступу і завершити роботу. (для простоти у виді код
//використовуйте змінну типу іnt).

//у ній буде розміщуватись база користувачів (logіn і password), і буде вимагатися не лише введення паролю, а й логінну і відповідний йому пароль.

//у випадку помилки в логіні чи паролі вивести відповідне повідомлення про помилку.

//у випадку потрійної помилки введення пароля для одного користувача вивести повідомлення
//про завершення сеансу, а у випадку перебору більш 3 - х логінів з видачею повідомлень про помилку в
//паролі видати повідомлення про спробу несанкціонованого доступу і завершити роботу.

//під логіном Admіnіstrator організувати виведення логінів і паролів усіх користувачів на екран.

#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<conio.h>//_getch()
#include<windows.h>

using namespace std;

int login_chek(string login);//перевурка логіна
int pass_chek(string pass);//перевірка пароля
void error();
void if_admin(string login);//у випадку активаціх адмін.

string base_log, base_pass;//логіни і паролі з файлу
ifstream base;

int i;//універсальная змінна для так\ні

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Ця програма емулює вхід в систему\nВи можете ввести логін та пароль, і якщо вони співпадуть\nз тими, що є в базі користувачів, програма надасть вам 'доступ'\n";
	_getch();
	system("cls");

	cout << "\nСистема заблокована!\n\n";

	string login = "", pass = "";

Try_again: 

	login = ""; pass = "";
	base.open("base.txt");

	cout << "Будь ласка, введіть логін/пароль!\n\n\n\n";
	i = 3;

	while (1) {
		cout << "Логін: ";
		cin >> login;

		if (login_chek(login) == 1) {
			break;
		}
		else
			error();
	}
	system("cls");

	//
	cout << "Обраний користувач: " << login << "\n\n";

	i = 0;

	while (1) {
		cout << "Пароль: ";
		cin >> pass;

		if (pass_chek(pass) == 1) {
			break;
		}
		else
			error();
		if (i == 3) {
			base.close();
			goto Try_again; // оператор управління потоком виконання програм
		}
	}

	base.close();
	system("cls");
	cout << "\n		ЛАСКАВО ПРОСИМО!\n\n\n";

	if_admin(login);

	cout << "\n\nВийти з системи, чи припинити роботу програми?\n[''1'' для меню входу в систему, інше - завершити роботу]\n";
	cin >> i;

	if (i == 1) {
		system("cls");
		goto Try_again;
	}

	return 0;
}

/*перевірка пароля*/

int login_chek(string login) {

	while (getline(base, base_log)) {
		if (base_log == "login") {
			base >> base_log;
			if (login == base_log)
				return 1;
		}
	}

	return 0;
}

/*перевінка логіну*/

int pass_chek(string pass) {

	base >> base_pass;
	base >> base_pass;
	if (pass == base_pass)
		return 1;

	return 0;
}

/*помилка у разі неспівпадіння*/

void error() {
	i--;
	if (i > 0) {
		cout << "\n\nНекоректне введення!";
		cout << "\nСпробуйте ще раз! Залишилося " << i << " спроб(и)\n\n";
	}
	else if (i<0 && i>-3)
		cout << "Некоректне введення!\n\n";
	else if (i == 0) {
		system("cls");
		cout << "УВАГА\n\nВиявлено несанкціоновану спробу входу в систему! Систему буде вимкнено!\n		*********************\n\n\n";
		_getch();
		exit(1);
	}
	else if (i == -3) {
		i = 3;
		system("cls");
		cout << "Виявлено спробу перебору паролів! Сесію завершено!\n		*********************\n";
		_getch();
		system("cls");
	}
}

void if_admin(string login) {
	ifstream base1("base.txt");
	string a = "", b = "";

	if (login == "Administrator") {
		cout << "\n\n!!!ВІТАЄМО!!! ВИ АДМІН!\n\nХочете переглянути список користувачів?\n[''1'' якщо ''так'', інше - пропустити]\n";
		cin >> i;
		if (i == 1) {
			system("cls");

			cout << "Список:\n\n";
			while (getline(base1, a)) {
				base1 >> a;
				base1 >> b;
				base1 >> b;
				cout << "Логін: " << a << "\nПароль: " << b << "\n\n";
				base1 >> a;
			}
			base1.close();
			system("pause");
		}

	}
}
