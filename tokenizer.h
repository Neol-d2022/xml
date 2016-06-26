#ifndef TOKENIZER
#define TOKENIZER

char* trim_char(const char * str_char);
char* advance_char(FILE *input_FILE, unsigned int *lineCount_uint, char **str_char, unsigned int *idx_uint);

#endif