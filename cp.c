void copyFile (char * source, char * dest, char * buffer, char parentIndex);
void copyFolder (char * source, char * dest, char * buffer, char parentIndex);

int main()
{
    int i;
    char buffer[512 * 16];
    int isFolder;
    int isDestFolder;

    char currentDir;
    char argc;
    char *argv[16];

    getParameters(&currentDir, &argc, argv);

    if (argc != 2) {
        printString("Usage: cp <source> <destination>");
        returnToSender();
        return 0;
    }

    isFolder = isPathFolder(argv[0], currentDir);
    isDestFolder = isPathFolder(argv[1], currentDir);

    if (isDestFolder != 1) {
        printString("Usage: cp <source> <destination>\r\n");
        printString("Destinasi harus sebuah directory");
    }

    if (isFolder == -1) {
        printString("Bukan file atau directory");
    } else if (isFolder == 0) {
        // COPY FILE
        copyFile(argv[0], argv[1], buffer, currentDir);
    } else {
        copyFolder(argv[0], argv[1], buffer, currentDir);
    }
    
    returnToSender();
    return 0;
}

void copyFile (char * source, char * dest, char * buffer, char parentIndex) {
    int result;
    int copyIndex;

    readFile(buffer, source, &result, parentIndex);

    copyIndex = getPathIndex(parentIndex, dest);

    writeFile(buffer, source, &result, copyIndex);
}

void copyFolder (char * source, char * dest, char * buffer, char parentIndex) {
    int result;
    int copyIndex;

    char name[15];
    int n;
    char isFolder;

    int i;

    copyIndex = getPathIndex(parentIndex, dest);

    createFolder(source, copyIndex);

    listContent(getPathIndex(parentIndex, source), &n);
    for (i = 0; i < n; i++) {
        getContentInFolder(i, name, &isFolder);
        if (isFolder) {
            copyFolder(name, source, buffer, copyIndex);
        } else {
            copyFile(name, source, buffer, copyIndex);
        }
    }
}
