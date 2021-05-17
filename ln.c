#include "textmodule.h"
#include "fileIOmodule.h"
#include "mathmodule.h"

void main () {
    char link[14], path[100], tempBuff[512], isiFile[512 * 16], currDir;
	int found, i, j, k;
	found = 0;
	
	//empty Buffer
	for (i = 0; i < 100; i++) {
		path[i] = 0x0;
	}
	for (i = 0; i < 14; i++) {
		link[i] = 0x0;
	}

    // get parentIdx and filelink
	interrupt(0x21, 0x02, tempBuff, 512, 0);
    currDir = tempBuff[0];
    for (i = 0; i < 100; i++) {
		path[i] = tempBuff[i + 1];
	}

	if (tempBuff[i] == 0x0){
		printString("masukkan symbolic link");
	}

	i++;
	j = 0;

	while(tempBuff[i] != 0x0){
		link[j] = tempBuff[i];
		i++;
    	j++;
  	}

	interrupt(0x21, 0x06, "shell", 0x2000, &found);
}