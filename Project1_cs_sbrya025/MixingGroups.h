#ifndef MIXINGGROUPS_H
#define MIXINGGROUPS_H
#include <list>
#include <string>
#include "Person.h"
#include "FowardDeclaration.h" ///It took me 3 weeks days to figure out why my stupid classes would not see each other!

using namespace std;

const double familyRates[2][2]{0.0325, 0.0124,
                               0.0124, 0.0151};

class MixingGroups
{
    public:
        MixingGroups();
        ~MixingGroups();
        MixingGroups(int i);


        int GetId() {return id;}
        void Setid(int val) { id = val; }
        string getGroupType(){ return groupType; }
        void SetGroupType(string val) { groupType = val; }
        void getPointersFromActualPeopleAndAddItToPointerList(Person& boy);
        void addPerson(Person& PTR) { personPTR.push_back(&PTR);}
        void displayPeopleInGroups();
        void exposePeopleInGroups();
        //void exposeTheExposedPeoplesOtherGroups();
        void spreadInfection();
        void groupInfectionRate();
        void calcProb(Person& p);

    private:
        int id;
        double baseRate;
        double famBaseRate;
        double famBaseRate1;
        double famBaseRate2;
        list<Person*>personPTR;
        string groupType;


};

#endif // MIXINGGROUPS_H
