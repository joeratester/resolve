#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "resolve.h"

static void print_information(struct addrinfo *);
static void die(const char *, ... );
static void print_address(struct sockaddr *);

/* reslove name to address */
void resolve_address(const char *host,
		     const char *port)
{
	struct addrinfo *info;
	int ret_val = 0;

	ret_val = getaddrinfo(host, port, NULL,
			      &info);
	if (!ret_val)
		print_information(info);
	else
		die("resolve_address failed : %s\n",
		    gai_strerror(ret_val));

	/* free */
	freeaddrinfo(info);
}


/* print information */
static void print_information(struct addrinfo *info)
{
	
	for (;info; info = info->ai_next)
		print_address(info->ai_addr);
}

/* print address */
static void print_address(struct sockaddr *addr)
{
	void *numeric_address;
	in_port_t port;
	char buffer[INET6_ADDRSTRLEN];
	
	if (addr->sa_family == AF_INET) {
		numeric_address = &((struct sockaddr_in *)addr)->sin_addr;
		port = ntohs(((struct sockaddr_in *)addr)->sin_port);
	} else if (addr->sa_family == AF_INET6) {
		numeric_address = &((struct sockaddr_in6 *)addr)->sin6_addr;
		port = ntohs(((struct sockaddr_in6 *)addr)->sin6_port);
	}
	else
		fprintf(stderr, "[unknown type]\n");
       

	if (!inet_ntop(addr->sa_family, numeric_address,
		      buffer, sizeof(buffer))) 
		fprintf(stderr, "Invalid address\n");
	else 
		printf("%s:%u\n", buffer, port);
	
}


void die(const char *format, ...)
{
	va_list args;
	va_start(args,format);
	vfprintf(stderr, format, args);
	va_end(args);
}
