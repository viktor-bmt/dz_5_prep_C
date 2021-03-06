#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Person.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

static Person* create_array(ifstream& file, int& nPerson);
static void add_to_array(Person& aPerson, const string& str);
static void print_elders(const Person* pPerson, const int& nPerson, const int& age);
static void print_with_HE(const Person* pPerson, const int& nPerson);
static void print_males(const Person* pPerson, const int& nPerson);

int main(int argc, char* argv[]) {

	if (argc != 2) {

		cout << "Incorrect command line arguments!"
			<< endl;

		return 1;
	}

	ifstream fp(argv[1]);

	if (!fp.is_open()) {

		cout << "Incorrect file!"
			<< endl;

		return 2;
	}

	int array_len = 0;

	Person* pPerson = nullptr;//create_array(fp, array_len);

	if (!pPerson) {

		cout << "Unsuccessful array creation!"
			<< endl;
		fp.close();

		return 3;
	}

	fp.close();

	int age = 0;

	cout << "Enter age: ";
	cin >> age;

	print_elders(pPerson, array_len, age);

	print_with_HE(pPerson, array_len);

	print_males(pPerson, array_len);

	delete[] pPerson;

	return 0;
}

static Person* create_array(ifstream& file, int& nPerson) {

	int capacity = 0;

	Person* pPerson = nullptr;

	while(true) {

		if (nPerson == capacity) {
	
			Person* pDummy = new Person[2 * capacity + 1];
			for (int i = 0; i < capacity; ++i)
				pDummy[i] = pPerson[i];		

			delete[] pPerson;
			pPerson = pDummy;
			pDummy = nullptr;

			capacity *= 2;
			capacity += 1;
		}

		string line;
		getline(file, line, '\n');

		if(line.empty())
			break;

		add_to_array(pPerson[nPerson], line);
		++nPerson;
	}

	return pPerson;
}

static void add_to_array(Person& aPerson, const string& str) {

	int start = 0;
	int end = 0;

	while(!isspace(str[end++]));
	aPerson.set_second_name(str.substr(start, end - start - 1));

	start = end;
	while(isspace(str[start++]));
	--start;
	end = start;

	while(!isspace(str[end++]));
	aPerson.set_first_name(str.substr(start, end - start - 1));

	start = end;
	while(isspace(str[start++]));
	--start;
	end = start;

	while(!isspace(str[end++]));
	aPerson.set_patronymic(str.substr(start, end - start - 1));

	start = end;
	while(isspace(str[start++]));
	--start;
	end = start;

	while(!isspace(str[end++]));
	aPerson.set_address(str.substr(start, end - start - 1));

	start = end;
	while(isspace(str[start++]));
	--start;
	end = start;


	aPerson.set_sex(str[start++]);

	while(isspace(str[start++]));
	--start;
	end = start;

	while(!isspace(str[end++]));
	aPerson.set_education(str.substr(start, end - start - 1));

	start = end;
	while(isspace(str[start++]));
	--start;

	int year = 0;
	for (int i = 0; i < 4; ++i) {

		year *= 10;
		year += static_cast<int>(str[start] - '0');
		++start;
	}

	aPerson.set_birth_year(year);

	return;
}

static void print_elders(const Person* pPerson, const int& nPerson, const int& age) {

	if (!pPerson) {

		cout << "Incorrect use of 'print_elders()'"
			<< endl;

		return;
	}

	cout << endl
		<< "List of people who is elder than "
		<< age << ":"
		<< endl;

	bool flag = false;

	for(int i = 0; i < nPerson; ++i)

		if ((CURRENT_YEAR - pPerson[i].get_birth_year()) > age) {

			flag = true;
			pPerson[i].show();
		}

	if(!flag)
		cout << "List is empty."
			<< endl;

	return;
}

static void print_with_HE(const Person* pPerson, const int& nPerson) {

	if (!pPerson) {

		cout << "Incorrect use of 'print_elders()'"
			<< endl;

		return;
	}

	cout << endl
		<< "People with higher education:"
		<< endl;

	bool flag = false;

	for(int i = 0; i < nPerson; ++i)

		if (pPerson[i].get_education() == "HE") {

			flag = true;
			pPerson[i].show();
		}

	if(!flag)
		cout << "List is empty."
			<< endl;

	return;
}

static void print_males(const Person* pPerson, const int& nPerson) {

	if (!pPerson) {

		cout << "Incorrect use of 'print_elders()'"
			<< endl;

		return;
	}

	cout << endl
		<<"Males:"
		<< endl;

	bool flag = false;

	for (int i = 0; i < nPerson; ++i)

		if (pPerson[i].get_sex() == 'M') {

			pPerson[i].show();
			flag = true;
		}

	if (!flag)
		cout << "List is empty."
			<< endl;

	return;
}
