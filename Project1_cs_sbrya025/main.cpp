#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <list>
#include <cstdlib>
#include <fstream>
#include "Person.h"
#include "MixingGroups.h"

// .01 workgroups
// .03 elementary
// .008 middle
// .01 high
// .0

using namespace std;

void displayTheNumberOfScrubs(int x);
void displayTheFamilyScrubs(int x);
void displayTheNumberOfExposedScrubs(int x);
void displayTheNumberOfInfectedScrubs(int x);
void displayTheNumberOfSymptomaticFeverScrubs(int x);
void displayTheNumberOfSymptomaticBleedingScrubs(int x);
void displayTheNumberOfDeadScrubs(int x);
void displayTheNewPopulation(int x);


///Store probabilities within specific mixing groups and add those probabilities to each person populating them.

///Certain risk of illness will vary based on jobs.

///Start day count

///Start updating status of each person as each day progress as the virus gets introduced

///For family mixing groups, get number of children and number of adults and then calculate probability for infectiousness based off of their respective probabilities



///Traverse each person in each mixing group

///Remove all person pointers that are dead

/// Expose 1 MG -> update status and inform MGs -> Change of status -> MGs compute score -> Person computes 1-Pi -> Change Status

///Make <MG>, Make <People>, Expose 1 MG, <MG> informs <Persons> change of Status

///Time Loop: {Each person informs all of their mixing groups of the change in status, Each mixing group computes score (1-p)^n, Each person computes 1-Pi(Scores) -roll dice}

///Person chance of getting infected: 1-[(.98)(number of people exposed to and their respective probabilities)]


