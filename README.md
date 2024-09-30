./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

◦ number_of_philosophers: The number of philosophers and also the number \n
of forks.
◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die \n
milliseconds since the beginning of their last meal or the beginning of the simulation, they die. \n
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. \n
During that time, they will need to hold two forks. \n
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping. \n
◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies. \n
• Each philosopher has a number ranging from 1 to number_of_philosophers. \n
• Philosopher number 1 sits next to philosopher number number_of_philosophers. \n
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
6 \n
Philosophers I never thought philosophy would be so deadly \n
About the logs of your program: \n
• Any state change of a philosopher must be formatted as follows: \n
◦ timestamp_in_ms X has taken a fork \n
◦ timestamp_in_ms X is eating \n
◦ timestamp_in_ms X is sleeping \n
◦ timestamp_in_ms X is thinking \n
◦ timestamp_in_ms X died \n
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number. \n
• A displayed state message should not be mixed up with another message. \n
• A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher. \n
• Again, philosophers should avoid dying! \n
