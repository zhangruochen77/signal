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

// struct sigaction {
//		void	 (*sa_handler)(int);
//		void     (*sa_sigaction)(int, siginfo_t *, void *);
//		sigset_t   sa_mask;
//		int        sa_flags;
//		void     (*sa_restorer)(void);
// };
int main() {
	int signum = SIGINT; // 设置信号值
	struct sigaction act, oldact; // 信号对象
	sigset_t set; // 信号集合
	sigemptyset(&set); // 重置信息集合
	act.sa_sigaction = func; // 信号回调函数
	act.sa_mask = set;
	int r = sigaction(signum, &act, &oldact); // 信号注册
	if (-1 == r) { // 错误判断
		err("sigaction err\n");
	}


	while (1) {

	}

	return 0;
}

