/*
Assignment 1: HTTP server:

Goal: build a system that uses strong modularity. 

1. We are creating a server that will listen and accept the connections 
*/

/*
./httpserver <port>
1. Read the port requested from the client and 
2. Get header request:

PUT /foo.txt HTTP/1.1\r\nContent-Length: 12\r\n\r\nHello world!

3. HTTP server must always produce HTTP version string, HTTP/1.1
4. List of status-codes that http server needs to produce 

Status code: 
200 - OK with a message displaying
201 - Created 
400 - Bad Request
403 - Forbidden
404 - Not Found
500 - Internal server error
501 - Not implemented


*/

#include <stdio.h>

void function(){

}

