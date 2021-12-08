#include "func28.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <nlohmann/json.hpp>

// file func28.cpp
// Реалізація методів классів та функцій
// Виконав студент гр. Компмат - 2
// А.В. Немирович

// класс Людина

//метод встановлення імені
void Person::set_name(string name) { this->name = name; }

//виведення імені
void Person::print () {
    cout << "Name: " << name << "\t";
    //if (endline) out << endl;
}

//введення імені
void Person::input() {
    cin >> name;
}

//виведення імені в форматі json
void Person::ins() {
	j["name"] = name;
}


//класс Студент

// метод введення оцінок
// приймається послідовність натуральних чисел ДО нуля
vector<int> Student::input_vec() {
    vector<int> v;
    int a;
    while (1) {
        cin >> a;
        if (!a) {
            break;
        }
        v.push_back(a);
    }
    this->marks = v;
    return v;
}

// метод встановлення стипендії
void Student::set_stip(float _stip) {
    sch_sh = _stip;
}

// метод обчислення середнього балу
float Student::sr() {
    vector<int>::iterator it = marks.begin();
    int i = 0;
    float s = 0;
    while (!(it == marks.end())) {
        s += (*it);
        i++;
        it++;
    }
    this->sredn = (s / i);
    return sredn;
}

// метод вирахування стипендії
void Student::stipend() {
    if (sredn >= 4.0 && sredn < 5.0) {
        sch_sh = 30 * sredn;
    }
    else if (sredn == 5.0) {
        sch_sh = 200;
    }
    else {
        sch_sh = 0.0;
    }
}

// метод введення курсу
void Student::input() {
    Person::input();
    cin >> course;
}

// виведення в консоль 
void Student::print() {
    Person::print();
    cout << " Average: " << std::setprecision(3) << sr() << "\t" << " Course: " << course << "\t" << " Stipendia: " << std::setprecision(4) << sch_sh << "\t";
    //if (endline) out << endl;
}

// виведення в форматі json
void Student::ins() {
    Person::ins();
    j["marks"] = marks;
    j["course"] = course;
    j["sredn"] = sredn;
    j["stipendia"] = sch_sh;
}

// введення викладачів
// приймає послідовність рядків ДО 0
vector<string> Zachetka::input_prep() {
    vector<string> v;
    string a;
    while (1) {
        cin >> a;
        if (a == "0") {
            break;
        }
        v.push_back(a);
    }
    this->lecturers = v;
    return v;
}

// введення викладачів
// приймає послідовність рядків ДО 0
vector<string> Zachetka::input_disc() {
    vector<string> v;
    string a;
    while (1) {
        cin >> a;
        if (a == "0") {
            break;
        }
        v.push_back(a);
    }
    this->discipl = v;
    return v;
}

// виведення в форматі json
void Zachetka::ins() {
    Student::ins();
    j["disciplines"] = discipl;
    j["lecturers"] = lecturers;
}

// класс Співробітник

// виведення окладу
void Employee::print() {
    Person::print();
    cout << ' ' << "Oklad " << oklad << "\t";
}

// введення окладу і стажу
void Employee::input() {
    Person::input();
    cin >> oklad >> stazh;
}

// виведення в форматі json
void Employee::ins() {
    Person::ins();
    j["oklad"] = oklad;
    j["stazh"] = stazh;
}

// клас Викладач

// обчислення зарплати
void Lecturer::cal_s() {
    double h;
    h = oklad + 0.4 * oklad * (double(stazh) / 100);

    if (step == "teacher") {
        this->salary = h * 1.2;
    }
    else if (step == "candidate") {
        this->salary = h * 1.4;
    }
    else if (step == "doctor") {
        this->salary = h * 1.6;
    }
    else
    {
        this->salary = h;
    }
}

// введеня наук. степені
void Lecturer::input() {
    Employee::input();
    cin >> step;
}

// виведення степені та зарплати
void Lecturer::print() {
     Employee::print();
     cout << ' ' << " Stepen " << step << "\t" << ' ' << " Salary " << salary << "\t";
 }

