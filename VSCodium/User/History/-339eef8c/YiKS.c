#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


void error(const char *msg)
{
    perror(msg);
    exit(1);
}


int main(int argc, char *argv[])
{	

    // Check if the required number of arguments is provided
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s -p <port>\n", argv[0]);
        exit(1);
    }

    int port;

	// Parse command line arguemnts
	for (int i = 1; i < argc; i++)
	{
		// Chekc for port switch
		if (strcmp(argv[i], "-p") == 0)
		{
            if (argv[i + 1])
            {
                port = atoi(argv[i + 1]);
                if (port <= 0)
                {
                    fprintf(stderr, "[ERROR] Port must be a positive integer.\n");
                    return 1;
                }
            }
        }
        
        // Add other switches here if needed.

	}


    // Start server socket
    if (port)
    {

        int sockfd, connfd, len;
        struct sockaddr_in server_addr, client_addr;
        socklen_t client_len;

        // Creating socket
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) // socket() returns -1 on error.
        {
            error("[ERROR] could not open socket.");
        }

        // Clearing server address memory space to avoid funny business.
        bzero((char *) &server_addr, sizeof(server_addr));
 
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        // Binding socket
        if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        {
           error("[ERROR] could not bind socket");
        }
        
 
        if (listen(sockfd, 3))
        {
            
        }


        // printf("[LISTENING] Server started on port %d\n", port);
    }
    else
    {
        fprintf(stderr, "[ERROR] No port provided. Idk how you even reached this error idiot tf u doing\n");
    }

    return 0;
}
