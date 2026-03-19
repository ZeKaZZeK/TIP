#include <iostream>
using namespace std;

class Connection {
private:
    int id;
    bool inUse;
    
public:
    Connection(int connectionId) : id(connectionId), inUse(false) {
        cout << "Создано соединение #" << id << endl;
    }
    
    ~Connection() {
        cout << "Удалено соединение #" << id << endl;
    }
    
    void connect() {
        inUse = true;
        cout << "Соединение #" << id << " активировано" << endl;
    }
    
    void disconnect() {
        inUse = false;
        cout << "Соединение #" << id << " деактивировано" << endl;
    }
    
    // Проверка доступности по флагу
    bool isAvailable() {
        return !inUse;
    }
    
    int getId() {
        return id;
    }
};

class ConnectionPool {
private:
    Connection** pool;  // Динамический массив указателей
    int poolSize;
    
public:
    ConnectionPool(int size) : poolSize(size) {
        pool = new Connection*[poolSize];
        
        for (int i = 0; i < poolSize; i++) {
            pool[i] = new Connection(i + 1);
        }
        
        cout << "Создан пул из " << poolSize << " соединений" << endl;
    }
    
    // Деструктор: удаляем все объекты и массив
    ~ConnectionPool() {
        for (int i = 0; i < poolSize; i++) {
            delete pool[i];
        }
        delete[] pool;
        cout << "Пул соединений уничтожен" << endl;
    }
    
    // Поиск первого свободного соединения
    Connection* acquireConnection() {
        for (int i = 0; i < poolSize; i++) {
            if (pool[i]->isAvailable()) {
                pool[i]->connect();
                return pool[i];
            }
        }
        
        cout << "Нет доступных соединений!" << endl;
        return nullptr;
    }
    
    // Возврат соединения в пул
    void releaseConnection(Connection* conn) {
        if (conn != nullptr) {
            conn->disconnect();
        }
    }
    
    void printStatus() {
        cout << "Статус соединений:" << endl;
        for (int i = 0; i < poolSize; i++) {
            cout << "  Соединение #" << pool[i]->getId() 
                 << " - " << (pool[i]->isAvailable() ? "свободно" : "используется") 
                 << endl;
        }
    }
};

int main() {
    cout << "=== Тестирование пула соединений ===" << endl;
    
    ConnectionPool pool(3);
    cout << endl;
    
    cout << "Запрашиваем 2 соединения:" << endl;
    Connection* conn1 = pool.acquireConnection();
    Connection* conn2 = pool.acquireConnection();
    cout << endl;
    
    pool.printStatus();
    cout << endl;
    
    cout << "Возвращаем соединения:" << endl;
    pool.releaseConnection(conn1);
    pool.releaseConnection(conn2);
    cout << endl;
    
    pool.printStatus();
    cout << endl;
    
    cout << "Запрашиваем 3 соединения:" << endl;
    conn1 = pool.acquireConnection();
    conn2 = pool.acquireConnection();
    Connection* conn3 = pool.acquireConnection();
    cout << endl;
    
    pool.printStatus();
    cout << endl;
    
    cout << "Пробуем запросить четвертое соединение:" << endl;
    Connection* conn4 = pool.acquireConnection();
    cout << endl;
    
    cout << "Возвращаем одно и запрашиваем снова:" << endl;
    pool.releaseConnection(conn2);
    conn4 = pool.acquireConnection();
    cout << endl;
    
    pool.printStatus();
    cout << endl;
    
    cout << "Возвращаем все соединения:" << endl;
    pool.releaseConnection(conn1);
    pool.releaseConnection(conn3);
    pool.releaseConnection(conn4);
    cout << endl;
    
    cout << "Завершение программы:" << endl;
    return 0;
}
