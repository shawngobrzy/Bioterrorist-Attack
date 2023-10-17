#include "Person.h"
#include "MixingGroups.h"
#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <list>
#include <cstdlib>


Person::Person()
{
    id = 0;
    familyId = 0;
    age = 0;
    status = 0;
    incubation = 0;
    rate = 0.0;
    probability = 0;
    uglyProbabilityEquation = 1.0;
    countedAlready = false;
}

Person::~Person()
{
    //dtor

}

int Person::inSchoolOrNah()
{
    for(MixingGroups* testGroups : individualGroups)
    {
        if(testGroups->GetId() == 15)
        {
            return 1;
        }

    }

    return 0;
}

string Person::displayStatus()
{
    switch(this->Getstatus())
    {
    case 0:
        return "Healthy";
        break;
    case 1:
        return "Exposed";
        break;
    case 2:
        return "Infected";
        break;
    case 3:
        return "Symptomatic Fever";
    case 4:
        return "Symptomatic Bleeding";
    case 5:
        return "Dead";
        break;
    default:
        break;

    }
}

void Person::displayPersonsAttributes()
{
    cout << "Person " << id << "'s age is " << age << "." << endl;
    cout << "This person belongs to family #" << familyId << " and" <<
    " this person's status is: " << this->displayStatus() << "." << endl;
    cout << "Lastly, the groups that this person is associated with consist of: ";

    displayPersonsGroups();
}

void Person::displayPersonsGroups()
{
    for(MixingGroups* myGroups : individualGroups)
    {
        cout << "Group: " << myGroups->getGroupType() << endl;

    }
}

void Person::incubationTracker()
{
    if(this->status >= 2)
    {
        incubation++;
    }
}


void Person::infectiousRate()
{

    switch(incubation)
    {
        case 1 ... 10: rate = 1;
        break;

        case 11: rate = 5;
        status = 3;
        break;

        case 12: rate = 10;
        break;

        case 13 ... 18: rate = 20;
        status = 4;
        break;

        case 19 ... 20: rate = 10;
        break;

        case 21: rate = 0;
        status = 5;
        break;
    }
}


void Person::updateStatus()
{
    this->incubationTracker();
    this->infectiousRate();

}

void Person::updateUglyProbabilityEquation(double rate)
{
    uglyProbabilityEquation = uglyProbabilityEquation * rate;
}

void Person::probabilityFunction()
{
    cout << "Person " << id << " ugly: " << uglyProbabilityEquation << endl;
    probability = 1 - uglyProbabilityEquation;
}

void Person::rollInfectionProbabilty(default_random_engine& gen)
{
    uniform_real_distribution<double> diceRoll(0, 1);
    double infectChance = diceRoll(gen);
    cout << "Rolling person " << id << ", chance: " << probability << endl;
    if(infectChance < probability)
    {
        status = 2;
    }
}

int Person::wasExposedToday()
{
    if(probability != 0)
    {
        return 1;
    }
    return 0;
}

int Person::ageToIndex()
{
    if(age<18)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}




