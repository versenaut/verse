
#include <stdlib.h>
#include <stdio.h>
#include "verse_header.h"
#include "v_cmd_gen.h"
#include "v_cmd_buf.h"

#if defined(V_GENERATE_FUNC_MODE)

void v_gen_system_cmd_def(void)
{
	v_cg_new_manual_cmd(0, "connect", "VSession *verse_send_connect(const char *name, const char *pass, const char *address)", NULL, NULL);

/*	v_cg_new_cmd(V_NT_SYSTEM,		"connect", 0, VCGCT_ONCE);
	v_cg_add_param(VCGP_NAME,		"name");
	v_cg_add_param(VCGP_NAME,		"pass");
	v_cg_add_param(VCGP_POINTER_TYPE,	"char");
	v_cg_add_param(VCGP_POINTER,	"address");
	v_cg_add_param(VCGP_POINTER_TYPE,	"VSession *");
	v_cg_add_param(VCGP_POINTER,	"connection");
	v_cg_add_param(VCGP_PACK_INLINE, "\t{\n"
	"\t\tvoid *con;\n"
	"\t\tcon = v_con_connect(address);\n"
	"\t\tif(connection != NULL)\n"
	"\t\t\t*connection = con;\n"
	"\t}\n");
	v_cg_add_param(VCGP_UNPACK_INLINE, "\t{\n"
	"\t\tif(func_connect != NULL)\n"
	"\t\t\tfunc_connect(user_data, name, pass, v_fs_connect_get_address(), NULL);\n"
	"\t\treturn buffer_pos;\n"
	"\t}\n");
	v_cg_end_cmd();
*/
	v_cg_new_manual_cmd(1, "connect_accept", "VSession *verse_send_connect_accept(VNodeID avatar, const char *address)", NULL, NULL);
/*
	v_cg_new_cmd(V_NT_SYSTEM,		"acsept_connect", 1, VCGCT_UNIQUE);
	v_cg_add_param(VCGP_NODE_ID,		"avatar");
	v_cg_add_param(VCGP_POINTER_TYPE,	"char");
	v_cg_add_param(VCGP_POINTER,	"address");
	v_cg_add_param(VCGP_POINTER_TYPE,	"VSession *");
	v_cg_add_param(VCGP_POINTER,	"connection");
	v_cg_add_param(VCGP_PACK_INLINE, "\t{\n"
	"\t\tvoid *con;\n"
	"\t\tcon = v_con_connect(address);\n"
	"\t\tif(connection != NULL)\n"
	"\t\t\t*connection = con;\n"
	"\t}\n");
	v_cg_end_cmd();
*/
	v_cg_new_cmd(V_NT_SYSTEM,		"connect_deny", 2, VCGCT_UNIQUE);
	v_cg_add_param(VCGP_POINTER,	"address");
	v_cg_add_param(VCGP_PACK_INLINE, "\t{\n"
	"\t\tvoid *a;\n"
	"\t\ta = v_n_create_network_address(0, address);\n"
	"\t\tbuffer_pos = vnp_raw_pack_uint16(&buf[buffer_pos], 1);/* a packet id */\n"
	"\t\tbuffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 2);/* Packing the command */\n"
	"\t\tv_n_send_data(buf, a, buffer_pos);\n"
	"\t\tv_n_destroy_network_address(a);\n"
	"\t\tv_cmd_buf_free(head);\n"
	"\t\treturn;\n"
	"\t}\n");
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"connect_terminate", 3, VCGCT_UNIQUE);
	v_cg_add_param(VCGP_LONG_NAME,	"bye");
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"get_time", 4, VCGCT_UNIQUE);
	v_cg_add_param(VCGP_UINT32,		"time");
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"ping", 5, VCGCT_UNIQUE);
	v_cg_add_param(VCGP_LONG_NAME,	"address");
	v_cg_add_param(VCGP_LONG_NAME,	"text");
	v_cg_add_param(VCGP_PACK_INLINE, "\t{\n"
	"\t\tvoid *a;\n"
	"\t\ta = v_n_create_network_address(0, address);\n"
	"\t\tbuffer_pos = vnp_raw_pack_uint16(&buf[buffer_pos], 1);/* a packet id */\n"
	"\t\tbuffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 5);/* Packing the command */\n"
	"\t\tbuffer_pos += vnp_raw_pack_string(&buf[buffer_pos], text, 500);\n"
	"\t\tv_n_send_data(buf, a, buffer_pos);\n"
	"\t\tv_n_destroy_network_address(a);\n"
	"\t\tv_cmd_buf_free(head);\n"
	"\t\treturn;\n"
	"\t}\n");
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"error_message", 6, VCGCT_UNIQUE);
	v_cg_add_param(VCGP_LONG_NAME, "message");

	v_cg_new_cmd(V_NT_SYSTEM,		"packet_ack", 7, VCGCT_INVISIBLE_SYSTEM);
	v_cg_add_param(VCGP_UINT32,		"packet_id");
	v_cg_add_param(VCGP_PACK_INLINE, "\tv_cmd_buf_set_uniqe_size(head, buffer_pos);\n"
	"\tv_nq_send_ack_nak_buf(v_con_get_network_queue(), head);\n"
	"\treturn;\n");
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"packet_nak", 8, VCGCT_INVISIBLE_SYSTEM);
	v_cg_add_param(VCGP_UINT32,		"packet_id");
	v_cg_add_param(VCGP_PACK_INLINE, "\tv_cmd_buf_set_uniqe_size(head, buffer_pos);\n"
	"\tv_nq_send_ack_nak_buf(v_con_get_network_queue(), head);\n"
	"\treturn;\n");
	v_cg_end_cmd();


	v_cg_new_cmd(V_NT_SYSTEM,		"node_list", 9, VCGCT_NORMAL);
	v_cg_add_param(VCGP_UINT32,		"mask");
	v_cg_add_param(VCGP_END_ADDRESS, NULL);
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"node_create", 10, VCGCT_NORMAL);
	v_cg_add_param(VCGP_NODE_ID,	"node_id");
	v_cg_add_param(VCGP_END_ADDRESS, NULL);
	v_cg_add_param(VCGP_ENUM_NAME,	"VNodeType");
	v_cg_add_param(VCGP_ENUM,		"type");
	v_cg_add_param(VCGP_NODE_ID,	"owner_id");
	v_cg_alias(FALSE, "node_destroy", "if(owner_id == -1 || type >= V_NT_NUM_TYPES)", 1, NULL);
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"node_subscribe", 11, VCGCT_NORMAL);
	v_cg_add_param(VCGP_NODE_ID,	"node_id");
	v_cg_add_param(VCGP_END_ADDRESS, NULL);
	v_cg_alias(TRUE, "node_unsubscribe", NULL, 1, NULL);
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"tag_group_create", 16, VCGCT_NORMAL);
	v_cg_add_param(VCGP_NODE_ID,	"node_id");
	v_cg_add_param(VCGP_UINT16,		"group_id");
	v_cg_add_param(VCGP_END_ADDRESS, NULL);
	v_cg_add_param(VCGP_NAME,		"name");
	v_cg_alias(FALSE, "tag_group_destroy", "if(name[0] == 0)", 2, NULL);
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"tag_group_subscribe", 17, VCGCT_NORMAL);
	v_cg_add_param(VCGP_NODE_ID,	"node_id");
	v_cg_add_param(VCGP_UINT16,		"group_id");
	v_cg_add_param(VCGP_END_ADDRESS, NULL);
	v_cg_alias(TRUE, "tag_group_unsubscribe", NULL, 2, NULL);
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"tag_create", 18, VCGCT_NORMAL);
	v_cg_add_param(VCGP_NODE_ID,	"node_id");
	v_cg_add_param(VCGP_UINT16,		"group_id");
	v_cg_add_param(VCGP_UINT16,		"tag_id");
	v_cg_add_param(VCGP_END_ADDRESS, NULL);
	v_cg_add_param(VCGP_NAME,		"name");
	v_cg_add_param(VCGP_ENUM_NAME,	"VNTagType");
	v_cg_add_param(VCGP_ENUM,		"type");
	v_cg_add_param(VCGP_POINTER_TYPE, "VNTag");
	v_cg_add_param(VCGP_POINTER,	"tag"); 
	v_cg_add_param(VCGP_PACK_INLINE, "\tif(type > VN_TAG_BLOB)\n"
	"\t{\n"
	"\t\tv_cmd_buf_free(head);\n"
	"\t\treturn;\n"
	"\t}\n"
	"\tswitch(type)\n"
	"\t{\n"
	"\t\tcase VN_TAG_BOOLEAN :\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], ((VNTag *)tag)->active);\n"
	"\t\tbreak;\n"
	"\t\tcase VN_TAG_INTEGER :\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], ((VNTag *)tag)->integer);\n"
	"\t\tbreak;\n"
	"\t\tcase VN_TAG_REAL :\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_double(&buf[buffer_pos], ((VNTag *)tag)->real);\n"
	"\t\tbreak;\n"
	"\t\tcase VN_TAG_STRING :\n"
	"\t\t{\n"
	"\t\t\tunsigned int i;\n"
	"\t\t\tfor(i = 0; ((VNTag *)tag)->string[i] != 0 && i < VN_TAG_MAX_BLOB_SIZE; i++)\n"
	"\t\t\t\tbuffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], ((VNTag *)tag)->string[i]);\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 0);\n"
	"\t\t}\n"
	"\t\tbreak;\n"
	"\t\tcase VN_TAG_VECTOR :\n"
	"\t\t{\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_double(&buf[buffer_pos], ((VNTag *)tag)->vector[0]);\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_double(&buf[buffer_pos], ((VNTag *)tag)->vector[1]);\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_double(&buf[buffer_pos], ((VNTag *)tag)->vector[2]);\n"
	"\t\t}\n"
	"\t\tbreak;\n"
	"\t\tcase VN_TAG_LINK :\n"
	"\t\t{\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], ((VNTag *)tag)->link);\n"
	"\t\t}\n"
	"\t\tbreak;\n"
	"\t\tcase VN_TAG_ANIMATION :\n"
	"\t\t{\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], ((VNTag *)tag)->animation.curve);\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], ((VNTag *)tag)->animation.start);\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], ((VNTag *)tag)->animation.end);\n"
	"\t\t}\n"
	"\t\tbreak;\n"
	"\t\tcase VN_TAG_BLOB :\n"
	"\t\t{\n"
	"\t\t\tunsigned int i;\n"
	"\t\t\tif(((VNTag *)tag)->blob.blob_size > VN_TAG_MAX_BLOB_SIZE)\n"
	"\t\t\t\t((VNTag *)tag)->blob.blob_size = VN_TAG_MAX_BLOB_SIZE;\n"
	"\t\t\tbuffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], ((VNTag *)tag)->blob.blob_size);\n"
	"\t\t\tfor(i = 0; i < ((VNTag *)tag)->blob.blob_size; i++)\n"
	"\t\t\t\tbuffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], ((uint8 *)((VNTag *)tag)->blob.blob)[i]);\n"
	"\t\t}\n"
	"\t\tbreak;\n"
	"\t}\n");
	v_cg_add_param(VCGP_UNPACK_INLINE, "\tif(type < VN_TAG_TYPE_COUNT)\n"
	"\t{\n"
	"\t\tVNTag tag;\n"
	"\t\tunsigned int i;\n"
	"\t\tchar string[VN_TAG_MAX_BLOB_SIZE];\n"
	"\t\tswitch(type)\n"
	"\t\t{\n"
	"\t\t\tcase VN_TAG_BOOLEAN :\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &tag.active);\n"
	"\t\t\tbreak;\n"
	"\t\t\tcase VN_TAG_INTEGER :\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &tag.integer);\n"
	"\t\t\tbreak;\n"
	"\t\t\tcase VN_TAG_REAL :\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &tag.real);\n"
	"\t\t\tbreak;\n"
	"\t\t\tcase VN_TAG_STRING :\n"
	"\t\t\t{\n"
	"\t\t\t\ttag.string = string;\n"
	"\t\t\t\tvnp_raw_unpack_string(&buf[buffer_pos], string, VN_TAG_MAX_BLOB_SIZE, buffer_length - buffer_pos);\n"
	"\t\t\t}\n"
	"\t\t\tbreak;\n"
	"\t\t\tcase VN_TAG_VECTOR :\n"
	"\t\t\t{\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &tag.vector[0]);\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &tag.vector[1]);\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &tag.vector[2]);\n"
	"\t\t\t}\n"
	"\t\t\tbreak;\n"
	"\t\t\tcase VN_TAG_LINK :\n"
	"\t\t\t{\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &tag.link);\n"
	"\t\t\t}\n"
	"\t\t\tbreak;\n"
	"\t\t\tcase VN_TAG_ANIMATION :\n"
	"\t\t\t{\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &tag.animation.curve);\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &tag.animation.start);\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &tag.animation.end);\n"
	"\t\t\t}\n"
	"\t\t\tbreak;\n"
	"\t\t\tcase VN_TAG_BLOB :\n"
	"\t\t\t{\n"
	"\t\t\t\tbuffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &tag.blob.blob_size);\n"
	"\t\t\t\tif(tag.blob.blob_size > VN_TAG_MAX_BLOB_SIZE)\n"
	"\t\t\t\t\ttag.blob.blob_size = VN_TAG_MAX_BLOB_SIZE;\n"
	"\t\t\t\ttag.blob.blob = string;\n"
	"\t\t\t\tfor(i = 0; i < tag.blob.blob_size; i++)\n"
	"\t\t\t\t\tbuffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &string[i]);\n"
	"\t\t\t}\n"
	"\t\t\tbreak;\n"
	"\t\t}\n"
	"\t\tif(func_tag_create != NULL)\n"
	"\t\tfunc_tag_create(user_data, node_id, group_id, tag_id, name, type, &tag);\n"
	"\t\treturn buffer_pos;\n"
	"\t}\n");
	v_cg_alias(FALSE, "tag_destroy", "", 3, NULL);
	v_cg_end_cmd();

	v_cg_new_cmd(V_NT_SYSTEM,		"node_name_set", 19, VCGCT_NORMAL); 
	v_cg_add_param(VCGP_NODE_ID,	"node_id");
	v_cg_add_param(VCGP_END_ADDRESS, NULL);
	v_cg_add_param(VCGP_LONG_NAME,	"name");

	v_cg_end_cmd();
}

#endif
