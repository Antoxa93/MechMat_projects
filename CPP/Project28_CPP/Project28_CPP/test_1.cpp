#include <iostream>
#include <iomanip>
#include "func28.h"

// file test1.cpp
// Реалізація методів классів та функцій
// Виконав студент гр. Компмат - 2
// А.В. Немирович
//реферативну частину додам

using namespace std;

void test1() {
	Zachetka d("Anton", { 4,5,4 }, { "a", "s", "d" }, { "b", "n", "m" }, 2);
	cout << "Input mark, to stop - input 0 : ";
	d.input_vec();
	cout << "\nInput discipl, to stop - input 0 : ";
	d.input_disc();
	cout << "\nInput prepod, to stop - input 0 : ";
	d.input_prep();
	d.sr();
	d.stipend();
	d.ins();
	d.print();
	cout << "\n" << d.get_sredn() << endl;
	cout << d.j << endl;
}

void test2() {
	Specialist e("", 0, 0, "", "");
	e.input();
	e.cal_s();
	//e.print();
	e.ins();
	cout << e << endl;
}

void test_inp_outp_stud() {

	//введення інформації (за необхідністю)
	std::cout << "Attention: to end filling marks/lecturers/disciplines put '0' \n";
	std::string f_name = "stud_info_28.txt";
	File_stud fs(f_name);
	std::cout << "To RE-input student`s info put not '0': ";
	int bol;
	std::cin >> bol;
	if (bol) { fs.input_stud_information(); }

	//додавання інформації (за необхідністю)
	std::cout << "To add student`s info put not '0': \n";
	int bol1, n;
	std::cin >> bol1;
	if (bol1) { 
		std::cout << "Number students to add: " << std::endl;
		std::cin >> n;
		for (int i = 0; i < n; i++) {
			fs.add_stud_information();
		}
	}
	
	// видалення інформації (за необхідністю)
	std::string nam;
	std::cout << "Input name to delete: ";
	std::cin >> nam;
	fs.del_stud(nam);

	std::vector<Zachetka> Z;
	Z = fs.get_stud();

	//виведення інформації в консоль
	std::vector<Zachetka>::iterator it = Z.begin();
	std::cout << std::endl;
	while (it != Z.end()) {
		std::cout << (*it) << std::endl;
		it++;
	}
}

void test_inp_outp_lect() {
	//введення інформації (за необхідністю)
	std::string f_name = "lect_info_28.txt";
	File_lect fs(f_name);
	std::cout << "To RE-input lecturer`s info put not '0': ";
	int bol;
	std::cin >> bol;
	if (bol) { fs.input_lect(); }
	//

	//додавання інформації (за необхідністю)
	std::cout << "To add lecturers`s info put not '0': \n";
	int bol1, n;
	std::cin >> bol1;
	if (bol1) {
		std::cout << "Number lecturers to add: " << std::endl;
		std::cin >> n;
		for (int i = 0; i < n; i++) {
			fs.add_lect_info();
		}
	}

	// видалення інформації (за необхідністю)
	std::string nam;
	std::cout << "Input name of Lecurer to delete: ";
	std::cin >> nam;
	fs.del_lect(nam);

	//виведення інформації в консоль
	std::vector<Specialist> Z;
	Z = fs.get_lect();
	std::vector<Specialist>::iterator it = Z.begin();
	std::cout << std::endl;
	while (it != Z.end()) {
		(*it).cal_s();
		std::cout << (*it) << std::endl;
		it++;
	}
}



int main() {
	test_inp_outp_stud(); //тест для студентів
	test_inp_outp_lect(); //для викладачів
	std::cout << "Print students of the Lecturer:" << std::endl;
	st(); //виведення студентів, що навчаються у даного викладача.
}