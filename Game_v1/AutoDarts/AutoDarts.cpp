// AutoDarts.cpp 

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <Windows.h>

bool ERROR_configurated{ false };//общий флаг какой либо ошибки при конфигурации

// функция выхода из программы
bool UserWantExitProgram()
{
    std::string exit_Y_N{};

    do
    {

        std::cout << "Exit programm (Y/N): ";
        std::cin >> exit_Y_N;

        if (exit_Y_N == "Y" || exit_Y_N == "y") {
            return false;
            break;
        }
        else if (exit_Y_N == "N" || exit_Y_N == "n") {
            return true;
            break;
        }
        else {
            std::cout << "Incorrect data!" << std::endl;
            continue;
        }

    } while (true);
}

//счиывание и преобразование / или \ в "\\" пути к файлу с консоли
std::string InputTransformWay() {
    std::string way{ "" };
    std::string way_file{ "" };

    std::cout << "Введите путь к файлу (если файл не в корневом каталоге программы): ";
    getline(std::cin >> std::ws, way_file);

    for (auto& ch : way_file) {

        if (ch == '\\' || ch == '/') {

            way = way + '\\' + '\\';
        }
        else {
            way = way + ch;
        }
    }
    return way;
}

//класс работы с сообщениями
class MessageTextAudio {
public:
    //считывание файла сообщений
    void ReadConfMessageFile() {
        
            std::ifstream  f_in(".\\Config_game\\Config_m.c"); // открыли файл по заданному пути на чтение
            if (f_in.is_open()) {
                int x_line = 0; //счетчик количества строк в файле
                std::string x_text{ "" }; //считывание слов или строк из файла

                line_file_.clear();

                //проход по файлу в режиме считывания и подсчет элементов
                do {
                    getline(f_in >> std::ws, x_text);
                    if (x_text[0] != '#' && x_text[0] != '\n' && x_text != "") {
                        line_file_.push_back(x_text);
                        ++x_line;
                    }
                    x_text.clear();

                    if (f_in.eof()) {
                        f_in.clear(); //очистка потока ввода из файла
                        f_in.seekg(0, std::ios::beg);//возврат курсора в начало файла
                        break;
                    }
                } while (true);

                f_in.close();
                std::cout << "Файл конфигурации сообщений успешно прочитан!" << std::endl;              
            }
            else {
                std::cout << "Файл сообщений не найден! Переустановите файл конфигурации сообщений." << std::endl;
                ERROR_configurated = true;
             }        
    }

    //создание блока данных пути
    std::pair<std::string, std::string> CreateMessage(const std::string& message_id) {
        std::pair<std::string, std::string> mes_text_audio{ {""},{""} };

        if (!line_file_.empty()) {

            auto it = std::find(line_file_.begin(), line_file_.end(), message_id);//поиск итератора по значению

            if (line_file_.end() != it) {

               // int x = it - line_file_.begin();//определение индекса элемента через итераторы                               
               // std::cout << *it << "---" << x << "---" << *line_file_.begin() << std::endl; пример для пнимания работы итераторов
  
                return mes_text_audio = { { *(it + 1)},{ *(it + 2)} };//прямое обращение через раименованный итератор
            }
            else {
                return mes_text_audio = { {"н/д"},{"н/д"} };
            }
        }

       /* int counter_x_{0}; //счетчик

        if (!line_file_.empty()) {
            for (const auto& text_line : line_file_) {

                if (text_line == message_id) {

                    return mes_text_audio = { {line_file_[counter_x_ + 1]},{line_file_[counter_x_ + 2]} };

                }
                ++counter_x_;
            }
        }else return mes_text_audio = { {"н/д"},{"н/д"}};

        return mes_text_audio = { {"н/д"},{"н/д"} };
        */
    }

private:
    std::vector <std::string> line_file_{""};
   // std::vector<std::string> block_x_{""};
};

