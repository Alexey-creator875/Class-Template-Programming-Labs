#include "Executor.h"

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <string>
#include <vector>

namespace {
const char kInputFileName[] = "input.txt";
const char kOutputFileName[] = "output.txt";

const double kMinRandomNumberFourthTask = -50.;
const double kMaxRandomNumberFourthTask = 50.;

const double kMinRandomNumberSixthTask = -50.;
const double kMaxRandomNumberSixthTask = 50.;

const size_t kInitialVectorSize = 10;
const int kPrecision = 3;
const int kRemoveIndex = 8;

const size_t kInitialListSize = 10;

double GenerateRandomRealNumber(double min, double max) {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_real_distribution<double> segment(min, max);

    return segment(randomEngine);
}

void PrintVectorFourthTask(const std::vector<double>& vector) {
    for (auto element : vector) {
        std::cout << std::fixed << std::setprecision(kPrecision) << element << ' ';
    }

    std::cout << '\n';
}

void PrintVectorFifthTask(const std::vector<Executor::Box>& vector) {
    for (auto box : vector) {
        std::cout << box.getWidth() << ' ' << box.getHeight() << ' ' << box.getLength() << '\n';
    }
}

void PrintListSixthTask(const std::list<double>& list) {
    for (auto element : list) {
        std::cout << std::fixed << std::setprecision(kPrecision) << element << ' ';
    }

    std::cout << std::endl;
}

void PrintListSeventhTask(const std::list<Executor::Graduate>& list) {
    for (auto graduate : list) {
        std::cout << graduate.getName() << ' ' << graduate.getRating() << '\n';
    }

    std::cout << '\n';
}

void PrintMapEighthTask(const std::map<std::string, std::string>& map) {
    for (auto pair : map) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }

    std::cout << '\n';
}

void PrintMapNinthTask(const std::map<std::string, int>& map) {
    for (auto pair : map) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }

    std::cout << '\n';
}
}  // namespace

