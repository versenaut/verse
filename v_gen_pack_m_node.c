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
#include "v_network_que.h"
#include "v_network.h"
#include "v_connection.h"

void verse_send_m_fragment_create(VNodeID node_id, VNMFragmentID frag_id, VNMFragmentType type, VMatFrag *fragment)
{
	uint8 *buf;
	unsigned int buffer_pos = 0, address_size = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_1500);/* Allocating the buffer */
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 64);/* Packing the command */
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_m_fragment_create(node_id = %u frag_id = %u type = %u fragment = %p );\n", node_id, frag_id, type, fragment);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], frag_id);
	address_size = buffer_pos;
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], (uint8)type);
	switch(type)
	{
	case VN_M_FT_COLOR :
		buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->color.red);
		buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->color.green);
		buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->color.blue);
		break;
	case VN_M_FT_LIGHT :
		buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], fragment->light.type);
		buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->light.normal_falloff);
		buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], fragment->light.brdf);
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->light.brdf_r, 16);
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->light.brdf_g, 16);
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->light.brdf_b, 16);
		break;
	case VN_M_FT_REFLECTION :
		buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->reflection.normal_falloff);
		break;
	case VN_M_FT_TRANSPARENCY :
		buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->transparency.normal_falloff);
		buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->transparency.refraction_index);
		break;
	case VN_M_FT_GEOMETRY :
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->geometry.layer_r, 16);
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->geometry.layer_g, 16);
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->geometry.layer_b, 16);
		break;
	case VN_M_FT_TEXTURE :
		buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], fragment->texture.bitmap);
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->texture.layer_r, 16);
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->texture.layer_g, 16);
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->texture.layer_b, 16);
		buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->texture.mapping);
		break;
	case VN_M_FT_TAG :
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->tag.name, 16);
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->tag.group, 16);
		break;
	case VN_M_FT_NOISE :
		buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], (uint8)fragment->noise.type);
		buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->noise.mapping);
		break;
	case VN_M_FT_BLENDER :
		buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], fragment->blender.type);
		buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->blender.data_a);
		buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->blender.data_b);
		buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->blender.mapping);
		break;
	case VN_M_FT_MATRIX :
		{
			unsigned int i;
			for(i = 0; i < 16; i++)
				buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->matrix.matrix[i]);
			buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->matrix.data);
		}
		break;
	case VN_M_FT_RAMP :
		{
			unsigned int i, pos;
			double last;
			buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], fragment->ramp.type);
			buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], fragment->ramp.channel);
			buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->ramp.mapping);
			pos = buffer_pos;
			buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], fragment->ramp.point_count);
			last = fragment->ramp.ramp[0].pos - 1;
			for(i = 0; i < fragment->ramp.point_count && fragment->ramp.ramp[i].pos > last && i < 48; i++)
			{
				buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->ramp.ramp[i].pos);
				last = fragment->ramp.ramp[i].pos;
				buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->ramp.ramp[i].red);
				buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->ramp.ramp[i].green);
				buffer_pos += vnp_raw_pack_double(&buf[buffer_pos], fragment->ramp.ramp[i].blue);
			}if(i != fragment->ramp.point_count)
				vnp_raw_pack_uint8(&buf[pos], i);
		}
		break;
	case VN_M_FT_ALTERNATIVE :
		buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->alternative.alt_a);
		buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->alternative.alt_b);
		break;
	case VN_M_FT_OUTPUT :
		buffer_pos += vnp_raw_pack_string(&buf[buffer_pos], fragment->output.type, 16);
		buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->output.front);
		buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], fragment->output.back);
		break;
	}
	v_cmd_buf_set_address_size(head, address_size, buffer_pos);
	v_nq_send_buf(v_con_get_network_queue(), head);
}

void verse_send_m_fragment_destroy(VNodeID node_id, VNMFragmentID frag_id)
{
	uint8 *buf;
	unsigned int buffer_pos = 0, address_size = 0;
	VCMDBufHead *head;
	head = v_cmd_buf_allocate(VCMDBS_1500);/* Allocating the buffer */
	buf = ((VCMDBuffer10 *)head)->buf;

	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], 64);/* Packing the command */
#if defined V_PRINT_SEND_COMMANDS
	printf("send: verse_send_m_fragment_destroy(node_id = %u frag_id = %u );\n", node_id, frag_id);
#endif
	buffer_pos += vnp_raw_pack_uint32(&buf[buffer_pos], node_id);
	buffer_pos += vnp_raw_pack_uint16(&buf[buffer_pos], frag_id);
	address_size = buffer_pos;
	buffer_pos += vnp_raw_pack_uint8(&buf[buffer_pos], (uint8)-1);
	v_cmd_buf_set_address_size(head, address_size, buffer_pos);
	v_nq_send_buf(v_con_get_network_queue(), head);
}

unsigned int v_unpack_m_fragment_create(const char *buf, size_t buffer_length)
{
	unsigned int buffer_pos = 0;
	void (* func_m_fragment_create)(void *user_data, VNodeID node_id, VNMFragmentID frag_id, VNMFragmentType type, VMatFrag *fragment);
	VNodeID node_id;
	VNMFragmentID frag_id;
	uint8 type;
	VMatFrag *fragment;
	
	func_m_fragment_create = v_fs_get_user_func(64);
	if(buffer_length < 7)
		return -1;
	buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &node_id);
	buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag_id);
	buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &type);
