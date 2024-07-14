#include "constants.h"
#include <cbm.h>
#include <stdio.h>
#include "screen.h"

unsigned char globalFile, globalDevice, globalChannel, globalDriveStatus, globalReturnedByte;
char * globalCommand = "";

void clearGlobalVars()
{
    globalFile = 0;
    globalDevice = 0;
    globalChannel = 0;
    globalDriveStatus = 0;
    globalReturnedByte = 0;
    globalChannel = 0;
}

void printCommandChannel(unsigned char file, unsigned char device, unsigned char channel)
{
    clearGlobalVars();
    
    globalFile = file;
    globalDevice = device;
    globalChannel = channel;

    cbm_k_setlfs(globalFile, globalDevice, globalChannel); 
    cbm_k_setnam("");
    cbm_k_open();
    cbm_k_chkin(globalFile);

    globalReturnedByte = cbm_k_getin();

    while (globalReturnedByte != 0xd)
    {
        cbm_k_bsout(globalReturnedByte);
        globalReturnedByte = cbm_k_getin();
    }

}

unsigned char readDriveStatus(unsigned char file, unsigned char device, unsigned char channel)
{
    clearGlobalVars();
    
    globalFile = file;
    globalDevice = device;
    globalChannel = channel;

    cbm_k_setlfs(globalFile, globalDevice, globalChannel); 
    cbm_k_setnam("");
    cbm_k_open();
    cbm_k_ckout(globalFile);
    globalDriveStatus = cbm_k_readst();

    return globalDriveStatus;

}


void sendDriveCommand(unsigned char file, unsigned char device, unsigned char channel, char * command)
{
    clearGlobalVars();

    globalFile = file;
    globalDevice = device;
    globalChannel = channel;
    globalCommand = command;

    cbm_k_setlfs(globalFile, globalDevice, globalChannel);
    cbm_k_setnam(globalCommand);
    cbm_k_open();

}


void loadCommand(unsigned char file, unsigned char device, unsigned char channel, char * fileName)
{
    clearGlobalVars();
    
    globalFile = file;
    globalDevice = device;
    globalChannel = channel;

    cbm_k_setlfs(globalFile, globalDevice, globalChannel); 
    cbm_k_setnam(fileName);
    cbm_k_load(0, 0xc000);

}