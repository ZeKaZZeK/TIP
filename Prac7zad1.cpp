#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int i = 65;
    double d = 3.14159;
    float f = 2.71828f;
    char c = 'A';
    bool b = true;

    cout << fixed << setprecision(5);

    double i_to_d = static_cast<double>(i);
    cout << "int → double: " << i << " → " << i_to_d << " (без потерь)\n";

    int d_to_i = static_cast<int>(d);
    cout << "double → int: " << d << " → " << d_to_i << " (потеря дробной части)\n";

    float d_to_f = static_cast<float>(d);
    cout << "double → float: " << d << " → " << d_to_f << " (возможна потеря точности)\n";

    double f_to_d = static_cast<double>(f);
    cout << "float → double: " << f << " → " << f_to_d << " (без потерь)\n";

    int c_to_i = static_cast<int>(c);
    cout << "char → int: '" << c << "' → " << c_to_i << " (ASCII код)\n";

    char i_to_c = static_cast<char>(i);
    cout << "int → char: " << i << " → '" << i_to_c << "'\n";

    int big = 200;
    char big_to_c = static_cast<char>(big);
    cout << "int → char (выход): " << big << " → '" << big_to_c << "' (потеря данных)\n";

    int b_to_i = static_cast<int>(b);
    cout << "bool → int: " << b << " → " << b_to_i << '\n';

    int zero = 0, nonzero = 10;
    bool i_to_b1 = static_cast<bool>(zero);
    bool i_to_b2 = static_cast<bool>(nonzero);
    cout << "int → bool: 0 → " << i_to_b1 << ", 10 → " << i_to_b2 << '\n';

    return 0;
}
