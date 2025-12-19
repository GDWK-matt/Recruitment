#include "agentstvo.h"

void Agentstvo::addSoiskatel() {
    std::string name, sector, email;
    int age, experience;
    bool education;
    int eduInput;

    std::cout << "Введите имя: ";
    std::cin >> name;
    std::cout << "Введите возраст: ";
    while (!(std::cin >> age) || age >= 70 || age < 18) {
        std::cout << "Ошибка ввода. Введите целое число для возраста (18-70 лет): ";
        std::cin.clear();
        while (std::cin.get() != '\n') continue;
    }

    std::cout << "Высшее образование? (1 - Да, 0 - Нет): ";
    while (!(std::cin >> eduInput) || (eduInput != 0 && eduInput != 1)) {
        std::cout << "Ошибка ввода. Введите 1 (Да) или 0 (Нет): ";
        std::cin.clear();
        while (std::cin.get() != '\n') continue;
    }
    education = (eduInput == 1);

    std::cout << "Введите опыт работы в годах: ";
    while (!(std::cin >> experience) || (experience > age - 16) || (experience < 0)) {
        std::cout << "Ошибка ввода (опыт не может превышать время от возможной работы (с 16 лет)): ";
        std::cin.clear();
        while (std::cin.get() != '\n') continue;
    }

    std::cout << "Введите должность: ";
    std::cin >> sector;
    std::cout << "Введите email: ";
    std::cin >> email;

    Soiskatel newSoiskatel(name, age, education, experience, sector, email);
    soiskateli.push_back(newSoiskatel);
    saveToFile();
    std::cout << std::string(100, '=') << "\n";
    std::cout << "Соискатель успешно добавлен!\n";
    std::cout << std::string(100, '=') << "\n";
}

void Agentstvo::showSoiskateli() {
    if (soiskateli.empty()) {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "Нет соискателей для отображения.\n";
        std::cout << std::string(100, '=') << "\n";
        return;
    }

    std::sort(soiskateli.begin(), soiskateli.end(), [](const Soiskatel& a, const Soiskatel& b) {
        if (a.sector == b.sector) {
            return a.experience > b.experience;
            return a.education > b.education;
        }
        return a.sector < b.sector;
        });

    std::cout << std::left << std::setw(6) << "#"
        << std::setw(15) << "Имя"
        << std::setw(10) << "Возраст"
        << std::setw(18) << "Высш. Образов."
        << std::setw(10) << "Опыт"
        << std::setw(20) << "Должность"
        << std::setw(30) << "Email" << "\n";

    std::cout << std::string(100, '=') << "\n";

    for (size_t i = 0; i < soiskateli.size(); ++i) {
        const Soiskatel& s = soiskateli[i];
        std::cout << std::left << std::setw(6) << i + 1
            << std::setw(15) << s.name
            << std::setw(10) << s.age
            << std::setw(18) << (s.education ? "Да" : "Нет")
            << std::setw(10) << s.experience
            << std::setw(20) << s.sector
            << std::setw(30) << s.email
            << std::setw(10) << (s.isBooked ? "Забронирован" : "Свободен") << "\n";
        std::cout << std::string(100, '_') << "\n";
    }
}

