/*
**
*/

#if defined WIN32
#include <winsock.h>
typedef unsigned int uint;
typedef SOCKET VSocket;
#else
typedef int VSocket;
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#include "v_cmd_gen.h"
#include "v_network.h"

typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned char uint8;
typedef char int8;

#define	TRUE	1
#define	FALSE	0

typedef struct{
	struct sockaddr_in address;
	struct hostent *he;
} VNetworkConnection;

#define VERSE_STD_CONNECT_TO_PORT 4950

struct VNetworkAddress {
	VSocket	socket;
	uint32	their_ip;
	uint16	their_port;
	uint16	my_port;
};

VSocket v_n_socket_create(void)
{
	VSocket sock;

	if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		return -1;
#if defined(_WIN32)
	if(ioctlsocket(sock, FIONBIO, &one) != 0)
		return -1;
#else
	if(fcntl(sock, F_SETFL, O_NONBLOCK) != 0)
		return -1;
#endif
	return sock;
}

void v_n_socket_destroy(VSocket s)
{
#if defined(_WIN32)
	closesocket(s);
#else
	close(s);
#endif
}

void v_n_destroy_network_address(VNetworkAddress *address)
{
	v_n_socket_destroy(address->socket);
	free(address);
}

void v_n_print_address(VNetworkAddress *address)
{
	printf("%u.%u.%u.%u:%u", address->their_ip / (256 * 256 * 256), (address->their_ip / (256 * 256)) % 256, (address->their_ip / 256) % 256, address->their_ip % 256, address->their_port);
}

/* A strdup() implementation, since we can't depend on it being available in e.g. Windows. */
static char * v_n_strdup(const char *str)
{
	size_t	len;
	char	*buf;

	if(str == NULL)
		return NULL;
	len = strlen(str);
	if((buf = malloc(len + 1)) != NULL)
	{
		strcpy(buf, str);
		return buf;
	}
	return NULL;
}

VNetworkAddress * v_n_create_network_address(int my_port, const char *addr)
{
	VNetworkAddress *address;
	struct sockaddr_in address_in;

#if defined(WIN32)
	static boolean initialized = FALSE;
	if(!initialized)
	{

		WSADATA wsaData;
		if(WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
		{
			fprintf(stderr, "WSAStartup failed.\n");
			exit(1);
		}
		initialized = TRUE;
	}
#endif
	address = malloc(sizeof *address);
	if((address->socket = v_n_socket_create()) != -1)
	{
		char *work = v_n_strdup(addr), *colon;
		uint16 their_port = VERSE_STD_CONNECT_TO_PORT;
		int ok = FALSE;
		struct hostent *he;

		if((colon = strchr(work, ':')) != NULL)
		{
			unsigned int tp;

			*colon = '\0';
			if(sscanf(colon + 1, "%u", &tp) == 1)
				their_port = tp;
		}
		if((he = gethostbyname(work)) != NULL)
		{
			address->my_port = my_port;
			memcpy(&address->their_ip, he->h_addr_list[0], he->h_length);
			address->their_ip = ntohl(address->their_ip);
			address->their_port = their_port;

			address_in.sin_family = AF_INET;     /* host byte order */
			address_in.sin_port = htons(my_port); /* short, network byte order */
			address_in.sin_addr.s_addr = INADDR_ANY;
			bind(address->socket, (struct sockaddr *)&address_in, sizeof(struct sockaddr));
			ok = TRUE;
		}
		free(work);
		if(ok)
			return address;
		v_n_socket_destroy(address->socket);
	}
	free(address);
	return NULL;
}

unsigned int v_n_send_data(VNetworkAddress *address, const char *data, unsigned int length)
{
	unsigned int size,  i;
	struct sockaddr_in address_in;
	address_in.sin_family = AF_INET;     /* host byte order */
	address_in.sin_port = htons(address->their_port); /* short, network byte order */
	address_in.sin_addr.s_addr = htonl(address->their_ip);
	for(i = 0; i < 8; i++)
		((char *)address_in.sin_zero)[i] = 0; /* zero the rest of the struct */
	size = sendto(address->socket, data, length, 0, (struct sockaddr *) &address_in, sizeof(struct sockaddr));

	return size;
}

#if !defined(V_GENERATE_FUNC_MODE)

extern void *v_con_get_network_address_id(unsigned int id);
extern unsigned int v_con_get_network_address_count();

void v_n_wait_for_inncoming(unsigned int milliseconds) 
{
	struct timeval tv;
	unsigned int count, i;
	fd_set fd_select;
	VNetworkAddress *address;
	if(milliseconds == 0)
		return;
	tv.tv_sec = milliseconds / 1000000;
	tv.tv_usec = milliseconds % 1000000;
	FD_ZERO(&fd_select);
	count = v_con_get_network_address_count();
	for(i = 0; i < count; i++)
	{
		address = v_con_get_network_address_id(i);
		FD_SET(address->socket, &fd_select);
	}
	select(i, &fd_select, NULL, NULL, &tv);
}

#endif

unsigned int v_n_receive_data(VNetworkAddress *address, char *data, unsigned int length, int connection_exclusive)
{
	unsigned int size, from_length;
	struct sockaddr_in address_in;
	memset(&address_in, 0, sizeof address_in);
	address_in.sin_family = AF_INET;
	address_in.sin_port = htons(address->my_port); 
	address_in.sin_addr.s_addr = INADDR_ANY;
	from_length = sizeof(struct sockaddr);
	size = recvfrom(address->socket, data, length, 0, (struct sockaddr *) &address_in, &from_length);
	if(size == -1)
		return -1;
	if(connection_exclusive && ntohl(address_in.sin_addr.s_addr) != address->their_ip)
		return -1;
	address->their_ip = ntohl(address_in.sin_addr.s_addr);
	address->their_port = ntohs(address_in.sin_port);
	return size;
}

void v_n_get_address_string(const VNetworkAddress *address, char *string)
{
	sprintf(string, "%u.%u.%u.%u:%u", address->their_ip / (256 * 256 * 256), (address->their_ip / (256 * 256)) % 256, (address->their_ip / 256) % 256, address->their_ip % 256, address->their_port);
}
