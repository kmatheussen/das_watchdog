#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	struct sched_param params;
	// "done" is volatile to prevent the compiler from optimising the
	// time-wasting loops below into nothing.
	volatile int done = 0;
	struct timeval tv;
	time_t startsec;
	unsigned long int loops;
	int outer_loops;

	params.sched_priority = 1;
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &params);


	{
	  struct sched_param par;
	  par.sched_priority = sched_get_priority_min(SCHED_FIFO);
	  if(sched_setscheduler(0,SCHED_FIFO,&par)==-1){
	    fprintf(stderr,"das_watchdog: Unable to set SCHED_FIFO realtime priority for the watchdog thread. Exiting.\n");
	    return 0;
	  }
	}

	gettimeofday(&tv,0);
	startsec = tv.tv_sec;

	printf("My pid is %d\n",getpid());
	sleep(1);
	  
#if 0
	while(!done) {
		gettimeofday(&tv, 0);
		if(tv.tv_sec - startsec > 10)
			done = 1;		
	}
#else
	for (outer_loops = 0; outer_loops < 10; ++outer_loops) {
		for (loops = 0; loops < 1000000000; loops++)
		  {
		    done += 1;
		    //sched_yield();
		  }
	}
#endif
	exit (EXIT_SUCCESS);
}
