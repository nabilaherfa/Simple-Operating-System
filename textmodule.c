#include "textmodule.h"

void printString(char *string) {
	int i = 0;
	while(string[i] != '\0'){
		interrupt(0x10, 0xE00 + string[i], 0, 0, 0);
		i++;
	}
}

void readString(char *string) {
	int i = 0;
	int idx = 0;
	char input;
	do {
		input = interrupt(0x16, 0, 0, 0, 0);
		if (input == '\r') {
			string[idx] = '\0';
			interrupt(0x10, 0xE00 + input, 0, 0, 0);
		} 
		else if (input != '\b') {
			interrupt(0x10, 0xE00 + input, 0, 0, 0);
			string[idx] = input;
			idx++;
		} 
		else if (idx > 0) {
			idx--;
			interrupt(0x10, 0xE00+ '\b', 0, 0, 0);
		}
	} 
	while (input != '\r');
	interrupt(0x10, 0xE00 + '\r', 0, 0, 0);
}

void printLogo(){
	printStringPosition(".-------------------------.---------------------.-----------------.", 0, 0, 0xD);//ungu
	printStringPosition("|                                                                 |", 0, 1, 0xD);
	printStringPosition("|   _ (`-.                .-')                 .-') _             |", 0, 2, 0xA);//hijau
	printStringPosition("|  ( (OO  )              ( OO ).              ( OO ) )            |", 0, 3, 0xB);//cyan
	printStringPosition("| _.`     \\ .-'),-----. (_)---\\_)  ,-.-') ,--./ ,--,'  ,----.     |", 0, 4, 0xC);//merah
	printStringPosition("|(__...--''( OO'  .-.  '/    _ |   |  |OO)|   \\ |  |\\ '  .-./-')  |", 0, 5, 0xE);//kuning
	printStringPosition("| |  /  | |/   |  | |  |\\  :` `.   |  |  \\|    \\|  | )|  |_( O- ) |", 0, 6, 0xF);//putih
	printStringPosition("| |  |_.' |\\_) |  | |  | '..`''.)  |  |(_/|  .     |/ |  | .--, \\ |", 0, 7, 0xE);
	printStringPosition("| |  .___.'  \\ |  | |  |.-._)   \\ ,|  |_.'|  |\\    | (|  | '. (_/ |", 0, 8, 0xC);
	printStringPosition("| |  |        `'  '-'  '\\       /(_|  |   |  | \\   |  |  '--'  |  |", 0, 9, 0xB);
	printStringPosition("| `--'          `-----'  `-----'   `--'   `--'  `--'   `------'   |", 0, 10, 0xA);
	printStringPosition("|                                                                 |", 0, 11, 0xD);
	printStringPosition("'-------------------------.---------------------.-----------------'", 0, 12, 0xD);
	printStringPosition(".-------------------------.------------------------.-----------------.", 0, 13, 0xD);//ungu
	printStringPosition("|                                                                     |", 0, 14, 0xD);
	printStringPosition("|.-------.     ,-----.       .-'''-. .-./`) ,---.   .--.  .-_'''-.    |", 0, 15, 0xA);
	printStringPosition("|\\  _(`)_ \\  .'  .-,  '.    / _     \\\\ .-.')|    \\  |  | '_( )_   \\   |", 0, 16, 0xB);
	printStringPosition("|| (_ o._)| / ,-.|  \\ _ \\  (`' )/`--'/ `-' \\|  ,  \\ |  ||(_ o _)|  '  |", 0, 17, 0xC);
	printStringPosition("||  (_,_) /;  \\  '_ /  | :(_ o _).    `-'` `|  |\\_ \\|  |. (_,_)/___|  |", 0, 18, 0xE);
	printStringPosition("||   '-.-' |  _`,/ \\ _/  | (_,_). '.  .---. |  _( )_\\  ||  |  .-----. |", 0, 19, 0xF);
	printStringPosition("||   |     : (  '\\_/ \\   ;.---.  \\  : |   | | (_ o _)  |'  \\  '-   .' |", 0, 20, 0xE);
	printStringPosition("||   |      \\ ` /  \\  ) / \\    `-'  | |   | |  (_,_)\\  | \\  `-'`   |  |", 0, 22, 0xC);
	printStringPosition("|/   )       '. \\_/`` .'   \\       /  |   | |  |    |  |  \\        /  |", 0, 23, 0xB);
	printStringPosition("|`---'         '-----'      `-...-'   '---' '--'    '--'   `'-...-'   |", 0, 24, 0xA);
	printStringPosition("|                                                                     |", 0, 25, 0xD);
	printStringPosition("'-------------------------.-------------------------.-----------------'", 0, 26, 0xD);
}

void printStringPosition(char *string, int x, int y, int color){
	if ((x >= 0 && x <= 30) && (y >= 0 && y <= 30)){
		int i = 0;
		while ((string[i] != 0x0) && (string[i] != 0x0a)){
			putInMemory(0xB000, 0x8000 + (80 * y + x) * 2, string[i]);
			putInMemory(0xB000, 0x8000 + (80 * y + x) * 2 + 1, color);
			i++;
			x++;
		}
	}
}