int main()
{

    int population = 5000;                                                                     ///Set default value for population
    default_random_engine* gptr;
    gptr = new default_random_engine(time(NULL));
    normal_distribution<double> ageDistribution(45,20);                                        ///Create a random generator for the age of people and schools
    uniform_int_distribution<int> numberOfElemtarySchools(1,8);
    uniform_int_distribution<int> numberOfMiddleSchools(9,12);
    uniform_int_distribution<int> numberOfHighSchools(13,14);
    uniform_int_distribution<int> numberOfUniversities(1,2);

    list<Person> people;                                                                       ///Create a list of People and Mixing group objects along with an iterator for each list and an extra iterator identifying the last work mixing group
    list<Person>::iterator pitr;
    list<MixingGroups> groups;
    list<MixingGroups>::iterator mitr;
    list<MixingGroups>::iterator lastWork;

    cout << "¿Cuántos idiotas vivirán sus horribles vidas en tu mundo repugnante?" << endl;
    cin >> population;                                                                         ///Prompt the user to enter a number for the population

    int familyID = 0;
    Person * newPerson = nullptr;                                                              ///Create pointer objects for the Person and Mixing Group classes
    MixingGroups * family = nullptr;


    for(int i = 0; i <= (population/25)+15; i++)
    {
        MixingGroups newGroup(i);
        switch(i)                                /// Create 1 Hospital, 7 Elementary schools, 3 Middle Schools, 2 High Schools, 1 University, and the Workforce while populating the workforce with 25 people in each group
        {

        case 0:
            newGroup.SetGroupType("Hospital");
            break;
        case 1 ... 8:
            newGroup.SetGroupType("P. U. Dummington Elementary School");
            break;
        case 9 ... 12:
            newGroup.SetGroupType("Flip a Duh Skip a Duh Middle School");
            break;
        case 13 ... 14:
            newGroup.SetGroupType("MOMMAH High School");
            break;
        case 15:
            newGroup.SetGroupType("Trump University");
            break;
        default:
            newGroup.SetGroupType("Boring Work Industries");
            break;
        }
        newGroup.groupInfectionRate();                                   ///Put all the created groups in the list of groups and assign infection rates to their respective groups
        groups.push_back(newGroup);
    }
    lastWork = groups.end();                                             ///Use the last work iterator to identify where the last misc group ends and first family group begins
    lastWork--;
    familyID = lastWork->GetId()+1;

    int familyTotal = 0;
    for(int i = 1; i < population; i++)                                  ///Create a new person and a new family for every new person
    {
        family = new MixingGroups(familyID);
        family->SetGroupType("Family");
        newPerson = new Person;
        newPerson->Setid(i);
        newPerson->SetfamilyId(familyID);
        while(newPerson->Getage() < 18)
        {
            newPerson->Setage(ageDistribution(*gptr));
        }
        people.push_back(*newPerson);
        delete newPerson;
        int random = rand() % 6;

        familyTotal++;

        for(int j = 0; j < random; j++)                                  ///Generate a family and add a random number between 1 and 6 of people to add to that initial person's family
        {
            i++;
            if(i>=population)
            {
                break;
            }
            newPerson = new Person;
            newPerson->SetfamilyId(familyID);
            newPerson->Setid(i);
            while(newPerson->Getage() < 1)
            {
                newPerson->Setage(ageDistribution(*gptr));
            }
            people.push_back(*newPerson);
            delete newPerson;
        }
        groups.push_back(*family);          ///Add that family to the end of the group list
        delete family;
        familyID++;
    }
    mitr = lastWork;
    mitr ++;                                ///Set the iterator to the position of the first family group and add all those people to list of people objects
    for(Person& p : people)
    {
        if(mitr->GetId() == p.GetfamilyId())
        {
            mitr->getPointersFromActualPeopleAndAddItToPointerList(p);
            p.addGroups(*mitr);
        }
        else
        {
            mitr++;
            mitr->getPointersFromActualPeopleAndAddItToPointerList(p);
            p.addGroups(*mitr);
        }
    }
    for(Person& p : people)
    {
        mitr = groups.begin();
        switch (p.Getage())                                             /// Add students to the school respective to their age
        {
        case 1 ... 11:
            //newPerson.groups.GetGroupType("Daddy Day Care");
            for(int i=0; i < numberOfElemtarySchools(*gptr); i++)
            {
                mitr++;
            }
            mitr->addPerson(p);
            p.addGroups(*mitr);
            break;

        case 12 ... 14:
            //newPerson.groups.GetGroupType("Flip a Duh Skip a Duh Middle School");

            for(int i=0; i< numberOfMiddleSchools(*gptr); i++)
            {
                mitr++;
            }
            mitr->addPerson(p);
            p.addGroups(*mitr);
            break;
        case 15 ... 17:
            //newPerson.groups.GetGroupType("Ta Peeyuke High School");
            for(int i=0; i< numberOfHighSchools(*gptr); i++)
            {
                mitr++;
            }
            mitr->addPerson(p);
            p.addGroups(*mitr);
            break;
        case 18 ... 24:
            //newPerson.groups.GetGroupType("Trump University");
            if(numberOfUniversities(*gptr) == 1)
            {
                for(int i=0; i< 15; i++)
                {
                    mitr++;
                }
                mitr->addPerson(p);
                p.addGroups(*mitr);
            }
            break;

        }
    }

    displayTheNumberOfScrubs(population);                                       ///Display the total population and total number of families
    displayTheFamilyScrubs(familyTotal);


    cout << "You have a total of " << lastWork->GetId() << " groups. (Not including families by the way)";

    uniform_int_distribution<int> numberOfJobs(16, lastWork->GetId());
    int workGroup = 0;
    for(Person& p : people)
    {
        mitr = groups.begin();
        if(p.Getage() > 24)                                                     ///Add adults to the workgroups
        {
            workGroup = numberOfJobs(*gptr);
            std::advance(mitr, workGroup);
            mitr->addPerson(p);
        }
        else if(p.Getage() <= 24 && p.Getage() >= 18)
        {
            ///Check to see if they are in school
            switch(p.inSchoolOrNah())
            {
            case 0:                                 ///If not, send them to work
                workGroup = numberOfJobs(*gptr);
                std::advance(mitr, workGroup);
                mitr->addPerson(p);
                break;

            case 1:                                ///If so, leave them alone
                break;
            default:
                cout << "Error" << endl;
            }
        }
    }

    mitr = groups.end();
    mitr--;
    uniform_int_distribution<int> MasterListOfGroups(0, mitr->GetId());

    for(int i=0; i< MasterListOfGroups(*gptr); i++)                             ///Expose the first group randomly
    {
        mitr++;

    }

    mitr->exposePeopleInGroups();


    int numberOfInfectedPeople = 0;
    int numberOfHealthyPeople = 0;
    int numberOfExposedPeople = 0;
    int numberOfSymptomaticFeverPeople = 0;
    int numberOfSymptomaticBleedingPeople = 0;
    int numberOfDeadPeople = 0;

    ///Introduce the possibility of exposed people being infected
    for(Person& person : people)
    {

        if(person.Getstatus() == 1)
        {
            int chance = rand() % 2;

            switch(chance)
            {
            case 0:
                person.changeStatus(0);
                break;

            case 1:
                person.changeStatus(2);
                break;
            }
        }

        if(person.Getstatus() == 2)
        {
            numberOfInfectedPeople++;
        }

    }




    int newPopulation = population;


    int extinctionLevelEventStart = 0;                              ///Start counting the days once someone gets infected

    while(numberOfInfectedPeople >= 1 || numberOfDeadPeople < 500)
    {

        for(Person& p : people)
        {
            p.resetUglyProbability();                              ///Reset the probability of infection for every person at the beginning of each day
        }
        for(MixingGroups& groupsToBeInfected : groups)
        {
            groupsToBeInfected.spreadInfection();                  ///Spread the infection through every group in the list

        }
        for(Person& peopleToBeUpdated : people)
        {
            peopleToBeUpdated.probabilityFunction();               ///Update each person's probability equation and roll the dice to simulate them getting infected or not
            peopleToBeUpdated.rollInfectionProbabilty(*gptr);
            peopleToBeUpdated.updateStatus();
        }                                                         ///Update status to track where they are in terms of health of after the simulation

        mitr = groups.begin();                                    ///Reset the iterator for groups to the beginning of the list to go through each group in the next simulation
        numberOfInfectedPeople = 0;
        numberOfHealthyPeople = 0;
        numberOfExposedPeople = 0;
        numberOfSymptomaticFeverPeople = 0;
        numberOfSymptomaticBleedingPeople = 0;
        numberOfDeadPeople = 0;
        for(Person peopleToBeUpdated : people)
        {
            numberOfExposedPeople += peopleToBeUpdated.wasExposedToday();       ///Update the number of people occupying each status
            if(peopleToBeUpdated.Getstatus() >= 3)
            {
                mitr->addPerson(peopleToBeUpdated);
            }

            switch(peopleToBeUpdated.Getstatus())
            {
            case 2:
                numberOfInfectedPeople++;
                break;
            case 3:
                numberOfSymptomaticFeverPeople++;
                break;
            case 4:
                numberOfSymptomaticBleedingPeople++;
                break;
            case 5:
                numberOfDeadPeople++;
                //newPopulation--;
                break;
            }

        }

        for(Person peopleToBeUpdated : people)
        {
            if(peopleToBeUpdated.getDeadYet() == false)
            {
                if(peopleToBeUpdated.Getstatus() == 5)
                {

                    newPopulation--;
                    peopleToBeUpdated.setDeadYet(true);

                }
            }
        }

        extinctionLevelEventStart++;                                        ///Start the next day and display relevant information at the end of each day to the screen and the text file

        ofstream outfile;
        outfile.open("hemorrhagic_smallpox_results.txt");
        outfile << "End of day " << extinctionLevelEventStart << ":"<< endl;
        outfile << "The total number of people that were exposed after day " << extinctionLevelEventStart << ": " << numberOfExposedPeople << endl;
        outfile << "The total number of people that were infected after day " << extinctionLevelEventStart << ": " << numberOfInfectedPeople << endl;
        outfile << "The total number of people that were symptomatic (Fever) after day " << extinctionLevelEventStart << ": " << numberOfSymptomaticFeverPeople << endl;
        outfile << "The total number of people that were symptomatic (Bleeding) after day " << extinctionLevelEventStart << ": " << numberOfSymptomaticBleedingPeople << endl;
        outfile << "The total number of people that were dead after day " << extinctionLevelEventStart << ": " << numberOfDeadPeople << endl;
        outfile << "The current population at the end of day " << extinctionLevelEventStart << ": "<< newPopulation << endl;

        outfile.close();

        cout << "End of day " << extinctionLevelEventStart << "."<< endl;
        displayTheNumberOfExposedScrubs(numberOfExposedPeople);
        displayTheNumberOfInfectedScrubs(numberOfInfectedPeople);
        displayTheNumberOfSymptomaticFeverScrubs(numberOfSymptomaticFeverPeople);
        displayTheNumberOfSymptomaticBleedingScrubs(numberOfSymptomaticBleedingPeople);
        displayTheNumberOfDeadScrubs(numberOfDeadPeople);
        displayTheNewPopulation(newPopulation);
        char action = '\0';                                                 ///Prompt user to continue the spread of the virus
        cout << "enter key to continue";
        cin >> action;

    }


    ///866-820-8785


    return 0;
}

