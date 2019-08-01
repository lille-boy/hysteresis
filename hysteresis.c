/*
 * Example of a hysteresis
 * The hysteresis takes a percentage as an input
 * It ouputs a level between 0 and 4
 */
 
unsigned int hysteresis(unsigned int an_volt_percent) {
    unsigned int discrete_level = 0;
    static unsigned int prev_discrete_level;
    
    
    prev_discrete_level = discrete_level;
    
    return discrete_level;
}
