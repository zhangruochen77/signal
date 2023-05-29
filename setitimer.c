#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <errno.h>
void err(const char* msg) {
	perror(msg);
	perror(strerror(errno));
	_exit(1);
}

int main() {
	int which = 0;
	struct itimerval* newVal, olbVal;
	int ret = setitimer();
}
