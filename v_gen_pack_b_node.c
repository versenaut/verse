/*
** This is automatically generated source code -- do not edit.
** Changes are affected either by editing the corresponding protocol
** definition file (v_cmd_def_X.c where X=node type), or by editing
** the code generator itself, in v_cmd_gen.c.
*/

#include <stdlib.h>
#include <stdio.h>

#include "v_cmd_gen.h"
#if !defined(V_GENERATE_FUNC_MODE)
#include "verse.h"
#include "v_cmd_buf.h"
#include "v_network_out_que.h"
#include "v_network.h"
#include "v_connection.h"

void verse_send_b_init_dimensions(VNodeID node_id, uint16 width, uint16 height, uint16 depth)
{
	uint8 *buf;
	unsigned int buffer_pos = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_50);/* Allocating the buffer */
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 80);/* Packing the command */
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_b_init_dimensions(node_id = %u width = %u height = %u depth = %u );\n", node_id, width, height, depth);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], width);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], height);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], depth);
	if(node_id == (uint32)(-1))
		v_cmd_buf_set_unique_address_size(head, 5);
	else
		v_cmd_buf_set_address_size(head, 5);
	v_cmd_buf_set_size(head, buffer_pos);
	v_noq_send_buf(v_con_get_network_queue(), head);
}

unsigned int v_unpack_b_init_dimensions(const char *buf, size_t buffer_length)
{
	unsigned int buffer_pos = 0;
	void (* func_b_init_dimensions)(void *user_data, VNodeID node_id, uint16 width, uint16 height, uint16 depth);
	VNodeID node_id;
	uint16 width;
	uint16 height;
	uint16 depth;
	
	func_b_init_dimensions = v_fs_get_user_func(80);
	if(buffer_length < 4)
		return -1;
	buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &node_id);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &width);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &height);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &depth);
#if defined V_PRINT_RECEIVE_COMMANDS
	printf("receive: verse_send_b_init_dimensions(node_id = %u width = %u height = %u depth = %u ); callback = %p\n", node_id, width, height, depth, v_fs_get_user_func(80));
#endif
	if(func_b_init_dimensions != NULL)
		func_b_init_dimensions(v_fs_get_user_data(80), node_id, width, height, depth);

	return buffer_pos;
}

void verse_send_b_layer_create(VNodeID node_id, VLayerID layer_id, const char *name, VNBLayerType type)
{
	uint8 *buf;
	unsigned int buffer_pos = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_50);/* Allocating the buffer */
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 81);/* Packing the command */
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_b_layer_create(node_id = %u layer_id = %u name = %s type = %u );\n", node_id, layer_id, name, type);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], layer_id);
	buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], name, 16);
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], (uint8)type);
	if(node_id == (uint32)(-1) || layer_id == (uint16)(-1))
		v_cmd_buf_set_unique_address_size(head, 7);
	else
		v_cmd_buf_set_address_size(head, 7);
	v_cmd_buf_set_size(head, buffer_pos);
	v_noq_send_buf(v_con_get_network_queue(), head);
}

void verse_send_b_layer_destroy(VNodeID node_id, VLayerID layer_id)
{
	uint8 *buf;
	unsigned int buffer_pos = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_50);/* Allocating the buffer */
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 81);/* Packing the command */
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_b_layer_destroy(node_id = %u layer_id = %u );\n", node_id, layer_id);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], layer_id);
	buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], NULL, 16);
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], (uint8)-1);
	if(node_id == (uint32)(-1) || layer_id == (uint16)(-1))
		v_cmd_buf_set_unique_address_size(head, 7);
	else
		v_cmd_buf_set_address_size(head, 7);
	v_cmd_buf_set_size(head, buffer_pos);
	v_noq_send_buf(v_con_get_network_queue(), head);
}

unsigned int v_unpack_b_layer_create(const char *buf, size_t buffer_length)
{
	uint8 enum_temp;
	unsigned int buffer_pos = 0;
	void (* func_b_layer_create)(void *user_data, VNodeID node_id, VLayerID layer_id, const char *name, VNBLayerType type);
	VNodeID node_id;
	VLayerID layer_id;
	char name[16];
	VNBLayerType type;
	
	func_b_layer_create = v_fs_get_user_func(81);
	if(buffer_length < 6)
		return -1;
	buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &node_id);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &layer_id);
	buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], name, 16, buffer_length - buffer_pos);
	if(buffer_length < 1 + buffer_pos)
		return -1;
	buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &enum_temp);
	type = (VNBLayerType)enum_temp;
