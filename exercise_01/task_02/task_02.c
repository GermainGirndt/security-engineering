#include <stdio.h>
#include <time.h>
int main() {
    	time_t timeT = time(NULL);
		struct tm* time = localtime(&timeT);
		char timeString[100];
		strftime(timeString, 100, "%c", time);
		printf("%s\n", timeString);
}