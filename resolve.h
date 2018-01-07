#ifndef RESOLVE_H
#define RESOLVE_H

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern void resolve_address(const char *
			    , const char *);

#endif /* RESOLVE_H */
