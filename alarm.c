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
	int pre = alarm(1);
	printf("pre = %d\n", pre);

	int i = 0;
	for (;; i++) {
		printf("%d\n", i);
	}

	return 0;
}
