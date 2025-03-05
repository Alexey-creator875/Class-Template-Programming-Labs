#pragma once

#include "Planet/Planet.h"
#include "Person/Person.h"

#include <cstddef>

namespace PlanetsExecutor {
enum class Mode {
    SolarSystem = 1,
    ConstructionTeam,
};

enum class Action {
    Exit,
    ReadDataBaseFromFile,
    SaveDataBaseToFile,
    SortDataBase,
    AddItemToDataBase,
    RemoveItemFromDataBase,
    EditDataBase,
    PrintDataBase,
};

enum class EditPlanet {
    Done,
    ChangeName,
    ChangeDiameter,
    ChangeInhabited,
    ChangeSatellites,
};

enum class EditPerson {
    Done,
    ChangeName,
    ChangeAge,
    ChangeHeight,
    ChangeWeight,
};

void ReadSolarSystemFromFile(Planet*& solarSystem, size_t& size, const char* fileName);
void SaveSolarSystemToFile(Planet* solarSystem, const size_t size, const char* fileName);
void SortSolarSystemByDiameter(Planet*& solarSystem, const size_t size);
void AddPlanetToSolarSystem(Planet*& solarSystem, size_t& size);
void RemovePlanetFromSolarSystem(Planet*& solarSystem, size_t& size);
void EditSolarSystem(Planet*& solarSystem, const size_t size);
void PrintSolarSystem(Planet* solarSystem, const size_t size);

void ReadConstructionTeamFromFile(Person*& constructionTeam, size_t& size, const char* fileName);
void SaveConstructionTeamToFile(Person* constructionTeam, const size_t size, const char* fileName);
void SortConstructionTeamByName(Person*& constructionTeam, const size_t size);
void AddPersonToConstructionTeam(Person*& constructionTeam, size_t& size);
void RemovePersonFromConstructionTeam(Person*& constructionTeam, size_t& size);
void EditConstructionTeam(Person*& constructionTeam, const size_t size);
void PrintConstructionTeam(Person* constructionTeam, const size_t size);

void SelectSolarSystem();
void SelectConstructionTeam();

void RunApplication();
}  // namespace PlanetsExecutor
