//Program to implement	fibanocii series using TCP client

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main()
{
	int socket_desc;
	
	char client_message[3];
	
	struct sockaddr_in server_addr,client_addr;
	
	memset(client_message,'\0',sizeof(client_message));
	
	
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(socket_desc<0)
	{
		printf("\nSocket not created");
		return(-1);
	
	}
	
	//Add addresses
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2003);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	printf("\nSocket created successfully");
	
	if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("\nCouldnot connect");
		return(-1);
	}
	
	printf("\nConnected successfully");
	
	
	
	while(1)
	{
		
	
		
		int num;
		printf("\nEnter the number terms in the fibonacii series (greater than or equal to 2):");
		scanf("%d",&num);
		
		int result[num];
		
		if(send(socket_desc,&num,sizeof(num),0)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSent successfully");
		
		
		if(recv(socket_desc,result,sizeof(result),0)<0)
		{
			printf("\nCouldnot recieve");
			return(-1);
		}
		
		
		printf("\nThe fibonacii series is:");
		for(int i=0;i<num;i++)
		{
			printf("%d\t",result[i]);
		}
		printf("\n");
		
		
		memset(client_message,'\0',sizeof(client_message));
		
		printf("\nDo you want to continue:");
		scanf("%s",client_message);
		
		if(send(socket_desc,client_message,sizeof(client_message),0)<0)
		{
			printf("\nCouldnot send");
			return(-1);
		}
		printf("\nSent successfully");
		
		if(strcmp(client_message,"no")==0)
			break;
			
		
	}
	printf("\n");
	
	//Closing the sockets
	close(socket_desc);
}