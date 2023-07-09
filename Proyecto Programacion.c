#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// primer uso de estructuras para guardar los nombres, los ingredientes y el precio de cada plato.
typedef struct
{
    char Nombre[50];
    char Ingredientes[100];
    float Precio;
} Plato;
// Funciones para guardar los platos en un archivos
void Guardar_Platos(Plato Platos[], int Numero_Platos)
{
    FILE *archivo;
    archivo = fopen("Platos.txt", "w");
    // si el archivo no se abre muestra un mensaje de error y retorna
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Guardar los platos y sus precios en el archivo "Platos.txt"
    for (int i = 0; i < Numero_Platos; i++)
    {
        // usamos fprintf para escribir en el archivo.
        // El formato "%s;%0.2f;" indica que vamos a escribir una cadena (nombre del plato) seguida de ';' para separar los campos, y luego un número decimal (precio del plato) con dos decimales, también seguido de ';'.
        fprintf(archivo, "%s;%0.2f;", Platos[i].Nombre, Platos[i].Precio);
    }

    fclose(archivo);
}
// funcion para guardar los ingredientes en un archivo
void Guardar_Ingredientes(Plato Platos[], int Numero_Platos)
{
    FILE *archivo;
    archivo = fopen("Ingredientes.txt", "w");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Guardar los ingredientes de cada plato en el archivo "Ingredientes.txt"
    for (int i = 0; i < Numero_Platos; i++)
    {
        // hacemos el mismo uso de fprintf que en la funcion anterior todo para que la informacion salga en el archivo sin salto de linea y separadas por:
        fprintf(archivo, "%s;%s;", Platos[i].Nombre, Platos[i].Ingredientes);
    }

    fclose(archivo);
}