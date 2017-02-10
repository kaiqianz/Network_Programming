#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;
#define SERVERPORT 3333
#define MAXDATASIZE 100
#define BACKLOG 10
int content[4][4]; //the neighbor information from different serveres
struct sockaddr_in my_addr;


//create the TCP connection of the server and the client
void client_createTCP(){
    int sock_fd,client_fd,recvbytes;
    string s;
    
    int buf[MAXDATASIZE]; //the size of the buffer to store information
  
    struct sockaddr_in remote_addr;
//create the socket in the client side
    if((sock_fd = socket(AF_INET, SOCK_STREAM,0)) ==-1){
        perror("creat socket in error!");
        exit(1);
        
    }
    
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(SERVERPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    socklen_t len = sizeof(my_addr);

//bind with the server
    if(bind(sock_fd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr_in)) == -1){
        perror("bind in error!");
        exit(1);
        
    }

//listen for the request from the serverf
    if(listen(sock_fd,BACKLOG) == -1){
        perror("listen in error");
        exit(1);
    }

   
    int i = 0;
    
// ready for the transfer of information from the servers
    while(i < 4){
        socklen_t sin_size = sizeof(my_addr);
        
//accept the request of the server
        if((client_fd = accept(sock_fd, (struct sockaddr *)&remote_addr, &sin_size)) == -1) {
            perror("accept in error");
            continue;
        }
//receive information from the servers
        if((recvbytes = recv(client_fd, buf, MAXDATASIZE,0))==-1){
            perror("recv in error!");
            exit(1);
        }
        
        buf[recvbytes] = '\0';

        if(buf[0] == 1){ //reveive information from the serverA
            s = "serverA";
             cout<<"The Client has TCP port number 25748 and IP address "<<inet_ntoa(remote_addr.sin_addr)<<"."<<endl;
             cout<<"The Client recevies neighbor information from the ServerA with TCP port number "<<ntohs(remote_addr.sin_port)<<" and IP address "<<inet_ntoa(remote_addr.sin_addr)<<endl;
            cout<<"The Server A has the following neighbor information:"<<endl;
//print out the neighbor information of the servers
            cout<<"Neighbor-----Cost"<<endl;
            for(int i=0;i<4;i++) {
                content[0][i] = buf[i+1];
                if(content[0][i]!=0){
                    if(i == 0){
                        cout<<"serverA      "<<content[0][i]<<endl;
                    }
                    if(i ==1){
                        cout<<"serverB      "<<content[0][i]<<endl;
                    }
                    if(i ==2){
                      cout<<"serverC      "<<content[0][i]<<endl;
                    }
                    if(i ==3){
                        cout<<"serverD      "<<content[0][i]<<endl;
                    }
                    
                }
            }
            cout<< "For this connection with Server A, the client has TCP port number 25748 and IP address "<<inet_ntoa(remote_addr.sin_addr)<<endl;
            
        }
        if(buf[0] == 2){ //reveive information from the serverB
            s = "serverB";
                cout<<"The client recevies neighbor information from the ServerB with TCP port number "<<ntohs(remote_addr.sin_port)<<" and IP address "<<inet_ntoa(remote_addr.sin_addr)<<endl;
            for(int i=0;i<4;i++) {
                content[1][i] = buf[i+1];
                if(content[1][i]!=0){
                    if(i == 0){
                        cout<<"serverA      "<<content[1][i]<<endl;
                    }
                    if(i ==1){
                        cout<<"serverB      "<<content[1][i]<<endl;
                    }
                    if(i ==2){
                        cout<<"serverC      "<<content[1][i]<<endl;
                    }
                    if(i ==3){
                        cout<<"serverD      "<<content[1][i]<<endl;
                    }
                    
                    
                }

             
                //cout <<"serverB: "<< content[1][i]<<endl;
            }
             cout<< "For this connection with Server B, the client has TCP port number 25748 and IP address "<<inet_ntoa(my_addr.sin_addr)<<endl;
        }
        if(buf[0] == 3){ //reveive information from the serverC
            s = "serverC";
             cout<<"The client recevies neighbor information from the ServerC with TCP port number "<<ntohs(remote_addr.sin_port)<<" and IP address "<<inet_ntoa(remote_addr.sin_addr)<<endl;
            for(int i=0;i<4;i++) {
                content[2][i] = buf[i+1];
                if(content[2][i]!=0){
                    if(i == 0){
                        cout<<"serverA      "<<content[2][i]<<endl;
                    }
                    if(i ==1){
                        cout<<"serverB      "<<content[2][i]<<endl;
                    }
                    if(i ==2){
                        cout<<"serverC      "<<content[2][i]<<endl;
                    }
                    if(i ==3){
                        cout<<"serverD      "<<content[2][i]<<endl;
                    }
                    
                    
                }

                
              
            }
            cout<< "For this connection with Server C, the client has TCP port number 25748 and IP address "<<inet_ntoa(my_addr.sin_addr)<<endl;
        }
        if(buf[0] == 4){ //reveive information from the serverD
            s = "serverD";
             cout<<"The client recevies neighbor information from the ServerD with TCP port number "<<ntohs(remote_addr.sin_port)<<" and IP address "<<inet_ntoa(remote_addr.sin_addr)<<endl;
            for(int i=0;i<4;i++) {
                content[3][i] = buf[i+1];
                if(content[3][i]!=0){
                    if(i == 0){
                        cout<<"serverA      "<<content[3][i]<<endl;
                    }
                    if(i ==1){
                        cout<<"serverB      "<<content[3][i]<<endl;
                    }
                    if(i ==2){
                        cout<<"serverC      "<<content[3][i]<<endl;
                    }
                    if(i ==3){
                        cout<<"serverD      "<<content[3][i]<<endl;
                    }
                    
                    
                }

                
               
            }
             cout<< "For this connection with Server D, the client has TCP port number 25748 and IP address "<<inet_ntoa(my_addr.sin_addr)<<endl;
            
        }
     
        
        i++;
        
//get the IP address and the port number of the servers and the client
        socklen_t len = sizeof(my_addr);
        int socket_name = getpeername(client_fd, (struct sockaddr *)&remote_addr, &len);
        
        socklen_t lenC = sizeof(my_addr);
        int ssocket_name = getsockname(client_fd, (struct sockaddr *)&my_addr, &lenC);

    }
    close(client_fd);

}

