# Bioterrorist-Attack
An infestation of small pox has all of a sudden broke out and started to decimate a population! This program will simulate how long it will take for the disease to spread and take out an entire community.
Store probabilities within specific mixing groups and add those probabilities to each person populating them.
Certain risk of illness will vary based on jobs.
Start day count
Start updating status of each person as each day progress as the virus gets introduced
For family mixing groups, get number of children and number of adults and then calculate probability for infectiousness based off of their respective probabilities
Traverse each person in each mixing group
Remove all person pointers that are dead
Expose 1 MG -> update status and inform MGs -> Change of status -> MGs compute score -> Person computes 1-Pi -> Change Status
Make <MG>, Make <People>, Expose 1 MG, <MG> informs <Persons> change of Status
Time Loop: {Each person informs all of their mixing groups of the change in status, Each mixing group computes score (1-p)^n, Each person computes 1-Pi(Scores) -roll dice}
Person chance of getting infected: 1-[(.98)(number of people exposed to and their respective probabilities)]
