#include <stdio.h>
#include <time.h>

// Based on the time library tutorial
// https://www.youtube.com/watch?v=Qoed2uBwF_o

int main()
{

    time_t now = time(NULL);
    printf("Seconds since Jan. 1, 1970: %ld\n", now);

    // passing the pointer to the time_t variable to the ctime function,
    // which returns a pointer to the string
    char *string_now = ctime(&now);

    printf("Actual time: %s/n", string_now);

    return 0;
}