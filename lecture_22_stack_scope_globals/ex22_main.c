/***********************************************************************************
* global vs static
* 
* extern
*    This keyword is a way to tell the compiler "the variable exists, but it's in 
*    another 'external' location". Typically this means that one .c file is going 
*    to use a variable that's been defined in another .c file. In this case, we're 
*    saying ex22.c has a variable THE_SIZE that will be accessed from ex22_main.c.
*
* static (file)
*    This keyword is kind of the inverse of extern and says that the variable is 
*    only used in this .c file, and should not be available to other parts of the 
*    program. Keep in mind that static at the file level (as with THE_AGE here) is 
*    different than in other places.
* 
* static (function)
*    If you declare a variable in a function static, then that variable acts like a 
*    static defined in the file, but it's only accessible from that function. It's 
*    a way of creating constant state for a function, but in reality it's rarely used 
*    in modern C programming because they are hard to use with threads. 
*
* Tips:
*    1) Avoid too many globals, especially if across multiple files. If you have to then 
*    use accessor functions like I've done with get_age. This doesn't apply to constants, 
*    since those are read-only. I'm talking about variables like THE_SIZE. If you want 
*    people to modify or set this, then make accessor functions.
*    2) Don't use function static variables like I did in update_ratio. They're rarely 
*    useful and end up being a huge pain when you need to make your code concurrent in 
*    threads. They are also hard as hell to find compared to a well done global variable.
*
***********************************************************************************/
#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
    log_info("count is: %d", count);

    if(count > 10) {
        int count = 100;  // BAD! BUGS!

        log_info("count in this scope is %d", count);
    }

    log_info("count is at exit: %d", count);

    count = 3000;

    log_info("count after assign: %d", count);
}

int main(int argc, char *argv[])
{
    // test out THE_AGE accessors
    log_info("My name: %s, age: %d", MY_NAME, get_age());

    set_age(100);

    log_info("My age is now: %d", get_age());

    // test out THE_SIZE extern
    log_info("THE_SIZE is: %d", THE_SIZE);
    print_size();

    THE_SIZE = 9;

    log_info("THE SIZE is now: %d", THE_SIZE);
    print_size();

    // test the ratio function static
    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));

    // test the scope demo
    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);

    log_info("count after calling scope_demo: %d", count);

    return 0;
}
