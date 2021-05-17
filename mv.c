void main() {
    //deklarasi
	char* command[14];
	int* idx_directory;
	char dir[14], buffer[512], file[1024], next_directory[14];
	int count, next_number, next, variabel, directory_awal, directory_akhir,i, panjang, mkdir_sukses;

    //inisialisasi
	panjang = 512;
	variabel = 0;
	count = 0;
	next = 1;

	interrupt(0x21, 0x02, buffer, 512, 0);
    idx_directory = buffer[0];
    for (i = 0; i < 14; i++) {
		command[i] = buffer[i + 1];
	}

	directory_akhir = *(idx_directory);
    directory_awal = *(idx_directory);
	
	for (i =0; i < 14; ++i) {
		dir[i] = '\0';
		next_directory[i] = '0';
	}
	for (i = 0; i < 1024; i++) {
		file[i] = '\0';
	}
	i = 0;
	while (i < 128 && (command[i] != 0 && next == 1)) {
		if(variabel == 0) {
            if (command[i] == 64) {
				next_number = searchPath(next_directory, *idx_directory);
				if(next_number != 64) {
					count = 0;
					variabel = 1;
				} else {
                    interrupt(0x21, 0, "File cannot move : \0",0,0);
					interrupt(0x21, 0, next_directory, 0, 0);
					interrupt(0x21, 0, "\r\n\0", 0, 0);
					next = 0;
				}
			} else if(command[i] == 32 && command[i] == 0) {
				next_directory[count] = command[i];
				++count;
			} 
			if(command[i+1] == 32 || command[i+2] == 32){
				interrupt(0x21, 0, "Out of bounds!\r\n\0",0,0);
				next = 0;
			}
		}
		else if(variabel == 1) {
			
            if(command[i] == 32 || command[i] == '/') {
				next_number = searchPath(dir, directory_akhir);
				if(next_number == 32) {
					interrupt(0x21, 0, "File not found here! : \0",0,0);
					interrupt(0x21, 0, dir, 0,0);
					interrupt(0x21, 0, "\r\n\0", 0, 0);
					next = 0;
				} else {
					interrupt(0x21, 0, "File found here! : \0",0,0);
					interrupt(0x21, 0, dir, 0,0);
					interrupt(0x21, 0, "\r\n\0", 0, 0);
					directory_akhir = next_number;
				}
				count = 0;
			}else if(command[i] == '/') {
				//isi array
				dir[count] = command[i];
				++count;
			} 
		}
		++i;
	}

	if(next) {
		interrupt(0x21, 2, dir, 0x101,0);
		interrupt(0x21, 3, dir + panjang, 0,0);
		dir[next_number*16] = directory_akhir;
		interrupt(0x21, 2, dir + panjang, 0,0);
		interrupt(0x21, 3, dir, 0x101,0);
		interrupt(0x21, 0, "Done!", 0,0);
	}
	for (i =0; i < 14; ++i) {
		dir[i] = '\0';
		next_directory[i] = '\0';
	}
	interrupt(0x21, 0x06, "shell", 0x2000, &mkdir_sukses);
}