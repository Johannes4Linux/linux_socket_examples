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
	int sockfd, status, opt = 1;
	struct sockaddr_in addr, client_addr;
	char text[255];
	socklen_t addr_len = sizeof(client_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket");
		return sockfd;
	}

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;

	status = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	if (status) {
		perror("bind");
		close(sockfd);
		return status;
	}

	status = recvfrom(sockfd, text, sizeof(text), 0, (struct sockaddr *) &client_addr, &addr_len);
	if (status > 0)
		printf("%s", text);

	printf("Client Port: %d, Client IP Addr: %s\n", client_addr.sin_port, inet_ntoa(client_addr.sin_addr));


	sprintf(text, "The Server says Hello :-)\n");
	sendto(sockfd, text, strlen(text), 0, (struct sockaddr *) &client_addr, addr_len);

	close(sockfd);
	return 0;
}
