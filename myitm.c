#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

#include <string.h>
#include <errno.h>
void err(const char* msg) {
	perror(msg);
	perror(strerror(errno));
	_exit(1);
}

int main() {
	int which = ITIMER_REAL;
	struct itimerval newVal;
	struct itimerval* oldVal;
	newVal.it_interval.tv_sec = 1;
	newVal.it_value.tv_sec = 2;
	newVal.it_interval.tv_usec = 1;
	newVal.it_value.tv_sec = 2;
//	signal(SIGALRM, myfunc);
	int ret = setitimer(which, &newVal, oldVal);
	if (-1 == ret) {
		err("setitimer error\n");
	}
	
	int i = 0;
	while (1) {
		printf("%d\n",i++);
	}

	return 0;
}
