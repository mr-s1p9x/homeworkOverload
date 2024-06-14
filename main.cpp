#include <iostream>  // Подключаем библиотеку ввода-вывода
using namespace std; // Используем пространство имен std для упрощения кода

// Определяем класс Date для работы с датами
class Date {
private:
    int day;     // Переменная для хранения дня
    int month;   // Переменная для хранения месяца
    int year;    // Переменная для хранения года

    // Проверка корректности даты
    bool isValidDate(int d, int m, int y) {
        if (m < 1 || m > 12 || d < 1 || y < 0) return false; // Проверяем, что месяц в диапазоне от 1 до 12, день больше 0 и год не отрицательный
        int daysInMonth[] = {31, 28 + (isLeapYear(y) ? 1 : 0), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Массив с количеством дней в каждом месяце, учитывая високосный год
        if (d > daysInMonth[m - 1]) return false; // Проверяем, что день не превышает количество дней в данном месяце
        return true; // Возвращаем true, если дата корректна
    }

    // Проверка на високосный год
    bool isLeapYear(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); // Год високосный, если он кратен 4, но не кратен 100, или кратен 400
    }

    // Увеличение дня с переходом месяца/года
    void incrementDay() {
        int daysInMonth[] = {31, 28 + (isLeapYear(year) ? 1 : 0), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Массив с количеством дней в каждом месяце, учитывая високосный год
        day++; // Увеличиваем день на 1
        if (day > daysInMonth[month - 1]) { // Если день превышает количество дней в текущем месяце
            day = 1; // Устанавливаем день на 1
            month++; // Увеличиваем месяц на 1
            if (month > 12) { // Если месяц превышает 12
                month = 1; // Устанавливаем месяц на 1 (январь)
                year++; // Увеличиваем год на 1
            }
        }
    }

    // Уменьшение дня с переходом месяца/года
    void decrementDay() {
        int daysInMonth[] = {31, 28 + (isLeapYear(year) ? 1 : 0), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Массив с количеством дней в каждом месяце, учитывая високосный год
        day--; // Уменьшаем день на 1
        if (day < 1) { // Если день меньше 1
            month--; // Уменьшаем месяц на 1
            if (month < 1) { // Если месяц меньше 1
                month = 12; // Устанавливаем месяц на 12 (декабрь)
                year--; // Уменьшаем год на 1
            }
            day = daysInMonth[month - 1]; // Устанавливаем день на последний день предыдущего месяца
        }
    }

public:
    // Конструктор по умолчанию
    Date() : day(1), month(1), year(2000) {} // Инициализируем дату 1 января 2000 года

    // Конструктор с параметрами
    Date(int d, int m, int y) {
        if (!isValidDate(d, m, y)) { // Проверяем корректность переданной даты
            throw invalid_argument("Invalid date"); // Если дата некорректна, выбрасываем исключение
        }
        day = d; // Устанавливаем день
        month = m; // Устанавливаем месяц
        year = y; // Устанавливаем год
    }

    // Методы доступа (getters и setters)
    int getDay() const { return day; } // Возвращаем день
    int getMonth() const { return month; } // Возвращаем месяц
    int getYear() const { return year; } // Возвращаем год

    void setDay(int d) {
        if (!isValidDate(d, month, year)) { // Проверяем корректность нового дня
            throw invalid_argument("Invalid day"); // Если день некорректен, выбрасываем исключение
        }
        day = d; // Устанавливаем новый день
    }

    void setMonth(int m) {
        if (!isValidDate(day, m, year)) { // Проверяем корректность нового месяца
            throw invalid_argument("Invalid month"); // Если месяц некорректен, выбрасываем исключение
        }
        month = m; // Устанавливаем новый месяц
    }

    void setYear(int y) {
        if (!isValidDate(day, month, y)) { // Проверяем корректность нового года
            throw invalid_argument("Invalid year"); // Если год некорректен, выбрасываем исключение
        }
        year = y; // Устанавливаем новый год
    }

    // Перегрузка операторов ++ (префиксный и постфиксный)
    Date& operator++() {
        incrementDay(); // Увеличиваем день
        return *this; // Возвращаем текущий объект
    }

    Date operator++(int) {
        Date temp = *this; // Сохраняем текущий объект во временную переменную
        incrementDay(); // Увеличиваем день
        return temp; // Возвращаем временный объект
    }

    // Перегрузка операторов -- (префиксный и постфиксный)
    Date& operator--() {
        decrementDay(); // Уменьшаем день
        return *this; // Возвращаем текущий объект
    }

    Date operator--(int) {
        Date temp = *this; // Сохраняем текущий объект во временную переменную
        decrementDay(); // Уменьшаем день
        return temp; // Возвращаем временный объект
    }

    // Перегрузка операторов + и - (добавление и вычитание дней)
    Date operator+(int days) const {
        Date temp = *this; // Сохраняем текущий объект во временную переменную
        while (days-- > 0) { // Уменьшаем days на 1, пока он не станет 0
            temp.incrementDay(); // Увеличиваем день
        }
        return temp; // Возвращаем временный объект
    }

    Date operator-(int days) const {
        Date temp = *this; // Сохраняем текущий объект во временную переменную
        while (days-- > 0) { // Уменьшаем days на 1, пока он не станет 0
            temp.decrementDay(); // Уменьшаем день
        }
        return temp; // Возвращаем временный объект
    }

    // Перегрузка операторов += и -= (добавление и вычитание дней)
    Date& operator+=(int days) {
        while (days-- > 0) { // Уменьшаем days на 1, пока он не станет 0
            incrementDay(); // Увеличиваем день
        }
        return *this; // Возвращаем текущий объект
    }

    Date& operator-=(int days) {
        while (days-- > 0) { // Уменьшаем days на 1, пока он не станет 0
            decrementDay(); // Уменьшаем день
        }
        return *this; // Возвращаем текущий объект
    }

    // Перегрузка операторов сравнения
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year; // Сравниваем года
        if (month != other.month) return month < other.month; // Если года равны, сравниваем месяцы
        return day < other.day; // Если года и месяцы равны, сравниваем дни
    }

    bool operator>(const Date& other) const {
        return other < *this; // Используем перегруженный оператор < для сравнения
    }

    bool operator<=(const Date& other) const {
        return !(other < *this); // Используем перегруженный оператор < для сравнения
    }

    bool operator>=(const Date& other) const {
        return !(*this < other); // Используем перегруженный оператор < для сравнения
    }

    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day; // Сравниваем года, месяцы и дни
    }

