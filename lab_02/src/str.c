#include <stddef.h>


char * my_strcpy(char * restrict to,
		 const char * restrict from) {

	char * begin = to;

	while (*from != '\0') {
		*to = *from;
		to += 1;
		from += 1;
	}
	*to = '\0';

	return begin;
}


char * my_strcat(char * restrict first,
		const char * restrict second) {

	char * begin = first;

	while (*first != '\0') {
		first += 1;
	}

	while (*second != '\0') {
		*first = *second;
		first += 1;
		second += 1;
	}
	*first = '\0';

	return begin;
}


int my_strcmp(const char * first, const char * second) {
	while (*first != '\0'&& *second != '\0') {
		if (*first > *second) {
			return 1;
		} else if (*first < *second) {
			return -1;
		}

		first += 1;
		second += 1;
	}

	if (*first != '\0') {
		return 1;
	}
	if (*second != '\0') {
		return -1;
	}

	return 0;
}


size_t my_strlen(const char * string) {
	size_t len = 0;
	while (*string != '\0') {
		string += 1;
		len += 1;
	}
	return len;
}

