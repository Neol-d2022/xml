#include <stdlib.h>
#include <string.h>

#include "vector.h"

typedef struct STRUCT_XML_NODE {
	char *key_char;
	char *val_char;
	VECTOR *nodes_VECTOR;
	void **index_void;
	unsigned int order_uint;
} XML_NODE;

XML_NODE* CreateXMLNode_XML_NODE(void) {
	XML_NODE *ret_XML_NODE;
	
	ret_XML_NODE = malloc(sizeof(*ret_XML_NODE));
	if(!ret_XML_NODE) return 0;
	memset(ret_XML_NODE, 0, sizeof(*ret_XML_NODE));
	return ret_XML_NODE;
}

void DestroyXMLNode_void(XML_NODE *parent_XML_NODE) {
	unsigned int idx_uint, n_uint;
	
	if(parent_XML_NODE->nodes_VECTOR) {
		n_uint = VectorGetElementCount_uint(parent_XML_NODE->nodes_VECTOR);
		for(idx_uint = 0; idx_uint < n_uint; idx_uint += 1)
			DestroyXMLNode_void(VectorAt_void(parent_XML_NODE->nodes_VECTOR, idx_uint));
		DestroyVector_void(parent_XML_NODE->nodes_VECTOR, 0);
	}
	
	if(parent_XML_NODE->key_char) free(parent_XML_NODE->key_char);
	if(parent_XML_NODE->val_char) free(parent_XML_NODE->val_char);
	if(parent_XML_NODE->index_void) free(parent_XML_NODE->index_void);
}

char* SetXMLKey_char(XML_NODE *x_XML_NODE, const char *str_char) {
	size_t len;
	char *new_char;
	
	len = strlen(str_char);
	new_char = malloc(len + 1);
	if(!new_char) return 0;
	memcpy(new_char, str_char, len + 1);
	if(x_XML_NODE->key_char) free(x_XML_NODE->key_char);
	x_XML_NODE->key_char = new_char;
	return new_char;
}

char* GetXMLKey_char(XML_NODE *x_XML_NODE) {
	return x_XML_NODE->key_char;
}

char* SetXMLVal_char(XML_NODE *x_XML_NODE, const char *str_char) {
	size_t len;
	char *new_char;
	
	if(x_XML_NODE->nodes_VECTOR) return 0;
	
	len = strlen(str_char);
	new_char = malloc(len + 1);
	if(!new_char) return 0;
	memcpy(new_char, str_char, len + 1);
	if(x_XML_NODE->val_char) free(x_XML_NODE->val_char);
	x_XML_NODE->val_char = new_char;
	return new_char;
}

char* GetXMLVal_char(XML_NODE *x_XML_NODE) {
	return x_XML_NODE->val_char;
}

static int cmpXMLNodeKey_int(const void *a, const void *b) {
	XML_NODE *c = *((XML_NODE**)a);
	XML_NODE *d = *((XML_NODE**)b);
	
	return strcmp(c->key_char, d->key_char);
}

static int cmpXMLNodeOrder_int(const void *a, const void *b) {
	XML_NODE *c = *((XML_NODE**)a);
	XML_NODE *d = *((XML_NODE**)b);
	
	if(c->order_uint > d->order_uint) return 1;
	else if(c->order_uint < d->order_uint) return -1;
	else return 0;
}

int AddXMLNode_int(XML_NODE *parent_XML_NODE, XML_NODE *child_XML_NODE) {
	unsigned int childCount_uint;
	
	if(parent_XML_NODE->val_char) return -1;
	
	if(!parent_XML_NODE->nodes_VECTOR) {
		parent_XML_NODE->nodes_VECTOR = CreateVector_VECTOR(sizeof(*child_XML_NODE));
		if(!parent_XML_NODE->nodes_VECTOR) return -1;
	}
	
	childCount_uint = VectorGetElementCount_uint(parent_XML_NODE->nodes_VECTOR);
	child_XML_NODE->order_uint = childCount_uint;
	if(!AddToVector_VECTOR(parent_XML_NODE->nodes_VECTOR, child_XML_NODE)) {
		return -1;
	}
	
	if(parent_XML_NODE->index_void) free(parent_XML_NODE->index_void);
	parent_XML_NODE->index_void = VectorIndex_void(parent_XML_NODE->nodes_VECTOR, cmpXMLNodeKey_int);
	return 0;
}

XML_NODE* GetXMLNodeByKey_XML_NODE(XML_NODE *parent_XML_NODE, const char *key_char) {
	XML_NODE _key_XML_NODE;
	XML_NODE *key_XML_NODE;
	
	if(!(parent_XML_NODE->index_void)) return 0;
	_key_XML_NODE.key_char = (char*)key_char;
	key_XML_NODE = &_key_XML_NODE;
	return *((XML_NODE**)bsearch(&key_XML_NODE, parent_XML_NODE->index_void, VectorGetElementCount_uint(parent_XML_NODE->nodes_VECTOR), sizeof(*(parent_XML_NODE->index_void)), cmpXMLNodeKey_int));
}

XML_NODE* GetXMLNodeByOrder_XML_NODE(XML_NODE *parent_XML_NODE, unsigned int order_uint) {
	XML_NODE key_XML_NODE;
	
	if(!(parent_XML_NODE->nodes_VECTOR)) return 0;
	key_XML_NODE.order_uint = order_uint;
	return (XML_NODE*)VectorFind_void(parent_XML_NODE->nodes_VECTOR, &key_XML_NODE, cmpXMLNodeOrder_int);
}

int RemoveXMLNodeByOrder_int(XML_NODE *parent_XML_NODE, unsigned int order_uint) {
	XML_NODE key_XML_NODE;
	XML_NODE *res_XML_NODE;
	
	res_XML_NODE = GetXMLNodeByOrder_XML_NODE(parent_XML_NODE, order_uint);
	if(!res_XML_NODE) return -1;
	DestroyXMLNode_void(res_XML_NODE);
	key_XML_NODE.order_uint = order_uint;
	return VectorRemove_void(parent_XML_NODE->nodes_VECTOR, &key_XML_NODE, cmpXMLNodeOrder_int, 0);
}

int RemoveXMLNodeByKey_int(XML_NODE *parent_XML_NODE, const char *key_char) {
	XML_NODE *res_XML_NODE;
	unsigned int order_uint;
	
	res_XML_NODE = GetXMLNodeByKey_XML_NODE(parent_XML_NODE, key_char);
	if(!res_XML_NODE) return -1;
	order_uint = res_XML_NODE->order_uint;
	return RemoveXMLNodeByOrder_int(parent_XML_NODE, order_uint);
}

