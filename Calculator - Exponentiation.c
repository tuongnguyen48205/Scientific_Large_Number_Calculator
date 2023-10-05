/* Update the indicated variable var1 by doing a exponentiation
   using var2 to compute var1 = var1 ^ var2.
*/
void 
do_power(longint_t var1, longint_t var2) {
    /* anything to the power of zero is one.
    */
    if ((var2[INT_ZERO] == INT_ONE || var2[INT_ZERO] == INT_ZERO)
        && var2[INT_ONE] == INT_ZERO) {
        var1[INT_ZERO] = INT_ONE;
        var1[INT_ONE] = INT_ONE;
        return;
    }
    
    /* zero to the power of anything other than zero is zero and one to the
       power of anything is one.
    */
    if ((var1[INT_ZERO] == INT_ONE || var1[INT_ZERO] == INT_ZERO)
        && var1[INT_ONE] == INT_ZERO) {
        return;
    }
    else if (var1[INT_ZERO] == INT_ONE && var1[INT_ONE] == INT_ONE) {
        return;
    }
    
    /* It isn't possible to have a power greater than 1660 so deal with 
       this now for efficiency.
    */
    longint_t max_power = {LONG_ZERO};
    max_power[INT_ZERO] = INT_FOUR;
    max_power[INT_ONE] = INT_ZERO;
    max_power[INT_TWO] = INT_SIX;
    max_power[INT_THREE] = INT_SIX;
    max_power[INT_FOUR] = INT_ONE;
    
    if (check_if_var2_bigger(max_power, var2) == TRUE) {
        print_error("This operation leads to integer overflow.");
        exit(EXIT_FAILURE);
    }
    
    /* Exponentiation can be done through repeated multiplication. For
       example, var1^3 is var1 multiplied by var1 3 times. However, as the
       multiplications happen, var1 is altered and so temp is used to store
       the original var1.
    */
    longint_t temp;
    do_assign(temp, var1);
    
    /* Do the repeated multiplication var2 number of times. var2 is 
       reduced by one each time in the cycle until it is one.
    */
    while (TRUE) {
        longint_t one = {LONG_ZERO};
        one[INT_ZERO] = INT_ONE;
        one[INT_ONE] = INT_ONE;
        if (var2[INT_ZERO] == INT_ONE && var2[INT_ONE] == INT_ONE) {
            break;
        }
        else {
            do_minus(var2, one);
            /* No need to place length of the resultant number in index
               zero since the do_multiplication function already does this.
            */
            do_multiply(var1, temp);
        }
    }

    /* Now to deal with integer overflow.
    */
    if ((var1[INT_ZERO] == INT_ONE || var1[INT_ZERO] == INT_ZERO)
        && var1[INT_ONE] == INT_ZERO) {
        print_error("This operation leads to integer overflow.");
        exit(EXIT_FAILURE);
    }
}
