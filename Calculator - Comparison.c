/* Checks if the var2 variable is larger than the var1 variable. Returns
   True if var2 is larger and returns False if var1 is larger using a flag.
*/
int 
check_if_var2_bigger(longint_t var1, longint_t var2) {
    int var_2_is_bigger = FALSE;
    
    /* If var2 has more digits than var1, it is larger than var1. 
    */
    if (var2[INT_ZERO] > var1[INT_ZERO]) {
        var_2_is_bigger = TRUE;
        return var_2_is_bigger;
    }
    /* If they have the same number of digits, loop through each digit to
       determine which one is larger. 
    */
    else if (var2[INT_ZERO] == var1[INT_ZERO]) {
        for (int i = var2[0]; i > INT_ZERO; i--) {
            if (var2[i] > var1[i]) {
                var_2_is_bigger = TRUE;
                return var_2_is_bigger;
            }
            else if (var2[i] == var1[i]) {
                 continue;
            }
            else {
                return var_2_is_bigger;
            }
        }
        return var_2_is_bigger;
    }
    /* If var2 does not have more than or equal number of digits
       to var1, then var1 has more digits so var1 is larger. 
    */
    else {
        return var_2_is_bigger;       
    }
}