#include <stdio.h>
#include <string.h>
#include <math.h>
#include "simpSP.h"


typedef struct city
{
	char postalCode[100];
	char placeName[100];
	char state[100];
	double latitude;
	double longitude;

}cityInfo;

static char* returning;

cityInfo cityCode[6000];
int cont = 0;
int fileRead = 0;

void readcsvfromfile(){

	if(!fileRead){//se o arquivo ainda não foi lido
	
	FILE *arq;
	char Linha[100];
	int result;

	char postalCode[100];
	char placeName[100];
	char state[100];
	char latitude[100];
	char longitude[100];

    int resultado;


	arq = fopen("br_postal_codes.csv", "rt");//abrir arquivo, rt= abertura para leitura

	if(arq == NULL){
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	}


	printf("Teste1\n");
	result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'

  	while (!feof(arq))
  	{
		// Lê uma linha (inclusive com o '\n')
	      result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'


	      if (result) { // Se foi possível ler

				char latitude[100];
				char longitude[100];
                puts(Linha);
	      		resultado = sscanf(Linha, "%[^','],%[^','],%[^','],%[^','],%s",postalCode,
	      			placeName,
	      			state,latitude,longitude);
	      		strcpy(cityCode[cont].postalCode, postalCode);
	      		strcpy(cityCode[cont].placeName, placeName);
	      		strcpy(cityCode[cont].state, state);

	      		cityCode[cont].latitude = atof(latitude);
	      		cityCode[cont].longitude = atof(longitude);   		
	      		cont++;
	      }
 	}

 	printf("Leitura de arquivo Terminada.\n");

	fclose(arq);//fecha o arquivo
	printf("Lat e Long de onde nao existe: %lf : %lf \n", cityCode[cont].latitude, cityCode[cont].longitude);
	fileRead = 1;
	}
}

char** citysearch_1_svc(char** cidade, struct svc_req * rqstp){
	int i, resultado = 0;
	readcsvfromfile();//lê o arquivo 
	printf("\nCidade para busca %s", *cidade);
	for (i = 0; i < cont; i++)
	{//compara a cidade buscada com as cidades do vetor
		returning = cityCode[i].postalCode;
		if(strcmp(*cidade,cityCode[i].placeName) == 0){//se for igual
			printf("\nCidade enviada: %s\n", cityCode[i].placeName);//retorna o CEP
			return  &returning;
		}
	}
	return &returning;
}
char** latlongsearch_1_svc(coordenada* coord, struct svc_req * rqstp){
	int flag = 0, i;
	readcsvfromfile();
	for (i = 0; i < cont; ++i)
	{//compara a distância entre as coordenadas
		if(fabs(cityCode[i].latitude - coord->latitude) + fabs(cityCode[i].longitude - coord->longitude) 
			<
			fabs(cityCode[flag].latitude - coord->latitude) + fabs(cityCode[flag].longitude - coord->longitude)){
			flag = i;
		}
	}

	returning = cityCode[flag].postalCode;//retorna CEP da coordenada que possuir a menor distância entre a latitude/longitude informados e as coordenadas do vetor

	return &returning;
}
