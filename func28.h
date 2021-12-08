#pragma once
#ifndef FUNC28_H
#define FUNC28_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <nlohmann/json.hpp>

// file func28.cpp
// Реалізація методів классів та функцій
// Виконав студент гр. Компмат - 2
// А.В. Немирович


using namespace std;

// класс Людина - базовий
class Person {

private:

    string name; //ім'я людини

public:

    nlohmann::json j{}; //об'єкт для роботи з json

    //конструктор
    Person(string _name) : name(_name) {}

    //отримати ім'я
    string get_name() { return name; }

    //встановити ім'я
    void set_name(string name);

    //введення
    virtual void input();

    //виведення
    virtual void print();

    //виведення у json
    void ins();

    // виведення оператором <<
    friend ostream& operator<<(ostream& out, Person& p) {
        p.print();
        return out;
    }

};

// класс Студент
class Student : public Person {
private:
    float sredn = 0.0;
    int course;
    vector<int> marks;

public:
    float sch_sh = 0.0;
     // конструктор 
    Student(string _name, vector<int> _marks, int _course = 1) :
        Person(_name), marks(_marks), course(_course) {}

    //введення оцінок
    vector<int> input_vec();

    //обчислення середнього балу
    float sr();

    //обчислення стипендії
    void stipend();

    // отримати середній бал
    float get_sredn() { return sr(); }
    //void set_marks(float _sredn) {this->sredn = sredn;}
    
    // отримати номер курсу
    int& get_course() { return course; }

    // встановити курс
    void set_course(int course) { this->course = course; }

    // встановити стипендію (для введення з файлу)
    void set_stip(float _stip);

    // виведення полів
    virtual void input();

    //введення
    virtual void print();

    // виведення json
    void ins();
};

// класс Заліковка

class Zachetka : public Student {

public:
    vector<string> discipl; //дисципліни
    vector<string> lecturers; //викладачі

    //конструктор
    Zachetka(string _name, vector<int> _marks, vector<string> _discipl, vector<string> _lecturers, int _course = 1) :
        Student(_name, _marks, _course), lecturers(_lecturers), discipl(_discipl) {}

    //введення викладачів
    //приймається послідовність рядків ДО 0
    vector<string> input_prep();

    //отримати вектор з викладачами
    vector<string> get_lect() { return lecturers; }

    //введення дисциплін
    //приймається послідовність рядків ДО 0
    vector<string> input_disc();

    // виведення json
    void ins();
};

//описуємо класси для співробітників/викладачів

class Employee : public Person {
public:
    double oklad;
    int stazh;

    //конструктор
    Employee(string _name, double _oklad = 1000, int _stazh = 0) :
        Person(_name), oklad(_oklad), stazh(_stazh) {}

    // отримати оклад
    double get_oklad() { return oklad; }

    //встановити оклад
    void set_oklad(double oklad) { this->oklad = oklad; }

    //отримати стаж
    double get_stazh() { return stazh; }

    //встановити стаж
    void set_stazh(double _stazh) { this->stazh = _stazh; }

    //введення значень для полів 
    virtual void input();

    //введення полів
    virtual void print();

    // виведення json
    void ins();
};

// виведення json

class Lecturer : public Employee {
private:
    //float koef;
    string step;
    float salary = 0.0;
public:
    //конструктор
    Lecturer(string _name, double _oklad = 1000, int _stazh = 0, string _step = "") :
        Employee(_name, _oklad, _stazh), step(_step) {}

    //отримати степінь
    string get_step() { return step; }

    //отримати зарплату
    float get_salary() { return salary; }
    
    //встановити степінь
    void set_step(string step) { this->step = step; }

    //обрахувати зарплату
    void cal_s();

    //введення
    virtual void input();

    //виведення аналогічно до попередніх
    virtual void print();

    // виведення json
    void ins();
};

//класс Спеціаліст

class Specialist : public Lecturer {
public:
    string spec;

    //конструктор
    Specialist(string _name, double _oklad = 1000, int _stazh = 0, string _step = "employee", string _spec = "none") :
        Lecturer(_name, _oklad, _stazh, _step), spec(_spec) {}

    //введення спеціальності
    virtual void input();

    //виведення спеціальності
    virtual void print();

    // виведення json
    void ins();
};

//класс для роботи з массивом студентів та файлом

class File_stud {

private:
    string filename; //ім'я файлу

public:
    //конструктор
    File_stud(string _filename) :
        filename(_filename) {}

    //введення інформації про n студентів в файл в json
    void input_stud_information();

    //додавання одного студента в json
    void add_stud_information(); 

    //видалення одного студента
    void del_stud(string name);

    //отримати вектор заліковок
    vector<Zachetka> get_stud();
};

//класс для роботи з массивом викладачів

class File_lect {
private:
    string filename; 
public:
    //конструктор
    File_lect(string _filename) :
        filename(_filename) {}

    //введення інформації про n викладачів в файл в json
    void input_lect();

    //додавання одного викладача в json
    void add_lect_info();

    //видалення одного викладача
    void del_lect(string name);

    //отримати вектор спеціалістів
    vector<Specialist> get_lect();
};

// функція наявності рядка у векторі з рядків
bool poisk(std::vector<std::string> N, std::string prep);

// отримання даних про студентів, в яких читає даний викладач
void st();




#endif