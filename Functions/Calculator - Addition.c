/* Update the indicated variable var1 by doing an addition
   using var2 to compute var1 = var1 + var2
*/
void
do_plus(longint_t var1, longint_t var2) {
    /* check which of the two variables is larger. 
    */
    int larger_num = var1[INT_ZERO];
    if (check_if_var2_bigger(var1, var2) == TRUE) {
        larger_num = var2[INT_ZERO];
    }
    
    /* Time to actually do the addition and deal with integer overflow.
       To save time, this only needs to be looped through 'the number of
       digits of the larger number' times, else it'll keep adding 0 to the 
       following digit which is redundant.
    */
    for (int j = 1; j <= larger_num + INT_ONE; j++) {
        var1[j] += var2[j];
        /* Each array index can only contain one digit so if it goes over
           ten, add one to the next number to be added and reduce it so that
           it only contains one digit instead of two. Also, the resultant
           number after addition can be at most only one digit larger than
           the larger number between var1 and var2 so if this happens and
           either var1 or var2 happen to be INTSIZE digits long, this would
           lead to integer overflow.
        */
        if (var1[j] >= INT_TEN) {
            if (j == INTSIZE) {
                print_error("This operation leads to integer overflow.");
                exit(EXIT_FAILURE);
            }
            var1[j] -= INT_TEN;
            var2[j + INT_ONE] += INT_ONE;
        }
    } 
    
    /* Now find out how long the resultant number is.
    */
    var1[INT_ZERO] = count_length(var1); 
}
