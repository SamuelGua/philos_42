#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	struct timeval time;
	struct timeval time2;
	gettimeofday(&time, NULL);
	for (int i = 0; i < 10000000; i++)
		;
	gettimeofday(&time2, NULL);
	double timeval1 = (time.tv_sec + ((double)time.tv_usec / 1000000)) * 1000;
	double timeval2 = (time2.tv_sec + ((double)time2.tv_usec / 1000000)) * 1000;
	double usec1 = (double)time.tv_usec / 1000000;
	double usec2 = (double)time2.tv_usec / 1000000;
	printf("time1 %ld	time2 %ld\n",time.tv_sec, time2.tv_sec);
	printf("time1 %ld	time2 %ld\n",time.tv_usec, time2.tv_usec);
	// printf("time %ld,%ld\n", (time2.tv_sec - time.tv_sec),(time2.tv_usec - time.tv_usec));
	printf("timevalsec  = %f | timevalusec  = %f\n", timeval1, usec1);
	printf("timevalsec  = %f | timevalusec  = %f\n", timeval2, usec2);
	printf("timeval = %f\n", timeval2 - timeval1);
	printf("timevalusec = %f\n", usec2 - usec1);
	return (0);

}