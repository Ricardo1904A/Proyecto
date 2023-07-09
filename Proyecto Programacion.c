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
// Función para agregar un nuevo plato al menú
void Agregar_Plato(Plato Platos[], int *Numero_Platos)
{
    char Nombre[50];
    char Ingredientes[100];
    float Precio;

    printf("Ingrese el nombre del nuevo plato: ");
    getchar();
    fgets(Nombre, sizeof(Nombre), stdin);
    Nombre[strcspn(Nombre, "\n")] = '\0';

    printf("Ingrese los ingredientes del nuevo plato (separados por comas): ");
    fgets(Ingredientes, sizeof(Ingredientes), stdin);
    Ingredientes[strcspn(Ingredientes, "\n")] = '\0';

    printf("Ingrese el precio del nuevo plato: ");
    scanf("%f", &Precio);
    // Agregar el nuevo plato a la estructura de datos
    // Utilizamos strcpy para copiar el nombre y los ingredientes del nuevo plato en la estructura de datos correspondiente.
    strcpy(Platos[*Numero_Platos].Nombre, Nombre);
    strcpy(Platos[*Numero_Platos].Ingredientes, Ingredientes);
    Platos[*Numero_Platos].Precio = Precio;
    // Incrementar el contador de platos
    (*Numero_Platos)++;

    // Guardar los platos y los ingredientes en archivos
    Guardar_Platos(Platos, *Numero_Platos);
    Guardar_Ingredientes(Platos, *Numero_Platos);

    printf("El plato ha sido agregado al menú correctamente.\n");
}

// Función para calcular los ingredientes utilizados en base a los platos vendidos
void Calcular_Ingredientes_Utilizados(Plato Platos[], int Numero_Platos, int Platos_Vendidos[])
{
    FILE *archivo;
    archivo = fopen("Ingredientes_gastados.txt", "w");
    // Verificamos si el archivo se pudo abrir correctamente. Si no, mostramos un mensaje de error y salimos de la función.
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Calcular los ingredientes utilizados y guardarlos en el archivo "Ingredientes_gastados.txt"
    for (int i = 0; i < Numero_Platos; i++)
    {
        // Utilizamos fprintf para escribir la cabecera de "Ingredientes gastados para [nombre del plato]: ".
        fprintf(archivo, "Ingredientes gastados para %s: ", Platos[i].Nombre);
        // Creamos una copia de los ingredientes del plato en la variable Ingredientes y utilizamos strtok para dividirlos por comas.
        char Ingredientes[100];
        strcpy(Ingredientes, Platos[i].Ingredientes);
        char *token = strtok(Ingredientes, ",");
        // utilizamos strtol para convertir el token (que representa la cantidad de ingredientes) en un valor entero, que almacenamos en la variable cantidad
        while (token != NULL)
        {
            char *cantidadPtr;
            int cantidad = strtol(token, &cantidadPtr, 10);

            char *Nombre_Ingrediente = cantidadPtr + 1;
            int Ingredientes_Utilizados = cantidad * Platos_Vendidos[i];

            fprintf(archivo, "%d %s", Ingredientes_Utilizados, Nombre_Ingrediente);
            // utilizo la variable token para dividir la cadena de ingredientes en diferentes partes, separadas por comas.
            // La función strtok se utiliza para dividir una cadena en "tokens" o segmentos más pequeños, utilizando un delimitador específico.

            token = strtok(NULL, ",");

            if (token != NULL)
            {
                fprintf(archivo, "; ");
            }
        }
    }

    fclose(archivo);
}
void calcularRecaudacion(Plato platos[], int numPlatos, int platosVendidos[]) {
    FILE *archivo;
    archivo = fopen("recaudacion.txt", "w"); // Abrir archivo en modo escritura
    
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n"); // Fallo al abrir el archivo
        return;
    }
    
    for (int i = 0; i < numPlatos; i++) {
        float recaudacion = platos[i].precio * platosVendidos[i]; // Calcular la recaudación por plato vendido
        fprintf(archivo, "Recaudación por plato vendido de %s: %.2f\n", platos[i].nombre, recaudacion); // Escribir la recaudación en el archivo
    }
    
    fclose(archivo); // Cerrar el archivo
}
int main() {
    Plato platos[100] = {
        {"salchipapa", "2 papas, 1 salchicha", 1.50},
        {"papipollo", "2 papas, 1 presa de pollo", 2.00},
        {"hot dogs", "1 pan para hot dogs, 1 salchicha", 1.25},
        {"hamburguesas", "1 hojas de lechuga, 1 tira de queso, 1 carne, 1 pan de hamburguesa", 2.50},
        {"papi carne", "2 papas, 1 carne", 1.75},
        {"papi huevo", "2 papas, 1 huevo", 1.25}
    };
    
    int numPlatos = 6;
    
    guardarPlatos(platos, numPlatos); // Guardar los platos iniciales en el archivo
    guardarIngredientes(platos, numPlatos); // Guardar los ingredientes iniciales en el archivo
    int opcion;
    int platosVendidos[100];
    
    printf("¡Bienvenido al Restaurante!\n");
    printf("Aquí está nuestra carta de platos:\n");
    for (int i = 0; i < numPlatos; i++) {
        printf("%d. %s - %.2f\n", i+1, platos[i].nombre, platos[i].precio);
    }
    
    do {
        printf("\n--- Menú ---\n");
        printf("1. Calcular ingredientes utilizados en base a los platos vendidos\n");
        printf("2. Calcular recaudación por plato vendido\n");
        printf("3. Agregar un nuevo plato\n");
        printf("4. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);
