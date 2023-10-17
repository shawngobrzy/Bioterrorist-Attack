#ifndef PERSON_H
#define PERSON_H
#include "MixingGroups.h"
#include "FowardDeclaration.h" ///It took me 3 weeks to figure out why my stupid classes would not see each other!
#include <list>
#include <random>

using namespace std;
class Person
{
    public:
        Person();
        ~Person();

        int Getid() { return id; }
        void Setid(int val) { id = val; }
        int Getage() { return age; }
        void Setage(int val) { age = val; }
        int GetfamilyId() { return familyId; }
        void SetfamilyId(int val) { familyId = val; }
        int Getstatus() { return status; }
        void exposeTheGroup(int val) { status = val; }
        void changeStatus(int val) {status = val;}
        int inSchoolOrNah();
        void displayPersonsAttributes();
        void displayPersonsGroups();
        string displayStatus();
        void addPersonToHospital();
        void updateStatus();
        void incubationTracker();
        void infectiousRate();
        double getInfectiousRate() { return rate; }
        double getProbability() { return probability; }
        void resetUglyProbability() {uglyProbabilityEquation = 1.0;}
        void updateUglyProbabilityEquation( double rate );
        void probabilityFunction();
        int wasExposedToday();
        void rollInfectionProbabilty(default_random_engine& gen);
        void addGroups(MixingGroups& PTR) { individualGroups.push_back(&PTR);}
        int ageToIndex();
        bool getDeadYet() { return countedAlready; }
        void setDeadYet(bool val) { countedAlready = val; }

        //void addSchoolGroups( MixingGroups& personGroup, list<MixingGroups> schoolGroup);
        //void probabilityOfBeingInfected();





    private:
        int id;
        int age;
        int familyId;
        int status;
        int incubation;
        double rate;
        double uglyProbabilityEquation;
        double probability;
        bool countedAlready;
        list<MixingGroups*>individualGroups;


};

#endif // PERSON_H
