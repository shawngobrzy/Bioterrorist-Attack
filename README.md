# Bioterrorist-Attack
This program models the outbreak and spread of smallpox within a population, simulating how long it would take for the disease to impact an entire community. The simulation uses distinct mixing groups to store infection probabilities, which are assigned to each individual based on their participation in those groups. The risk of illness varies according to factors such as occupation.

Key simulation components include:

Day-by-day tracking: The simulation begins with the introduction of the virus, tracking the progression of the disease and updating each individual's status daily.

Family mixing groups: For family units, the number of adults and children is considered, and the probability of infection is calculated based on their respective risk levels.

Mixing group traversal: The model traverses all individuals within each mixing group, removing deceased individuals and adjusting the probability calculations for the remaining population.

Infection exposure process: One mixing group is exposed to the virus, which triggers an update in the infection status of individuals. This, in turn, informs the associated mixing groups, updating their respective probabilities.

Simulation loop: In each time step, individuals notify their mixing groups of any status changes, mixing groups compute updated infection probabilities, and individuals recalculate their chance of infection based on the formula: 1−𝑃𝑖, where 𝑃𝑖 represents the combined probabilities of exposure.

Infection probability: Each person’s chance of infection is calculated using the formula 1−[(0.98)^number of exposures and respective probabilities], providing a dynamic model of the virus's impact.

This comprehensive simulation offers insights into how smallpox might spread through a community, accounting for individual risk factors and interaction patterns.
