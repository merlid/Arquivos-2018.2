#include <stdio.h>
#include <stdlib.h>

typedef struct _Endereco Endereco;  				//Cria o struck para acessar o CEP corretamente
 
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
	
	f0 = fopen("novo_cep_ordenado.dat","w"); 		//Abre o f0 para escrita 
	f1 = fopen("cep1_ordenado.dat","r");	 		//Abre o f1 para leitura 
	f2 = fopen("cep2_ordenado.dat","r");	 		//Abre o f2 para leitura
	
	c1 = fread(&e1,1,sizeof(Endereco),f1);
	c2 = fread(&e2,1,sizeof(Endereco),f2);
	
	while(c1>0 && c2>0){
		
		if(strncmp(e1.cep,e2.cep,8)<0){			//Compara o CEP atual de f1 com o de f2 
			fwrite(&e1,1,c1,f0);			//se o de f1 for menor, ele escreve o CEP de f1 em f0
			c1 = fread(&e1,1,sizeof(Endereco),f1);
		} else{
			fwrite(&e2,1,c2,f0);			//se o de f1 for maior ou igual, ele escreve o CEP de f2 em f0
			c2 = fread(&e2,1,sizeof(Endereco),f2);
		}		
	}
	
	while(c1>0){						//Se todos os CEPs de f2 já foram escritos,
		
		fwrite(&e1,1,c1,f0);				//ele escreve todos os CEPs restantes de f1 em f0
		c1 = fread(&e1,1,sizeof(Endereco),f1);
		
	}
	
	while(c2>0){						//Se todos os CEPs de f1 já foram escritos,
		
		fwrite(&e2,1,c2,f0);				//ele escreve todos os CEPs restantes de f2 em f0
		c2 = fread(&e2,1,sizeof(Endereco),f2);
		
	}
	
    fclose(f0);							//fecha f0
    fclose(f1);							//fecha f1
    fclose(f2);							//fecha f2
	
	return 0;
}
