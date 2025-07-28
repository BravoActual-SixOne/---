#include <iostream>
#include <string>
#include <stdexcept> 
using namespace std;

//bool IsKPeriodic(const string& str, int K)
//{
//    if (K <= 0)
//        throw invalid_argument("Значение K должно быть положительным.");
//
//    if (str.empty())
//        throw invalid_argument("Строка не должна быть пустой.");
//
//    if (K > static_cast<int>(str.length()))
//        throw invalid_argument("Значение K превышает длину строки.");
//
//    if (str.length() % K != 0)
//        return false;
//
//    string pattern = str.substr(0, K);
//
//    for (size_t i = K; i < str.length(); i += K)
//    {
//        if (str.substr(i, K) != pattern)
//            return false;
//    }
//
//    return true;
//}

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Префикс-функция КМП
vector<int> computePrefix(const string& pattern) {
    int m = pattern.length();
    vector<int> prefix(m, 0);
    int k = 0;
    for (int q = 1; q < m; q++) {
        while (k > 0 && pattern[k] != pattern[q])
            k = prefix[k - 1];
        if (pattern[k] == pattern[q])
            k++;
        prefix[q] = k;
    }
    return prefix;
}

// Функция для проверки кратности 
bool isKPeriodicKMP(const string& str, int k) {
    try {
        int n = str.length();

        if (k <= 0 || k > n)
            throw invalid_argument("Неверное значение K");
        if (n % k != 0)
            return false;

        string pattern = str.substr(0, k);
        vector<int> prefix = computePrefix(pattern);

        int q = 0;
        for (int i = 0; i < n; i++) {
            while (q > 0 && pattern[q] != str[i])
                q = prefix[q - 1];
            if (pattern[q] == str[i])
                q++;
            if (q == k) {
                // нашли полное вхождение шаблона
                if ((i - k + 1) % k != 0)
                    return false; // не кратно k — 0
                q = 0; // начинаем искать снова
            }
        }

        return true;
    }
    catch (const exception& ex) {
        cout << "Exception caught: " << ex.what() << endl;
        return false;
    }
}


int main(){
   /* string input = "abcabcabcabc";
    int k = 3;

    try {
        if (IsKPeriodic(input, k) == 1)
            cout << "Строка кратна " << k << "." << endl;
        else
            cout << "Строка НЕ кратна " << k << "." << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;*/

    string s1 = "abcabcabcabc";
    string s2 = "abababc";

    cout << boolalpha << isKPeriodicKMP(s1, 3) << endl; // true
    cout << boolalpha << isKPeriodicKMP(s2, 2) << endl; // false
    cout << boolalpha << isKPeriodicKMP("xxxx", 1) << endl; // true
    cout << boolalpha << isKPeriodicKMP("xyzxyzxy", 3) << endl; // false
    cout << boolalpha << isKPeriodicKMP("z", 0) << endl; // false, ловим exception
}