#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tammax 1000000

int key=0, keysize=0;
long tamreg=300;

int compara (const void * string1, const void * string2) {
	
	const char* str1 = (const char *)(string1);
	const char* str2 = (const char*)(string2);
	
	return strncmp(str1[key], str2[key],keysize);
	
}

int main(int argc, char *argv[]) {
	FILE *f0, *f1, *f2;
	int c0, c1, c2;
	long tamarq, qtdblok, qtdreg;
	
	key=290; keysize=8;
	
	f0 = fopen("cep.dat", "r");	
	fseek(f0,0,SEEK_END);
	tamarq=ftell(f0);
	rewind(f0);
	
	if(tamarq%tammax==0) qtdblok= tamarq/tammax;
	else qtdblok= tamarq/tammax +1;
	
	qtdreg = tammax/tamreg;
	
	char* buffer[maloc(qtdreg*tamreg)];
	
	while(c0>0){
		
		c0 = fread(buffer, tamreg, qtdreg, f0);
		
		qsort(buffer, qtdreg, tamreg, compara);
		
		
	}
	
	
	return 0;
}
