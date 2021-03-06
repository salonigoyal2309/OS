#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <elf.h>
int main(){

	char file[100],ch;
	printf("Enter Elf file path : ");
	scanf("%[^\n]s",file);
	
	FILE *fp;
	fp = fopen(file,"rwb");
	
	if (fp == NULL) {
  		fprintf(stderr, "Unable to open '%s'\n", file);
  		return;
	}

 	Elf64_Ehdr ehdr;
 	
 	if(fp){
 	
 		fread(&ehdr, 1, sizeof(ehdr), fp);

    // check so its really an elf file
    	if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) == 0) {
           printf("valid elf file\n");
           FILE* fout = fopen("output.txt", "rwb");
           if(fout) {
         		fwrite(&ehdr, 1, sizeof(ehdr), fout);
         		fclose(fout);
       		}
    	}

    // finally close the file
    	fclose(fp);
 		
 	}
	
	return;
	
}
