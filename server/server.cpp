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
static unsigned int clientCount = 0;
typedef struct{
    struct sockaddr_in address;
    int sockfd;
    int NRGG;
    char name[32];
    
} client_t;

 
client_t *clients[QUEUE_SIZE];
pthread_mutex_t SING_UP_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t CHAT_MESSAGES_MUTEX = PTHREAD_MUTEX_INITIALIZER;
struct thread_data_t
{
int socket;
};

void send_message(char *s, int sfd){

	for(int i=0; i<QUEUE_SIZE; i++){
		if(clients[i]){
			if(clients[i]->NRGG == sfd){
                write(clients[i]->sockfd, s, strlen(s));
            }
        }
    }
}

void *ThreadBehavior(void *t_data)
{
    pthread_detach(pthread_self());
    struct thread_data_t *th_data = (struct thread_data_t*)t_data;
    char buff1[255];
    clientCount++;
    int bytes;
    int ggsender;
    char name[32];
    std::string stringBuff;
    std::string oneChar;
    bool shouldBreak = false;
    while(1){
    
        stringBuff = "";
        memset(buff1,0,sizeof(buff1)); 
        while(1){
                bytes = read((*th_data).socket, buff1, 1);
                if (bytes == 0){
                    printf("Client closed, socket = %d\n", (*th_data).socket);
                    shouldBreak = true;
                    break; 
                }
                if(strncmp(buff1,"\n",1) == 0 || strncmp(buff1,"\0",1) == 0){
                    break;
                }
            stringBuff.push_back(buff1[0]);
        }
        if (shouldBreak){
            break;
        }

        char buff[stringBuff.length()+1];
        memset(buff,0,sizeof(buff)); 
        strncpy(buff,stringBuff.c_str(),stringBuff.length());
        buff[stringBuff.length()]='\0';
        
        if(strncmp(buff,"SIGN_UP",7)==0){
            pthread_mutex_lock(&SING_UP_MUTEX);

            std::ofstream usersFile;
            usersFile.open("users", std::ios_base::app);
            
            if (usersFile.is_open()){
                std::string s = buff;
                usersFile << s.substr(s.find(":")+1) << std::endl;
                usersFile.close();
                std::string contactsFileName = "contacts/" + s.substr(s.rfind(":")+1);
                std::ofstream contactsFile(contactsFileName);
                contactsFile.close();
                char ret[20] = "SIGN_UP:OK";
                
                write((*th_data).socket, ret, strlen(ret));
            } else {
                printf("Nie można otworzyć pliku \"users\"\n");
            }
            pthread_mutex_unlock(&SING_UP_MUTEX);
        }
        
        
        if(strncmp(buff,"SIGN_IN",7)==0){
            std::ifstream usersFile;
            usersFile.open("users");
            std::string s = buff;
            s = s.substr(s.find(":")+1);
            bool finded = false;
            bool already_logged=false;
            std::string ret;
            char buff2[50]; 
            if (usersFile.is_open()){
                std::string line;
                while (getline(usersFile,line)){
                    if (s.compare(line.substr(0,line.rfind(":")))== 0){
                        finded = true;
                        
                        ret = "SIGN_IN:OK:";
                        ret.append(line.substr(line.rfind(":")+1,line.length()));
                        for(int i=0;i<QUEUE_SIZE;i++){
                            if(clients[i]){
                                if(clients[i]->NRGG==std::stoi(line.substr(line.rfind(":")+1,line.length()))){
                                   strncpy(buff2,"SIGN_IN:LOGGED",sizeof(buff2));
                                   write((*th_data).socket, buff2, strlen(buff2));
                                   finded=false;
                                   already_logged=true;
                                   break;
                                }
                            }
                        }
                        if(already_logged){break;}
                        ggsender=stoi(line.substr(line.rfind(":")+1,line.length()));
                        for(int i=0; i<QUEUE_SIZE; i++){
                            if(clients[i]){
                                if(clients[i]->sockfd == (*th_data).socket){
                                    clients[i]->NRGG=std::stoi(line.substr(line.rfind(":")+1,line.length()));
                                    s=s.substr(0,s.find(":"));
                                    strcpy(clients[i]->name, s.c_str());;
                                    strcpy(name,clients[i]->name);
                                    
                                }
                            }
                        }
                        break;
                    }
                }   
                usersFile.close();
                            
                if(finded){
                    strncpy(buff2,ret.c_str(),sizeof(buff2));
                    buff2[ret.length()]=0;
                    write((*th_data).socket, buff2, strlen(buff2));
                } 
                else if(already_logged){
                    
                }
                else {
                    strncpy(buff2,"SIGN_IN:ERROR",sizeof(buff2));
                    write((*th_data).socket, buff2, strlen(buff2));
                }
                
            } else {
                printf("Nie można otworzyć pliku \"users\"\n");
            }
        }
        
        if(strncmp(buff,"ADD_CONT",8)==0){

            
            std::string s = buff;
            s = s.substr(s.find(":")+1,s.length());
            std::string filename = s.substr(0,s.find(":"));
            std::string contactsFileName = "contacts/" + filename;
            std::fstream contactsFile;
            contactsFile.open(contactsFileName);
            s = s.substr(s.find(":")+1);
            std::string line;
            bool finded = false;
            if (contactsFile.is_open()){
                std::string contact = s;
                 while (getline(contactsFile,line)){
                    if (contact.substr(0,contact.find(":")).compare(line.substr(0,line.find(":")))== 0 ||
                        contact.substr(contact.find(":")+1, contact.length()).compare(line.substr(line.find(":")+1, line.length()))== 0){
                        char buff2[17] = "ADD_CONT:EXISTS\n";
                        write((*th_data).socket, buff2, strlen(buff2));
                        finded = true;
                        break;
                    }
                }
                if(!finded){
                    bool signedUp = false;
                    std::fstream usersFile;
                    usersFile.open("users");
                    
                    if (usersFile.is_open()){
                        std::string line;
                        while (getline(usersFile,line)){
                            if (contact.substr(contact.find(":")+1, contact.length()).compare(line.substr(line.rfind(":")+1, line.length())) == 0){
                                signedUp = true;
                            }
                        }
                    } else {
                        printf("Nie można otworzyć pliku \"users\"\n");
                    }
                                 
                    if(signedUp){    
                        contactsFile.clear();
                        contactsFile.seekp(0, std::ios_base::end);
                        contactsFile << contact << std::endl;
                        char buff2[13] = "ADD_CONT:OK\n";
                        write((*th_data).socket, buff2, strlen(buff2));
                    } else {
                        char buff2[20] = "ADD_CONT:NO_SIGNED\n";
                        write((*th_data).socket, buff2, strlen(buff2));
                        std::cout<< buff2 << std::endl;
                    }
                    
                }
                
            } else {
                printf("Nie można otworzyć pliku \"contacts\"\n");
            }
            contactsFile.close();
        }
        
        if(strncmp(buff,"GET_CONT",8)==0){

            std::string s = buff;
            std::string filename = s.substr(s.find(":")+1,s.length());
            std::string contactsFileName = "contacts/" + filename;
            std::ifstream contactsFile;
            contactsFile.open(contactsFileName);
            std::string line;  
            char buff2[100];
            if (contactsFile.is_open()){
                while (getline(contactsFile,line)){
                    memset(buff2,0,sizeof(buff2));
                    s = "CONTACT:";
                    s.append(line);
                    std::string status="offline";
                    
                    for(int i=0; i<QUEUE_SIZE; i++){
                        if(clients[i]){
                            if(clients[i]->NRGG == std::stoi(line.substr(line.find(":")+1,line.length())) ){
                                status="online";
                            }
                        }
                    }
                    s.append(":");
                    s.append(status);
                    
                    strncpy(buff2,s.c_str(),sizeof(buff2));
                    buff2[s.length()]='\n';
                    buff2[s.length()+1]='\0';
                    write((*th_data).socket, buff2, strlen(buff2));
                    }
                    
            } else {
                printf("Nie można otworzyć pliku \"users\"\n");
            }
            
            contactsFile.close();
        }
        
        if(strncmp(buff,"SEND_MSG",8)==0){
            std::string s = buff;
           
            s = s.substr(s.find(":")+1,s.length());
            
            std::string GGReceivernr = s.substr(0,s.find(":"));
            
            int ggrecipient=std::stoi(GGReceivernr);
            std::string savetohistory;
            
            
            s = s.substr(s.find(":")+1,s.length());
            s = s.substr(0,s.find("\n"));
            savetohistory=s;
            
            for(int i=0; i<QUEUE_SIZE; i++){
                if(clients[i]){
                    
                    if(clients[i]->NRGG == ggrecipient){
                        std::string result = "RECV_MSG:";
                        for(int i=0; i<QUEUE_SIZE; i++){
                            if(clients[i]){
                                if(clients[i]->sockfd == (*th_data).socket){
                                    result = result.append(std::to_string(clients[i]->NRGG));
                                }
                            }
                        }
                        result = result.append(":");
                        result.append(s.c_str());
                        char result_array[result.length()+1];
                        strncpy(result_array, result.c_str(), sizeof(result_array));
                        result_array[result.length()] = '\n';
                        
                        
                        result_array[result.length()+1] = '\0';
                        std::cout << result_array << std::endl;
                        send_message(result_array, ggrecipient);
                    }
                }
            }
            std::string filename;
            if(ggrecipient>ggsender){
                filename = std::to_string(ggrecipient)+":"+std::to_string(ggsender);
            }
            else{
                filename = std::to_string(ggsender)+":"+std::to_string(ggrecipient);
            }
                std::string chathistoryFileName = "chathistory/" + filename;
                std::fstream DoesExist;
                pthread_mutex_lock(&CHAT_MESSAGES_MUTEX);
                DoesExist.open(chathistoryFileName, std::fstream::in | std::fstream::out | std::fstream::app);
                if(!DoesExist){
                    
                  std::ofstream chatHistoryFile;
                  chatHistoryFile.open(chathistoryFileName, std::ios_base::app);
                    
                }
                DoesExist.close();
                std::fstream Chathistory;
                Chathistory.open(chathistoryFileName);
                Chathistory.clear();
                Chathistory.seekp(0, std::ios_base::end);
                Chathistory << std::to_string(ggsender)<<":"<<savetohistory << std::endl;
               
                Chathistory.close();
                pthread_mutex_unlock(&CHAT_MESSAGES_MUTEX);
            
        }
        if(strncmp(buff,"GET_HISTORY",11)==0){
            std::string s =buff;
            s=s.substr(s.find(":")+1,s.length());
            int ggreciever=std::stoi(s.substr(0,s.find(":")));
            s=s.substr(s.find(":")+1,s.length());
            //int numberofmessages=std::stoi(s.substr(0,s.length()));
            
            std::string filename;
            if(ggreciever>ggsender){
                filename = std::to_string(ggreciever)+":"+std::to_string(ggsender);
            }
            else{
                filename = std::to_string(ggsender)+":"+std::to_string(ggreciever);
            }
                
            std::ifstream historyFile;
            std::string chathistoryFileName = "chathistory/" + filename;
            pthread_mutex_lock(&CHAT_MESSAGES_MUTEX);
            historyFile.open(chathistoryFileName);
            std::string line;  
            char buff2[100];
            if(historyFile.is_open()){
            
                     while (getline(historyFile,line)){
                        memset(buff2,0,sizeof(buff2));
                        s="RECV_HIS:";
                        s.append(std::to_string(ggreciever));
                        s.append(":");
                        s.append(line);
                        strncpy(buff2,s.c_str(),sizeof(buff2));
                        printf("%s",s.c_str());
                        buff2[s.length()]='\n';
                        buff2[s.length()+1]='\0';
                        write((*th_data).socket, buff2, strlen(buff2));
                }
                
            }
            pthread_mutex_unlock(&CHAT_MESSAGES_MUTEX);
                
        }
    }
    for(int i=0; i<QUEUE_SIZE; i++){
        if(clients[i]){
          if(clients[i]->sockfd == (*th_data).socket){
                clients[i]=NULL;
            }
        }
   }
    close((*th_data).socket);
    free(t_data);
    clientCount--;
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
   
    if(argc>2){
        server_address.sin_addr.s_addr = inet_addr(argv[2]);
   } else {
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
   }
   
   if(argc>1){
        server_address.sin_port = htons(atoi(argv[1]));
   } else {
        server_address.sin_port = htons(SERVER_PORT);
   }
  
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
   
    struct sigaction act;   
    memset(&act, '\0', sizeof(act));   
    act.sa_handler = SIG_IGN;   
    if (sigaction(SIGPIPE, &act, NULL)) {
       perror("sigaction");
       exit(1);   
    }

    while(1)
    {
        connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);
        if((clientCount) == QUEUE_SIZE){
			printf("Maksymalna ilosc GaduGadaczy! Polaczenie odrzucone \n");
			close(connection_socket_descriptor);
			continue;
		}
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


