/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** define
*/

#ifndef DEFINE_H_
    #define DEFINE_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <ctype.h>
    #include <sys/wait.h>
    #include <errno.h>
    #include <netdb.h>
    #include <sys/select.h>
    #include <uuid/uuid.h>
    #include <dlfcn.h>
    #include <stdbool.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <time.h>
    #include <math.h>
    #include "lib.h"
    #include "content.h"

    #define NORTH 1
    #define EAST 2
    #define SOUTH 3
    #define WEST 4

    // index for command
    #define MSZ 0
    #define BCT 1
    #define MCT 2
    #define TNA 3
    #define PNW 4
    #define PPO 5
    #define PLV 6
    #define PIN 7
    #define PEX 8
    #define PBC 9
    #define PIC 10
    #define PIE 11
    #define PFK 12
    #define PDR 13
    #define PGT 14
    #define PDI 15
    #define ENW 16
    #define EBO 17
    #define EDI 18
    #define SGT 19
    #define SST 20
    #define SEG 21
    #define SMG 22
    #define SUC 23
    #define SBP 24
    #define FORWARD 25
    #define RIGHT 26
    #define LEFT 27
    #define LOOK 28
    #define INVENTORY 29
    #define BROADCAST 30
    #define CONNECT_NBR 31
    #define FORK 32
    #define EJECT 33
    #define TAKE 34
    #define SET 35
    #define INCANTATION 36
    #define START 37

    // index for resources
    #define FOOD 0
    #define LINEMATE 1
    #define DERAUMERE 2
    #define SIBUR 3
    #define MENDIANE 4
    #define PHIRAS 5
    #define THYSTAME 6

    // nubmber of thread per pool for player
    #define NUM_THREADS 10

#endif /* !DEFINE_H_ */
