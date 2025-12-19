#include "Menu.h"

void Menu::adminMenu(Agentstvo& agency, AuthSystem& auth) {
    while (true) {
        system("cls");
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "\n ____|МЕНЮ АДМИНИСТРАТОРА|____\n"
            << "1. Показать всех соискателей\n"
            << "2. Добавить соискателя\n"
            << "3. Поиск по критериям\n"
            << "4. Удалить соискателя\n"
            << "5. Изменить данные\n"
            << "6. Показать всех пользователей\n"
            << "7. Добавить нового пользователя\n"
            << "8. Удалить пользователя\n"
            << "9. Выход\n"
            << "Выбор: ";

        int choice;
        while (!(std::cin >> choice)  (choice < 1  choice > 9)) {
            std::cout << "Ошибка ввода. Пожалуйста, введите 1 - 9: ";
            std::cin.clear();
            while (std::cin.get() != '\n') continue;
        }
        if (choice == 9) {
            system("cls");
            break;
        }

        switch (choice) {
        case 1: {
            system("cls");
            std::cout << std::string(100, '=') << "\n";
            agency.showSoiskateli();
            std::cout << "\n Введите 0, чтобы вернуться назад:";
            int naz;
            while (!(std::cin >> naz) || naz != 0) {
                std::cout << "Ошибка ввода. Пожалуйста, введите 0: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            break;
        }
        case 2: {
            system("cls");
            std::cout << std::string(100, '=') << "\n";
            agency.addSoiskatel();
            std::cout << "\n Введите 0, чтобы вернуться назад:";
            int naz;
            while (!(std::cin >> naz) || naz != 0) {
                std::cout << "Ошибка ввода. Пожалуйста, введите 0: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            break;
        }
        case 3: {
            system("cls");
            agency.searchPo();
            break;
        }
        case 4: {
            system("cls");
            int index;
            std::cout << std::string(100, '=') << "\n";
            agency.showSoiskateli();
            std::cout << "Введите индекс соискателя для удаления: ";
            while (!(std::cin >> index)) {
                std::cout << "Ошибка ввода. Введите целое число: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            std::cout << "Вы действительно хотите удалить этого пользователя? \n";
            std::cout << "1. Да \n";
            std::cout << "2. Нет \n";
            int f;
            while (!(std::cin >> f)  (f < 1  f > 2)) {
                std::cout << "Ошибка ввода. Пожалуйста, введите 1 или 2: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            if (f == 1) {
                agency.deleteSoiskatel(index - 1); // -1 для перевода в 0-based индекс
                std::cout << "\n Введите 0, чтобы вернуться назад:";
                int naz;
                while (!(std::cin >> naz) || naz != 0) {
                    std::cout << "Ошибка ввода. Пожалуйста, введите 0: ";
                    std::cin.clear();
                    while (std::cin.get() != '\n') continue;
                }
            }
            break;

        }
        case 5: {
            system("cls");
            int index;
            std::cout << std::string(100, '=') << "\n";
            agency.showSoiskateli();
            std::cout << "Введите индекс соискателя для изменения: ";
            while (!(std::cin >> index)) {
                std::cout << "Ошибка ввода. Введите целое число: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            agency.updateSoiskatel(index - 1); // -1 для перевода в 0-based индекс
            break;
        }
        case 6: {
            system("cls");
            std::cout <<

                std::string(100, '=') << "\n";
            auth.showAllUsers();
            std::cout << "\n Введите 0, чтобы вернуться назад:";
            int naz;
            while (!(std::cin >> naz) || naz != 0) {
                std::cout << "Ошибка ввода. Пожалуйста, введите 0: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            break;
        }
        case 7: {
            system("cls");
            std::string login, password;
            std::cout << std::string(100, '=') << "\n";
            std::cin.clear();
            while (std::cin.get() != '\n');
            while (true) {
                std::cout << "Введите логин нового пользователя (без пробелов):";

                std::getline(std::cin, login);

                if (login.find(' ') != std::string::npos) {
                    std::cout << "Ошибка: логин не должен содержать пробелы.\n";
                }
                else {
                    break; // ввод корректен
                }
            }

            // Ввод пароля с проверкой на пробелы
            while (true) {
                std::cout << "Введите пароль (без пробелов): ";
                std::getline(std::cin, password);
                if (password.find(' ') != std::string::npos) {
                    std::cout << "Ошибка: пароль не должен содержать пробелов!\n";
                }
                else break; // ввод корректен
            }

            int isAdmin;
            std::cout << "Дать права администратора? (1 - Да, 0 - Нет): ";
            while (!(std::cin >> isAdmin) || (isAdmin != 0 && isAdmin != 1)) {
                std::cout << "Ошибка ввода. Введите 1 или 0: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }

            if (auth.addUser(login, password, isAdmin == 1)) {
                std::cout << std::string(100, '=') << "\n";
                std::cout << "Пользователь успешно добавлен!\n";
                std::cout << std::string(100, '=') << "\n";
            }
            else {
                std::cout << std::string(100, '=') << "\n";
                std::cout << "Ошибка: пользователь с таким логином уже существует!\n";
                std::cout << std::string(100, '=') << "\n";
            }
            std::cout << "\n Введите 0, чтобы вернуться назад:";
            int naz;
            while (!(std::cin >> naz) || naz != 0) {
                std::cout << "Ошибка ввода. Пожалуйста, введите 0: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            break;
        }
        case 8: {
            system("cls");
            std::string username;
            std::cout << std::string(100, '=') << "\n";
            auth.showAllUsers();
            std::cout << "Введите логин пользователя для удаления: ";
            std::cin >> username;
            std::cout << "Вы действительно хотите удалить этого пользователя? \n";
            std::cout << "1. Да \n";
            std::cout << "2. Нет \n";
            int flag;
            while (!(std::cin >> flag)  (flag < 1  flag > 2)) {
                std::cout << "Ошибка ввода. Пожалуйста, введите 1 или 2: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            switch (flag) {
            case 1: {
                if (auth.removeUser(username)) {
                    std::cout << std::string(100, '=') << "\n";
                    std::cout << "Пользователь успешно удален!\n";
                    std::cout << std::string(100, '=') << "\n";
                }
                else {
                    std::cout << std::string(100, '=') << "\n";
                    std::cout << "Ошибка: нельзя удалить данного пользователя!\n";
                    std::cout << std::string(100, '=') << "\n";
                }
                std::cout << "\n Введите 0, чтобы вернуться назад:";
                int naz;
                while (!(std::cin >> naz) || naz != 0) {
                    std::cout


                        << "Ошибка ввода. Пожалуйста, введите 0: ";
                    std::cin.clear();
                    while (std::cin.get() != '\n') continue;
                }
                break;
            }
            case 2:  break;
            }
        }
        }
    }
}

void Menu::userMenu(Agentstvo& agency, const std::string& username) {
    while (true) {
        system("cls");
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "\n ____|МЕНЮ ПОЛЬЗОВАТЕЛЯ|____\n"
            << "1. Показать всех соискателей\n"
            << "2. Поиск по критериям\n"
            << "3. Забронировать соискателя\n"
            << "4. Мои забронированные соискатели\n"
            << "5. Отменить бронь\n"
            << "6. Возврат в главное меню\n"
            << "Выбор: ";

        int employerChoice;
        while (!(std::cin >> employerChoice)  (employerChoice < 1 employerChoice > 6)) {
            std::cout << "Ошибка ввода. Пожалуйста, введите 1-6: ";
            std::cin.clear();
            while (std::cin.get() != '\n') continue;
        }

        if (employerChoice == 6) {
            system("cls");
            break;
        }

        switch (employerChoice) {
        case 1: {
            system("cls");
            std::cout << std::string(100, '=') << "\n";
            agency.showSoiskateli();
            std::cout << "\n Введите 0, чтобы вернуться назад:";
            int naz;
            while (!(std::cin >> naz) || naz != 0) {
                std::cout << "Ошибка ввода. Пожалуйста, введите 0: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            break;
        }

        case 2: {
            system("cls");
            agency.searchPo();
            break;
        }
        case 3: {
            system("cls");
            agency.showSoiskateli();
            std::cout << "Введите номер соискателя для бронирования: ";
            int index;
            std::cin >> index;
            agency.bookSoiskatel(index - 1, username);

            std::cout << "\nВведите 0, чтобы вернуться назад:";
            int naz;
            while (!(std::cin >> naz) || naz != 0) {
                std::cout << "Ошибка ввода. Пожалуйста, введите 0: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            break;
        }
        case 4: {
            system("cls");
            agency.showBookedSoiskateli(username);

            std::cout << "\nВведите 0, чтобы вернуться назад:";
            int naz;
            while (!(std::cin >> naz) || naz != 0) {
                std::cout << "Ошибка ввода. Пожалуйста, введите 0: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            break;
        }
        case 5: {
            system("cls");
            agency.showBookedSoiskateli(username);
            std::cout << "Введите номер соискателя для отмены брони: ";
            int index;
            std::cin >> index;

            if (agency.isBookedByUser(index - 1, username)) {
                agency.unbookSoiskatel(index - 1);
            }
            else {
                std::cout << "Этот соискатель не забронирован вами!\n";
            }

            std::cout << "\nВведите 0, чтобы вернуться назад:";
            int naz;
            while (!(std::cin >> naz) || naz != 0) {
                std::cout << "Ошибка ввода. Пожалуйста, введите 0: ";
                std::cin.clear();
                while (std::cin.get() != '\n') continue;
            }
            break;
        }
        }
    }
}