// виведення в форматі json
void Lecturer::ins() {
     Employee::ins();
     j["step"] = step;
     j["salary"] = salary;
 }

// класс Спеціаліст

// введення спеціальності
void Specialist::input() {
     Lecturer::input();
     cin >> spec;
 }

// виведення спеціальності
void Specialist::print() {
    Lecturer::print();
    cout << " Specialization: " << spec;
}

// // виведення в форматі json
void Specialist::ins() {
    Lecturer::ins();
    j["specialization"] = spec;
}

// класс для роботи з файлом студентів

//введення інформаціі про n студентів
void File_stud::input_stud_information() {
    int n;
    cout << "Input number of students: ";
    cin >> n;
    cout << endl;
    string name;
    vector<int> marks;
    vector<string> preps;
    vector<string> discip;
    int course;

    vector<Zachetka> z;
    nlohmann::json J{};
    for (int i = 0; i < n; i++) {
        Zachetka z0("A", { 1 }, { "i" }, { "y" }, 0);
        cout << "Name: ";
        cin >> name;
        z0.set_name(name);
        cout << endl << "Input marks: ";
        z0.input_vec();
        cout << endl << "Input disciplines: ";
        z0.input_disc();
        cout << endl << "Input lecturers: ";
        z0.input_prep();
        cout << endl << "Input course: ";
        cin >> course;
        z0.set_course(course);
        z0.sr();
        z0.stipend();
        z0.ins();
        //cout << endl << endl << z0.j << endl;
        J.push_back(z0.j);
        z.push_back(z0);
    }
    cout << J << endl;
    ofstream outj;
    outj.open(filename);
    outj << J; //вводимо json-інформацію в файл
    outj.close();
}

// додавання одного студента
void File_stud::add_stud_information() {
    string name;
    vector<int> marks;
    vector<string> preps;
    vector<string> discip;
    int course;

    vector<Zachetka> z;
    nlohmann::json J{};
    ifstream inj;
    inj.open(filename);
    inj >> J; // зчитування з json
    inj.close();

    for (int i = 0; i < 1; i++) {
        Zachetka z0("A", { 1 }, { "i" }, { "y" }, 0);
        cout << "Name: ";
        cin >> name;
        z0.set_name(name);
        cout << endl << "Input marks: ";
        z0.input_vec();
        cout << endl << "Input disciplines: ";
        z0.input_disc();
        cout << endl << "Input lecturers: ";
        z0.input_prep();
        cout << endl << "Input course: ";
        cin >> course;
        z0.set_course(course);
        z0.sr();
        z0.stipend();
        z0.ins();
        //cout << endl << endl << z0.j << endl;
        J.push_back(z0.j);
        z.push_back(z0);
    }
    //cout << J << endl;
    ofstream outj;
    outj.open(filename);
    outj << J; //вводимо json-інформацію в файл з новим студентом
    outj.close();
}

// видалення студента
// щоб не видаляти нікого, ввести довільний рядок
void File_stud::del_stud(string name) {
    nlohmann::json J{};
    ifstream inj;
    inj.open(filename);
    inj >> J;
    inj.close();
    nlohmann::json::iterator it = J.begin();
    //cout << J[2] << endl;
    nlohmann::json J1{};
    while (!(it == J.end())) {
        if (!((*it)["name"] == name)) {
            J1.push_back(*it);
        }
        it++;
    }
    ofstream outj;
    outj.open(filename);
    outj << J1; // виведення в json але без студента
    outj.close();
}

// отримання вектору об'єктів Заліковка з файлу для подальшої роботи
vector<Zachetka> File_stud::get_stud() {
    nlohmann::json J{};
    ifstream inj;
    inj.open(filename);
    inj >> J;
    inj.close();
    vector<Zachetka> Z;
    nlohmann::json::iterator it = J.begin();

    while (!(it == J.end())) {
        Zachetka z{ (*it)["name"], (*it)["marks"], (*it)["disciplines"], (*it)["lecturers"], (*it)["course"] };
        z.set_stip((*it)["stipendia"]);
        //cout << z.get_course() << endl;
        Z.push_back(z);
        it++;
    }
    return Z;
}


