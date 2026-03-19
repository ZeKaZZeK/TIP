#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;
    
    Node(int value) : data(value), next(nullptr), prev(nullptr) {
        cout << "Создан узел с данными: " << data << endl;
    }
    
    ~Node() {
        cout << "Удален узел с данными: " << data << endl;
    }
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    int count;
    
public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    // Деструктор: ручное удаление всех узлов
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        cout << "Список удален" << endl;
    }
    
    void pushBack(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;  // Устанавливаем обратную связь
            tail = newNode;
        }
        count++;
    }
    
    void pushFront(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        count++;
    }
    
    void popBack() {
        if (tail == nullptr) return;
        
        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;  // Новый хвост - предыдущий элемент
            tail->next = nullptr;
        }
        delete temp;  // Освобождаем память
        count--;
    }
    
    void popFront() {
        if (head == nullptr) return;
        
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;  // Новая голова - следующий элемент
            head->prev = nullptr;
        }
        delete temp;  // Освобождаем память
        count--;
    }
    
    void printForward() {
        cout << "Список (с начала): ";
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    // Печать с конца по обратным указателям
    void printBackward() {
        cout << "Список (с конца): ";
        Node* current = tail;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
    
    int getCount() {
        return count;
    }
};

int main() {
    cout << "=== Тестирование двусвязного списка ===" << endl;
    
    LinkedList list;
    
    cout << "\nДобавляем элементы:" << endl;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushFront(5);
    list.pushFront(1);
    
    cout << "\nКоличество элементов: " << list.getCount() << endl;
    
    cout << "\nВывод списка:" << endl;
    list.printForward();
    list.printBackward();
    
    cout << "\nУдаляем элементы:" << endl;
    list.popFront();
    list.popFront();
    list.popBack();
    
    cout << "\nИтоговый список:" << endl;
    list.printForward();
    list.printBackward();
    cout << "Количество элементов: " << list.getCount() << endl;
    
    cout << "\nЗавершение программы:" << endl;
    return 0;
}
