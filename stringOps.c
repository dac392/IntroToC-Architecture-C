#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){

	int count = 0;
	for(int i = 1; i < argc; i++){
		int j = 0;
		char *str = argv[i];
		while(str[j]!='\0'){
			if(str[j] == 'a'||str[j] == 'e'||str[j] == 'i'
				||str[j] == 'o'||str[j] == 'u'||str[j] == 'A'
				||str[j] == 'E'||str[j] == 'I'||str[j] == 'O'||str[j] == 'U'){
				count ++;
			}
			j++;
		}
	}

	char *statement = malloc(count+1);
	int pos = 0;
	for(int i = 1; i < argc; i++){
		int j = 0;
		char *str = argv[i];
		while(str[j]!='\0'){
			if(str[j] == 'a'||str[j] == 'e'||str[j] == 'i'
				||str[j] == 'o'||str[j] == 'u'||str[j] == 'A'
				||str[j] == 'E'||str[j] == 'I'||str[j] == 'O'||str[j] == 'U'){
				statement[pos] = str[j];
				pos++;
			}
			j++;
		}
	}
	
	int fucksSake = 0;
	while(fucksSake < count){
		printf("%c", statement[fucksSake]);
		fucksSake ++;
	}
	printf("\n");
	
	free(statement);

	return 0;

}
