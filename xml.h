#ifndef XML
#define XML

#include "vector.h"

typedef struct STRUCT_XML_NODE {
	const char *key_char;
	const char *val_char;
	const VECTOR *nodes_VECTOR;
	const void **index_void;
	const unsigned int order_uint;
} XML_NODE;

XML_NODE* CreateXMLNode_XML_NODE(void);
void DestroyXMLNode_void(XML_NODE *parent_XML_NODE);

char* SetXMLKey_char(XML_NODE *x_XML_NODE, const char *str_char);
char* GetXMLKey_char(XML_NODE *x_XML_NODE);
char* SetXMLVal_char(XML_NODE *x_XML_NODE, const char *str_char);
char* GetXMLVal_char(XML_NODE *x_XML_NODE);

int AddXMLNode_int(XML_NODE *parent_XML_NODE, XML_NODE *child_XML_NODE);
XML_NODE* GetXMLNodeByKey_XML_NODE(XML_NODE *parent_XML_NODE, const char *key_char);
XML_NODE* GetXMLNodeByOrder_XML_NODE(XML_NODE *parent_XML_NODE, unsigned int order_uint);
int RemoveXMLNodeByKey_int(XML_NODE *parent_XML_NODE, const char *key_char);
int RemoveXMLNodeByOrder_int(XML_NODE *parent_XML_NODE, unsigned int order_uint);

#endif