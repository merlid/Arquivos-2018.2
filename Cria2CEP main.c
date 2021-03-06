#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define t 300

int main(int argc, char *argv[]) {
	
	FILE *e0, *e1, *e2;
	char buffer[t];
	int c;
	
	srand(time(NULL));				//Permite que o rand() gere números aleatórios
	
	e0 = fopen("cep_ordenado.dat","r");		//Abre e0 para leitura
	e1 = fopen("cep1_ordenado.dat","w");		//Abre e1 para escrita
	e2 = fopen("cep2_ordenado.dat","w");		//Abre e2 para escrita
	
	c = fread(buffer,1,t,e0);
	
    while(c > 0)
    {
    	if(rand()%2==1)	fwrite(buffer,1,c,e1);		//Preenche aleatoriamente e1 e e2 com os CEPs de e0
        else fwrite(buffer,1,c,e2);
        
        c = fread(buffer,1,t,e0);
    }
 
    fclose(e0);						//Fecha e0
    fclose(e1);						//Fecha e1
    fclose(e2);						//Fecha e2
	
	return 0;
}
