#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

void list_regular(char * path){
	DIR * wd = opendir(path);
	struct dirent current_file;
	while ( current_file = readdir(wd) ){
		if (current_file->d_type == DT_REG){
			printf("%s\n", current_file->d_name);
		}
	}
	closedir(wd);
}

void list_directory(char * path){
        DIR * wd = opendir(path);
        struct dirent current_file;
        while ( *current_file = readdir(wd) ){
                if (current_file->d_type == DT_DIR){
                        printf("%s\n", current_file->d_name);
                }
        }
	closedir(wd);
}


int main(){

	
}
