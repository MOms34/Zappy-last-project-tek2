/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-gaetan.darrort [WSL: Ubuntu]
** File description:
** detect_command
*/

#include "server.h"

int detect_command_4(char *buffer)
{
    if (strncmp(buffer, "Incantation", 11) == 0)
        return INCANTATION;
    if (strncmp(buffer, "Start", 5) == 0)
        return START;
    return -1;
}

int detect_command_3(char *buffer)
{
    if (strncmp(buffer, "Left", 4) == 0)
        return LEFT;
    if (strncmp(buffer, "Look", 4) == 0)
        return LOOK;
    if (strncmp(buffer, "Inventory", 9) == 0)
        return INVENTORY;
    if (strncmp(buffer, "Broadcast", 9) == 0)
        return BROADCAST;
    if (strncmp(buffer, "Connect_nbr", 11) == 0)
        return CONNECT_NBR;
    if (strncmp(buffer, "Fork", 4) == 0)
        return FORK;
    if (strncmp(buffer, "Eject", 5) == 0)
        return EJECT;
    if (strncmp(buffer, "Take", 4) == 0)
        return TAKE;
    if (strncmp(buffer, "Set", 3) == 0)
        return SET;
    return detect_command_4(buffer);
}

int detect_command_2(char *buffer)
{
    if (strncmp(buffer, "edi", 3) == 0)
        return EDI;
    if (strncmp(buffer, "sgt", 3) == 0)
        return SGT;
    if (strncmp(buffer, "sst", 3) == 0)
        return SST;
    if (strncmp(buffer, "seg", 3) == 0)
        return SEG;
    if (strncmp(buffer, "smg", 3) == 0)
        return SMG;
    if (strncmp(buffer, "suc", 3) == 0)
        return SUC;
    if (strncmp(buffer, "sbp", 3) == 0)
        return SBP;
    if (strncmp(buffer, "Forward", 7) == 0)
        return FORWARD;
    if (strncmp(buffer, "Right", 5) == 0)
        return RIGHT;
    return detect_command_3(buffer);
}

int detect_command_1(char *buffer)
{
    if (strncmp(buffer, "pbc", 3) == 0)
        return PBC;
    if (strncmp(buffer, "pic", 3) == 0)
        return PIC;
    if (strncmp(buffer, "pie", 3) == 0)
        return PIE;
    if (strncmp(buffer, "pfk", 3) == 0)
        return PFK;
    if (strncmp(buffer, "pdr", 3) == 0)
        return PDR;
    if (strncmp(buffer, "pgt", 3) == 0)
        return PGT;
    if (strncmp(buffer, "pdi", 3) == 0)
        return PDI;
    if (strncmp(buffer, "enw", 3) == 0)
        return ENW;
    if (strncmp(buffer, "ebo", 3) == 0)
        return EBO;
    return detect_command_2(buffer);
}

int detect_command(char *buffer)
{
    if (strncmp(buffer, "bct", 3) == 0)
        return BCT;
    if (strncmp(buffer, "msz", 3) == 0)
        return MSZ;
    if (strncmp(buffer, "mct", 3) == 0)
        return MCT;
    if (strncmp(buffer, "tna", 3) == 0)
        return TNA;
    if (strncmp(buffer, "pnw", 3) == 0)
        return PNW;
    if (strncmp(buffer, "ppo", 3) == 0)
        return PPO;
    if (strncmp(buffer, "plv", 3) == 0)
        return PLV;
    if (strncmp(buffer, "pin", 3) == 0)
        return PIN;
    if (strncmp(buffer, "pex", 3) == 0)
        return PEX;
    return detect_command_1(buffer);
}
