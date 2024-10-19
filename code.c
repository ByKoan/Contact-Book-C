#ifndef __CODE_C__
#define __CODE_C__
#include "code.h"

// Función para inicializar una lista
Contactos* InitList() {
    // Reservar memoria para el nodo (Contacto)
    Contactos *Contacto = (Contactos *)malloc(sizeof(Contactos));
    if (Contacto == NULL) {
        printf("Error al asignar memoria para el contacto\n");
        return NULL; 
    }

    Contacto->Name = NULL; // Inicializar el nombre
    Contacto->PhoneNumber = NULL; // Inicializar el numero de teléfono
    Contacto->NextContact = NULL; // Declaramos el siguiente como NULL
    Contacto->LastContact = NULL; // Declaramos el anterior como NULL

    return Contacto; // Retornamos el nodo (Contacto)
}

Contactos* NextContact(Contactos *contacto) {
    char buffer[20]; // Aumentar el tamaño del buffer

    Contactos *nuevoContacto = InitList();
    if (nuevoContacto == NULL) {
        return NULL; // Retorna NULL si no se puede crear el nuevo contacto
    }

    // Ingresar nombre
    printf("Introduce un nombre: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Eliminar el salto de línea

    // Asignar memoria para el nombre
    nuevoContacto->Name = malloc(strlen(buffer) + 1);
    if (nuevoContacto->Name == NULL) {
        free(nuevoContacto); // Liberar la memoria ya asignada
        return NULL;
    }
    strcpy(nuevoContacto->Name, buffer); // Copiar el nombre

    // Ingresar numero de teléfono
    printf("Introduce un numero de telefono: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Eliminar el salto de línea

    // Asignar memoria para el numero de teléfono
    nuevoContacto->PhoneNumber = malloc(strlen(buffer) + 1); // +1 para el '\0'
    if (nuevoContacto->PhoneNumber == NULL) {
        free(nuevoContacto->Name); // Liberar la memoria ya asignada
        free(nuevoContacto);
        return NULL;
    }
    strcpy(nuevoContacto->PhoneNumber, buffer); // Copiar el numero

    // Asignar enlaces de contacto
    nuevoContacto->LastContact = contacto; // Guardamos el nodo actual en el anterior nodo
    contacto->NextContact = nuevoContacto; // Guardamos el siguiente nodo

    return nuevoContacto; // Devuelve el nuevo contacto creado
}

void Print(Contactos* List) { // Función para imprimir lista
    printf("Lista de Contactos:\n");
    for (Contactos *i = List; i != NULL; i = i->NextContact) { // Recorremos la lista
        printf("Nombre: %s, Telefono: %s\n",
            i->Name ? i->Name : "Sin nombre", // Verificar si el nombre no es NULL
            i->PhoneNumber ? i->PhoneNumber : "Sin numero" // Verificar si el numero no es NULL
        );
    }
}

// Función para exportar contactos a un archivo
void ExportContactsToFile(Contactos* List) {
    FILE *file = fopen("contactos.txt", "w");  // Creamos el archivo contactos.txt y le asignamos permisos de escritura
    if (file == NULL) {
        printf("Error al abrir el archivo para escribir.\n"); // Si no consiguio crear el archivo que muestre este mensaje
        return;
    }

    // Comenzamos desde el primer contacto válido
    for (Contactos *i = List->NextContact; i != NULL; i = i->NextContact) {
        fprintf(file, "Nombre: %s, Telefono: %s\n",  // Imprimimos en el archivo el contacto con sus datos
            i->Name ? i->Name : "Sin nombre",
            i->PhoneNumber ? i->PhoneNumber : "Sin numero");
    }

    fclose(file); // Cerramos el archivo
    printf("Contactos exportados a contactos.txt\n");
}

void ClearScreen() {
    // Funcion basica para borrar pantalla
#ifdef _WIN32
    system("cls"); // Para Windows
#else
    system("clear"); // Para sistemas UNIX
#endif
}

int main() {
    Contactos *primerContacto = InitList();  // Iniciamos lista
    if (primerContacto == NULL) {
        return 1; // Salir si no se puede asignar memoria
    }

    char opcion[10];  
    Contactos *ultimoContacto = primerContacto;

    do {
        // Limpiar la pantalla
        ClearScreen();

        // Crear nuevo contacto
        ultimoContacto = NextContact(ultimoContacto);
        if (ultimoContacto == NULL) {
            printf("Error al agregar contacto.\n");
            break;
        }

        // Limpiar la pantalla antes de imprimir la lista
        ClearScreen();
        // Imprimir la lista de contactos
        Print(primerContacto);

        // Preguntar si el usuario desea agregar otro contacto
        printf("Deseas agregar otro contacto? (s/n): ");
        fgets(opcion, sizeof(opcion), stdin);
        opcion[strcspn(opcion, "\n")] = 0; // Eliminar el salto de línea
    } while (opcion[0] == 's' || opcion[0] == 'S'); // Continuar mientras sea 's' o 'S'

    // Exportar contactos antes de salir
    ExportContactsToFile(primerContacto);

    // Liberar memoria
    Contactos *temp;
    while (primerContacto != NULL) {
        temp = primerContacto;
        primerContacto = primerContacto->NextContact;
        free(temp->Name);
        free(temp->PhoneNumber);
        free(temp);
    }

    return 0;
}

#endif