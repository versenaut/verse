/*
**
*/

#include <stdio.h>
#include <stdlib.h>

#include "v_cmd_gen.h"

#if !defined V_GENERATE_FUNC_MODE

#include "verse.h"
#include "vs_server.h"

extern void verse_send_o_link_set(VNodeID node_id, uint16 link_id, VNodeID link, const char *name, uint32 target_id);
extern void verse_send_o_link_destroy(VNodeID node_id, uint16 link_id);

typedef struct {
	VNodeID link;
	char	name[16];
	uint32	target_id;
} VSLink;

typedef struct {
	char		name[16];
	uint8		param_count;
	VNOParamType *param_types;
	char		*param_names;
} VSMethod;

typedef struct {
	char		name[VN_O_METHOD_GROUP_NAME_SIZE];
	VSMethod	*methods;
	unsigned int	method_count;
	VSSubscriptionList *subscribers;
} VSMethodGroup;

typedef struct {
	VSNodeHead	head;
	double		light[3];
	VSMethodGroup	*groups;
	uint16		group_count;
	VSLink		*links;
	uint16		link_count;
} VSNodeObject;

VSNodeObject * vs_o_create_node(unsigned int owner)
{
	VSNodeObject *node;
	unsigned int i;
	char name[48];
	node = malloc(sizeof *node);
	vs_add_new_node(&node->head, V_NT_OBJECT);
	sprintf(name, "Object_Node_%u", node->head.id);
	create_node_head(&node->head, name, owner);
	node->groups = malloc((sizeof *node->groups) * 16);
	node->group_count = 16;
	for(i = 0; i < 16; i++)
	{
		node->groups[i].name[0] = 0;
		node->groups[i].methods = NULL;
		node->groups[i].method_count = 0;
		node->groups[i].subscribers = NULL;
	}

	node->links = malloc((sizeof *node->links) * 16);
	node->link_count = 16;
	for(i = 0; i < 16; i++)
	{
		node->links[i].link = -1;
		node->links[i].name[0] = 0;
		node->links[i].target_id = -1;
	}
	return node;
}

void vs_o_destroy_node(VSNodeObject *node)
{
	unsigned int i, j;
	destroy_node_head(&node->head);
	for(i = 0; i < node->group_count; i++)
	{
		if(node->groups[i].name[0] != 0)
		{
			for(j = 0; j < node->groups[i].method_count; j++)
			{
				if(node->groups[i].methods[j].name[0] != 0 && node->groups[i].methods[j].param_count != 0)
				{
					free(node->groups[i].methods[j].param_types);
					free(node->groups[i].methods[j].param_names);
				}
			}
			if(node->groups[i].methods != NULL)
				free(node->groups[i].methods);
		}
	}
	free(node->groups);
	free(node);
}

void vs_o_subscribe(VSNodeObject *node)
{
	unsigned int i;
	for(i = 0; i < node->link_count; i++)
		if(node->links[i].name[0] != 0)
			verse_send_o_link_set(node->head.id, i, node->links[i].link, node->links[i].name, node->links[i].target_id);
	if(node->light[0] > -0.000001 && node->light[0] < 0.000001 && node->light[1] > -0.000001 && node->light[1] < 0.000001 && node->light[2] > -0.000001 && node->light[2] < 0.000001)
		verse_send_o_set_light(node->head.id, node->light[0], node->light[1], node->light[2]);
	for(i = 0; i < node->group_count; i++)
		if(node->groups[i].name[0] != 0)
			verse_send_o_method_group_create(node->head.id, i, node->groups[i].name);
}

static void callback_send_o_set_light(void *user, VNodeID node_id, real64 light_r, real64 light_g, real64 light_b)
{
	VSNodeObject *node;
	unsigned int i, count;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL)
		return;
	node->light[0] = light_r;
	node->light[1] = light_g;
	node->light[2] = light_b;
	count =	vs_get_subscript_count(node->head.subscribers);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->head.subscribers, i);
		verse_send_o_set_light(node_id, light_r, light_g, light_b);
	}
	vs_reset_subscript_session();
}

static void callback_send_o_link_set(void *user, VNodeID node_id, uint16 link_id, VNodeID link, const char *name, uint32 target_id)
{
	VSNodeObject *node;
	unsigned int i, count;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL)
		return;

	if(name[0] == 0)
		return;
	if(vs_get_node_head(link) == 0)
		link = 0;

	if(link_id >= node->link_count || node->links[link_id].name[0] == 0)
	{
		for(link_id = 0; link_id < node->link_count && node->links[link_id].name[0] != 0; link_id++);
	
		if(link_id == node->link_count)
		{
			i = node->link_count;
			node->link_count += 16;
			node->links = realloc(node->links, (sizeof *node->links) * node->link_count);
			for(; i < node->link_count; i++)
				node->links[link_id].name[i] = 0;
		}
	}

	node->links[link_id].link = -1;
	node->links[link_id].name[0] = 0;
	node->links[link_id].target_id = -1;

	count =	vs_get_subscript_count(node->head.subscribers);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->head.subscribers, i);
		verse_send_o_link_set(node_id, link_id, link, name, target_id);
	}
	vs_reset_subscript_session();
}