// класс для роботи з файлом викладачів

// метод введення інформації про n викладачів
void File_lect::input_lect() {
    int n;
    cout << "Input number of lecturers: ";
    cin >> n;
    cout << endl;
    nlohmann::json J{};

    string name;
    string step;
    for (int i = 0; i < n; i++) {
        Specialist s0("", 0, 0, "", "");
        cout << "Name: ";
        cin >> name;
        s0.set_name(name);
        cout << endl << "Input oklad: ";
        cin >> s0.oklad;
        cout << endl << "Input time of work: ";
        cin >> s0.stazh;
        cout << endl << "Input specialization: ";
        cin >> s0.spec;
        cout << endl << "Input stepen: ";
        cin >> step;
        s0.set_step(step);
        s0.cal_s();
        s0.ins();
        //cout << endl << endl << s0.j << endl;
        J.push_back(s0.j);
    }
    ofstream outj;
    outj.open(filename);
    outj << J << endl;
    outj.close();
}

// додавання одного викладача
void File_lect::add_lect_info() {
    nlohmann::json J{};
    ifstream inj;
    inj.open(filename);
    inj >> J;
    inj.close();

    string name;
    string step;
    for (int i = 0; i < 1; i++) {
        Specialist s0("", 0, 0, "", "");
        cout << "Name: ";
        cin >> name;
        s0.set_name(name);
        cout << endl << "Input oklad: ";
        cin >> s0.oklad;
        cout << endl << "Input time of work: ";
        cin >> s0.stazh;
        cout << endl << "Input specialization: ";
        cin >> s0.spec;
        cout << endl << "Input stepen: ";
        cin >> step;
        s0.set_step(step);
        s0.cal_s();
        s0.ins();
        //cout << endl << endl << s0.j << endl;
        J.push_back(s0.j);
    }
    //cout << J << endl;
    ofstream outj;
    outj.open(filename);
    outj << J;
    outj.close();
}

// видалення викладача
void File_lect::del_lect(string name) {
    nlohmann::json J{};
    ifstream inj;
    inj.open(filename);
    inj >> J;
    inj.close();
    nlohmann::json::iterator it = J.begin();
    //cout << J[2] << endl;
    nlohmann::json J1{};
    while (!(it == J.end())) {
        if (!((*it)["name"] == name)) {
            J1.push_back(*it);
        }
        it++;
    }
    ofstream outj;
    outj.open(filename);
    outj << J1;
    outj.close();
}

// отримання вектору об'єктів Спеціаліст з файлу для подальшої роботи
vector<Specialist> File_lect::get_lect() {
    nlohmann::json J{};
    ifstream inj;
    inj.open(filename);
    inj >> J;
    inj.close();
    vector<Specialist> Z;
    nlohmann::json::iterator it = J.begin();

    while (!(it == J.end())) {
        Specialist z{ (*it)["name"], (*it)["oklad"], 50, (*it)["step"], (*it)["specialization"] };
        //cout << z.get_course() << endl;
        Z.push_back(z);
        it++;
    }
    return Z;
}

// функція наявності рядка у векторі з рядків
bool poisk(std::vector<std::string> N, std::string prep) {
    std::vector<std::string>::iterator it = N.begin();
    bool result = false;
    while (it != N.end()) {
        if ((*it) == prep) {
            result = true;
        }
        it++;
    }
    return result;
}

// отримання даних про студентів, в яких читає даний викладач
void st() {
    std::string prepod;
    std::cout << "Input name of lecturer: ";
    std::cin >> prepod;
    std::cout << std::endl;

    std::vector<Zachetka> Z;
    File_stud Fs{ "stud_info_28.txt" };
    Z = Fs.get_stud();

    std::vector<Zachetka>::iterator it = Z.begin();
    while (it != Z.end()) {

        if (poisk((*it).lecturers, prepod)) {
            std::cout << "Name: " << (*it).get_name() << "\t" << std::setprecision(3) << "  Sredn: " << (*it).get_sredn() << endl;
        }

        it++;
    }
}