#if defined V_PRINT_RECEIVE_COMMANDS
	if(name[0] == 0)
		printf("receive: verse_send_b_layer_destroy(node_id = %u layer_id = %u ); callback = %p\n", node_id, layer_id, v_fs_get_alias_user_func(81));
	else
		printf("receive: verse_send_b_layer_create(node_id = %u layer_id = %u name = %s type = %u ); callback = %p\n", node_id, layer_id, name, type, v_fs_get_user_func(81));
#endif
	if(name[0] == 0)
	{
		void (* alias_b_layer_destroy)(void *user_data, VNodeID node_id, VLayerID layer_id);
		alias_b_layer_destroy = v_fs_get_alias_user_func(81);
		if(alias_b_layer_destroy != NULL)
			alias_b_layer_destroy(v_fs_get_alias_user_data(81), node_id, layer_id);
		return buffer_pos;
	}
	if(func_b_layer_create != NULL)
		func_b_layer_create(v_fs_get_user_data(81), node_id, layer_id, name, (VNBLayerType)type);

	return buffer_pos;
}

void verse_send_b_layer_subscribe(VNodeID node_id, VLayerID layer_id, uint8 level)
{
	uint8 *buf;
	unsigned int buffer_pos = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_10);/* Allocating the buffer */
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 82);/* Packing the command */
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_b_layer_subscribe(node_id = %u layer_id = %u level = %u );\n", node_id, layer_id, level);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], layer_id);
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], level);
	if(node_id == (uint32)(-1) || layer_id == (uint16)(-1))
		v_cmd_buf_set_unique_address_size(head, 7);
	else
		v_cmd_buf_set_address_size(head, 7);
	v_cmd_buf_set_size(head, buffer_pos);
	v_noq_send_buf(v_con_get_network_queue(), head);
}

void verse_send_b_layer_unsubscribe(VNodeID node_id, VLayerID layer_id)
{
	uint8 *buf;
	unsigned int buffer_pos = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_10);/* Allocating the buffer */
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 82);/* Packing the command */
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_b_layer_unsubscribe(node_id = %u layer_id = %u );\n", node_id, layer_id);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], layer_id);
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], -1);
	if(node_id == (uint32)(-1) || layer_id == (uint16)(-1))
		v_cmd_buf_set_unique_address_size(head, 7);
	else
		v_cmd_buf_set_address_size(head, 7);
	v_cmd_buf_set_size(head, buffer_pos);
	v_noq_send_buf(v_con_get_network_queue(), head);
}

unsigned int v_unpack_b_layer_subscribe(const char *buf, size_t buffer_length)
{
	unsigned int buffer_pos = 0;
	void (* func_b_layer_subscribe)(void *user_data, VNodeID node_id, VLayerID layer_id, uint8 level);
	VNodeID node_id;
	VLayerID layer_id;
	uint8 level;
	
	func_b_layer_subscribe = v_fs_get_user_func(82);
	if(buffer_length < 6)
		return -1;
	buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &node_id);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &layer_id);
	buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &level);
#if defined V_PRINT_RECEIVE_COMMANDS
	if(level == 255)
		printf("receive: verse_send_b_layer_unsubscribe(node_id = %u layer_id = %u ); callback = %p\n", node_id, layer_id, v_fs_get_alias_user_func(82));
	else
		printf("receive: verse_send_b_layer_subscribe(node_id = %u layer_id = %u level = %u ); callback = %p\n", node_id, layer_id, level, v_fs_get_user_func(82));
#endif
	if(level == 255)
	{
		void (* alias_b_layer_unsubscribe)(void *user_data, VNodeID node_id, VLayerID layer_id);
		alias_b_layer_unsubscribe = v_fs_get_alias_user_func(82);
		if(alias_b_layer_unsubscribe != NULL)
			alias_b_layer_unsubscribe(v_fs_get_alias_user_data(82), node_id, layer_id);
		return buffer_pos;
	}
	if(func_b_layer_subscribe != NULL)
		func_b_layer_subscribe(v_fs_get_user_data(82), node_id, layer_id, level);

	return buffer_pos;
}

