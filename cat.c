#include "textmodule.h"
#include "fileIOmodule.h"
#include "mathmodule.h"

void main () {
    char namaFile[14], tempBuff[512], isiFile[512 * 16], currDir;
	int found, i;
	found = 0;
	
    // get parentIdx and filenamaFile
	interrupt(0x21, 0x02, tempBuff, 512, 0);
    currDir = tempBuff[0];
    for (i = 0; i < 14; i++) {
		namaFile[i] = tempBuff[i + 1];
	}

	//empty Buffer
	for (i = 0; i < 512 * 16; i++) {
		isiFile[i] = 0x0;
	}

	//read isiFile
	readFile(isiFile, namaFile, &found, currDir);

	if (found == 1) {
		printString("isi File : --------------------------------------\n");
		printString(isiFile);
		printString("----------------------------\n");
	} else {
		printString("File Tidak Ditemukkan\n\0");
	}
    interrupt(0x21, 0x06, "shell", 0x2000, &found);
}
