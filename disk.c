#include "constants.h"
#include <cbm.h>
#include <stdio.h>
#include "screen.h"

void printCommandChannel(unsigned char file, unsigned char device, unsigned char channel)
{
    unsigned char returnedByte;

    cbm_k_setlfs(file, device, channel); 
    cbm_k_setnam("");
    cbm_k_open();
    cbm_k_chkin(file);

    returnedByte = cbm_k_getin();

    while (returnedByte != 0xd)
    {
        cbm_k_bsout(returnedByte);
        returnedByte = cbm_k_getin();
    }
}

unsigned char readDriveStatus(unsigned char file, unsigned char device, unsigned char channel)
{
    unsigned char driveStatus;

    cbm_k_setlfs(file, device, channel); 
    cbm_k_setnam("");
    cbm_k_open();
    cbm_k_ckout(file);
    driveStatus = cbm_k_readst();

    return driveStatus;
}


void sendDriveCommand(unsigned char file, unsigned char device, unsigned char channel, char * command)
{
    cbm_k_setlfs(file, device, channel);
    cbm_k_setnam(command);
    cbm_k_open();
}


void loadCommand(unsigned char file, unsigned char device, unsigned char channel, char * fileName)
{
    cbm_k_setlfs(file, device, channel); 
    cbm_k_setnam(fileName);
    cbm_k_load(0, 0xc000);

}