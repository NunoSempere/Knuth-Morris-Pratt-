#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100
#define FALSE 0
#define TRUE 1
int next(char pattern[MAX], int len1, int len2);
int* BuildListNext(char* pattern, int l1);
int main(){

	char pattern[MAX];
	char text[MAX];
	int* PatternNextList;
	int i, j, l1,l2, encontrado;	
	char c;

	// introducir el patrón: Fuck fgets.
	for(i=0; i<MAX; i++){
		pattern[i]='\0';
		text[i]='\0';
	}
	fprintf(stdout, "Introduce un patron: ");
	i=0;
	while((c=fgetc(stdin))!='\n' && i<MAX){
			pattern[i]=c;
			i++;
	}
	l1=i-1;
	PatternNextList = BuildListNext(pattern, l1);

	// introducir el texto:
	fprintf(stdout, "Introduce un texto en el que buscar nuestro patrón: ");
	i=0;
	while((c=fgetc(stdin))!='\n' && i<MAX){
			text[i]=c;
			i++;
	}
	l2=i-1;

	// encontrar el lugar:
	i=0;
	j=0;
	encontrado=FALSE;
	while(encontrado == FALSE && i<l2 && j<l1){
			//fprintf(stdout, "\n i=%d, j=%d", i, j);
			//fprintf(stdout, "\n text[i]=%c, pattern[j]=%c", text[i], pattern[j]);
			if(pattern[j]!=text[i]){
				if(j==0)	{
					i++;				
				}
				else{
					j=PatternNextList[j-1];
				 	//fprintf(stdout, "\n next(j)=%d", PatternNextList[j-1]);
					if(j==-2){
						encontrado =TRUE;	// Hemos encontrado el patrón.	
					}
					else{
						if(text[i]==pattern[j]){ // Si vamos a next[j], tenemos que comparar el caracter actual, no el siguiente
							i++;
							j++;
						}
					}
				}
			}
			else{
				i++;
				j++;			
			}
	}
	if(j>=l1 || encontrado == TRUE){
		fprintf(stdout, "\nSe ha encontrado el patrón empezando en i=%d\n", i-j);
	}
	//berberecho

}

int* BuildListNext(char* pattern, int l1){
	
	int *L=malloc(l1*sizeof(int));
	int i;
	for (i=0; i<=l1; i++){
		L[i]=next(pattern, l1,i);
		//fprintf(stdout,"%d",L[i]);
	}
	//fprintf(stdout,"\n");
	return L;
}

int next(char *pattern, int len1, int len2){
	// We want to find the longest PROPER prefix of substring which is also a suffix of pattern.
	// Substring is the string which begins at pattern[0] an ends at pattern[len2]
	// substring is obviously a prefix of pattern, which means that l1>l2;
	// por ejemplo, pattern = berberecho, string = berber
	// len1+1 is the length of pattern, len2+1 is the length of substring.
		

	int i,j;
	int rechazar =0;
	int output =-1;
	
	/*fprintf(stdout, "\n");
	for(i=0; i<=len2;i++){
		fprintf(stdout, "%c",pattern[i]);
	}
	fprintf(stdout, "\n");
	*/

	if(len1==len2){
		return -2;	
	}
	else if(len2==0){
		return 0;	
	}	

	else{
		i=0;
		while(i<=len2-1){
			j=0;
			rechazar=0;
			while(j<=i && rechazar ==0){
	

// fprintf(stdout, "\ni= %d, j = %d, pattern[j] =%c, substring[len2-i+j] = %c", i,j, pattern[j],pattern[len2-i+j]);


				if(pattern[j]!=pattern[len2-i+j]){
					rechazar =1;

				}
				j++;
			}
			if(rechazar ==0){
				output = i;
			}
			i++;
			//fprintf(stdout, "\noutput = %d\n", output);
		}
		
	}
	return output+1;
}
