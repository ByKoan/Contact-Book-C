#ifndef __CODE_H__
#define __CODE_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contactos { /* Estructura la cual usaremos para crear el tipo 
                        de dato "Contactos" y crear los nodos y los datos*/

    char* Name; // Variable para guardar numero de telefono
    char* PhoneNumber;  // Variable para guardar numero de telefono
    struct Contactos* NextContact; // Variable puntero hacia siguiente nodo
    struct Contactos* LastContact; // Variable puntero hacia anterior nodo
    
} Contactos;

Contactos *InitList ();
Contactos *NextNode (Contactos *Nodo, char* PhoneNumber);
void Print(Contactos* List);
void ExportContactsToFile(Contactos* List);
void ClearScreen();

#endif 
