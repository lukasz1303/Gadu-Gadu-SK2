#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <fstream>
#include <iostream>
#include <string>

#define SERVER_PORT 1234
#define QUEUE_SIZE 5

typedef struct{
    struct sockaddr_in address;
    int sockfd;
    int id;
    char name[32];
} client_t;

int id=0;
 
client_t *clients[QUEUE_SIZE];

struct thread_data_t
{
int socket;
};

void send_message(char *s, int sfd){

	for(int i=0; i<QUEUE_SIZE; i++){
		if(clients[i]){
			if(clients[i]->sockfd != sfd){
                write(clients[i]->sockfd, s, strlen(s));
            }
        }
    }
}

void *ThreadBehavior(void *t_data)
{
    pthread_detach(pthread_self());
    struct thread_data_t *th_data = (struct thread_data_t*)t_data;
    char buff[255];
    int bytes;

    while(1){
    
        memset(buff,0,sizeof(buff));
        bytes = read((*th_data).socket, buff, 255);
        if (bytes == 0){
            printf("Client closed, socket = %d\n", (*th_data).socket);
            break;
        }
        printf("read %d bytes\n", bytes);
        printf("%s\n", buff);
        
        if(strncmp(buff,"SIGN_UP",7)==0){
            std::ofstream usersFile;
            usersFile.open("users", std::ios_base::app);
            
            if (usersFile.is_open()){
                std::string s = buff;
                usersFile << s.substr(s.find(":")+1) << std::endl;
                usersFile.close();
                char ret[20] = "SIGN_UP:OK";
                
                write((*th_data).socket, ret, strlen(ret));
            } else {
                printf("Nie można otworzyć pliku \"users\"\n");
            }
        }
        
        if(strncmp(buff,"SIGN_IN",7)==0){
            std::ifstream usersFile;
            usersFile.open("users");
            std::string s = buff;
            s = s.substr(s.find(":")+1);
            bool finded = false;
            
            if (usersFile.is_open()){
                std::string line;
                while (getline(usersFile,line)){
                    if (s.compare(line.substr(0,line.rfind(":")))== 0){
                        finded = true;
                        break;
                    }
                }   
                usersFile.close();
                if(finded){
                    char ret[20] = "SIGN_IN:OK";
                    write((*th_data).socket, ret, strlen(ret));
                } else {
                    char ret[20] = "SIGN_IN:ERROR";
                    write((*th_data).socket, ret, strlen(ret));
                }
                
            } else {
                printf("Nie można otworzyć pliku \"users\"\n");
            }
        }
        
        
            
        send_message(buff, (*th_data).socket);
    }
    free(t_data);
    pthread_exit(NULL);
}



void handleConnection(int connection_socket_descriptor) {
    int create_result = 0;

    pthread_t thread1;

    struct thread_data_t *t_data = (struct thread_data_t*) malloc(sizeof(struct thread_data_t));

    t_data->socket = connection_socket_descriptor;

    create_result = pthread_create(&thread1, NULL, ThreadBehavior, (void *)t_data);
    if (create_result){
       printf("Błąd przy próbie utworzenia wątku, kod błędu: %d\n", create_result);
       exit(-1);
    }

}

int main(int argc, char* argv[])
{
   int server_socket_descriptor;
   int connection_socket_descriptor;
   int bind_result;
   int listen_result;
   char reuse_addr_val = 1;
   struct sockaddr_in server_address;
   
   memset(&server_address, 0, sizeof(struct sockaddr));
   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);
   server_address.sin_port = htons(SERVER_PORT);

   server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
   if (server_socket_descriptor < 0)
   {
       fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda..\n", argv[0]);
       exit(1);
   }
   setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));

   bind_result = bind(server_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
   if (bind_result < 0)
   {
       fprintf(stderr, "%s: Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n", argv[0]);
       exit(1);
   }

   listen_result = listen(server_socket_descriptor, QUEUE_SIZE);
   if (listen_result < 0) {
       fprintf(stderr, "%s: Błąd przy próbie ustawienia wielkości kolejki.\n", argv[0]);
       exit(1);
   }

   while(1)
   {
       connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
       if (connection_socket_descriptor < 0)
       {
           fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
           exit(1);
       } else {
          printf("Nawiazano poloczenie, socket = %d\n",connection_socket_descriptor );
       }

       handleConnection(connection_socket_descriptor);
       
       client_t *client = (client_t *)malloc(sizeof(client_t));
		client->sockfd = connection_socket_descriptor;
		client->id = id++;
       
       for(int i=0; i < QUEUE_SIZE; i++){
		if(clients[i]==NULL){
			clients[i] = client;
			break;
		}
	}
   }

   close(server_socket_descriptor);
   return(0);
}