    bool operator!=(const Date& other) const {
        return !(*this == other); // Используем перегруженный оператор == для сравнения
    }

    // Метод для вывода даты
    void print() const {
        cout << day << "/" << month << "/" << year << endl; // Выводим дату в формате день/месяц/год
    }
};

// Функция main для тестирования класса Date
int main() {
    try {
        // Создаем объекты date1 и date2 с использованием конструктора с параметрами
        Date date1(1, 1, 2000); // Создаем объект date1 с датой 1 января 2000 года
        Date date2(31, 12, 1999); // Создаем объект date2 с датой 31 декабря 1999 года

        // Выводим даты
        date1.print(); // Выводим дату date1
        date2.print(); // Выводим дату date2

        // Тестируем префиксный инкремент
        ++date1; // Увеличиваем дату date1 на 1 день
        date1.print(); // Выводим измененную дату date1

        // Тестируем постфиксный декремент
        date2--; // Уменьшаем дату date2 на 1 день
        date2.print(); // Выводим измененную дату date2

        // Тестируем оператор +
        Date date3 = date1 + 30; // Добавляем 30 дней к date1 и сохраняем результат в date3
        date3.print(); // Выводим дату date3

        // Тестируем оператор -
        Date date4 = date1 - 30; // Вычитаем 30 дней из date1 и сохраняем результат в date4
        date4.print(); // Выводим дату date4

        // Тестируем оператор +=
        date1 += 365; // Добавляем 365 дней к date1
        date1.print(); // Выводим измененную дату date1

        // Тестируем оператор -=
        date2 -= 365; // Вычитаем 365 дней из date2
        date2.print(); // Выводим измененную дату date2

        // Тестируем операторы сравнения
        cout << (date1 > date2) << endl; // Выводим результат сравнения date1 и date2 (date1 больше date2)
        cout << (date1 < date2) << endl; // Выводим результат сравнения date1 и date2 (date1 меньше date2)
        cout << (date1 == date2) << endl; // Выводим результат сравнения date1 и date2 (date1 равно date2)
        cout << (date1 != date2) << endl; // Выводим результат сравнения date1 и date2 (date1 не равно date2)

    } catch (const invalid_argument& e) {
        // Обрабатываем исключение, если дата некорректна
        cout << "Exception: " << e.what() << endl; // Выводим сообщение об ошибке
    }

    return 0; // Возвращаем 0 для обозначения успешного завершения программы
}