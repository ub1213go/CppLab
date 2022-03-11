#include <iostream>
using namespace std;

namespace Udemy {
    class string {
    public:
        static int count;
        static bool develop;
        int id;
        string(const char* str){
            count++;
            id = count;
            if (develop == true) {
                cout << id << " 出生中" << endl;
            }
            int length = strlen(str);
            _str = new char[length + 1];
            for (int i = 0; i < length; i++) {
                _str[i] = str[i];
            }
            _str[length] = '\0';
        }
        string() {
            count++;
            id = count;
            if (develop == true) {
                cout << id << " 出生很乾淨" << endl;
            }
        }
        ~string() {
            if (develop == true) {
                cout << id << " 我被解構了" << endl;
            }
            delete [] _str;
        }

        string& operator=(const string str) {
            if (develop == true) {
                cout << id << " 實體被複製中" << endl;
            }
            delete[] _str;
            int length = strlen(str._str);
            _str = new char[length + 1];
            for (int i = 0; i < length; i++) {
                _str[i] = str._str[i];
            }
            _str[length] = '\0';
            return *this;
        }
        string& operator+(const string& str) {
            if (develop == true) {
                cout << id << " 實體被處理中" << endl;
            }
            string* str_copy = new string();
            int length = strlen(str._str);
            int lengthSelf = strlen(_str);
            int lengthTotal = length + lengthSelf;
            str_copy->_str = new char[length + lengthSelf + 1];
            for (int i = 0; i < lengthTotal; i++) {
                if (i < lengthSelf)
                    str_copy->_str[i] = _str[i];
                else
                    str_copy->_str[i] = str._str[i - lengthSelf];
            }
            str_copy->_str[lengthTotal] = '\0';
            return *str_copy;
        }
        friend ostream& operator<<(ostream& os, const string& str) {
            os << str._str;
            return os;
        }
        void Display() { cout << id << " str: " << _str << endl; }
    private:
        char* _str = nullptr;
    };
    int string::count = 0;
    bool string::develop = false;

    template <class T>
    class Arr2D {
    public:
        int xlength = 0;
        int ylength = 0;
        T** m = nullptr;
        Arr2D(int x, int y) {
            xlength = x;
            ylength = y;
            m = new T* [y] {nullptr};
            for (int i = 0; i < y; i++) {
                m[i] = new T[x] {0};
            }
        }
        ~Arr2D() {
            for (int i = 0; i < ylength; i++) {
                delete [] m[i];
            }
            delete [] m;
        }

        void SetValue(int x, int y, T value) {
            m[x][y] = value;
        }
    };

    class Metrix {
    public:
        Metrix(int x, int y) {
            _arr = new Arr2D<double>(x, y);
        };

        void SetMetrix(const double& arr) {
            for (int i = 0; i < _arr->ylength; i++) {
                for (int j = 0; j < _arr->xlength; j++) {
                    _arr->m[i][j] = *(&arr + i * _arr->xlength + j);
                }
            }
        }

        void GetReduceRowEchelonForm() {
            cout << "reduce row echelonform method start" << endl;

            int x = 0;
            int y = 0;
            int n = 0;
            bool repeat = false;
            string result;
            string repeatStr;
            while (true) {
                if (!(x < _arr->xlength && y < _arr->ylength)) {
                    break;
                }
                n++;
                if (_arr->m[x][y] == 1) {
                    result = "符合";

                    if (repeat == true) {
                        repeatStr = " (運算)";
                    }
                    else {
                        repeatStr = "";
                    }
                    cout << "step " << x + 1 << repeatStr << endl;
                    this->Display();
                    cout << result << endl << endl;

                    x++;
                    y++;

                    repeat = false;
                }
                else {
                    result = "不符合，運算中";

                    if (repeat == true) {
                        repeatStr = " (運算)";
                    }
                    else {
                        repeatStr = "";
                    }
                    cout << "step " << x + 1 << repeatStr << endl;
                    this->Display();
                    cout << result << endl << endl;

                    double divisor = _arr->m[x][y];
                    for (int j = 0; j < _arr->xlength; j++) {
                        if (_arr->m[x][j] == 0 && divisor < 0) {
                            continue;
                        }
                        _arr->m[x][j] = _arr->m[x][j] / divisor;
                    }

                    repeat = true;
                }
                if (n == 10) {
                    break;
                }
            }

        }

        bool CheckTriangular() {
            bool check = true;
            for (int i = 0; i < _arr->ylength; i++) {
                for (int j = 0; j < _arr->xlength; j++) {
                    if (i == j) {
                        if (_arr->m[i][j] != 1) {
                            check = false;
                            break;
                        }
                    }
                    else {
                        if (j != _arr->xlength - 1 && _arr->m[i][j] != 0) {
                            check = false;
                            break;
                        }
                    }
                }
            }
            return check;
        }

        void Display() {
            int temp = 1;
            int length = 1;
            for (int i = 0; i < _arr->ylength; i++) {
                for (int j = 0; j < _arr->xlength; j++) {
                    temp = GetDigits(_arr->m[i][j]);
                    if (length < temp) {
                        length = temp;
                    }
                }
            }

            double val = 0;
            int length2 = 0;
            for (int i = 0; i < _arr->ylength; i++) {
                cout << "[";
                for (int j = 0; j < _arr->xlength; j++) {
                    val = _arr->m[i][j];
                    length2 = GetDigits(val);

                    if (length2 < length) {
                        for (int k = 0; k < length - length2; k++) {
                            cout << " ";
                        }
                    }

                    cout << val;

                    if (j != _arr->xlength - 1)
                        cout << " ";
                }
                cout << "]" << endl;
            }
        }

        ~Metrix() {
            delete _arr;
        }
    private:
        Arr2D<double>* _arr = nullptr;

        int GetDigits(int number) {
            int temp = 1;
            if (number < 0) temp++;
            bool next = number >= 10;
            while (next) {
                temp++;
                number = number / 10;
                next = number >= 10;
            }
            return temp;
        }
    };

}
int main(int argc, char** argv)
{
    Udemy::Metrix m = Udemy::Metrix(4, 3);

    // Argummented Matrix
    // 1 -2  1 |  0
    // 0  2 -8 |  8
    // 5  0 -5 | 10
    double* arr = new double[] {1, -2, 1, 0, 0, 2, -8, 8, 5, 0, -5, 10};

    m.SetMetrix(*arr);

    m.Display();

    try {
        throw "err";
    }
    catch (const char* str) {
        cout << "catch " << str << endl;
    }

    m.GetReduceRowEchelonForm();
}
