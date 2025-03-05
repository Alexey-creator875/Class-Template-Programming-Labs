#include "DataBaseExecutor.h"

#include <cstddef>
#include <iostream>
#include <iomanip>

#include "Planet/Planet.h"

namespace {
const size_t kDefaultDataBaseSize = 8;
const size_t kMaxNameSize = 30;
const int kColumnWidth = 20;

const char kSolarSystemFileName[] = "SolarSystem.txt";
const char kConstructionTeamFileName[] = "ConstructionTeam.txt";

void ChangeName(Planet& planet) {
    std::cout << "Enter new name:\n";
    char name[kMaxNameSize];
    std::cin >> name;

    planet.setName(name);

    std::cout << "Name was changed successfully!\n\n";
}

void ChangeDiameter(Planet& planet) {
    std::cout << "Enter new diameter:\n";
    int diameter = 0;
    std::cin >> diameter;

    planet.setDiameter(diameter);

    std::cout << "Diameter was changed successfully!\n\n";
}

void ChangeInhabited(Planet& planet) {
    planet.setInhabited(!planet.getInhabited());

    if (planet.getInhabited()) {
        std::cout << "Magic! Life appeared on the planet!\n\n";
    } else {
        std::cout << "Unfortunately, the planet became uninhabitable!\n\n";
    }
}

void ChangeSatellitesNumber(Planet& planet) {
    std::cout << "Enter new number of satellites:\n";
    int satellites = 0;
    std::cin >> satellites;

    planet.setSatellites(satellites);

    std::cout << "Number of satellites was changed successfully!\n\n";
}

void ChangeName(Person& person) {
    std::cout << "Enter new name:\n";
    char name[kMaxNameSize];
    std::cin >> name;

    person.setName(name);

    std::cout << "Name was changed successfully!\n\n";
}

void ChangeAge(Person& person) {
    std::cout << "Enter new age:\n";
    int age = 0;
    std::cin >> age;

    person.setAge(age);

    std::cout << "Age was changed successfully!\n\n";
}

void ChangeHeight(Person& person) {
    std::cout << "Enter new height:\n";
    int height = 0;
    std::cin >> height;

    person.setHeight(height);

    std::cout << "Height was changed successfully!\n\n";
}

void ChangeWeight(Person& person) {
    std::cout << "Enter new height:\n";
    int weight = 0;
    std::cin >> weight;

    person.setWeight(weight);

    std::cout << "Weight was changed successfully!\n\n";
}
}  // namespace

