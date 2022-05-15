#include <dirent.h> 
#include <stdio.h> 

int main(void) {
	DIR *d;
	struct dirent *dir;
	d = opendir("Catalogos");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			printf("%s\n", dir -> d_name);
			if((dir -> d_name) == ("a.txt")){
				printf("EUREKA");
			}
			else{
				printf("T-T");
			}
		}
		closedir(d);
	}
	return(0);
	}
