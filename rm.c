#include "textmodule.h"
#include "fileIOmodule.h"
#include "folderIOmodule.h"

void main() {
    char namaFile[14], FolderFile[512*2], tempBuff[512], currDir;
	int i, j, isFound, namaSama, index, inputFolderFile, isSuccess;
	isFound = 0;

	// get parentIdx and filename
	interrupt(0x21, 0x02, tempBuff, 512, 0);
    currDir = tempBuff[0];
    for (i = 0; i < 14; i++) {
		namaFile[i] = tempBuff[i + 1];
	}

	//read sector 257 and 258 (file/folder)
	interrupt(0x21, 0x02, FolderFile, 257, 0);
	interrupt(0x21, 0x02, FolderFile + 512, 258, 0);
	
	i = 0;
	while (!isFound && i < 1024) {
        // Search for files / folder
        for (i = 0; i < 1024; i += 16) {
			if (FolderFile[i] == currDir) {
				if (FolderFile[i + 2] != 0x0) {
                	index = i + 2;
                
                	//matching name
                	namaSama = 1;
	                for (j = 0; j < 14; j++) {
    	                if (namaFile[j] != FolderFile[j + index]) {
        	                namaSama = 0;
							break;
                	    } else if (FolderFile[j + index] == '\0' && namaFile[j] == '\0') {
                    		break;
                    	}
                	}

                	if (namaSama) {
                    	isFound = 1;
                    	inputFolderFile = FolderFile[i + 1];
						break;
                	}
				}
        	}
		}
    }
	
	if (!isFound) {
		printString("File/folder not found\r\n\0");
	}
	else {
		if (inputFolderFile == 0xFF) {
			delDir(inputFolderFile);
			printString("Folder deleted successfully!\r\n\0");
		} else {
			delFile(inputFolderFile);
			printString("File deleted successfully!\r\n\0");
		}
	}
    interrupt(0x21, 0x06, "shell", 0x2000, &isSuccess);
}