#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include <string.h>
#include <errno.h>
void err(const char* msg) {
	perror(msg);
	perror(strerror(errno));
	_exit(1);
}

void func(int signo) {
	printf("get info %d\n", signo);
	return;
}

void p_set(sigset_t set) {
	int i = 0;
	for (; i < 32; i++) {
		if (sigismember(&set, i)) {
			printf("1");
		} else {
			printf("0");
		}
	}

	printf("\n");
}

int main() {
	sigset_t set, oldSet, ped; // 定义一个信号集合
	int r = sigemptyset(&set); // 重置信号集合
	r = sigaddset(&set, SIGINT);
	r = sigaddset(&set, SIGQUIT);
	//r = sigprocmask(SIG_UNBLOCK, &set, &oldSet);
	r = sigprocmask(SIG_BLOCK, &set, &oldSet);

	signal(SIGINT, func);

	while (1){
		sigpending(&ped);
		p_set(ped);
		sleep(1);
	}

	return 0;
}