static void callback_send_o_link_destroy(void *user, VNodeID node_id, uint16 link_id)
{
	VSNodeObject *node;
	unsigned int i, count;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL)
		return;

	if(link_id >= node->link_count || node->links[link_id].name[0] == 0)
		return;

	node->links[link_id].name[0] = 0;

	count =	vs_get_subscript_count(node->head.subscribers);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->head.subscribers, i);
		verse_send_o_link_destroy(node_id, link_id);
	}
	vs_reset_subscript_session();
}

static void callback_send_o_method_group_create(void *user, VNodeID node_id, uint16 group_id, char *name)
{
	VSNodeObject *node;
	unsigned int i, j, count;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL || vs_get_node(node_id, V_NT_OBJECT) == NULL)
		return;

	for(i = 0; i < node->group_count; i++)
	{
		for(j = 0; node->groups[i].name[j] == name[j] && node->groups[i].name[j] != 0; j++);
		if(node->groups[i].name[j] == name[j])
			return;
	}
	if(group_id < node->group_count && node->groups[group_id].name[0] != 0)
	{
		for(i = 0; i < 16; i++)
			node->groups[group_id].name[i] = name[i];
	}else
	{
		for(group_id = 0; group_id < node->group_count && node->groups[group_id].name[0] != 0; group_id++)
		if(group_id == node->group_count)
		{
			node->groups = realloc(node->groups, sizeof(*node->groups) * (node->group_count + 16));
			for(i = node->group_count; i < node->group_count + 16U; i++)
			{
				node->groups[i].name[0] = 0;
				node->groups[i].methods = NULL;
				node->groups[i].method_count = 0;
			}
			node->group_count += 16;
		}
		node->groups[group_id].subscribers = vs_create_subscription_list();
	}
	count =	vs_get_subscript_count(node->head.subscribers);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->head.subscribers, i);
		verse_send_o_method_group_create(node_id, group_id, name);
	}
	vs_reset_subscript_session();
}

static void callback_send_o_method_group_destroy(void *user, VNodeID node_id, uint16 group_id)
{
	VSNodeObject *node;
	unsigned int i, count;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL || vs_get_node(node_id, V_NT_OBJECT) == NULL)
		return;

	if(group_id >= node->group_count || node->groups[group_id].name[0] == 0)
		return;
	node->groups[group_id].name[0] = 0;
	for(i = 0; i < node->groups[group_id].method_count; i++)
	{
		if(node->groups[group_id].methods[i].name[0] != 0 && node->groups[group_id].methods[i].param_count > 0)
		{
			free(node->groups[group_id].methods[i].param_names);
			free(node->groups[group_id].methods[i].param_types);
		}
	}
	free(node->groups[group_id].methods);
	node->groups[group_id].methods = NULL;
	node->groups[group_id].method_count = 0;
	vs_destroy_subscription_list(node->groups[group_id].subscribers);
	count =	vs_get_subscript_count(node->head.subscribers);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->head.subscribers, i);
		verse_send_o_method_group_destroy(node_id, group_id);
	}
	vs_reset_subscript_session();
}

static void callback_send_o_method_group_subscribe(void *user, VNodeID node_id, uint16 group_id)
{
	VSNodeObject *node;
	unsigned int i, j;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL || vs_get_node(node_id, V_NT_OBJECT) == NULL)
		return;
	if(group_id < node->group_count && node->groups[group_id].name[0] != 0)
		vs_add_new_subscriptor(node->groups[group_id].subscribers);
	for(i = 0; i < node->groups[group_id].method_count; i++)
	{
		if(node->groups[group_id].methods[i].name[0] != 0)
		{
			char *names[255];
			for(j = 0; j < node->groups[group_id].methods[i].param_count; j++)
				names[j] = &node->groups[group_id].methods[i].name[j * 16];
			verse_send_o_method_create(node_id, group_id, i, node->groups[group_id].methods[i].name, node->groups[group_id].methods[i].param_count, node->groups[group_id].methods[i].param_types, names);
		}
	}
}

static void callback_send_o_method_group_unsubscribe(void *user, VNodeID node_id, uint16 group_id)
{
	VSNodeObject *node;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL || vs_get_node(node_id, V_NT_OBJECT) == NULL)
		return;
	if(group_id < node->group_count && node->groups[group_id].name[0] != 0)
		vs_remove_subscriptor(node->groups[group_id].subscribers);
}

