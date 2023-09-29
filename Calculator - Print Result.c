/* Print out a longint value
*/
void
do_print(int varnum, longint_t var) {   

    printf("register %c: ", varnum+CH_A);
    
    /* If the variable has no register, the default value is 0. 
    */
    if (var[INT_ZERO] == INT_ZERO) {
        printf("%d", INT_ZERO);
    }
        
    /* The following is responsible for actually printing the variable
       number as well as placing commas in the appropriate locations.
    */      
    for (int i = var[INT_ZERO]; i > INT_ZERO; i--) {
        if (i % INT_THREE == INT_ZERO && i != var[INT_ZERO]) {
            printf(",%d", var[i]);
        }
        else {
            printf("%d", var[i]);
        }
    }
    
    /* Now print new line character for next function call. 
    */
    printf("\n");
}