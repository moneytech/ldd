#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

char buf[1024];

int main(void)
{
	int fd;
	int ret;
	char *ptr;
	int i;

	system("ps -eo vsz,rss,pid,comm | grep a.out");
	system("cat /proc/meminfo | grep MemFree");
	
	fd = open("/dev/my_mem0", O_RDWR | O_SYNC);
	if (fd < 0) {
		printf("fail to open my_mem0\n");
		return 0;
	}

	ptr = mmap(NULL, 4096*16, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED) {
		perror("mmap failed");
	}

	printf("ptr-%p\n", ptr);
	for (i = 0; i < 30; i++) {
		printf("%x ", ptr[i]);
	}
	printf("\n");

	system("ps -eo vsz,rss,pid,comm | grep a.out");
	system("cat /proc/meminfo | grep MemFree");
	system("cat /proc/self/maps");

	munmap(ptr, 4096*16);
	close(fd);

	return 0;
}
