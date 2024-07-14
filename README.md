# Commander X16 Drive Utilities
Dan O'Malley

A small program to directly handle IEC serial devices on the Commander X16. Some functions do not work properly in the Commander X16 emulator. The functions work on real FD-2000 and 1581 hardware, however.

To build, run "make" once you have cc65 installed. Then run the DRVUTILS.PRG on your Commander X16.


        **** COMMANDER X16 DRIVE UTILITIES v0.1 ****
                    dan@binarywonder.com

        1.  Read Drive Status
        2.  Enumerate Drives (8 - 15)
        3.  Initialize Drive
        4.  Reset Individual Drive
        5.  Get Current CMD Partition
        6.  Reset All Drives (8 - 15)
        7.  Change CMD Partition
        8.  Issue Direct Disk Command (Experimental)
        9.  Get CMD Partition Directory
        10. Exit to Basic
