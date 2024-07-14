#include <stdio.h>
#include "disk.h"
#include "screen.h"
#include "constants.h"
#include <cx16.h>
#include <cbm.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"


void menuShow();
void myExit();
void menuReadDriveStatus();

void myExit() {}

void menuReadDriveStatus()
{
    unsigned char device, anyKey, driveStatus;
    unsigned char logicalFile = 10;

    while (anyKey != 0)
    {
        anyKey = 1;
        
        printf("\n\n\n        Enter device to read: ");
        scanf("%u", &device);
        
        driveStatus = readDriveStatus(logicalFile,device,COMMAND_CHANNEL);

        if (driveStatus == 0)
        {
            printf("\n        Status: %u - ", driveStatus);
            printCommandChannel(logicalFile,device,COMMAND_CHANNEL);
        }
        else if (driveStatus == 128)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Device Not Present)        ", driveStatus);
        }
        else if (driveStatus == 64)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (End of File)        ", driveStatus);
        }
        else if (driveStatus == 32)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Cassette Checksum Error)        ", driveStatus);
        }
        else if (driveStatus == 16)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Verify Error)        ", driveStatus);
        }
        else if (driveStatus == 8)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Data Block Too Long)        ", driveStatus);
        }
        else if (driveStatus == 4)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Data Block Too Short)        ", driveStatus);
        }
        else if (driveStatus == 2)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Time Out on Listener)        ", driveStatus);
        }
        else if (driveStatus == 1)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Time Out on Talker)        ", driveStatus);
        }
        else
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (UNKNOWN ERROR!)        ", driveStatus);
        }

        cbm_k_close(logicalFile);
        
        printf("\n\n        Press 1 <enter> to continue or 0 <enter> to exit: ");
        scanf("%u", &anyKey);
    }
    
    menuShow();

}

void menuEnumerateDrives()
{
    unsigned char device, anyKey, driveStatus;
    unsigned char logicalFile = 10;

    device = 8;

    printf("\n        Enumerating Drive Statuses (8 - 15)\n");
    printf("        ___________________________________");

    while (device <= 15)
    {                
        sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)"uj");
        driveStatus = readDriveStatus(logicalFile,device,COMMAND_CHANNEL);

        if (driveStatus == 0)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u - ", driveStatus);
            printCommandChannel(logicalFile,device,COMMAND_CHANNEL);
        }
        else if (driveStatus == 128)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Device Not Present)        ", driveStatus);
        }
        else if (driveStatus == 64)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (End of File)        ", driveStatus);
        }
        else if (driveStatus == 32)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Cassette Checksum Error)        ", driveStatus);
        }
        else if (driveStatus == 16)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Verify Error)        ", driveStatus);
        }
        else if (driveStatus == 8)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Data Block Too Long)        ", driveStatus);
        }
        else if (driveStatus == 4)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Data Block Too Short)        ", driveStatus);
        }
        else if (driveStatus == 2)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Time Out on Listener)        ", driveStatus);
        }
        else if (driveStatus == 1)
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (Time Out on Talker)        ", driveStatus);
        }
        else
        {
            printf("\n\n        Device: %u        ", device);
            printf("\n        Status: %u (UNKNOWN ERROR!)        ", driveStatus);
        }

        cbm_k_close(logicalFile);
        device++;
        logicalFile++;
    }

    printf("\n        ___________________________________\n");
    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%u", &anyKey);

    menuShow();
}

void menuInitializeDrive()
{
    unsigned char device, anykey;
    unsigned char logicalFile = 10;
       
    printf("\n\n\n        Enter drive to initialize : ");
    scanf("%u", &device);
    
    sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)"i");
    cbm_k_close(logicalFile);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%u", &anykey);

    menuShow();
}

void menuResetDrive()
{
    unsigned char device, anykey;
    unsigned char logicalFile = 10;
       
    printf("\n\n\n        Enter drive to reset : ");
    scanf("%u", &device);
    
    sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)"uj");
    printf("\n        ");
    printCommandChannel(logicalFile,device,COMMAND_CHANNEL);

    cbm_k_close(logicalFile);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%u", &anykey);

    menuShow();
}

