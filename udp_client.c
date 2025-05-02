#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main()
{
	int sockfd, status;
	struct sockaddr_in addr;
	char text[255];
	socklen_t addr_len = sizeof(addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket");
		return sockfd;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	inet_aton("127.0.0.1", &addr.sin_addr);

	sprintf(text, "Hello from the Client!\n");
	sendto(sockfd, text, strlen(text), 0, (struct sockaddr *) &addr, addr_len);

	status = recvfrom(sockfd, text, sizeof(text), 0, (struct sockaddr *) &addr, &addr_len);
	if (status > 0)
		printf("%s", text);

	close(sockfd);
	return 0;
}