#if defined V_PRINT_RECEIVE_COMMANDS
	if(type > VN_M_FT_OUTPUT)
		printf("receive: verse_send_m_fragment_destroy(node_id = %u frag_id = %u ); callback = %p\n", node_id, frag_id, v_fs_get_alias_user_func(64));
	else
		printf("receive: verse_send_m_fragment_create(node_id = %u frag_id = %u type = %u ); callback = %p\n", node_id, frag_id, type, v_fs_get_user_func(64));
#endif
	if(type <= VN_M_FT_OUTPUT)
	{
		VMatFrag frag;
		switch(type)
		{
		case VN_M_FT_COLOR :
			if(buffer_pos + 3 * 8 > buffer_length)
				return -1;
			buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.color.red);
			buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.color.green);
			buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.color.blue);
			break;
		case VN_M_FT_LIGHT :
			if(buffer_pos + 13 > buffer_length)
				return -1;
			buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &frag.light.type);
			buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.light.normal_falloff);
			buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &frag.light.brdf);
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.light.brdf_r, 16, buffer_length - buffer_pos);
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.light.brdf_g, 16, buffer_length - buffer_pos);
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.light.brdf_b, 16, buffer_length - buffer_pos);
			break;
		case VN_M_FT_REFLECTION :
			if(buffer_pos + 8 > buffer_length)
				return -1;
			buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.reflection.normal_falloff);
			break;
		case VN_M_FT_TRANSPARENCY :
			if(buffer_pos + 16 > buffer_length)
				return -1;
			buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.transparency.normal_falloff);
			buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.transparency.refraction_index);
			break;
		case VN_M_FT_GEOMETRY :
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.geometry.layer_r, 16, buffer_length - buffer_pos);
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.geometry.layer_g, 16, buffer_length - buffer_pos);
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.geometry.layer_b, 16, buffer_length - buffer_pos);
			break;
		case VN_M_FT_TEXTURE :
			if(buffer_pos + 4 > buffer_length)
				return -1;
			buffer_pos += vnp_raw_unpack_uint32(&buf[buffer_pos], &frag.texture.bitmap);
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.texture.layer_r, 16, buffer_length - buffer_pos);
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.texture.layer_g, 16, buffer_length - buffer_pos);
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.texture.layer_b, 16, buffer_length - buffer_pos);
			buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.texture.mapping);
			break;
		case VN_M_FT_TAG :
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.tag.name, 16, buffer_length - buffer_pos);
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.tag.group, 16, buffer_length - buffer_pos);
			break;
		case VN_M_FT_NOISE :
			if(buffer_pos + 4 > buffer_length)
				return -1;
			buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &frag.noise.type);
			buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.noise.mapping);
			break;
		case VN_M_FT_BLENDER :
			if(buffer_pos + 7 > buffer_length)
				return -1;
			buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &frag.blender.type);
			buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.blender.data_a);
			buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.blender.data_b);
			buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.blender.mapping);
			break;
		case VN_M_FT_MATRIX :
			if(buffer_pos + 8 * 16 + 2 > buffer_length)
				return -1;
			else
			{
				unsigned int i;
				for(i = 0; i < 16; i++)
					buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.matrix.matrix[i]);
				buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.matrix.data);
			}
			break;
		case VN_M_FT_RAMP :
			if(buffer_pos + 5 + 4 * 8 > buffer_length)
				return -1;
			else
			{
				unsigned int i, pos;
				double last;
				buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &frag.ramp.type);
				buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &frag.ramp.channel);
				buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.ramp.mapping);
				pos = buffer_pos;
				buffer_pos += vnp_raw_unpack_uint8(&buf[buffer_pos], &frag.ramp.point_count);
				for(i = 0; i < frag.ramp.point_count && buffer_pos + 8 * 4 <= buffer_length && i < 48; i++)
				{
					buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.ramp.ramp[i].pos);
					buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.ramp.ramp[i].red);
					buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.ramp.ramp[i].green);
					buffer_pos += vnp_raw_unpack_double(&buf[buffer_pos], &frag.ramp.ramp[i].blue);
				}if(i != frag.ramp.point_count)
					frag.ramp.point_count = i;
			}
			break;
		case VN_M_FT_ALTERNATIVE :
			if(buffer_pos + 4 > buffer_length)
				return -1;
			buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.alternative.alt_a);
			buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.alternative.alt_b);
			break;
		case VN_M_FT_OUTPUT :
			buffer_pos += vnp_raw_unpack_string(&buf[buffer_pos], frag.output.type, 16, buffer_length - buffer_pos);
			if(buffer_pos + 4 > buffer_length)
				return -1;
			buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.output.front);
			buffer_pos += vnp_raw_unpack_uint16(&buf[buffer_pos], &frag.output.back);
			break;
		}
		if(func_m_fragment_create != NULL)
			func_m_fragment_create(v_fs_get_user_data(64), node_id, frag_id, type, &frag);
		return buffer_pos;
	}

	if(type > VN_M_FT_OUTPUT)
	{
		void (* alias_m_fragment_destroy)(void *user_data, VNodeID node_id, VNMFragmentID frag_id);
		alias_m_fragment_destroy = v_fs_get_alias_user_func(64);
		if(alias_m_fragment_destroy != NULL)
			alias_m_fragment_destroy(v_fs_get_alias_user_data(64), node_id, frag_id);
		return buffer_pos;
	}
	if(func_m_fragment_create != NULL)
		func_m_fragment_create(v_fs_get_user_data(64), node_id, frag_id, (VNMFragmentType)type, fragment);

	return buffer_pos;
}

#endif

