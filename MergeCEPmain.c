#include <stdio.h>
#include <stdlib.h>

typedef struct _Endereco Endereco;
 
struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int main(int argc, char *argv[]) {
	
	FILE *f0, *f1, *f2;
	Endereco e1, e2;
	int c1, c2;
	
	f0 = fopen("novo_cep_ordenado.dat","w");
	f1 = fopen("cep1_ordenado.dat","r");
	f2 = fopen("cep2_ordenado.dat","r");
	
	c1 = fread(&e1,1,sizeof(Endereco),f1);
	c2 = fread(&e2,1,sizeof(Endereco),f2);
	
	while(c1>0 && c2>0){
		
		if(strncmp(e1.cep,e2.cep,8)<0){
			fwrite(&e1,1,c1,f0);
			c1 = fread(&e1,1,sizeof(Endereco),f1);
		} else{
			fwrite(&e2,1,c2,f0);
			c2 = fread(&e2,1,sizeof(Endereco),f2);
		}		
	}
	
	while(c1>0){
		
		fwrite(&e1,1,c1,f0);
		c1 = fread(&e1,1,sizeof(Endereco),f1);
		
	}
	
	while(c2>0){
		
		fwrite(&e2,1,c2,f0);
		c2 = fread(&e2,1,sizeof(Endereco),f2);
		
	}
	
    fclose(f0);
    fclose(f1);
    fclose(f2);
	
	return 0;
}
