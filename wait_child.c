#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include <string.h>
#include <errno.h>
void err(const char* msg) {
	perror(msg);
	perror(strerror(errno));
	_exit(1);
}

void catch_child(signum) {
	int status;
	pid_t pid;
	while (-1 != (pid = waitpid(-1, &status, 0))) {
		if (-1 == pid) {
			err("wait error\n");
		} else {
			printf("wait %d\n", pid);
		}
	}
}

int main() {
	sigset_t set;
	sigemptyset(&set); // 至空信号集合
	sigaddset(&set, SIGCHLD); // 添加子进程结束信号响应
	sigprocmask(SIG_BLOCK, &set, NULL); // 设置将信号响应应用到实际进程当中
	int i;
	const int end = 15;
	for (i = 0; i < end; i++) { // 创建子进程
		pid_t p = fork();
		if (-1 == p) {
			err("fork error\n");
		} else if (0 == p) {
			break;
		}
	}

	if (end == i) { // 父进程
		struct sigaction act;
		act.sa_sigaction = catch_child; // 捕捉处理函数
		sigemptyset(&(act.sa_mask));    // 制空信号集合
		sigaction(SIGCHLD, &act, NULL); // 注册信号
		sigprocmask(SIG_UNBLOCK, &set, NULL); // 设置信号响应到实际进程

		sleep(1);
	} else { // child 
		printf("child %d\n", getpid());
	}
}
