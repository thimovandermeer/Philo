// three things are being done by a group of philosophers eating sleaping and thinking
// they cant do the same thing at the same time
// they should eat with two forks 
// the philosophers must never starve
// they need to eat
// they dont speak to eachother 
// they dont know when another philosophers is going to die
// as soon as they finish eating they drop the forks and start sleeping
// when a philosopher is done sleeping he starts eating
// the simulation stops when a philosopher dies



// every program has these inputs
// number of philosophers
	// is the number of philosophers and also the number of forks
// time to die
	// this counter start when the program start or when the philosopher has eaten the last time if it hits zero the philosopher dies
// time to eat
	// this is the length of eating time for this time the philo occupies two forks
// time to sleep 
	// this is the time a philo is sleeping
// and optional number of times each philosopher must eat
	// if all philosophers have eaten this much times the simulation stops

// each philosoper should be given a number from one to number of philosopers
// the philosopers are seated in order of numbers given above
// any change of status needs to be written according a format:
	//	timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
	//	timestamp_in_ms X is sleeping
	//	timestamp_in_ms X is thinking
	//	timestamp_in_ms X died
// the status must not be scrambled with another status
// you cant have more than 10 ms between the death of a philosopher and when it will print its death
// philosopers should avoid to die