///Display information about the population, number families and people in each individual group, number of people exposed, infected, symptomatic, and dead.

void displayTheNumberOfScrubs(int x)
{
    cout << "¡Tienes " << x << " idiotas en tu mundo incompetente!" << endl;
}

void displayTheFamilyScrubs(int x)
{
    cout << "¡Tienes " << x << " familias incultas en tu mundo incompetente!" << endl;
}

void displayTheNumberOfExposedScrubs(int x)
{
    cout << "¡Tienes " << x << " idiotas sin educación que fueron expuestos en tu mundo incompetente!" << endl;
}

void displayTheNumberOfInfectedScrubs(int x)
{
    cout << "¡Tienes " << x << " idiotas sin educación que fueron infectados en tu mundo incompetente!" << endl;
}

void displayTheNumberOfSymptomaticFeverScrubs(int x)
{
    cout << "¡Tienes " << x << " idiotas sin educación que eran sintomáticos en tu mundo incompetente!" << endl;
}

void displayTheNumberOfSymptomaticBleedingScrubs(int x)
{
    cout << "¡Tienes " << x << " idiotas sin educación que eran sintomáticos en tu mundo incompetente!" << endl;
}

void displayTheNumberOfDeadScrubs(int x)
{
    cout << "¡Tienes " << x << " idiotas sin educación que ahora están muertos en tu mundo incompetente!" << endl;
}

void displayTheNewPopulation(int x)
{
    cout << "¡El nuevo número de idiotas en tu mundo repulsivo es " << x << "!" << endl;

}



///Data File needs, total population, total exposed, total infected, and total dead to be updated and outputed for each day.
/*
void SchoolMixingGroup(MixingGroups& personGroup, list<MixingGroups> schoolGroup, ) ///Add person to their designated school
{

}
*/