namespace Executor {
bool operator<(const Box& first, const Box& second) {
    return (first.width * first.height * first.length) < (second.width * second.height * second.length);
}

bool operator==(const Box& first, const Box& second) {
    return (first.width * first.height * first.length) == (second.width * second.height * second.length);
}

bool operator<(const Graduate& first, const Graduate& second) {
    return (first.rating < second.rating) || ((first.rating == second.rating) && (first.name < second.name));
}

bool operator==(const Graduate& first, const Graduate& second) {
    return (first.rating == second.rating) && (first.name == second.name);
}

void PerformFirstTask() {
    std::string name;
    std::cout << "Enter your name:\n";
    std::cin >> name;

    std::string middleName;
    std::cout << "Enter your patronymic:\n";
    std::cin >> middleName;

    std::string surname;
    std::cout << "Enter your surname:\n";
    std::cin >> surname;

    std::string fullName;
    fullName += name;
    fullName += ' ';
    fullName += middleName;
    fullName += ' ';
    fullName += surname;

    std::cout << "Full name:\n" << fullName << '\n';
}

void PerformSecondTask() {
    std::string text;
    std::cout << "Enter text with square brackets:\n";
    std::getline(std::cin, text);
    std::getline(std::cin, text);

    std::string textEnclosedInBrackets;

    size_t index = 0;

    while (index < text.length() && text[index] != '[') {
        ++index;
    }

    if (index == text.length()) {
        std::cout << "Opening bracket not found\n";
        return;
    }

    ++index;

    while (index < text.length() && text[index] != ']') {
        textEnclosedInBrackets += text[index];
        ++index;
    }

    if (text[index] != ']') {
        std::cout << "Closing bracket not found\n";
        return;
    }

    std::cout << "Text enclosed in brackets:\n" << textEnclosedInBrackets << '\n';
}

void PerformThirdTask() {
    std::ifstream inputFile(kInputFileName);

    if (!inputFile) {
        std::cout << "Failed to open file\n";
        return;
    }

    std::string line;
    std::ofstream outputFile(kOutputFileName, std::ios::trunc);

    while (std::getline(inputFile, line)) {
        if (line[line.length() - 1] == '!') {
            outputFile << line << '\n';
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "The task completed successfully!\n";
}

void PerformFourthTask() {
    std::vector<double> vector;

    for (size_t i = 0; i < kInitialVectorSize; ++i) {
        vector.push_back(GenerateRandomRealNumber(kMinRandomNumberFourthTask, kMaxRandomNumberFourthTask));
    }

    std::cout << "Vector\n";
    PrintVectorFourthTask(vector);

    double average = 0.;
    std::vector<double>::iterator p = vector.begin();

    while (p != vector.end()) {
        average += *p;
        ++p;
    }

    average /= vector.size();
    std::cout << "Average:\n" << average << '\n';

    std::vector<double> newVector;

    for (auto element : vector) {
        if (element > average) {
            newVector.push_back(element);
        }
    }

    std::cout << "New vector\n";
    PrintVectorFourthTask(newVector);

    std::cout << "delete eighth element from first vector\n";
    vector.erase(vector.begin() + kRemoveIndex);
    PrintVectorFourthTask(vector);
}

void PerformFifthTask() {
    std::vector<Box> vector = {
        {1,  2,  63},
        {14, 57, 19},
        {7,  32, 20},
        {5,  13, 23},
        {10, 19, 45},
        {19, 9,  59}
    };

    PrintVectorFifthTask(vector);

    Box largestBox;

    for (auto box : vector) {
        if (largestBox < box) {
            largestBox = box;
        }
    }

    std::cout << "The largest box:\n";
    std::cout << largestBox.getWidth() << ' ' << largestBox.getHeight() << ' ' << largestBox.getLength() << '\n';
}

void PerformSixthTask() {
    std::list<double> list;

    for (size_t i = 0; i < kInitialListSize; ++i) {
        list.push_back(GenerateRandomRealNumber(kMinRandomNumberSixthTask, kMaxRandomNumberSixthTask));
    }

    std::cout << "First list\n";
    PrintListSixthTask(list);

    double average = 0;

    std::list<double>::iterator iter;

    for (iter = list.begin(); iter != list.end(); ++iter) {
        average += *iter;
    }

    average /= list.size();
    std::cout << "Average:\n" << average << '\n';

    std::list<double> newList;

    for (auto element : list) {
        if (element > average) {
            newList.push_back(element);
        }
    }

    std::cout << "Second list\n";
    PrintListSixthTask(newList);

    std::list<double>::iterator remove = list.begin();

    for (size_t i = 0; i < kRemoveIndex; ++i) {
        ++remove;
    }

    list.erase(remove);
    std::cout << "Remove eighth element from first list\n";
    PrintListSixthTask(list);
}

void PerformSeventhTask() {
    std::list<Graduate> list = {
        {"Иванов",   99 },
        {"Петров",   430},
        {"Семенов", 70 },
        {"Котов",     540},
        {"Белых",     230},
        {"Черных",   350}
    };

    PrintListSeventhTask(list);

    Graduate bestGraduate;

    for (auto graduate : list) {
        if (bestGraduate < graduate) {
            bestGraduate = graduate;
        }
    }

    std::cout << "The best graduate\n";
    std::cout << bestGraduate.getName() << ' ' << bestGraduate.getRating() << '\n';

    double increment = 0.;
    std::cout << "Enter number on which you want to increase rating of all graduates:\n";
    std::cin >> increment;

    std::list<Graduate>::iterator iter;

    for (iter = list.begin(); iter != list.end(); ++iter) {
        (*iter).setRating((*iter).getRating() + increment);
    }

    std::cout << "New list\n";
    PrintListSeventhTask(list);
}

void PerformEighthTask() {
    std::map<std::string, std::string> map;
    map["Russia"] = "Moscow";
    map["Great Britain"] = "London";
    map["Japan"] = "Tokyo";
    map["Spain"] = "Madrid";
    map["France"] = "Paris";

    std::string userCountry;
    std::cout << "Enter name of country:\n";
    std::getline(std::cin, userCountry);
    std::getline(std::cin, userCountry);

    std::map<std::string, std::string>::iterator p = map.find(userCountry);

    if (p != map.end()) {
        std::cout << (*p).second << " is the capital of " << userCountry << "\n\n";
        PrintMapEighthTask(map);
        return;
    }

    std::cout << "There is no such country in map\n";
    std::cout << "Do you want to add this country? (y/n)\n";
    char add = 'n';
    std::cin >> add;

    if (add != 'y') {
        PrintMapEighthTask(map);
        return;
    }

    std::cout << "Enter the capital of your country:\n";
    std::string capital;
    std::getline(std::cin, capital);
    std::getline(std::cin, capital);
    map[userCountry] = capital;
    PrintMapEighthTask(map);
}

void PerformNinthTask() {
    std::map<std::string, int> map;

    map["Иванов"] = 123;
    map["Петров"] = 89;
    map["Сидоров"] = 108;
    map["Краснов"] = 132;
    map["Демин"] = 99;
    map["Черепанов"] = 111;

    int sum = 0;

    for (auto pair : map) {
        sum += pair.second;
    }

    std::cout << "Total collected: " << sum << " products\n";

    PrintMapNinthTask(map);
}

void RunApplication() {
    bool continueExecution = true;

    while (continueExecution) {
        int task = 0;
        std::cout << "\nEnter the number from 1 to 9 to choose \n"
                  << "Enter '0' to finish\n";
        std::cin >> task;

        switch (static_cast<Task>(task)) {
            case Task::Finish:
                continueExecution = false;
                break;
            case Task::First:
                PerformFirstTask();
                break;
            case Task::Second:
                PerformSecondTask();
                break;
            case Task::Third:
                PerformThirdTask();
                break;
            case Task::Fourth:
                PerformFourthTask();
                break;
            case Task::Fifth:
                PerformFifthTask();
                break;
            case Task::Sixth:
                PerformSixthTask();
                break;
            case Task::Seventh:
                PerformSeventhTask();
                break;
            case Task::Eighth:
                PerformEighthTask();
                break;
            case Task::Ninth:
                PerformNinthTask();
                break;
            default:
                std::cout << "Invalid number! Try again.\n";
                break;
        }
    }
}
}  // namespace Executor
