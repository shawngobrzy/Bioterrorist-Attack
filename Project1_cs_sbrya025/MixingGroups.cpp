#include "MixingGroups.h"
#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <list>
#include <cstdlib>

MixingGroups::MixingGroups()
{
    id = 0;
    baseRate = 0.0;
}

MixingGroups::MixingGroups(int i)
{
    ///Don't You Dare even Ask.
    id = i;
    baseRate = 0.0;
}

MixingGroups::~MixingGroups()
{
    //dtor
}

void MixingGroups::getPointersFromActualPeopleAndAddItToPointerList(Person& boy)
{
    personPTR.push_back(&boy);
}

void MixingGroups::displayPeopleInGroups()
{
    for(Person* myGroupsPeople : personPTR)
    {
        cout << "Person's ID: " << myGroupsPeople->Getid() << endl;

    }
}

void MixingGroups::exposePeopleInGroups()
{

    for(Person* myGroupsPeople : personPTR)
    {
        myGroupsPeople->exposeTheGroup(1);
    }
}



void MixingGroups::groupInfectionRate()
{
    if(groupType == "P. U. Dummington Elementary School")
    {
        baseRate = 0.01000;
    }
    else if(groupType == "Flip a Duh Skip a Duh Middle School")
    {
        baseRate = 0.00800;
    }
    else if(groupType == "MOMMAH High School")
    {
        baseRate = 0.00800;
    }
    else if(groupType == "Trump University")
    {
        baseRate = 0.00600;
    }
    else if(groupType == "Boring Work Industries")
    {
        baseRate = 0.01000;
    }

}

void MixingGroups::calcProb(Person& p)
{
    double dailyScore = 1.0;
    for(Person* r : personPTR)
    {
        if(r->Getstatus() > 1 && r != &p)
        {
            if(groupType == "Family")
            {
                dailyScore =  dailyScore * (1-(r->getInfectiousRate() * familyRates[r->ageToIndex()][p.ageToIndex()]));
            }
            else
            {
                dailyScore =  dailyScore * (1-(r->getInfectiousRate() * baseRate));
            }
        }
    }

    p.updateUglyProbabilityEquation(dailyScore);
}

void MixingGroups::spreadInfection()
{
    for(Person* myGroupsPeople : personPTR)
    {
        if(myGroupsPeople->Getstatus() == 0)
        {
            this->calcProb(*myGroupsPeople);
        }
    }
}

/*
void MixingGroups::exposeTheExposedPeoplesOtherGroups()
{
    for(Person* myGroupsPeople : personPTR)
    {
        myGroupsPeople->status = 1;

    }
}
*/
