/*******************************************************************************
 * Liberías utilizadas
 ******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> 
#include "puerto.h"
#include "allegro5/color.h"
/*******************************************************************************
 * Definiciones
 ******************************************************************************/
#define MASK  0xFF
/*******************************************************************************
 * Declaración de funciones
 ******************************************************************************/
void show_port (char Port_A);//Imprime en consola el valor del puerto,bit a bit
/*******************************************************************************
 * variables propias de este archivo
 ******************************************************************************/
static int input;
/******************************************************************************/
// Estado de los leds, 0 = apagado; 1 = encendido
static int status [8] = {0,0,0,0,0,0,0,0};
// Posicion inicial en x de cada led
static int posx [8] = {29, 142, 257, 370, 481, 594, 708, 821};
// Posicion inicial en y de cada led
static int posy = 93;

/*******************************************************************************
 * función principal, analiza el input y responde segun corresponda
 ******************************************************************************/
int main ()
{
    /***************************************************************************
    * Display
    ***************************************************************************/
    ALLEGRO_DISPLAY *display  = NULL;
    ALLEGRO_BITMAP  *port_a   = NULL;
    ALLEGRO_BITMAP  *led_off  = NULL;
    ALLEGRO_BITMAP  *led_on   = NULL;

    if(!al_init()) 
    {
            fprintf(stderr, "failed to initialize allegro!\n");
            return -1;
    }

    if(!al_init_image_addon()) 
    { // ADDON necesario para manejo(no olvidar el freno de mano) de imagenes 
            fprintf(stderr, "failed to initialize image addon !\n");
            return -1;
    }
    /***************************************************************************
    * Definicion de Port_A
    ***************************************************************************/
    port_a = al_load_bitmap("PORTA.jpg");
    if(!port_a) 
    {
            fprintf(stderr, "failed to load image !\n");
            return 0;
    }

    display = al_create_display(951,310);
    if(!display) 
    {
            al_destroy_bitmap(port_a);
      fprintf(stderr, "failed to create display!\n");
            return -1;
    }
    //void al_draw_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags) 
    al_draw_bitmap(port_a, 0, 0, 0);//flags(normalmente en cero, ver doc. para rotar etc)

    al_flip_display();
    al_rest(5);
    /***************************************************************************
    * Definicion de led_off
    ***************************************************************************/
    led_off = al_load_bitmap("LEDOFF.jpg");
    if(!led_off) 
    {
            fprintf(stderr, "failed to load image !\n");
            return 0;
    }

    display = al_create_display(102,94);
    if(!display) 
    {
            al_destroy_bitmap(led_off);
      fprintf(stderr, "failed to create display!\n");
            return -1;
    }
    //void al_draw_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags) 
    al_draw_bitmap(led_off, 0, 0, 0);//flags(normalmente en cero, ver doc. para rotar etc)
    /***************************************************************************
    * Definicion de led_on
    ***************************************************************************/
    led_on = al_load_bitmap("LEDON.jpg");
    if(!led_on) 
    {
            fprintf(stderr, "failed to load image !\n");
            return 0;
    }

    display = al_create_display(102,94);
    if(!display) 
    {
            al_destroy_bitmap(led_on);
      fprintf(stderr, "failed to create display!\n");
            return -1;
    }
    //void al_draw_bitmap(ALLEGRO_BITMAP *bitmap, float dx, float dy, int flags) 
    al_draw_bitmap(led_on, 0, 0, 0);//flags(normalmente en cero, ver doc. para rotar etc)
    /***************************************************************************
    * Input y respuesta
    ***************************************************************************/
    printf ("Ingrese el numero de LED o el comando\n");
    while ((input= getchar ()) != 'q' && input != 'Q')
    {
        /***********************************************************************
        * primero revisa se se trata de un numero de led
        ***********************************************************************/
        if((input <= '9') && (input >= '0'))
        {
            int counter=0;
            do{
                counter=(counter*10)+input;
              }
            while((input=getchar()) != '\n');
            //No se va a utilizar ahora pero en un futuro necesitaremos entrada de 2 digitos
            if ((counter <= '7') && (counter >= '0'))
            {
                counter-='0';
                bitSet ('a', counter);
                show_port ('a');
            }
            else
            printf("\nValor fuera del rango.\n");
        }
        /***********************************************************************
        * como el puerto solo tiene 8 espacios avisa en caso de que el numero
        * no coincida con alguno de ellos
        ***********************************************************************/

        /***********************************************************************
        * si se presiona la letra 'T' todos los bits cambian a su opuesto
        ***********************************************************************/
        else if ((input == 't') || (input == 'T'))
        {
            maskToggle ('a', MASK);
            show_port ('a');
        }
        /***********************************************************************
        * si se presiona la letra 'S' prende todos los bits
        ***********************************************************************/
        else if ((input == 's') || (input == 'S'))
        {
            maskOn ('a', MASK);
            show_port ('a');
        }
        /***********************************************************************
        * si se presiona la letra 'C' apaga todos los bits
        ***********************************************************************/
        else if ((input == 'c') || (input == 'C'))
        {
            maskOff ('a', MASK);
            show_port ('a');
        }
        /***********************************************************************
        * en caso de tocar cualquier otra letra (excepto la Q, pues con ella
        * se termina el programa)se notificará que no hay acciones disponibles
        ***********************************************************************/
        else  if(input!='\0' && input!='\n')
            printf ("El comando ingresado no es válido\n");
        /***********************************************************************
        * para finalizar, muestra el puerto en la pantalla para que se puedan
        * apreciar los cambios realizados
        ***********************************************************************/
        al_destroy_display(display);
	al_destroy_bitmap(port_a);
        al_destroy_bitmap(led_off);
        al_destroy_bitmap(led_on);
    }

    return 0;
}

/*******************************************************************************
 * función secundaria, muestra el puerto indicado en la pantalla
 ******************************************************************************/
void show_port (char Port_A)
{
    printf ("\n\nEstado del puerto A:\n");
    /***************************************************************************
    * toma cada bit e imprime el valor que le corresponde en la pantalla
    ***************************************************************************/
    for (int bit_number=7; bit_number>=0; --bit_number)
    {
        printf("\nRegistro:%c\tBit:%d\tValor:%d\n",Port_A,bit_number,bitGet(Port_A,bit_number));
    }
    printf ("\n");
}