namespace PlanetsExecutor {
void ReadSolarSystemFromFile(Planet*& solarSystem, size_t& size, const char* fileName) {
    if (Planet::readArrayFromFile(solarSystem, size, fileName)) {
        std::cout << "failed to read file\n\n";
        return;
    }

    std::cout << "Solar system was written sucessfully!\n\n";
}

void SaveSolarSystemToFile(Planet* solarSystem, const size_t size, const char* fileName) {
    if (Planet::saveArrayToFile(solarSystem, size, fileName)) {
        std::cout << "failed to save data base\n\n";
        return;
    }

    std::cout << "Solar system saved successfully\n\n";
}

void SortSolarSystemByDiameter(Planet*& solarSystem, const size_t size) {
    if (Planet::sortArrayByDiameter(solarSystem, size)) {
        std::cout << "Failed to sort solar system\n\n";
        return;
    }

    std::cout << "Solar system sorted successfully\n\n";
}

void AddPlanetToSolarSystem(Planet*& solarSystem, size_t& size) {
    std::cout << "Enter planet name:\n";
    char name[kMaxNameSize];
    std::cin >> name;

    std::cout << "Enter planet diameter:\n";
    int diameter = 0;
    std::cin >> diameter;

    std::cout << "Is planet inhabited or not (1/0):\n";
    bool inhabited = 0;
    std::cin >> inhabited;

    std::cout << "Enter the number of planet satellites:\n";
    int satellites = 0;
    std::cin >> satellites;

    Planet planet(name, diameter, inhabited, satellites);

    if (Planet::pushBack(solarSystem, size, planet)) {
        std::cout << "Failed to add planet to solar system\n\n";
        return;
    }

    std::cout << "Planet added to solar system successfulluy!\n\n";
}

void RemovePlanetFromSolarSystem(Planet*& solarSystem, size_t& size) {
    std::cout << "Enter name of planet which you want to remove:\n";
    char name[kMaxNameSize];
    std::cin >> name;

    bool validIndex = true;
    size_t removeIndex = Planet::findPlanetByName(solarSystem, size, name, validIndex);

    if (!validIndex) {
        std::cout << "There is no such planet in solar system\n\n";
        return;
    }

    if (Planet::removeFromArray(solarSystem, size, removeIndex)) {
        std::cout << "Failed to remove planet\n\n";
        return;
    }

    std::cout << "Planet removed successfully!\n\n";
}

void EditSolarSystem(Planet*& solarSystem, const size_t size) {
    std::cout << "Enter name of planet which you want to edit:\n";
    char name[kMaxNameSize];
    std::cin >> name;

    bool validIndex = true;
    size_t editIndex = Planet::findPlanetByName(solarSystem, size, name, validIndex);

    if (!validIndex) {
        std::cout << "There is no such planet in data base\n\n";
        return;
    }

    bool editMode = true;

    while (editMode) {
        int command = 0;

        std::cout << "Enter '1' to change name\n"
                  << "Enter '2' to change diameter\n"
                  << "Enter '3' to change inhabited\n"
                  << "Enter '4' to change number of satellites\n"
                  << "Enter '0' to finish editing\n";
        
        std::cin >> command;

        switch (static_cast<EditPlanet>(command)) {
            case EditPlanet::ChangeName:
                ChangeName(solarSystem[editIndex]);
                break;
            case EditPlanet::ChangeDiameter:
                ChangeDiameter(solarSystem[editIndex]);
                break;
            case EditPlanet::ChangeInhabited:
                ChangeInhabited(solarSystem[editIndex]);
                break;
            case EditPlanet::ChangeSatellites:
                ChangeSatellitesNumber(solarSystem[editIndex]);
                break;
            case EditPlanet::Done:
                editMode = false;
                break;
            default:
                std::cout << "invalid command\n\n";
        }
    }
}

void PrintSolarSystem(Planet* solarSystem, const size_t size) {
    std::cout << "Solar system\n";

    for (size_t i = 0; i < size; ++i) {
        std::cout << i << '\t' << solarSystem[i];
    }

    std::cout << '\n';
}

void SelectSolarSystem() {
    size_t size = 0;
    Planet* solarSystem = nullptr;

    ReadSolarSystemFromFile(solarSystem, size, kSolarSystemFileName);

    bool continueExecution = true;

    while (continueExecution) {
        int action = 0;

        std::cout << "Enter '1' to read solar system from file\n"
                  << "Enter '2' to save solar system to file\n"
                  << "Enter '3' to sort solar system by diameter\n"
                  << "Enter '4' to add new planet to solar system\n"
                  << "Enter '5' to remove planet from solar system\n"
                  << "Enter '6' to edit solar system\n"
                  << "Enter '7' to print solar system\n"
                  << "Enter '0' to finish\n";

        std::cin >> action;
        std::cout << '\n';

        switch (static_cast<Action>(action)) {
            case Action::ReadDataBaseFromFile:
                ReadSolarSystemFromFile(solarSystem, size, kSolarSystemFileName);
                break;
            case Action::SaveDataBaseToFile:
                SaveSolarSystemToFile(solarSystem, size, kSolarSystemFileName);
                break;
            case Action::SortDataBase:
                SortSolarSystemByDiameter(solarSystem, size);
                break;
            case Action::AddItemToDataBase:
                AddPlanetToSolarSystem(solarSystem, size);
                break;
            case Action::RemoveItemFromDataBase:
                RemovePlanetFromSolarSystem(solarSystem, size);
                break;
            case Action::EditDataBase:
                EditSolarSystem(solarSystem, size);
                break;
            case Action::PrintDataBase:
                PrintSolarSystem(solarSystem, size);
                break;
            case Action::Exit:
                continueExecution = false;
                break;
            default:
                std::cout << "invalid command\n";
                break;
        }

        std::cout << '\n';
    }

    if (solarSystem) {
        delete[] solarSystem;
    }
}

void ReadConstructionTeamFromFile(Person*& constructionTeam, size_t& size, const char* fileName) {
    if (Person::readArrayFromFile(constructionTeam, size, fileName)) {
        std::cout << "failed to read file\n";
        return;
    }

    std::cout << "Construction team was written sucessfully!\n\n";
}

void SaveConstructionTeamToFile(Person* constructionTeam, const size_t size, const char* fileName) {
    if (Person::saveArrayToFile(constructionTeam, size, fileName)) {
        std::cout << "failed to save data base\n\n";
        return;
    }

    std::cout << "Construction team saved successfully\n\n";
}

void SortConstructionTeamByName(Person*& constructionTeam, const size_t size) {
    if (Person::sortArrayByName(constructionTeam, size)) {
        std::cout << "Failed to sort construction team\n\n";
        return;
    }

    std::cout << "Construction team sorted successfully\n\n";
}

void AddPersonToConstructionTeam(Person*& constructionTeam, size_t& size) {
    std::cout << "Enter name:\n";
    char name[kMaxNameSize];
    std::cin >> name;

    std::cout << "Enter age:\n";
    int age = 0;
    std::cin >> age;

    std::cout << "Enter height:\n";
    bool height = 0;
    std::cin >> height;

    std::cout << "Enter weight:\n";
    int weight = 0;
    std::cin >> weight;

    Person person(name, age, height, weight);

    if (Person::pushBack(constructionTeam, size, person)) {
        std::cout << "Failed to add person to construction team\n\n";
        return;
    }

    std::cout << "Person added to construction team successfulluy!\n\n";
}

void RemovePersonFromConstructionTeam(Person*& constructionTeam, size_t& size) {
    std::cout << "Enter name of person who you want to remove:\n";
    char name[kMaxNameSize];
    std::cin >> name;

    bool validIndex = true;
    size_t removeIndex = Person::findPersonByName(constructionTeam, size, name, validIndex);

    if (!validIndex) {
        std::cout << "There is no such person in construction team\n\n";
        return;
    }

    if (Person::removeFromArray(constructionTeam, size, removeIndex)) {
        std::cout << "Failed to remove person\n\n";
        return;
    }

    std::cout << "Person removed successfully!\n\n";
}

void EditConstructionTeam(Person*& constructionTeam, const size_t size) {
    std::cout << "Enter name of person who you want to edit:\n";
    char name[kMaxNameSize];
    std::cin >> name;

    bool validIndex = true;
    size_t editIndex = Person::findPersonByName(constructionTeam, size, name, validIndex);

    if (!validIndex) {
        std::cout << "There is no such person in construction team\n\n";
        return;
    }

    bool editMode = true;

    while (editMode) {
        int command = 0;

        std::cout << "Enter '1' to change name\n"
                  << "Enter '2' to change age\n"
                  << "Enter '3' to change height\n"
                  << "Enter '4' to change weight\n"
                  << "Enter '0' to finish editing\n";
        
        std::cin >> command;

        switch (static_cast<EditPerson>(command)) {
            case EditPerson::ChangeName:
                ChangeName(constructionTeam[editIndex]);
                break;
            case EditPerson::ChangeAge:
                ChangeAge(constructionTeam[editIndex]);
                break;
            case EditPerson::ChangeHeight:
                ChangeHeight(constructionTeam[editIndex]);
                break;
            case EditPerson::ChangeWeight:
                ChangeWeight(constructionTeam[editIndex]);
                break;
            case EditPerson::Done:
                editMode = false;
                break;
            default:
                std::cout << "invalid command\n\n";
        }
    }
}

void PrintConstructionTeam(Person* constructionTeam, const size_t size) {
    std::cout << "Construction team\n";

    for (size_t i = 0; i < size; ++i) {
        std::cout << i << '\t' << constructionTeam[i];
    }

    std::cout << '\n';
}

void SelectConstructionTeam() {
    size_t size = 0;
    Person* constructionTeam = nullptr;

    ReadConstructionTeamFromFile(constructionTeam, size, kConstructionTeamFileName);

    bool continueExecution = true;

    while (continueExecution) {
        int action = 0;

        std::cout << "Enter '1' to read construction team from file\n"
                  << "Enter '2' to save construction team to file\n"
                  << "Enter '3' to sort construction team by age\n"
                  << "Enter '4' to add new person to construction team\n"
                  << "Enter '5' to remove person from construction team\n"
                  << "Enter '6' to edit construction team\n"
                  << "Enter '7' to print construction team\n"
                  << "Enter '0' to finish\n";

        std::cin >> action;
        std::cout << '\n';

        switch (static_cast<Action>(action)) {
            case Action::ReadDataBaseFromFile:
                ReadConstructionTeamFromFile(constructionTeam, size, kConstructionTeamFileName);
                break;
            case Action::SaveDataBaseToFile:
                SaveConstructionTeamToFile(constructionTeam, size, kConstructionTeamFileName);
                break;
            case Action::SortDataBase:
                SortConstructionTeamByName(constructionTeam, size);
                break;
            case Action::AddItemToDataBase:
                AddPersonToConstructionTeam(constructionTeam, size);
                break;
            case Action::RemoveItemFromDataBase:
                RemovePersonFromConstructionTeam(constructionTeam, size);
                break;
            case Action::EditDataBase:
                EditConstructionTeam(constructionTeam, size);
                break;
            case Action::PrintDataBase:
                PrintConstructionTeam(constructionTeam, size);
                break;
            case Action::Exit:
                continueExecution = false;
                break;
            default:
                std::cout << "invalid command\n";
                break;
        }

        std::cout << '\n';
    }

    if (constructionTeam) {
        delete[] constructionTeam;
    }
}

void RunApplication() {
    int mode = 0;

    std::cout << "Enter '1' to select Solar system\n"
              << "Enter '2' to select construction team\n";
    
    std::cin >> mode;

    switch (static_cast<Mode>(mode)) {
        case Mode::SolarSystem:
            SelectSolarSystem();
            break;
        case Mode::ConstructionTeam:
            SelectConstructionTeam();
            break;
        default:
            std::cout << "invalid mode\n";
            break;
    }
}
}  // namespace PlanetsExecutor
