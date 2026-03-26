#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct Student {
    int id;
    double averageGrade;
    char name[32];
};

void printMemory(const unsigned char* data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        cout << hex << setw(2) << setfill('0')
             << static_cast<int>(data[i]) << ' ';
    }
    cout << dec << '\n';
}

int main() {
    Student s = {12345, 4.75, "Alice"};

    cout << "Байтовое представление Student:\n";
    printMemory(reinterpret_cast<unsigned char*>(&s), sizeof(Student));

    int num = 0x12345678;
    cout << "\nБайты int 0x12345678: ";
    printMemory(reinterpret_cast<unsigned char*>(&num), sizeof(int));

    double pi = 3.14159;
    cout << "Байты double: ";
    printMemory(reinterpret_cast<unsigned char*>(&pi), sizeof(double));

    // запись
    ofstream out("student.bin", ios::binary);
    out.write(reinterpret_cast<char*>(&s), sizeof(Student));
    out.close();

    // чтение
    Student loaded;
    ifstream in("student.bin", ios::binary);
    in.read(reinterpret_cast<char*>(&loaded), sizeof(Student));
    in.close();

    cout << "\nЗагруженный студент: id=" << loaded.id
         << ", grade=" << loaded.averageGrade
         << ", name=" << loaded.name << '\n';
    //reinterpret_cast опасен тем, что он отключает 
    //проверку типов и игнорирует правила выравнивания памяти
    return 0;
}
