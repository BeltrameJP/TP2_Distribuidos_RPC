.c.o:
	gcc -c -Wall -DRPC_SVC_FG $<

all: client proxy server

simpCP: simpCP.o
	gcc -o simpCP simpCP.o

simpSP: simpSP.o
	gcc -o simpSP simpSP.o

client: simpclient.o simpCP_clnt.o simpCP_xdr.o
	gcc -o client simpclient.o simpCP_clnt.o simpCP_xdr.o -lnsl -g

server: simpservice.o simpSP_svc.o simpSP_xdr.o
	gcc -o server simpservice.o simpSP_svc.o simpSP_xdr.o -lrpcsvc -lnsl

proxy: proxy.o simpCP_svc.o simpCP_xdr.o simpSP_clnt.o simpSP_xdr.o
	gcc -o proxy proxy.o simpCP_svc.o simpCP_xdr.o simpSP_clnt.o simpSP_xdr.o -lnsl -g

simpCP.h: simpCP.x
	rpcgen -C simpCP.x

simpSP.h: simpSP.x
	rpcgen -C simpSP.x

clean:
	rm *.o simpSP.h simpCP.h simpCP_svc.* simpCP_clnt.* simpCP_xdr.* simpSP_svc.* simpSP_clnt.* simpSP_xdr.* 

simpclient.c: simpCP.h
simpservice.c: simpSP.h
