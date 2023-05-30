#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <string.h>
#include <errno.h>
void err(const char * msg) {
	perror(msg);
	perror(strerror(errno));
	_exit(1);
}

void sig_catch(int signo) {
	printf("signo = %d\n", signo);
}

int main() {

	signal(SIGINT, sig_catch); // 注册信息
	signal(SIGQUIT, sig_catch); // 注册信息

	while (1) {

	}

	return 0;
}
