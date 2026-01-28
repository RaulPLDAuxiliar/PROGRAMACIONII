#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "dentistas.dat"
#define MAX_NAME 50
#define MAX_DIR 100
#define MAX_TEL 20
#define MAX_ESP 50

typedef struct {
	char nombre[MAX_NAME];
	char direccion[MAX_DIR];
	char telefono[MAX_TEL];
	char especialidad[MAX_ESP];
} Dentista;

void altaDentista();
void mostrarDentista();
void mostrarTodos();

int main() {
	int opcion;
	do {
		printf("\n--- Agenda de Dentistas ---\n");
		printf("1. Alta de un dentista\n");
		printf("2. Mostrar un dentista en particular\n");
		printf("3. Mostrar todos los dentistas\n");
		printf("0. Salir\n");
		printf("Seleccione una opción: ");
		scanf("%d", &opcion);
		getchar(); // Limpiar buffer
		switch(opcion) {
			case 1: altaDentista(); break;
			case 2: mostrarDentista(); break;
			case 3: mostrarTodos(); break;
			case 0: printf("Saliendo...\n"); break;
			default: printf("Opción no válida.\n");
		}
	} while(opcion != 0);
	return 0;
}

void altaDentista() {
	Dentista d;
	FILE *f = fopen(FILE_NAME, "ab");
	if (!f) { printf("Error abriendo archivo.\n"); return; }
	printf("Nombre: "); fgets(d.nombre, MAX_NAME, stdin); d.nombre[strcspn(d.nombre, "\n")] = 0;
	printf("Dirección: "); fgets(d.direccion, MAX_DIR, stdin); d.direccion[strcspn(d.direccion, "\n")] = 0;
	printf("Teléfono: "); fgets(d.telefono, MAX_TEL, stdin); d.telefono[strcspn(d.telefono, "\n")] = 0;
	printf("Especialidad: "); fgets(d.especialidad, MAX_ESP, stdin); d.especialidad[strcspn(d.especialidad, "\n")] = 0;
	fwrite(&d, sizeof(Dentista), 1, f);
	fclose(f);
	printf("Dentista guardado exitosamente.\n");
}

void mostrarDentista() {
	char nombre[MAX_NAME];
	Dentista d;
	int encontrado = 0;
	FILE *f = fopen(FILE_NAME, "rb");
	if (!f) { printf("No hay datos guardados.\n"); return; }
	printf("Ingrese el nombre del dentista a buscar: ");
	fgets(nombre, MAX_NAME, stdin); nombre[strcspn(nombre, "\n")] = 0;
	while (fread(&d, sizeof(Dentista), 1, f)) {
		if (strcmp(d.nombre, nombre) == 0) {
			printf("\nNombre: %s\nDirección: %s\nTeléfono: %s\nEspecialidad: %s\n", d.nombre, d.direccion, d.telefono, d.especialidad);
			encontrado = 1;
			break;
		}
	}
	if (!encontrado) printf("Dentista no encontrado.\n");
	fclose(f);
}

void mostrarTodos() {
	Dentista d;
	FILE *f = fopen(FILE_NAME, "rb");
	if (!f) { printf("No hay datos guardados.\n"); return; }
	printf("\n--- Lista de Dentistas ---\n");
	while (fread(&d, sizeof(Dentista), 1, f)) {
		printf("Nombre: %s\nDirección: %s\nTeléfono: %s\nEspecialidad: %s\n---\n", d.nombre, d.direccion, d.telefono, d.especialidad);
	}
	fclose(f);
}
