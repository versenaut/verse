/*
**
*/

#if !defined V_NETWORK_H
#define	V_NETWORK_H

#include <netinet/in.h>

#define VERSE_STD_CONNECT_PORT 4950

typedef struct{
	/* IPv4 & IPv6 */
	unsigned int addrtype;
	struct sockaddr_in addr4;
	struct sockaddr_in6 addr6;
}VNetworkAddress;

extern boolean	compare_ip6_addr(struct in6_addr *addr1, struct in6_addr *addr2);
extern void		v_n_set_port(unsigned short port);
extern void		v_n_set_protocol(unsigned int protocol);
extern unsigned int	v_n_wait_for_incoming(unsigned int microseconds);
extern boolean	v_n_set_network_address(VNetworkAddress *address, const char *host_name);
extern int		v_n_send_data(VNetworkAddress *address, const char *data, size_t length);
extern int		v_n_receive_data(VNetworkAddress *address, char *data, size_t length);
extern void		v_n_get_address_string(const VNetworkAddress *address, char *string);

extern void		v_n_get_current_time(unsigned int *seconds, unsigned int *fractions);

#endif		/* V_NETWORK_H */
