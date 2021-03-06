#include <stdio.h>
 
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
 
int main(int argc, char**argv)
{
    FILE *f;
    Endereco e;
    int qt;
    long posicao, inicio, fim, meio;
 
   if(argc != 2)
    {
        fprintf(stderr, "USO: %s [CEP]", argv[0]);
        return 1;
    }
    
    f = fopen("cep_ordenado.dat","r");
    fseek(f,0,SEEK_END);
    posicao = ftell(f);
    rewind(f);
    printf("Tamanho do Arquivo: %ld\n", posicao);
    printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
    printf("Tamanho do Arquivo em Registros: %ld\n", posicao/sizeof(Endereco));
    inicio = 0;
    fim = (posicao/sizeof(Endereco))-1;   
  
   int i=0;   
    
    while(inicio<=fim)
    {
    	i++;
    	meio = (inicio+fim)/2;
    	
    	fseek(f, meio * sizeof(Endereco), SEEK_SET); 
    	qt = fread(&e,sizeof(Endereco),1,f);
    	
        if(strncmp(argv[1],e.cep,8)==0)
        {
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            printf("%ld tentativas \n",i);
            break;
        } else if(strncmp(argv[1],e.cep,8)>0){
        	inicio=meio+1;
		}else {
			fim=meio-1;
		}            
    }
    
    fclose(f);
    return 0;
}
