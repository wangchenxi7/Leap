#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main() {
	int is_session_create = 326;
	char *ipaddr = "rdma://1,10.0.0.4:9400";

	syscall(is_session_create, ipaddr);
	return 0;
}