void verse_send_b_layer_set_tile(VNodeID node_id, VLayerID layer_id, uint16 tile_x, uint16 tile_y, uint16 z, VNBLayerType type, VNBTile *tile)
{
	uint8 *buf;
	unsigned int buffer_pos = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_1500);/* Allocating the buffer */
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 83);/* Packing the command */
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_b_layer_set_tile(node_id = %u layer_id = %u tile_x = %u tile_y = %u z = %u type = %u tile = %p );\n", node_id, layer_id, tile_x, tile_y, z, type, tile);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], layer_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], tile_x);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], tile_y);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], z);
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], (uint8)type);
	{
		unsigned int i;
		switch(type)
		{
			case VN_B_LAYER_UINT1 :
				buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], tile->vuint1);
			break;
			case VN_B_LAYER_UINT8 :
				for(i = 0; i < VN_B_TILE_SIZE * VN_B_TILE_SIZE; i++)
					buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], tile->vuint8[i]);
			break;
			case VN_B_LAYER_UINT16 :
				for(i = 0; i < VN_B_TILE_SIZE * VN_B_TILE_SIZE; i++)
					buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], tile->vuint16[i]);
			break;
			case VN_B_LAYER_REAL32 :
				for(i = 0; i < VN_B_TILE_SIZE * VN_B_TILE_SIZE; i++)
					buffer_pos += vnp_raw_pack_real32(&buf[buffer_pos], tile->vreal32[i]);
			break;
			case VN_B_LAYER_REAL64 :
				for(i = 0; i < VN_B_TILE_SIZE * VN_B_TILE_SIZE; i++)
					buffer_pos += vnp_raw_pack_real64(&buf[buffer_pos], tile->vreal64[i]);
			break;
		}
	}
	if(node_id == (uint32)(-1) || layer_id == (uint16)(-1) || tile_x == (uint16)(-1) || tile_y == (uint16)(-1) || z == (uint16)(-1))
		v_cmd_buf_set_unique_address_size(head, 13);
	else
		v_cmd_buf_set_address_size(head, 13);
	v_cmd_buf_set_size(head, buffer_pos);
	v_noq_send_buf(v_con_get_network_queue(), head);
}

unsigned int v_unpack_b_layer_set_tile(const char *buf, size_t buffer_length)
{
	uint8 enum_temp;
	unsigned int buffer_pos = 0;
	void (* func_b_layer_set_tile)(void *user_data, VNodeID node_id, VLayerID layer_id, uint16 tile_x, uint16 tile_y, uint16 z, VNBLayerType type, VNBTile *tile);
	VNodeID node_id;
	VLayerID layer_id;
	uint16 tile_x;
	uint16 tile_y;
	uint16 z;
	VNBLayerType type;
	VNBTile *tile;
	
	func_b_layer_set_tile = v_fs_get_user_func(83);
	if(buffer_length < 12)
		return -1;
	buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &node_id);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &layer_id);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &tile_x);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &tile_y);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &z);
	buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &enum_temp);
	type = (VNBLayerType)enum_temp;
#if defined V_PRINT_RECEIVE_COMMANDS
	printf("receive: verse_send_b_layer_set_tile(node_id = %u layer_id = %u tile_x = %u tile_y = %u z = %u type = %u ); callback = %p\n", node_id, layer_id, tile_x, tile_y, z, type, v_fs_get_user_func(83));
#endif
	{
	unsigned int i;
		VNBTile tile;
		switch(type)
		{
			case VN_B_LAYER_UINT1 :
				buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &tile.vuint1);
			break;
			case VN_B_LAYER_UINT8 :
				for(i = 0; i < VN_B_TILE_SIZE * VN_B_TILE_SIZE; i++)
					buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &tile.vuint8[i]);
			break;
			case VN_B_LAYER_UINT16 :
				for(i = 0; i < VN_B_TILE_SIZE * VN_B_TILE_SIZE; i++)
					buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &tile.vuint16[i]);
			break;
			case VN_B_LAYER_REAL32 :
				for(i = 0; i < VN_B_TILE_SIZE * VN_B_TILE_SIZE; i++)
					buffer_pos += vnp_raw_unpack_real32(&buf[buffer_pos], &tile.vreal32[i]);
			break;
			case VN_B_LAYER_REAL64 :
				for(i = 0; i < VN_B_TILE_SIZE * VN_B_TILE_SIZE; i++)
					buffer_pos += vnp_raw_unpack_real64(&buf[buffer_pos], &tile.vreal64[i]);
			break;
		}
		if(func_b_layer_set_tile != NULL && type <= VN_B_LAYER_REAL64)
			func_b_layer_set_tile(v_fs_get_user_data(83), node_id, layer_id, tile_x, tile_y, z, type, &tile);
		return buffer_pos;
	}

	if(func_b_layer_set_tile != NULL)
		func_b_layer_set_tile(v_fs_get_user_data(83), node_id, layer_id, tile_x, tile_y, z, (VNBLayerType)type, tile);

	return buffer_pos;
}

#endif

