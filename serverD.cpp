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
#include <fstream>
using namespace std;
#define SERVERPORT 3333
#define MAXDATASIZE 100
int data[5];


//output an empty line
void OutPutAnEmptyLine(){
    cout<<"\n";
}
//read data from the file, Word by Word
void ReadDataFromFileWBW(){
    ifstream fin("serverD.txt");
    string s;
    data[0] = 4;
// read the neighbor information to the server
    cout<< "The server D has the following neighbor information:"<<endl;
    cout<< "Neighbor-----Cost"<<endl;
    while(fin >> s){
        
        if(s == "serverA"){
            int i = 1;
            fin >> s;
            int cost = atoi(s.c_str());
            data[i] = cost;
            
            cout << "serverA      " << cost << endl;
            
        }
        if(s == "serverB"){
            int i = 2;
            fin >> s;
            int cost = atoi(s.c_str());
            data[i] = cost;
            
            cout << "serverB      " << cost << endl;
            
        }
        if(s=="serverC"){
            int i = 3;
            fin >> s;
            int cost = atoi(s.c_str());
            data[i] = cost;
            
            cout << "serverC      " << cost << endl;
        }
        if(s == "serverD"){
            int i =4;
            fin >> s;
            int cost = atoi(s.c_str());
            data[i] = cost;
            
            cout << "serverD      " << cost << endl;
        }
    }
}

//create the TCP connection between the server and the client
void serverD_createTCP(){
    int sock_fd;
    
    char buf[MAXDATASIZE];//define the max size of the buffer
    struct hostent *host;
    struct sockaddr_in serv_addr, serverD;
    ReadDataFromFileWBW();
    OutPutAnEmptyLine();
    
    
    if((host = gethostbyname("localhost")) == NULL){
        herror("gethostbyname in error!");
        exit(1);
    }
    
//create the socket in the serverD side
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("creat socket in error!");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVERPORT);
    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
   
//create the connection between the serverD and the client
    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect in error!");
        exit(1);
    }
//send the neighbor information of serverD to the client
    if(send(sock_fd, data, sizeof(data), 0) == -1){
        perror("send in error!");
        exit(1);
    }
    
    socklen_t lenD = sizeof(serv_addr);
    int socket_name = getsockname(sock_fd, (struct sockaddr *)&serverD, &lenD);
    cout<< "The server D finishes sending its neighbor information to the Client with TCP port number "<<"25748"<<" and IP address "<<inet_ntoa(serverD.sin_addr)<<endl;
    cout<<"For this connection with the Client, the Server D has TCP port number "<<ntohs(serverD.sin_port)<<" and IP address "<<inet_ntoa(serverD.sin_addr)<<endl;

    close(sock_fd);//close the connection of the TCP connection
    
}

//create the UDP connection of the serverD and the client
void serverD_createUDP(){
    struct sockaddr_in server_addr,serverD;
  
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(24748);// the UDP port number of the serverD
    
// create socket of the serverD
    int server_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_socket_fd == -1)
    {
        perror("create socket failed:");
        exit(1);
    }
    
// bind the serverD and the client
    if((bind(server_socket_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in)))==-1)
    {
        perror("server bind failed:");
        exit(1);
    }
    

        struct sockaddr_in client_addr;
        socklen_t client_addr_length = sizeof(client_addr);
        
        // receive the data from the client
        int buffer[4][4];//the buffer to receive the information from the client
      
        if(recvfrom(server_socket_fd,buffer,sizeof(buffer),0,(struct sockaddr*)&client_addr, &client_addr_length) == -1){
            perror("receive data failed");
            exit(1);
        }
    
// to get the port number and IP address of the client and serverD
        socklen_t lenD = sizeof(server_addr);
        int UDP_socket_name = getsockname(server_socket_fd, (struct sockaddr *)&serverD, &lenD);
        
        socklen_t len = sizeof(server_addr);
        int socket_name = getpeername(server_socket_fd, (struct sockaddr *)&client_addr, &len);

       cout<<"The server D has received the network tpology from Client with UDP port number "<<ntohs(client_addr.sin_port)<<" and IP address "<<inet_ntoa(client_addr.sin_addr)<<endl;
//print out the connection information of all the server

    cout<<"Edge-----Cost"<<endl;
    
    for(int i=0;i<4;i++){
        for(int j=i;j<5;j++){
            if(buffer[i][j]!=0){
                if(i ==0){
                    if(j ==0){
                        cout<<"AA      "<<buffer[0][j]<<endl;
                    }
                    if(j ==1){
                        cout<<"AB      "<<buffer[0][j]<<endl;
                    }
                    if(j ==2){
                        cout<<"AC      "<<buffer[0][j]<<endl;
                    }
                    if(j ==3){
                        cout<<"AD      "<<buffer[0][j]<<endl;
                    }
                }
                if(i==1){
                    if(j==1){
                        cout<<"BB      "<<buffer[1][j]<<endl;
                    }
                    if(j ==2){
                        cout<<"BC      "<<buffer[1][j]<<endl;
                    }
                    if(j ==3){
                        cout<<"BD      "<<buffer[1][j]<<endl;
                    }
                }
                if(i==2){
                    if(j==2){
                        cout<<"CC      "<<buffer[2][j]<<endl;
                    }
                    if(j ==3){
                        cout<<"CD      "<<buffer[2][j]<<endl;
                    }
                    if(j ==3){
                        cout<<"CD      "<<buffer[2][j]<<endl;
                    }
                }
                if(i==3){
                    if(j==3){
                        cout<<"DD      "<<buffer[2][j]<<endl;
                    }
                    
                }
            }
        }
    }
    
    cout<<"For this connection with Client, the Server D has UDP port number "<<ntohs(serverD.sin_port)<<" and IP address "<<inet_ntoa(client_addr.sin_addr)<< endl;
    
    close(server_socket_fd);
    
}

int main(){
    
    cout << "The Server D is up and running."<<endl;
    serverD_createTCP();
    serverD_createUDP();
    return 0;
}

