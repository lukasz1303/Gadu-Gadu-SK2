#!/bin/bash
gcc -pthread server.c -Wall -o server
gcc -pthread client.c -Wall -o client
