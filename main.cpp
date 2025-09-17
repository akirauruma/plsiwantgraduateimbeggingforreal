#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "gtest/gtest.h"

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};


// Функция для добавления студента в базу данных
void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin >> student.name;
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin >> student.major;
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

// Новая функция — вычисление среднего возраста
double calculateAverageAge(const std::vector<Student>& database) {
    if (database.empty()) {
        throw std::runtime_error("База данных пуста");
    }
    int sum = 0;
    for (const auto& student : database) {
        sum += student.age;
    }
    return static_cast<double>(sum) / database.size();
}

// Функция для вывода всех студентов и среднего возраста
void displayStudents(const std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных пуста\n";
        return;
    }

    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }

    double avg = calculateAverageAge(database);
    std::cout << "Средний возраст всех студентов: " << avg << "\n";
}

// Тест: средний возраст считается правильно
TEST(StudentFunctionsTest, CalculateAverageAge_NormalCase) {
    std::vector<Student> database = {
        {"Ivan", 20, "Math", 4.5},
        {"Anna", 22, "Physics", 4.8},
        {"Petr", 24, "CS", 4.2}
    };
    double avg = calculateAverageAge(database);
    EXPECT_DOUBLE_EQ(avg, 22.0);
}

// Тест: база данных пуста -> выбрасывается исключение
TEST(StudentFunctionsTest, CalculateAverageAge_EmptyDatabase) {
    std::vector<Student> database;
    EXPECT_THROW(calculateAverageAge(database), std::runtime_error);
}

// Тест: если все одного возраста
TEST(StudentFunctionsTest, CalculateAverageAge_SameAge) {
    std::vector<Student> database = {
        {"Ivan", 21, "Math", 4.1},
        {"Anna", 21, "Physics", 4.2},
        {"Petr", 21, "CS", 4.3}
    };
    double avg = calculateAverageAge(database);
    EXPECT_DOUBLE_EQ(avg, 21.0);
}

// Тест: работает с одним студентом
TEST(StudentFunctionsTest, CalculateAverageAge_OneStudent) {
    std::vector<Student> database = {
        {"Ivan", 25, "Math", 4.5}
    };
    double avg = calculateAverageAge(database);
    EXPECT_DOUBLE_EQ(avg, 25.0);
}

// Тест: дробное среднее (пример 2 студента)
TEST(StudentFunctionsTest, CalculateAverageAge_Fractional) {
    std::vector<Student> database = {
        {"Ivan", 20, "Math", 4.5},
        {"Petr", 23, "CS", 4.2}
    };
    double avg = calculateAverageAge(database);
    EXPECT_DOUBLE_EQ(avg, 21.5);
}

// Тест: проверка с большим числом студентов
TEST(StudentFunctionsTest, CalculateAverageAge_LargeDataset) {
    std::vector<Student> database;
    for (int i = 0; i < 100; i++) {
        database.push_back({"Student" + std::to_string(i), 20 + (i % 5), "Major", 4.0});
    }
    double avg = calculateAverageAge(database);
    // Средний возраст должен быть от 20 до 24
    EXPECT_GE(avg, 20.0);
    EXPECT_LE(avg, 24.0);
}

void view() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
        view();
        return 0;
    }
}
