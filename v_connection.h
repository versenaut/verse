/*
**
*/

#include "v_network.h"

extern void *	v_con_get_network_queue(void);
extern const VNetworkAddress *	v_con_get_network_address(void);
extern void *	v_con_get_network_address_id(unsigned int id);
extern unsigned int *v_con_get_network_expected_packet(void);
extern void *	v_con_get_orderd_storage(void);
extern void *	v_con_get_func_storage(void);
extern VNetworkAddress *	v_con_connect(const char *address);
extern unsigned int v_con_get_network_address_count(void);

extern void	v_con_network_listen(void);

extern char *	v_fs_connect_get_address(void);

extern void	v_fs_connect_unpack(uint8 *data, unsigned int length, char *address);
extern void	v_fs_buf_unpack(const uint8 *data, unsigned int length);
extern void	v_fs_buf_store_pack(uint8 *data, unsigned int length);
extern boolean	v_fs_buf_unpack_stored(void);


extern boolean	v_fs_func_accept_connections(void);
extern void	v_fs_add_func(unsigned int cmd_id, unsigned int (*unpack_func)(const char *buf, size_t buffer_length), void *pack_func, void *alias_func);

extern void *	v_fs_get_alias_user_func(unsigned int cmd_id);
extern void *	v_fs_get_alias_user_data(unsigned int cmd_id);
extern void *	v_fs_get_user_func(unsigned int cmd_id);
extern void *	v_fs_get_user_data(unsigned int cmd_id);
