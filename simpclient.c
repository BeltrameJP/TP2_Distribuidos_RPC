#include <stdio.h>
#include "simpCP.h" 

int citySearchClient(char** cityS, CLIENT* clnt){//função Wrapper de busca usando nome
	printf("Cidade recebida: %s\n", *cityS);
	char** result;
	result = citysearch_proxy_1(cityS,clnt);//chama função do servidor(proxy) 
	if(result == NULL){
		printf("Erro");
	}
	printf("%s", *result);
	return 0;

}
int latLongSearchClient(double lat, double longt, CLIENT* clnt){//função Wrapper de busca usando coordenadas
	coordenada_proxy coord;
	coord.latitude = lat;
	coord.longitude = longt;
	printf("Lat: %lf long: %lf\n", coord.latitude, coord.longitude);//chama função do servidor(proxy)
	
	char** result = latlongsearch_proxy_1(&coord, clnt);
	if(result == NULL){
		printf("Erro");
	}
	printf("%s", *result);
	return 0;
}


int main(int argc, char const *argv[])
{

	CLIENT *clnt;

	double lat, longt;
	char *cityS;

	int op = atoi(argv[2]);//recebe a opção desejada pelo usuário


	if(op == 1){// verifica se a qtde de argumentos está certa de acordo com a opção escolhida
		
		if(argc!=4){
			fprintf(stderr,"Usage: %s hostname op city\n",argv[0]);
	    	exit(0);
		}
	}
	else{
		
		if(argc!=5){
			fprintf(stderr,"Usage: %s hostname op lat long\n",argv[0]);
	    	exit(0);
		}
	}

	clnt = clnt_create(argv[1], SIMP_CLIENT, SIMP_VERSION, "udp");

	 /* Make sure the create worked */
  	if (clnt == (CLIENT *) NULL) {
    	clnt_pcreateerror(argv[1]);
    	exit(1);
  	}
  	
  	if(op == 1){//se for 1, chama a função Wrapper de busca usando o nome
  		cityS = argv[3];
  		printf("\n Cidade: %s\n", cityS);
  		int busca = citySearchClient(&cityS, clnt);
  		printf("\nPassou da funcao");
  	}
  	else{//se for qualquer outro número, chama a função Wrapper de busca usando coordenadas
  		lat = atof(argv[3]);
  		longt = atof(argv[4]);
  		int buscaS = latLongSearchClient(lat,longt, clnt);
  	}
	
	return 0;
}
