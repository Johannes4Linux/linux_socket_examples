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

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket");
		return sockfd;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	inet_aton("127.0.0.1", &addr.sin_addr);

	status = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	if (status) {
		perror("connect");
		close(sockfd);
		return status;
	}

	sprintf(text, "Hello from the Client!\n");
	send(sockfd, text, strlen(text), 0);

	status = recv(sockfd, text, sizeof(text), 0);
	if (status > 0)
		printf("%s", text);

	close(sockfd);
	return 0;
}
