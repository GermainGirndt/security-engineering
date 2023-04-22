#include <stdio.h>
#include <time.h>
int main() {
		time_t timeT = time(NULL);
		char* timeString = ctime(&timeT);
		printf("%s", timeString);
}