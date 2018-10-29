#include<stdio.h>
#include <string.h>

int palindromo(char* arr,int length); 
//La funcion palindromo verifica si un arreglo es palindromo, solo requiere un puntero al arreglo y su largo

#define outsmall(x)    (x<'a' || x>'z')	//Verifica que este afuera de las minusculas
#define outcap(x)    (x<'A' || x>'Z') //Verifica que este afuera de las mayusculas
#define MAX 100 //Definimos un tamaño de arreglo, podria ser mas si asi se desease

int main() 
{
	char frase[MAX+1];    
	while(scanf("%100[^\n]",frase)+1) //Esto se hace por lo que devuelve scanf,...
	{				  // si se apreta enter se terminaria el programa por eso el "+1"

		if(((getchar())=='\n')&&(frase[0]))//Se analiza tambien el caso en el que solo se aprete enter
		{
				if(palindromo(frase,strlen(frase)))
				{
					printf("La palabra o frase ingresada es un palindromo\n");
				}
				else
				{
					printf("La palabra o frase ingresada no es un palindromo\n");
				}
		}
		
		
	}			
}

int palindromo(char* arr,int length)
{
	if(&arr[0]>=&arr[length-1]) //Verificamos que no se crucen las posiciones
	    return 1;  
	else if(outcap(arr[0])&&outsmall(arr[0])) //Verificamos que sea letra
	    return(palindromo(++arr,length-1));
	else if(outcap(arr[length-1])&&outsmall(arr[length-1])) //Verificamos que sea letra
	    return(palindromo(arr,length-1));
	else if(arr[0]==arr[length-1]) //Analizamos si las letras son iguales
	    return(palindromo(++arr,length-2));
	else if((arr[0]-('a'-'A'))==arr[length-1]) //Analizamos si la primera es minuscula y la segunda mayuscula
	    return(palindromo(++arr,length-2));
	else if(arr[0]==(arr[length-1]-('a'-'A'))) //Analizamos si la primera es mayuscula y la segunda minuscula
	    return(palindromo(++arr,length-2));
	else //Si no ha sido ninguno de los casos anteriores, implica que no es palindromo
	    return 0;
}

