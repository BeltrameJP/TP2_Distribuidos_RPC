#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int qtdClient = atoi(argv[1]);//quantidade de clientes a ser simulada
	int time = atoi(argv[2]);//tempo entre as requisições de cada cliente
	int op = atoi(argv[3]);//recebe a opção desejada pelo usuário
	int i;
	if(op == 1){
	 	for(i=0;i<qtdClient;i++){
			system("./client 127.0.0.1 1 Capixaba");				
			usleep(time*1000);		
		}

	}else{
		for(i=0;i<qtdClient;i++){
			system("./client 127.0.0.1 2 -9.3934 -36.1239");				
			usleep(time*1000);		
		}
	}
}
