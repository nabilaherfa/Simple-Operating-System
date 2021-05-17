void main () {
    char dir[14], buffer[512], current_dir, file[1024];
	int i, found, x, mkdir_succ;
	
	interrupt(0x21, 0x02, buffer, 512, 0);
    current_dir = buffer[0];
    for (i = 0; i < 14; i++) {
		dir[i] = buffer[i + 1];
	}

	interrupt(0x21, 0x2, file, 0x101, 0);
	interrupt(0x21, 0x2, file + 512, 0x102, 0);
	
    i = 0;
	found = 0;
	while(i < 64 && !found) {
		if(file[i * 16] == 0x0 && file[i * 16 + 1] == 0) {
			found = 1;
			x = i;
			break;
		}
		++i;
	}
	
    if(found) {
		file[x * 16] = current_dir;
		file[x * 16 + 1] = 0xFF;
		for(i = 0; i < 14; i++) {
			file[x * 16 + 2 + i] = dir[i];
		}
		interrupt(0x21, 0x3, file, 257, 0);
	}
    interrupt(0x21, 0x06, "shell", 0x2000, &mkdir_succ);
}
