#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tammax 1000000

int key=290, keysize=8;
long tamreg=300;

int compara (const void * string1, const void * string2) {
	
	const char* str1 = (const char *)(string1);
	const char* str2 = (const char*)(string2);
	
	return strncmp(&str1[key], &str2[key],keysize);	
}

void merge(FILE *f0, FILE *f1, FILE *f2){
	
	
	
	int c1, c2;
	char buffer1[tamreg], buffer2[tamreg];
	
	c1 = fread(&buffer1,tamreg,1,f1);
	c2 = fread(&buffer2,tamreg,1,f2);
	
	while(c1>0 && c2>0){
		
		if(strncmp(&buffer1[key],&buffer2[key],keysize)<0){			
			fwrite(&buffer1,c1,1,f0);			
			c1 = fread(&buffer1,tamreg,1,f1);
		} else{
			fwrite(&buffer2,c2,1,f0);			
			c2 = fread(&buffer2,tamreg,1,f2);
		}		
	}
	
	while(c1>0){		
		fwrite(&buffer1,c1,1,f0);				
		c1 = fread(&buffer1,tamreg,1,f1);		
	}
	
	while(c2>0){		
		fwrite(&buffer2,c2,1,f0);				
		c2 = fread(&buffer2,tamreg,1,f2);		
	}
}

int main(int argc, char *argv[]) {
	FILE *f0, *f1, *f2;
	int c0;
	long tamarq, qtdblok, qtdreg;
		
	f0 = fopen("cep.dat", "r");	
	fseek(f0,0,SEEK_END);
	tamarq=ftell(f0);
	rewind(f0);
		
	if(tamarq%tammax==0) qtdblok= tamarq/tammax;
	else qtdblok= tamarq/tammax +1;
	
	int atual=0, final=qtdblok-1;
	
	char nome[20];
		
	qtdreg = tammax/tamreg;	
	
	char buffer[qtdreg*tamreg];	
	
	c0 = fread(buffer, tamreg, qtdreg, f0);
	while(c0>0){
		
		qsort(buffer, qtdreg, tamreg, compara);
		
		sprintf(nome,"bloco%d.dat", atual);	
		atual++;
		
		f1= fopen(nome,"w");
		fwrite(buffer, tamreg, c0, f1);
		fclose(f1);
		
		c0 = fread(buffer, tamreg, qtdreg, f0);
	}
	
	fclose(f0);
	
	int c1, c2;
	char buffer1[tamreg], buffer2[tamreg];
	atual=0;
	
	while(atual<final){
		
		sprintf(nome,"bloco%d.dat", atual);
		atual++;
		f1= fopen(nome, "r");
		
		sprintf(nome,"bloco%d.dat", atual);
		atual++;
		f2= fopen(nome, "r");
		
		final++;
		if(atual<final){			
			sprintf(nome, "bloco%d.dat", final);
			f0= fopen(nome,"w");
		} else{
			sprintf(nome, "bloco%d/blocofinal.dat", final);
			f0= fopen(nome,"w");
		}
		
	//	merge(f0, f1, f2);
	
	c1 = fread(&buffer1,tamreg,1,f1);
	c2 = fread(&buffer2,tamreg,1,f2);
	
	while(c1>0 && c2>0){
		
		if(strncmp(&buffer1[key],&buffer2[key],keysize)<0){			
			fwrite(&buffer1,c1,1,f0);			
			c1 = fread(&buffer1,tamreg,1,f1);
		} else{
			fwrite(&buffer2,c2,1,f0);			
			c2 = fread(&buffer2,tamreg,1,f2);
		}		
	}
	
	while(c1>0){		
		fwrite(&buffer1,c1,1,f0);				
		c1 = fread(&buffer1,tamreg,1,f1);		
	}
	
	while(c2>0){		
		fwrite(&buffer2,c2,1,f0);				
		c2 = fread(&buffer2,tamreg,1,f2);		
	}
		
		fclose(f0);
		fclose(f1);
		fclose(f2);		
	}
		
	return 0;
}
