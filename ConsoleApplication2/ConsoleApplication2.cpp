#include <algorithm>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <conio.h> 
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <iomanip>
#undef max

using namespace std;

long double OnlyNumbers(string x) {
	string a;
	for (char c : x) {
		if (c >=0 || c<=9) {
			a += c;
		}
	}
	return stod(a);
}

void ColorText(int x) {
	HANDLE console_color;
	console_color = GetStdHandle(
	STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(
	console_color, x);
}
void ColorReturn() {
	HANDLE console_color;
	console_color = GetStdHandle(
	STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(
	console_color, 7);
}

class Accounting {
public:
	
	void SaveToFile(const string& filename) {
		ofstream out_file(filename, ios::out);
		if (!out_file.is_open()) {
			cerr << "Could not open the file - '" << filename << "' for writing." << endl;
			return;
		}

		out_file << balance_ << endl;

		for (auto& inc : income_) {
			out_file << "Inc " << inc.first << " " << inc.second << endl;
		}

		for (auto& exp : expenses_) {
			out_file << "Exp " << exp.first << " " << exp.second << endl;
		}

		out_file.close();
	}

	void LoadFromFile(const string& filename) {
		ifstream in_file(filename, ios::in);

		if (!in_file.is_open()) {
			return;
		}

		in_file >> balance_;

		string type, target;
		int sum;

		while (in_file >> type >> target >> sum) {
			if (type == "Inc") {
				income_.push_back({ target, sum });
				history_.push_back({ target, {sum, "Income"} });
			}
			else if (type == "Exp") {
				expenses_.push_back({ target, sum });
				history_.push_back({ target, {sum, "Expenses"} });
			}
		}

		in_file.close();
	}

	void ShowBalance () {
		ColorText(10);
		cout << "Your balance at the moment: " <<fixed << setprecision(2) << balance_ << "\n" << endl;
		ColorReturn();
	}

	void ShowIncome() {
		int operationIndex = -1;
		cout << "Выберите операцию чтобы узнать сумму пополнения.\n" << endl;
		cout << endl;
		ColorText(14);
		for (int i = 0; i < income_.size(); i++) {
			cout << income_[i].first << " введите -> " << i << "." << endl;
		}
		cout << "\nЧтобы посмоитерь все операции дохода. Введите -> -1." << endl;
		cout << endl;
		ColorReturn();
		cin >> operationIndex;
		cout << endl;
		ColorText(10);
		if (operationIndex <= income_.size() && operationIndex >= 0 && operationIndex != -1) {
			cout << "Income " << income_[operationIndex].second << endl;
		}
		else if (operationIndex == -1) {
			for (auto &i : income_) {
				cout << i.first << " " << i.second << endl;
			}
		}
		else if (expenses_.empty() || operationIndex < -1) {
			ColorText(12);
			cout << "no operations" << endl;
		}
		cout << endl;
		ColorReturn();
	}

	void ShowExpenses() {
		int operationIndex = -1;
		cout << "Выберите операцию чтобы узнать сумму трат.\n" << endl;
		ColorText(14);
		for (int i = 0; i < expenses_.size(); i++) {
			cout << expenses_[i].first << " введите -> " << i << "." << endl;
		}
		cout << "\nЧтобы посмоитерь все операции трат. Введите -> -1" << endl;
		cout << endl;
		ColorReturn();
		cin >> operationIndex;
		cout << endl;
		ColorText(10);
		if (operationIndex <= expenses_.size() && operationIndex >= 0 && operationIndex != -1) {
			cout << expenses_[operationIndex].first << " " << expenses_[operationIndex].second << endl;
		}
		else if (operationIndex == -1) {
			for (auto &i : expenses_) {
				cout << i.first << " " << i.second << endl;
			}
		}
		else if (expenses_.empty() || operationIndex < -1) {
			ColorText(12);
			cout << "no operations" << endl;
		}
		cout << endl;
		ColorReturn();
	}

	void EditIncome(string date, long double sum) {
		balance_ += sum;
		history_.push_back({date,{sum,"Income"}});
		income_.push_back({date,sum});
	}

	void EditExpenses(string date, long double sum) {

		balance_ -= sum;
		history_.push_back({date,{sum,"Expenses"}});
		expenses_.push_back({date,sum});

	}
	void ShowAllHistory() {

		ColorText(10);
		for (auto &i : history_) {
			cout << i.first << " " << i.second.first << " " << i.second.second << endl;
		}
		ColorReturn();
	}

private:
	long double balance_ = 0;
	vector < pair < string, pair < long double, string >> > history_;
	vector<pair<string, long double>> income_;
	vector<pair<string, long double>> expenses_;
};


int main() {
	setlocale(0, "");
	Accounting one;
	one.LoadFromFile("accounting.txt");
	string edit;
	string target;
	int vote = 0;
	while (vote != -1) {
		string ie;
		cout << " Select an action! \n 1 - Show balance \n 2 - Edit expenses \n 3 - Edit income \n 4 - history exp/inc \n 5 - all history \n-1 - exit\n" << endl;
		cin >> vote;
		cout << endl;
		switch (vote)
		{
		
		case 1:
			system("cls");
			one.ShowBalance();
			break;

		case 2:
			system("cls");
			cout << " Enter the purpose of the spending and then the amount of the spending.\n\n Target: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, target);
			cout << " Sum: ";
			cin >> edit;
			cout << endl;
			one.EditExpenses(target, OnlyNumbers(edit));
			ColorText(10);
			cout << "Changes applied." << endl;
			cout << endl;
			ColorReturn();
			break;

		case 3:
			system("cls");
			cout << " Specify the purpose of the replenishment, and then the amount of income.\n\n Target: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, target);
			cout << " Sum: ";
			cin >> edit;
			cout << endl;
			one.EditIncome(target, OnlyNumbers(edit));
			ColorText(10);
			cout << "Changes applied." << endl;
			cout << endl;
			ColorReturn();
			break;

		case 4:
			system("cls");
			cout << "what do you want to watch? (expenses or income) pls enter" << endl;
			cin >> ie;
			cout << endl;
			if (ie == "income" || ie == "Income") {
				one.ShowIncome();
			}
			else if(ie == "Expenses" || ie == "expenses") {
				one.ShowExpenses();
			}

			break;

		case 5:

			system("cls");
			one.ShowAllHistory();
			cout << endl;
			break;

		default:
			system("cls");
			if (vote != -1) {
				ColorText(12);
				cout << "error" << endl;
				ColorReturn();
			}
			break;
		}
	}
	one.SaveToFile("accounting.txt");

    return 0;
}