static void callback_send_o_method_create(void *user, VNodeID node_id, uint16 group_id, uint16 method_id, char *name, uint8 param_count, VNOParamType *param_types, char * *param_names)
{
	VSNodeObject *node;
	unsigned int i, j, count;
	VSMethodGroup *group;

	node = (VSNodeObject *) vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL || vs_get_node(node_id, V_NT_OBJECT) == NULL)
		return;

	if(group_id >= node->group_count || node->groups[group_id].name[0] == 0)
		return;

	group = &node->groups[group_id];
	for(i = 0; i < group->method_count; i++)
	{
		for(j = 0; group->methods[i].name[j] == name[j] && group->methods[i].name[j] != 0; j++);
		if(group->methods[i].name[j] == name[j])
			return;
	}
	if(method_id < group->method_count && group->methods[method_id].name[0] != 0)
	{
		for(i = 0; i < 16; i++)
			group->methods[method_id].name[i] = name[i];
		if(group->methods[method_id].param_count != 0)
		{
			free(group->methods[method_id].param_names);
			free(group->methods[method_id].param_types);
		}
	}else
	{
		for(method_id = 0; method_id < group->method_count && group->methods[method_id].name[0] != 0; method_id++)
		if(group_id == group->method_count)
		{
			group->methods = realloc(group->methods, sizeof(*group->methods) * (group->method_count + 16));
			for(i = group->method_count; i < group->method_count + 16; i++)
				group->methods[i].name[0] = 0;
			group->method_count += 16;
		}
	}

	for(i = 0; i < VN_O_METHOD_NAME_SIZE && name[i] != 0; i++)
		group->methods[method_id].name[i] = name[i];
	group->methods[method_id].name[i] = '\0';
	
	group->methods[method_id].param_count = param_count; 
	group->methods[method_id].param_types = malloc((sizeof *group->methods[method_id].param_types) * param_count);
	group->methods[method_id].param_names = malloc((sizeof *group->methods[method_id].param_names) * param_count * 16);
	for(i = 0; i < param_count; i++)
	{
		group->methods[method_id].param_types[i] = param_types[i];
		for(j = 0; j < 15 && param_names[j] != 0; j++)
			group->methods[method_id].param_names[i * 16 + j] = param_names[i][j];
		group->methods[method_id].param_names[i * 16 + j] = param_names[i][j];
	}
	count =	vs_get_subscript_count(node->groups[group_id].subscribers);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->groups[group_id].subscribers, i);
		verse_send_o_method_create(node_id, group_id, method_id, name, param_count, param_types, param_names);
	}
	vs_reset_subscript_session();
}

static void callback_send_o_method_destroy(void *user, VNodeID node_id, uint16 group_id, uint16 method_id)
{
	VSNodeObject *node;
	unsigned int i, count;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL || vs_get_node(node_id, V_NT_OBJECT) == NULL)
		return;
	if(group_id >= node->group_count || node->groups[group_id].name[0] == 0 || method_id >= node->groups[group_id].method_count || node->groups[group_id].methods[method_id].name[0] == 0)
		return;

	node->groups[group_id].methods[method_id].name[0] = 0;
	if(node->groups[group_id].methods[method_id].param_count != 0)
	{
		free(node->groups[group_id].methods[method_id].param_names);
		free(node->groups[group_id].methods[method_id].param_types);
	}
	count =	vs_get_subscript_count(node->groups[group_id].subscribers);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->groups[group_id].subscribers, i);
		verse_send_o_method_destroy(node_id, group_id, method_id);
	}
	vs_reset_subscript_session();
}

static void callback_send_o_method_send(void *user, VNodeID node_id, uint16 group_id, uint16 method_id, VNodeID sender, void *params)
{
	VNOParam unpacked_params[255];
	void *data;
	VSNodeObject *node;
	unsigned int i, count;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL || vs_get_node(node_id, V_NT_OBJECT) == NULL)
		return;

	if(group_id >= node->group_count || node->groups[group_id].name[0] == 0 || method_id >= node->groups[group_id].method_count || node->groups[group_id].methods[method_id].name[0] == 0)
		return;
	if(!verse_unpack_method_call(params, node->groups[group_id].methods[method_id].param_count, unpacked_params, node->groups[group_id].methods[method_id].param_types))
		return;
	sender = vs_get_avatar();
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->groups[group_id].subscribers, i);
		data = verse_pack_method_call(node->groups[group_id].methods[method_id].param_count, unpacked_params, node->groups[group_id].methods[method_id].param_types);
		if(data != NULL)
			verse_send_o_method_send(node_id, group_id, method_id, sender, data);
	}
	vs_reset_subscript_session();

}


void vs_o_callback_init(void)
{
	verse_callback_set(verse_send_o_link_set, callback_send_o_link_set, NULL);
	verse_callback_set(verse_send_o_set_light, callback_send_o_set_light, NULL);
	verse_callback_set(verse_send_o_link_set, callback_send_o_link_set, NULL);
	verse_callback_set(verse_send_o_link_destroy, callback_send_o_link_destroy, NULL);
	verse_callback_set(verse_send_o_method_group_create, callback_send_o_method_group_create, NULL);
	verse_callback_set(verse_send_o_method_group_destroy, callback_send_o_method_group_destroy, NULL);
	verse_callback_set(verse_send_o_method_group_subscribe, callback_send_o_method_group_subscribe, NULL);
	verse_callback_set(verse_send_o_method_group_unsubscribe, callback_send_o_method_group_unsubscribe, NULL);
	verse_callback_set(verse_send_o_method_create, callback_send_o_method_create, NULL);
	verse_callback_set(verse_send_o_method_destroy, callback_send_o_method_destroy, NULL);
	verse_callback_set(verse_send_o_method_send, callback_send_o_method_send, NULL);
}

#endif
