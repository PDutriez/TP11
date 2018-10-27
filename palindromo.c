#include<stdio.h>
#include <string.h>
int palindromo(char* arr,unsigned int length);
#define outsmall(x)    (x<'a' || x>'z')
#define outcap(x)    (x<'A' || x>'Z')

int main() 
{
    char* chk="Re Conoc            Er";
   if(palindromo(chk,strlen(chk)))
    printf("Es palindromo");
   else
    printf("No es palindromo");
}

int palindromo(char* arr,unsigned int length)
{
    
    printf("strlen=%d\tarr[0]=%c\tarr[length-1]=%c\n",length,arr[0],arr[length-1]);
    if(&arr[0]>=&arr[length-1]) //Verificamos que no se crucen las posiciones
            return 1;  
    else if(outcap(arr[0])&&outsmall(arr[0])) //Verificamos que sea letra
            return(palindromo(++arr,length-1));
    else if(outcap(arr[length-1])&&outsmall(arr[length-1])) //Verificamos que sea letra
            return(palindromo(arr,length-2));
    else if(arr[0]==arr[length-1]) //Analizamos si las letras son iguales
            return(palindromo(++arr,length-2));
    else if((arr[0]-('a'-'A'))==arr[length-1]) //Analizamos si la primera es minuscula y la segunda mayuscula
            return(palindromo(++arr,length-2));
    else if(arr[0]==(arr[length-1]-('a'-'A'))) //Analizamos si la primera es mayuscula y la segunda minuscula
            return(palindromo(++arr,length-2));
    else //Si no ha sido ninguno de los casos anteriores, implica que no es palindromo
            return 0;
}
