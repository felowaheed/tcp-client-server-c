# TCP Client-Server Application (Windows - Winsock)

## Overview
A simple TCP client-server application written in C using the Winsock API.
The server listens for incoming connections, the client connects and sends a message, and the server responds back.

Foundation for networking concepts used in chat applications, IoT systems, CCTV/network systems, and client-server architectures.

## Technologies Used
- C Programming Language
- Winsock2 (Windows Sockets API)
- TCP Protocol (SOCK_STREAM)
- Multithreading using Windows Threads (CreateThread)

## Project Structure
project-folder/
├── server.c
├── client.c
└── README.md

## How to Compile
gcc server.c -o server -lws2_32
gcc client.c -o client -lws2_32

## How to Run
Run server first:
./server

Then run client in a separate terminal:
./client

## Expected Output
Server:
Server listening on port 12345...
Client connected
Client says: Hello from client!

Client:
Server reply: Hello from server!

## Notes
- Make sure the server is running before starting the client
- Runs on localhost (127.0.0.1) only
- Firewall may block connections on some systems

## Possible Extensions
- Multi-client chat system
- File transfer system
- Encrypted communication (SSL/TLS)
- IoT device communication

## Author
Felopateer Waheed — github.com/felowaheed