//класс создание пути
class CreateWay {

public:
    //чтение данных файла конфигурации путей
    void ReadConfWayFile() {
      
            std::ifstream  f_in(".\\Config_game\\Config_way.c"); // открыли файл по заданному пути на чтение
            if (f_in.is_open()) {

                int x_line = 0; //счетчик количества строк в файле
                std::string x_text{ "" }; //считывание слов или строк из файла
                line_file_.clear();

                //проход по файлу в режиме считывания и подсчет элементов
                do {
                    getline(f_in >> std::ws, x_text);
                    if (x_text[0] != '#' && x_text[0] != '\n' && x_text != "") {
                        line_file_.push_back(x_text);
                        ++x_line;
                    }
                    x_text.clear();

                    if (f_in.eof()) {
                        f_in.clear(); //очистка потока ввода из файла
                        f_in.seekg(0, std::ios::beg);//возврат курсора в начало файла
                        break;
                    }
                } while (true);

                f_in.close();
                std::cout << "Файл онфигурации путей успешно прочитан!" << std::endl;
            }
            else {
                std::cout << "Файл конфигурации путей не найден! Переустановите конфигурационный файл." << std::endl;
                ERROR_configurated = true;
            }
     }

    //создание блока данных пути
    void CreateBlockWay() {
        // int counter_x_{ 0 }; //счетчик
        //int counter_way{ 0 };

        bool blok_oupen = false;

        for (const auto& text_line : line_file_) {

            if (text_line == ">") {
                blok_oupen = true;
                //++counter_way;
            }
            if (text_line == "<") {
                if (!block_x_.empty()) {
                    way_x_.push_back(block_x_);
                }
                blok_oupen = false;
                block_x_.clear();
            }

            if (blok_oupen == true && text_line != ">") {
                block_x_.push_back(text_line);
            }
        }
    }

    std::vector < std::vector<std::string> > way_x_{};//блоки данных о путях
   
 private:       
        std::vector <std::string> line_file_;
        std::vector<std::string> block_x_{};
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
   // setlocale(LC_ALL, "Russian");
    

    CreateWay CreateWay_x;              //инициализация переменной класса пути
    MessageTextAudio Messages;          //инициализация переменной класса сообщений

    do {
        ERROR_configurated = false;
        std::cout << "Конфигурация программы!" << std::endl;
        Messages.ReadConfMessageFile();     //считывание файла конфигурации сообщений
        CreateWay_x.ReadConfWayFile();      //считывание данный о путях из конфигурации
        CreateWay_x.CreateBlockWay();       //создания вектора путей
        Sleep(2000);

        if (ERROR_configurated == true) {
            std::string exit_Y_N{};
            std::cout << "Ошибка инициализации. Исправьте файлы конфигурации" << std::endl;
            std::cout << "Перезапустить конфигурацию? (Д/Н): ";
            std::cin >> exit_Y_N;

            if (exit_Y_N == "Д" || exit_Y_N == "д") {
                //return false;
                std::cout << "\033c";//очистка консоли
                continue;
            }
            else if (exit_Y_N == "Н" || exit_Y_N == "н") {
                //return true;
                break;
            }
            else {
                std::cout << "Не корректный ввод!" << std::endl;
                continue;
            }
        }

    } while (ERROR_configurated);



    if (ERROR_configurated == false) {
        do {
            std::cout << "\033c";//очистка консоли

            std::cout << Messages.CreateMessage("@0000").first;
            std::cout << "\n" << std::endl;

            std::cout << Messages.CreateMessage("@0001").first << std::endl;
            std::cout << Messages.CreateMessage("@0001").second << std::endl;
            std::cout << "\n" << std::endl;
            std::cout << Messages.CreateMessage("@0002").first << std::endl;
            std::cout << Messages.CreateMessage("@0002").second << std::endl;
            std::cout << "\n" << std::endl;


            for (const auto& w : CreateWay_x.way_x_) {

                std::cout << "----------------------" << std::endl;

                std::cout << "Путь: " << w[0] << std::endl;

                int a = 0;
                for (const auto& b : w) {

                    std::cout << "Номер [" << a << "]: " << b << std::endl;
                    ++a;

                }

            }















            std::cout << std::endl;
        } while (UserWantExitProgram());
    }
}

