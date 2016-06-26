#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* trim_char(const char * str_char) {
	size_t i, j, len;
	char *ret;
	
	i = 0;
	len = strlen(str_char);
	j = len - 1;
	
	while(i < len)
		if(str_char[i] == ' ' || str_char[i] == '\t') i += 1;
		else break;
	if(i >= len) {
		ret = malloc(1);
		if(!ret) return 0;
		*ret = '\0';
		return ret;
	}
	while(j > i)
		if(str_char[j] == ' ' || str_char[j] == '\t' || str_char[j] == '\r' || str_char[j] == '\n') j -= 1;
		else break;
	
	if(i == j) {
		ret = malloc(1);
		if(!ret) return 0;
		*ret = '\0';
		return ret;
	}
	
	ret = malloc(j - i + 2);
	if(!ret) return 0;
	
	memcpy(ret, str_char + i, j - i + 1);
	ret[j - i + 1] = '\0';
	return ret;
}

char* advance_char(FILE *input_FILE, unsigned int *lineCount_uint, char **str_char, unsigned int *idx_uint) {
	char buf_char[1024];
	char *ret_char, *trimed_char;
	unsigned int j;
	
	while((*str_char)[*idx_uint] != '\0')
		if((*str_char)[*idx_uint] == ' ') *idx_uint += 1;
		else break;
	
	while((*str_char)[*idx_uint] == '\0') {
		*idx_uint = 0;
		if(!fgets(buf_char, sizeof(buf_char), input_FILE)) return 0;
		*lineCount_uint += 1;
		trimed_char = trim_char(buf_char);
		if(!trimed_char) return 0;
		free(*str_char);
		(*str_char) = trimed_char;
	}
	
	if((*str_char)[*idx_uint] == '<' || (*str_char)[*idx_uint] == '>') {
		ret_char = (char*)malloc(2);
		if(!ret_char) return 0;
		*ret_char = (*str_char)[*idx_uint];
		ret_char[1] = '\0';
		*idx_uint += 1;
		return ret_char;
	}
	
	j = (*idx_uint) + 1;
	while((*str_char)[j] != '\0')
		if((*str_char)[j] != '<' && (*str_char)[j] != '>') j += 1;
		else break;
	
	ret_char = (char*)malloc(j - (*idx_uint) + 1);
	memcpy(ret_char, (*str_char) + (*idx_uint), j - (*idx_uint));
	ret_char[j - (*idx_uint)] = '\0';
	(*idx_uint) = j;
	trimed_char = trim_char(ret_char);
	free(ret_char);
	return trimed_char;
}