//create the UDP connection between the server and the client
void client_createUDP(){
    int h= 0;
    int i =21748;

    while(h<4){
// create the interface of the UDP
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(i);
        i+=1000;
// create the socket of the client
    int client_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_socket_fd < 0){
        perror("create socket failed!");
        exit(1);
    }
    
// send the network topology to the servers
   
    if(sendto(client_socket_fd, content, sizeof(content), 0, (struct sockaddr*)&server_addr, sizeof(server_addr))< 0){
        perror("send the wrong network topology");
        exit(1);
    }
//get the IP address and the port number of the servers and the client
        socklen_t lenl = sizeof(client_socket_fd);
        int client_UDP_socket_name = getsockname(client_socket_fd, (struct sockaddr *)&my_addr, &lenl);
       
        socklen_t lenb = sizeof(server_addr);
        int socket_name = getpeername(client_socket_fd, (struct sockaddr *)&server_addr, &lenb);
        
        cout<<"The Client has sent the network topology to the network topology to the Server A with UDP port number "<<ntohs(server_addr.sin_port)<<" and IP address "<<inet_ntoa(server_addr.sin_addr)<<endl;
//print out the connection between differnt servers
        cout<<"Edge-----Cost"<<endl;
        
        for(int i=0;i<4;i++){
            for(int j=i;j<5;j++){
                if(content[i][j]!=0){
                    if(i ==0){
                        if(j ==0){
                            cout<<"AA      "<<content[0][j]<<endl;
                        }
                        if(j ==1){
                            cout<<"AB      "<<content[0][j]<<endl;
                        }
                        if(j ==2){
                            cout<<"AC      "<<content[0][j]<<endl;
                        }
                        if(j ==3){
                            cout<<"AD      "<<content[0][j]<<endl;
                        }
            

                    }
                    if(i==1){
                        if(j==1){
                            cout<<"BB      "<<content[1][j]<<endl;
                        }
                        if(j ==2){
                            cout<<"BC      "<<content[1][j]<<endl;
                        }
                        if(j ==3){
                            cout<<"BD      "<<content[1][j]<<endl;
                        }
                        
                   

                    }
                    if(i==2){
                        if(j==2){
                            cout<<"CC      "<<content[2][j]<<endl;
                        }
                        if(j ==3){
                            cout<<"CD      "<<content[2][j]<<endl;
                        }
                        if(j ==3){
                            cout<<"CD      "<<content[2][j]<<endl;
                        }
                        
                      

                    }
                    if(i==3){
                        if(j==3){
                            cout<<"DD      "<<content[2][j]<<endl;
                        }

                        
                    }
                }
            }
        }

        if(h==0){
           cout<<"For this connection with Server A, the Client has UDP port number "<<ntohs(my_addr.sin_port)<<" and IP address "<<inet_ntoa(my_addr.sin_addr)<< endl;
        }
        if(h==1){
            cout<<"For this connection with Server B, the Client has UDP port number "<<ntohs(my_addr.sin_port)<<" and IP address "<<inet_ntoa(my_addr.sin_addr)<< endl;
        }
        if(h==2){
            cout<<"For this connection with Server C, the Client has UDP port number "<<ntohs(my_addr.sin_port)<<" and IP address "<<inet_ntoa(my_addr.sin_addr)<< endl;
        }
        if(h==3){
            cout<<"For this connection with Server D, the Client has UDP port number "<<ntohs(my_addr.sin_port)<<" and IP address "<<inet_ntoa(my_addr.sin_addr)<< endl;
        }

        
    close(client_socket_fd);
        h++;
    }
}

int main()
{
   
    client_createTCP();
    client_createUDP();
    return 0;
    
}


