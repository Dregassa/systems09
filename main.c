#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void list_type(char * path, int file_type){
	DIR * wd = opendir(path);
	struct dirent * current_file;
	while ( current_file = readdir(wd) ){
		if (current_file->d_type == file_type){
			printf("\t%s\n", current_file->d_name);
		}
	}
	closedir(wd);
}

//Concantate parent directory and file
char * fullpath(char * parent, char * file){
	int len_parent = strlen(parent);
	int len_ret = len_parent + 1 + strlen(file);// one more for slash in between

	if ( parent[len_parent - 1] == '/' ){ // last character is a '/'
		len_parent--;
	}
	
	char * ret = (char *) calloc (sizeof(char),  len_ret);
	strncat(ret, parent, len_parent);
	strcat(ret, "/");
	strcat(ret, file);

	return ret;
}

long unsigned size_regular(char * path){
	DIR * wd = opendir(path);
	long unsigned sum = 0;
	struct stat source; //making this a ptr and using '->' breaks code for some reason
	struct dirent * current_file;

	while ( current_file = readdir(wd) ){

		if (current_file->d_type == DT_REG){
			//printf("%s\n", filename);
			char * file_path = fullpath(path, current_file->d_name);
			stat( file_path , &source);
			free(file_path);
			sum += source.st_size;
		}
	}
	closedir(wd);
	return sum;
} 

void scan_dir(char * path){
	printf("Statistics for directory: %s\n", path);	
	printf("Total Directory Size: %lu Bytes\n", size_regular(path));
	printf("Directories:\n");
	list_type(path, DT_DIR);	
	printf("Regular files:\n");	
	list_type(path, DT_REG);	
}

int main(){
	/*
	 * char * a = fullpath("/home/daniel/Documents/", "stuff");
	 * char * b = fullpath("/home/daniel/Documents", "stuff");
	 * printf("\n%s\n", a);
	 * printf("\n%s\n", b);
	 * free(a);
	 * free(b);
	*/

	
	//list_type("/home/daniel/Documents/", DT_REG);	
	//list_type(".", DT_DIR);
	//printf("\n%lu\n", size_regular("."));
	scan_dir(".");
}
