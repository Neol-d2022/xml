#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "xml.h"
#include "tokenizer.h"

XML_NODE* GetNode_XML_NODE(FILE *input_FILE, unsigned int *lineCount_uint, char **trimed_char, unsigned int *idx_uint, char **keyStr_char) {
	XML_NODE *ret_XML_NODE, *child_XML_NODE;
	char *tag_char;
	
	ret_XML_NODE = CreateXMLNode_XML_NODE();
	if(!ret_XML_NODE) {
		fprintf(stderr, "Cannot create base node(sub).\n");
		return 0;
	}
	
	if(!SetXMLKey_char(ret_XML_NODE, *keyStr_char)) {
		DestroyXMLNode_void(ret_XML_NODE);
		fprintf(stderr, "Set node key failed(sub).\n");
		return 0;
	}
	
	if(!(tag_char = advance_char(input_FILE, lineCount_uint, trimed_char, idx_uint))) {
		DestroyXMLNode_void(ret_XML_NODE);
		fprintf(stderr, "Cannot get next token(sub1).\n");
		return 0;
	}
	if(*tag_char != '>') {
		fprintf(stderr, "[Error] On line %u, '>' is expected, but found %s.\n", *lineCount_uint, tag_char);
		DestroyXMLNode_void(ret_XML_NODE);
		return 0;
	}
	free(tag_char);
	
	if(!(tag_char = advance_char(input_FILE, lineCount_uint, trimed_char, idx_uint))) {
		fprintf(stderr, "Cannot get next token(sub2).\n");
		DestroyXMLNode_void(ret_XML_NODE);
		return 0;
	}
	if(*tag_char == '<') {
		free(tag_char);
		if(!(tag_char = advance_char(input_FILE, lineCount_uint, trimed_char, idx_uint))) {
			fprintf(stderr, "Cannot get next token(sub3).\n");
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		if(*tag_char == '<' || *tag_char == '>') {
			fprintf(stderr, "[Error] On line %u, key is expected, but found %s.\n", *lineCount_uint, tag_char);
			free(tag_char);
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		
		if(*tag_char == '/' && !strcmp(tag_char + 1, *keyStr_char)) {
			if(!SetXMLVal_char(ret_XML_NODE, "")) {
				fprintf(stderr, "Cannot set node val to empty string(sub).\n");
				free(tag_char);
				DestroyXMLNode_void(ret_XML_NODE);
				return 0;
			}
			goto end;
		}
		else {
			while((child_XML_NODE = GetNode_XML_NODE(input_FILE, lineCount_uint, trimed_char, idx_uint, &tag_char))) {
				if(AddXMLNode_int(ret_XML_NODE, child_XML_NODE)) {
					fprintf(stderr, "Add child node failed.(main)\n");
					free(tag_char);
					DestroyXMLNode_void(ret_XML_NODE);
					return 0;
				}
				if(*tag_char == '/' && !strcmp(tag_char + 1, *keyStr_char)) goto end;
				/*else {
					free(tag_char);
					fprintf(stderr, "[Error] On line %u, '/%s' is expected, but found %s.\n", *lineCount_uint, *keyStr_char, tag_char);
					DestroyXMLNode_void(ret_XML_NODE);
					return 0;
				}*/
			}
			free(tag_char);
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
	}
	else if(*tag_char == '>') {
		fprintf(stderr, "[Error] On line %u, '<' or val is expected, but found %s.\n", *lineCount_uint, tag_char);
		free(tag_char);
		DestroyXMLNode_void(ret_XML_NODE);
		return 0;
	}
	else {
		if(!SetXMLVal_char(ret_XML_NODE, tag_char)) {
			fprintf(stderr, "Cannot set node val(sub4).\n");
			free(tag_char);
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		
		if(!(tag_char = advance_char(input_FILE, lineCount_uint, trimed_char, idx_uint))) {
			fprintf(stderr, "Cannot get next token(sub5).\n");
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		
		if(*tag_char != '<') {
			fprintf(stderr, "[Error] On line %u, '<' is expected, but found %s.\n", *lineCount_uint, tag_char);
			free(tag_char);
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		free(tag_char);
		
		if(!(tag_char = advance_char(input_FILE, lineCount_uint, trimed_char, idx_uint))) {
			fprintf(stderr, "Cannot get next token(sub6).\n");
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		if(*tag_char != '/' || strcmp(tag_char + 1, *keyStr_char)) {
			fprintf(stderr, "[Error] On line %u, '/%s' is expected, but found %s.\n", *lineCount_uint, *keyStr_char, tag_char);
			free(tag_char);
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		free(tag_char);
end:
		if(!(tag_char = advance_char(input_FILE, lineCount_uint, trimed_char, idx_uint))) {
			fprintf(stderr, "Cannot get next token(sub7).\n");
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		
		if(*tag_char != '>') {
			fprintf(stderr, "[Error] On line %u, '>' is expected, but found %s.\n", *lineCount_uint, tag_char);
			free(tag_char);
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		free(tag_char);
		
		if(!(tag_char = advance_char(input_FILE, lineCount_uint, trimed_char, idx_uint))) {
			if(feof(input_FILE)) return ret_XML_NODE;
			fprintf(stderr, "Cannot get next token(sub8).\n");
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		
		if(*tag_char != '<') {
			fprintf(stderr, "[Error] On line %u, '<' is expected, but found %s.\n", *lineCount_uint, tag_char);
			free(tag_char);
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		free(tag_char);
		
		if(!(tag_char = advance_char(input_FILE, lineCount_uint, trimed_char, idx_uint))) {
			fprintf(stderr, "Cannot get next token(sub9).\n");
			DestroyXMLNode_void(ret_XML_NODE);
			return 0;
		}
		
		free(*keyStr_char);
		*keyStr_char = tag_char;
		//free(tag_char);
	}
	
	return ret_XML_NODE;
}

int main(void) {
	char *tag_char, *trimed_char;
	XML_NODE *base_XML_NODE, *child_XML_NODE;
	FILE *input_FILE = stdin;
	unsigned int idx_uint, lineCount_uint;
	
	base_XML_NODE = CreateXMLNode_XML_NODE();
	if(!base_XML_NODE) return -1;
	
	if(!SetXMLKey_char(base_XML_NODE, "xml")) return -1;
	
	lineCount_uint = 0;
	trimed_char = malloc(1);
	if(!trimed_char) return -1;
	*trimed_char = '\0';
	idx_uint = 0;
	
	if(!(tag_char = advance_char(input_FILE, &lineCount_uint, &trimed_char, &idx_uint))) return -1;
	if(*tag_char != '<') fprintf(stderr, "[Error] On line %u, '<' is expected, but found %s.\n", lineCount_uint, tag_char);
	free(tag_char);
	if(!(tag_char = advance_char(input_FILE, &lineCount_uint, &trimed_char, &idx_uint))) return -1;
	if(*tag_char == '/') fprintf(stderr, "[Error] On line %u, tag start is expected, but found %s.\n", lineCount_uint, tag_char);
	
	while((child_XML_NODE = GetNode_XML_NODE(input_FILE, &lineCount_uint, &trimed_char, &idx_uint, &tag_char))) {
		if(AddXMLNode_int(base_XML_NODE, child_XML_NODE)) {
			fprintf(stderr, "Add child node failed.(main)\n");
			break;
		}
		if(feof(input_FILE)) break;
	}
	free(tag_char);
	
	if(feof(input_FILE)) return 0;
	else {
		fprintf(stderr, "Exit without reading up all input.\n");
		return -1;
	}
}