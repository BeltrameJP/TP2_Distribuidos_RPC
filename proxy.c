#include <stdio.h>
#include <string.h>
#include "simpSP.h"
#include "simpCP.h"
#include <time.h>

#include <stdlib.h>

	

/*void readIpFile(){
	
	FILE *arqIP; 
	char Linha[20];
	int result;
	int qtdServers = 0;
	char ipServer[20];
	int i = 1;
	arqIP = fopen("ipServers.txt", "rt");
	if(arqIP == NULL){
		printf("Erro, nao foi possivel abrir o arquivo de IP\n");
	}
	
	result = fgets(Linha, 20, arqIP);
	
	qtdServers = atoi(Linha);
	printf("Quantidade de servidores: %d\n", qtdServers);

	tamServer = qtdServers;
	
	printf("entrar no while\n");
	while(!feof(arqIP)){
		
		result = fgets(Linha, 20, arqIP); 
		
		if(result){			
			
			strcpy(servers[tamServer][i], Linha);
			printf("Linha %d: %s\n", i, servers[tamServer][i]);					
		}		
		i++;
	}
	printf("fechar arquivo\n");
	fclose(arqIP);
     
}

*/
char* serverRotation(){
	
	if(rand() % 2){//se for par
		return "192.168.43.94";
	}
	return "127.0.0.1";
}

char ** citysearch_proxy_1_svc(char ** cidade, struct svc_req * rqstp){
	
	char** result;
	
	CLIENT *clnt;
	
	char* serverActual = serverRotation();//servidor escolhido pelo método de balanceamento

	clnt = clnt_create("127.0.0.1", SIMP_SERVER, SIMP_VERSION, "udp");
	printf("cliente\n");

	 /* Make sure the create worked */
  	if (clnt == (CLIENT *) NULL) {
    	clnt_pcreateerror("127.0.0.1");
    	exit(1);
  	}

	result = citysearch_1(cidade, clnt);//chama a função do servidor de busca usando nome 
	if(result == NULL){
		printf("Erro proxy");
	}
	printf("%s", *result);

	return result;

}

char ** latlongsearch_proxy_1_svc(coordenada_proxy * coord, struct svc_req * rqstp){
	char** result;
	char* serverActual = serverRotation();//servidor escolhido pelo método de balanceamento

	CLIENT *clnt;

	
	clnt = clnt_create("127.0.0.1", SIMP_SERVER, SIMP_VERSION, "udp");

	 /* Make sure the create worked */
  	if (clnt == (CLIENT *) NULL) {
    	clnt_pcreateerror("127.0.0.1");
    	exit(1);
  	}


	coordenada c;
	c.latitude = coord->latitude;
	c.longitude = coord->longitude;
	result = latlongsearch_1(&c, clnt);//chama a função do servidor de busca usando coordenada
	if(result == NULL){
		printf("Erro proxy");
	}
	printf("%s", *result);

	return result;

}
