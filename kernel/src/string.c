#include "../include/string.h"

size_t strlen(char *input){
	int i, value = 0;
	for(i = 0; input[i] != '\0'; i++, value++);
	return value;
}

char *strcpy(char *destination, char *source){
	int i = 0;
	while(source[i] != '\0'){
		destination[i] = source[i];
		i++;
	}
	return destination;
}

void *memcpy(void *destination, void *source, size_t num){
	size_t i;
	char *cSource = (char *)source;
	char *cDestination = (char *)destination;

	for(i = 0; i < num; i++)
		cDestination[i] = cSource[i];

	return destination;
}

int strcmp(char *str1, char *str2){
	size_t i;

	for(i = 0; i < strlen(str1) || i < strlen(str2) || str1[i] != '\n' || str2[i] != '\n'; i++)
		if(str1[i] != str2[i]){
			if(str1[i] > str2[i])
				return 1;
			return -1;
		}
	return 0;
}
