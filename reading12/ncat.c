
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

void usage (const char * program_name, int status) {
	fprintf(stderr, "Usage: %s HOST PORT\n", program_name);
	_exit(status);
}

int main (int argc, char ** argv) {

	char * PROGRAM_NAME = argv[0];
	if (argc != 3) usage(PROGRAM_NAME, 1);

	char * HOST = argv[1];
	char * PORT = argv[2];

	int sockfd;
	char buf[BUFSIZ] = {0};
	struct addrinfo hints, * servinfo, * p;
	int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(HOST, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "Could not loop up %s:%s: %s\n", HOST, PORT, gai_strerror(rv));
		return(EXIT_FAILURE);
	}

	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			fprintf(stderr, "Unable to connect to %s:%s: %s\n", HOST, PORT, strerror(errno));
			//perror("client: socket");
			return(EXIT_FAILURE);
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			fprintf(stderr, "Unable to connect to %s:%s: %s\n", HOST, PORT, strerror(errno));
			freeaddrinfo(servinfo);
			close(sockfd);
			return(EXIT_FAILURE);
			//perror("client: connect");
			continue;
		}
		break;
	}	

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}

	printf("Connected to %s:%s\n", HOST, PORT);

	fgets(buf, BUFSIZ, stdin);
	if (send(sockfd, buf, BUFSIZ, 0) == -1) {
		fprintf(stderr, "Error sending\n");
	}

	freeaddrinfo(servinfo);
	close(sockfd);

	return EXIT_SUCCESS;
}
