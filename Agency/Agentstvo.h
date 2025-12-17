#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include<stdlib.h>

class Soiskatel {
public:
    std::string name;
    int age;
    bool education;
    int experience;
    std::string sector;
    std::string email;
    bool isBooked;          // Забронирован ли соискатель
    std::string bookedBy;   // Кем забронирован (логин пользователя)

    Soiskatel(std::string n, int a, bool edu, int exp, std::string s, std::string e)
        : name(n), age(a), education(edu), experience(exp), sector(s), email(e),
        isBooked(false), bookedBy("") {
    }
};
class Agentstvo {
public:
    std::vector<Soiskatel> soiskateli;
    void addSoiskatel();//
    void showSoiskateli();//
    void updateSoiskatel(int index);//
    void deleteSoiskatel(int index);//
    void searchBySector(const std::string& sector);//
    void searchByOpyt(int minexp);//
    void searchByEducation(bool educ);//
    void searchPo();//
    void saveToFile();//
    void loadFromFile();//
    void bookSoiskatel(int index, const std::string& username);  // Бронирование
    void unbookSoiskatel(int index);                            // Отмена брони
    void showBookedSoiskateli(const std::string& username);     // Показать забронированных
    bool isBookedByUser(int index, const std::string& username);// Проверка брони
};
