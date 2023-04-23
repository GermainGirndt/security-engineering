#include <stdio.h>
#include <time.h>
int main()
{
	char *STANDARD_DATE_AND_TIME_STRING_FORMAT = "%c";
	int TIME_STRING_MAX_SIZE = 100;

	time_t timeT = time(NULL);

	struct tm *time = localtime(&timeT);
	char timeString[TIME_STRING_MAX_SIZE];
	strftime(timeString, TIME_STRING_MAX_SIZE, STANDARD_DATE_AND_TIME_STRING_FORMAT, time);
	printf("%s\n", timeString);
}