void Agentstvo::updateSoiskatel(int index) {
    if (index < 0 || index >= soiskateli.size()) {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "Неверный индекс соискателя!\n";
        std::cout << std::string(100, '=') << "\n";
        return;
    }

    Soiskatel& s = soiskateli[index];
    while (true) {
        int ch;
        std::cout << "\nВыберите, что изменить:\n";
        std::cout << "1. Имя\n";
        std::cout << "2. Возраст\n";
        std::cout << "3. Высшее образование\n";
        std::cout << "4. Опыт работы\n";
        std::cout << "5. Должность\n";
        std::cout << "6. Эл. почта\n";
        std::cout << "7. Назад\n";
        std::cout << "Выбор: ";
        std::cin >> ch;
        if (ch == 7) break;

        switch (ch) {
        case 1: {
            std::cout << "Введите новое имя: ";
            std::cin >> s.name;
            break;
        }
        case 2: {
            int newAge;
            std::cout << "Введите новый возраст: ";
            while (!(std::cin >> newAge) || newAge >= 70 || newAge <= 18) {
                std::cout << "Ошибка ввода. Введите возраст от 18-70 лет: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            s.age = newAge;
            break;
        }
        case 3: {
            int eduInput;
            std::cout << "Высшее образование? (1 - Да, 0 - Нет): ";
            while (!(std::cin >> eduInput) || (eduInput != 0 && eduInput != 1)) {
                std::cout << "Ошибка ввода. Введите 1 (Да) или 0 (Нет): ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            s.education = (eduInput == 1);
            break;
        }
        case 4: {
            int newExperience;
            std::cout << "Введите новый опыт работы: ";
            while (!(std::cin >> newExperience) || newExperience > s.age - 18) {
                std::cout << "Ошибка ввода. Опыт не может превышать время от возможного началаработы (с 18 лет): ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            s.experience = newExperience;
            break;
        }
        case 5: {
            std::cout << "Введите новую должность (с ЗАГЛАВНОЙ буквы!): ";
            std::cin >> s.sector;
            break;
        }
        case 6: {
            std::cout << "Введите новую эл. почту: ";
            std::cin >> s.email;
            break;
        }

        default:
            std::cout << "Неверный выбор. Попробуйте еще раз!\n";
            return;
        }
        std::cout << std::string(100, '=') << "\n";
        std::cout << "Данные успешно изменены!\n";
        std::cout << std::string(100, '=') << "\n";
        saveToFile();
    }
}
void Agentstvo::deleteSoiskatel(int index) {
    if (index >= 0 && index < soiskateli.size()) {
        soiskateli.erase(soiskateli.begin() + index);
        saveToFile();
        std::cout << std::string(100, '=') << "\n";
        std::cout << "Соискатель успешно удален.\n";
        std::cout << std::string(100, '=') << "\n";
    }
    else {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "Неверный индекс\n";
        std::cout << std::string(100, '=') << "\n";
    }
}

void Agentstvo::searchBySector(const std::string& sector) {
    bool found = false;
    std::cout << std::left << std::setw(15) << "Имя"
        << std::setw(10) << "Возраст"
        << std::setw(18) << "Выс. Образов."
        << std::setw(10) << "Опыт"
        << std::setw(20) << "Должность"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(100, '=') << "\n";
    for (const auto& s : soiskateli) {
        if (s.sector.find(sector) != std::string::npos) {
            std::cout << std::left << std::setw(15) << s.name
                << std::setw(10) << s.age
                << std::setw(18) << (s.education ? "Да" : "Нет")
                << std::setw(10) << s.experience
                << std::setw(20) << s.sector
                << std::setw(30) << s.email << "\n";
            found = true;
            std::cout << std::string(100, '_') << "\n";
            std::cout << "\n";

        }

    }
    if (!found) {
        std::cout << "\nСоискатели с должностью " << sector << " не найдены.\n";
        std::cout << std::string(100, '_') << "\n";
        std::cout << "\n";
    }

}

void Agentstvo::searchByOpyt(int minexp) {
    bool found = false;
    std::cout << std::left << std::setw(15) << "Имя"
        << std::setw(10) << "Возраст"
        << std::setw(18) << "Выс. Образов."
        << std::setw(10) << "Опыт"
        << std::setw(20) << "Должность"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(100, '=') << "\n";
    for (const auto& s : soiskateli) {
        if (s.experience >= minexp) {
            std::cout << std::left << std::setw(15) << s.name
                << std::setw(10) << s.age
                << std::setw(18) << (s.education ? "Да" : "Нет")
                << std::setw(10) << s.experience
                << std::setw(20) << s.sector
                << std::setw(30) << s.email << "\n";
            found = true;
            std::cout << std::string(100, '_') << "\n";
        }
    }
    if (!found) {
        std::cout << "\nСоискатели с опытом работы от " << minexp << " не найдены.\n";
        std::cout << std::string(100, '_') << "\n";
        std::cout << "\n";

    }
}

void Agentstvo::searchByEducation(bool educ) {
    bool found = false;
    std::cout << std::left << std::setw(15) << "Имя"
        << std::setw(10) << "Возраст"
        << std::setw(18) << "Выс. Образов."
        << std::setw(10) << "Опыт"
        << std::setw(20) << "Должность"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(100, '=') << "\n";

    for (const auto& s : soiskateli) {
        if (s.education == educ) {
            std::cout << std::left << std::setw(15) << s.name
                << std::setw(10) << s.age
                << std::setw(18) << (s.education ? "Да" : "Нет")
                << std::setw(10) << s.experience
                << std::setw(20) << s.sector
                << std::setw(30) << s.email << "\n";
            found = true;
            std::cout << std::string(100, '_') << "\n";
            std::cout << "\n";

        }
    }

    if (!found) {
        std::cout << "Соискатели " << (educ ? "с" : "без") << " выс. образов. не найдено\n";
        std::cout << std::string(100, '_') << "\n";
    }
}

void Agentstvo::searchPo() {

    int vib;
    while (true) {
        std::cout << std::string(100, '=') << "\n";
        std::cout << "Выберите поиск:\n";
        std::cout << "1. Должность\n";
        std::cout << "2. Наличие выс. образован.\n";
        std::cout << "3. Минимальный опыт работы\n";
        std::cout << "4. Назад\n";

        std::cout << "Выбор: ";
        while (!(std::cin >> vib) || (vib < 1 || vib > 4)) {
            std::cout << "Ошибка ввода. Пожалуйста, введите 1, 2, 3 или 4: ";
            std::cin.clear();
            while (std::cin.get() != '\n') continue;
        }
        std::cout << "\n";
        if (vib == 4) break;

        switch (vib) {
        case 1: {
            std::string sector;
            std::cout << "Введите должность (Название должности вводите с ЗАГЛАВНОЙ буквы!): ";
            std::cin >> sector;
            std::cout << "\n";
            searchBySector(sector);
            break;
        }
        case 2: {
            bool educ;
            int edu;
            std::cout << "Да (1) | Нет (0): ";
            std::cin >> edu;
            while (!(std::cin >> edu) || (edu != 0 && edu != 1)) {
                std::cout << "Ошибка ввода. Введите 1 (Да) или 0 (Нет): ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            std::cout << "\n";
            educ = (edu == 1);
            searchByEducation(educ);
            break;
        }
        case 3: {
            int minexp;
            std::cout << "Введите минимальный опыт работы: ";
            std::cin >> minexp;
            while (!(std::cin >> minexp) || minexp < 0) {
                std::cout << "Ошибка ввода. Пожалуйста, введите значение не меньше 0: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            std::cout << "\n";
            searchByOpyt(minexp);
            break;
        }
        default:
            std::cout << "Неправильный выбор. Попробуйте еще раз.\n";
            std::cout << std::string(100, '=') << "\n";
            return;
        }
    }
}

void Agentstvo::saveToFile() {
    std::ofstream file("soiskateli.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!\n";
        return;
    }

    for (const auto& s : soiskateli) {
        file << s.name << '\n'
            << s.age << '\n'
            << s.education << '\n'
            << s.experience << '\n'
            << s.sector << '\n'
            << s.email << '\n'
            << s.isBooked << '\n'
            << s.bookedBy << '\n';
    }
    file.close();
}

void Agentstvo::loadFromFile() {
    std::ifstream file("soiskateli.txt");
    if (!file.is_open()) {
        std::cout << "Файл данных не найден, будет создан новый при сохранении.\n";
        return;
    }

    soiskateli.clear();
    std::string line;

    while (std::getline(file, line)) { // Читаем имя
        if (line.empty()) continue;

        Soiskatel s(line, 0, false, 0, "", "");

        // Читаем возраст
        std::getline(file, line);
        s.age = std::stoi(line);

        // Читаем образование
        std::getline(file, line);
        s.education = (line == "1");

        // Читаем опыт
        std::getline(file, line);
        s.experience = std::stoi(line);

        // Читаем должность
        std::getline(file, s.sector);

        // Читаем email
        std::getline(file, s.email);

        // Читаем статус брони
        std::getline(file, line);
        s.isBooked = (line == "1");

        // Читаем кто забронировал
        std::getline(file, s.bookedBy);

        soiskateli.push_back(s);
    }
    file.close();
}

// Бронирование соискателя
void Agentstvo::bookSoiskatel(int index, const std::string& username) {
    if (index >= 0 && index < soiskateli.size()) {
        if (!soiskateli[index].isBooked) {
            soiskateli[index].isBooked = true;
            soiskateli[index].bookedBy = username;
            saveToFile(); // Сохраняем изменения сразу
            std::cout << "Соискатель успешно забронирован!\n";
        }
        else {
            std::cout << "Этот соискатель уже забронирован!\n";
        }
    }
    else {
        std::cout << "Неверный индекс соискателя!\n";
    }
}

// Отмена брони
void Agentstvo::unbookSoiskatel(int index) {
    if (index >= 0 && index < soiskateli.size()) {
        soiskateli[index].isBooked = false;
        soiskateli[index].bookedBy = "";
        saveToFile(); // Сохраняем изменения сразу
        std::cout << "Бронь успешно отменена!\n";
    }
    else {
        std::cout << "Неверный индекс соискателя!\n";
    }
}

// Показать забронированных текущим пользователем
void Agentstvo::showBookedSoiskateli(const std::string& username) {
    bool found = false;

    std::cout << std::left << std::setw(6) << "#"
        << std::setw(15) << "Имя"
        << std::setw(20) << "Должность"
        << std::setw(30) << "Email" << "\n";
    std::cout << std::string(100, '=') << "\n";

    for (size_t i = 0; i < soiskateli.size(); ++i) {
        if (soiskateli[i].isBooked && soiskateli[i].bookedBy == username) {
            std::cout << std::left << std::setw(6) << i + 1
                << std::setw(15) << soiskateli[i].name
                << std::setw(20) << soiskateli[i].sector
                << std::setw(30) << soiskateli[i].email << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "У вас нет забронированных соискателей.\n";
    }
    std::cout << std::string(100, '=') << "\n";
}

// Проверка, забронирован ли соискатель текущим пользователем
bool Agentstvo::isBookedByUser(int index, const std::string& username) {
    if (index >= 0 && index < soiskateli.size()) {
        return soiskateli[index].isBooked && soiskateli[index].bookedBy == username;
    }
    return false;
}