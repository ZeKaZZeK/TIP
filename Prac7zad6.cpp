#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

class Event {
public:
    virtual ~Event() = default;
};

class MouseEvent : public Event {
public:
    int x, y;
    MouseEvent(int x, int y) : x(x), y(y) {}
};

class KeyboardEvent : public Event {
public:
    int keyCode;
    KeyboardEvent(int code) : keyCode(code) {}
};

class WindowEvent : public Event {
public:
    int windowId;
    WindowEvent(int id) : windowId(id) {}
};

void handleEvent(Event* event) {
    cout << "Тип события: " << typeid(*event).name();

    if (typeid(*event) == typeid(MouseEvent)) {
        MouseEvent* me = static_cast<MouseEvent*>(event);
        cout << " (MouseEvent) x=" << me->x << ", y=" << me->y;
      
    } else if (typeid(*event) == typeid(KeyboardEvent)) {
        KeyboardEvent* ke = static_cast<KeyboardEvent*>(event);
        cout << " (KeyboardEvent) key=" << ke->keyCode;
      
    } else if (typeid(*event) == typeid(WindowEvent)) {
        WindowEvent* we = static_cast<WindowEvent*>(event);
        cout << " (WindowEvent) id=" << we->windowId;
    }
    cout << '\n';
}

int main() {
    vector<Event*> events = {
        new MouseEvent(100, 200),
        new KeyboardEvent(65),
        new WindowEvent(42)
    };

    for (Event* e : events) {
        handleEvent(e);
        delete e;
    }

    // cравнение type_info
    MouseEvent m1(0,0), m2(1,1);
    if (typeid(m1) == typeid(m2))
        cout << "m1 и m2 одного типа\n";

    if (typeid(m1) != typeid(KeyboardEvent(0)))
        cout << "Разные типы\n";

    return 0;
}
