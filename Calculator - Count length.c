/* This function counts how many digits are present in the longint
   and returns this number.
*/
int count_length(longint_t var) {
    int counter = 0;
    /* Start counting from the right hand side at INT_ZERO. Since
       everything was set to zero at the beginning, everything on the
       right hand side of the array should be zero, each time it notices
       a zero, the counter will increase. However, if it runs into a 
       non zero number, it means that the actual longint number begins
       here. To get the length of the longint number, just minus the 
       largest number of digits possible, INTSIZE, by the number of 
       zeros encountered.
    */
    for (int j = INTSIZE; j > 0; j--) {
        if (var[j] != INT_ZERO) {
            return INTSIZE - counter;
        }
        else {
            counter++;
        }
    }

    /* If the function does not return by this point, it means that
       variable is 0.
    */
    return INTSIZE - counter;
}