void menuResetAllDrives()
{
    unsigned char device, anyKey;
    unsigned char logicalFile = 10;

    device = 8;

    printf("\n        Resetting All Drives (8 - 15)\n");

    while (device <= 15)
    {        
        sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)"uj");
        cbm_k_close(logicalFile);

        device++;
        logicalFile++;
    }
    
    printf("\n        Complete...");
    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%u", &anyKey);

    menuShow();
}

void menuReadCMDGetPartition()
{
    unsigned char device, anykey;
    unsigned char logicalFile = 10;
       
    printf("\n\n\n        Enter drive number : ");
    scanf("%u", &device);
    
    sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)"g-p");
    printf("\n        ");
    printCommandChannel(logicalFile,device,COMMAND_CHANNEL);

    cbm_k_close(logicalFile);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%u", &anykey);

    menuShow();
}

void menuChangeCMDPartition()
{
    unsigned char device, anykey;
    unsigned char logicalFile = 10;
    char * commandIssued = malloc(4);
    char * tmpStorage = malloc(4);
    char * partition = malloc(1);

    printf("\n\n\n        Enter drive number : ");
    scanf("%u", &device);
    
    printf("\n\n        Enter partition number : ");
    scanf("%u", &partition);
    itoa((unsigned char)partition, (char *)tmpStorage, (unsigned char)10);

    commandIssued = strcat((char*)"cp", (char *)tmpStorage);

    sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, (char*)commandIssued);
    printf("\n        ");
    printCommandChannel(logicalFile,device,COMMAND_CHANNEL);
    cbm_k_close(logicalFile);

    free(commandIssued);
    free(tmpStorage);
    free(partition);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%u", &anykey);

    menuShow();
}

void menuDirectDiskCommand()
{
    unsigned char device, anykey;
    char * commandIssued;
    unsigned char logicalFile = 10;
    
    printf("\n\n\n        Enter drive number : ");
    scanf("%u", &device);
    
    printf("\n\n        Enter disk command : ");
    scanf("%u", &commandIssued);

    sendDriveCommand(logicalFile, device, COMMAND_CHANNEL, commandIssued);
    cbm_k_close(logicalFile);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%u", &anykey);

    menuShow();
}

void menuCMDPartitionDirectory()
{
    unsigned char device, anykey;
    unsigned char logicalFile = 10;

    printf("\n\n\n        Enter drive number : ");
    scanf("%u", &device);
    
    loadCommand(logicalFile,device,COMMAND_CHANNEL, "$=p");

    printf("\n        ");
    printCommandChannel(logicalFile,device,COMMAND_CHANNEL);
    cbm_k_close(logicalFile);

    printf("\n\n        Press 0 <enter> to exit: ");
    scanf("%u", &anykey);

    menuShow();

}

void menuShow()
{
    unsigned char choice;

    clearScreen();
    
    printf("\n\n\n        **** COMMANDER X16 DRIVE UTILITIES v0.1 ****");
    printf("\n                    dan@binarywonder.com");
    printf("\n\n\n        1.  Read Drive Status");
    printf("\n        2.  Enumerate Drives (8 - 15)");
    printf("\n        3.  Initialize Drive");
    printf("\n        4.  Reset Individual Drive");
    printf("\n        5.  Get Current CMD Partition");
    printf("\n        6.  Reset All Drives (8 - 15)");
    printf("\n        7.  Change CMD Partition");
    printf("\n        8.  Issue Direct Disk Command (Experimental)");
    printf("\n        9.  Get CMD Partition Directory");
    printf("\n        10. Exit to Basic");
    printf("\n\n\n        Choice: ");
    scanf("%u", &choice);

    if (choice == (unsigned char)1) { menuReadDriveStatus(); }
    else if (choice == (unsigned char)2) { menuEnumerateDrives(); }
    else if (choice == (unsigned char)3) { menuInitializeDrive(); }
    else if (choice == (unsigned char)4) { menuResetDrive(); }
    else if (choice == (unsigned char)5) { menuReadCMDGetPartition(); }
    else if (choice == (unsigned char)6) { menuResetAllDrives(); }
    else if (choice == (unsigned char)7) { menuChangeCMDPartition(); }
    else if (choice == (unsigned char)8) { menuDirectDiskCommand(); }
    else if (choice == (unsigned char)9) { menuCMDPartitionDirectory(); }
    else if (choice == (unsigned char)10) { myExit(); }
    else { menuShow(); }
}