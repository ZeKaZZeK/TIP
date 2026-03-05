#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// ЗАДАЧА 1 (Инкапсуляция) — Матрица
class Matrix {
private:
    vector<vector<int>> data;
    int rows, cols;
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(r, vector<int>(c, 0));
    }
    int get(int r, int c) {
        if(r < 0 || r >= rows || c < 0 || c >= cols) return -1;
        return data[r][c];
    }
    void set(int r, int c, int val) {
        if(r >= 0 && r < rows && c >= 0 && c < cols)
            data[r][c] = val;
    }
    void operator=(const Matrix& other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data;
    }
    Matrix transpose() {
        Matrix res(cols, rows);
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                res.data[j][i] = data[i][j];
        return res;
    }
    void print() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++)
                cout << data[i][j] << " ";
            cout << endl;
        }
    }
};

void task1() {
    cout << "\n=== ЗАДАЧА 1: Матрица ===" << endl;
    Matrix m(2, 3);
    m.set(0, 0, 5);
    m.set(1, 2, 9);
    cout << "Исходная матрица:" << endl;
    m.print();
    Matrix m2 = m;
    Matrix m3 = m2.transpose();
    cout << "Транспонированная:" << endl;
    m3.print();
}

// ЗАДАЧА 2 (Наследование 1) — Библиотека
class LibraryItem {
protected:
    string title;
    bool isTaken;
public:
    LibraryItem(string t) : title(t), isTaken(false) {}
    virtual void show() { cout << title << " - " << (isTaken ? "Выдана" : "В наличии") << endl; }
    void take() { isTaken = true; }
    void ret() { isTaken = false; }
};
class Book : public LibraryItem {
    int pages;
public:
    Book(string t, int p) : LibraryItem(t), pages(p) {}
    void show() { cout << "Книга: " << title << ", " << pages << " стр." << endl; }
};
class Magazine : public LibraryItem {
    int issue;
public:
    Magazine(string t, int i) : LibraryItem(t), issue(i) {}
    void show() { cout << "Журнал: " << title << ", Выпуск " << issue << endl; }
};
class Catalog {
    vector<LibraryItem*> items;
public:
    void add(LibraryItem* item) { items.push_back(item); }
    void showAll() { for(auto item : items) item->show(); }
};
void task2() {
    cout << "\n=== ЗАДАЧА 2: Библиотека ===" << endl;
    Catalog lib;
    Book b("Гарри Поттер", 300);
    Magazine m("Нэшнл Гео", 5);
    lib.add(&b);
    lib.add(&m);
    cout << "Каталог:" << endl;
    lib.showAll();
    cout << "\nВыдаем книгу..." << endl;
    b.take();
    lib.showAll();
}

// ЗАДАЧА 3 (Наследование 2) — Персонал [ИСПРАВЛЕНО]
class Employee {
protected:
    string name;
    double salary;
public:
    Employee(string n, double s) : name(n), salary(s) {}
    virtual double getBonus() { return salary * 0.1; }
    void raise(double p) { salary += salary * p / 100; }
    virtual void show() { cout << name << " - " << salary << " руб." << endl; }
    double getSalary() const { return salary; }
};
class Manager : public Employee {
public:
    Manager(string n, double s) : Employee(n, s) {}
    double getBonus() { return salary * 0.2; }
    void show() { cout << "Менеджер: " << name << " - " << salary << " руб." << endl; }
};
class Developer : public Employee {
public:
    Developer(string n, double s) : Employee(n, s) {}
    double getBonus() { return salary * 0.15; }
    void show() { cout << "Разработчик: " << name << " - " << salary << " руб." << endl; }
};
class HR {
    vector<Employee*> staff;
public:
    void add(Employee* e) { staff.push_back(e); }
    void review() {
        for(auto e : staff) {
            e->show();
            cout << "  Премия: " << e->getBonus() << " руб." << endl;
            e->raise(5);
            cout << "  Зарплата после повышения: " << e->getSalary() << " руб." << endl;
        }
    }
};
void task3() {
    cout << "\n=== ЗАДАЧА 3: Персонал ===" << endl;
    HR hr;
    Manager m("Анна", 100000);
    Developer d("Борис", 80000);
    hr.add(&m);
    hr.add(&d);
    cout << "Аттестация сотрудников:" << endl;
    hr.review();
}

// ЗАДАЧА 4 (Полиморфизм) — Платежи
class PaymentMethod {
public:
    virtual bool pay(double amount) = 0;
    virtual string info() = 0;
};
class Card : public PaymentMethod {
    string num;
public:
    Card(string n) : num(n) {}
    bool pay(double amount) { return amount <= 10000; }
    string info() { return "Карта *" + num; }
};
class Cash : public PaymentMethod {
public:
    bool pay(double amount) { return true; }
    string info() { return "Наличные"; }
};
class PaymentSystem {
    vector<string> history;
public:
    void process(PaymentMethod* p, double amount) {
        bool ok = p->pay(amount);
        string status = ok ? "УСПЕХ" : "ОТКАЗ";
        history.push_back(p->info() + ": " + to_string((int)amount) + " руб. - " + status);
    }
    void showHistory() {
        cout << "История платежей:" << endl;
        for(auto h : history) cout << "  " << h << endl;
    }
};
void task4() {
    cout << "\n=== ЗАДАЧА 4: Платежи ===" << endl;
    PaymentSystem sys;
    Card c("4567");
    Cash cash;
    sys.process(&c, 5000);
    sys.process(&c, 20000);
    sys.process(&cash, 20000);
    sys.showHistory();
}

// ЗАДАЧА 5 (Абстракция) — Геометрия
struct Point {
    double x, y, z;
    Point(double x_=0, double y_=0, double z_=0) : x(x_), y(y_), z(z_) {}
};
class GeometryCalculator {
public:
    virtual double distance(Point p1, Point p2) = 0;
};
class Calc2D : public GeometryCalculator {
public:
    double distance(Point p1, Point p2) {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        return sqrt(dx*dx + dy*dy);
    }
};
class Calc3D : public GeometryCalculator {
public:
    double distance(Point p1, Point p2) {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        double dz = p1.z - p2.z;
        return sqrt(dx*dx + dy*dy + dz*dz);
    }
};
void task5() {
    cout << "\n=== ЗАДАЧА 5: Геометрия ===" << endl;
    Calc2D c2d;
    Calc3D c3d;
    Point a(0, 0, 0);
    Point b(3, 4, 0);
    Point c(0, 0, 5);
    cout << "2D расстояние A-B: " << c2d.distance(a, b) << endl;
    cout << "3D расстояние A-B: " << c3d.distance(a, b) << endl;
    cout << "3D расстояние A-C (по Z): " << c3d.distance(a, c) << endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    task1();
    task2();
    task3();
    task4();
    task5();
    cout << "\n=== Все задачи выполнены ===" << endl;
    return 0;
}
