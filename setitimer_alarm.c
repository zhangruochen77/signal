#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include <string.h>
#include <errno.h>
void err(const char* msg) {
	perror(msg);
	perror(strerror(errno));
	_exit(1);
}

// 使用 setitimer 实现 alarm
int main() {
	int which = ITIMER_REAL;
	struct itimerval val;
	struct itimerval* old;
	val.it_value.tv_sec = 1;
	val.it_interval.tv_sec = 0;
	val.it_value.tv_usec = 0;
	val.it_interval.tv_usec = 0;
	int ret = setitimer(ITIMER_REAL, &val, old);
	if (-1 == ret) {
		err("setitimer error\n");
	}

	int j = 0;
	while (1) {
		j++;
		printf("%d\n", j);
	}

	return 0;
}
