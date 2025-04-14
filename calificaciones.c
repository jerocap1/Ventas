
#include <stdio.h>
#include <string.h>

int main() {
    int i, j, opcion;
    int max_estudiantes = 5;
    int max_asignaturas = 3;
    int num_estudiantes = 0, num_asignaturas = 0;
    int datos_ingresados = 0, notas_ingresadas = 0;

    float calificaciones[5][3];
    char nombres[5][50];
    char asignaturas[3][50];
    float suma_estudiante, suma_asignatura;
    float promedio_estudiante[5];
    float promedio_asignatura[3];
    float max_estudiante[5], min_estudiante[5];
    float max_asignatura[3], min_asignatura[3];
    int aprobados[3] = {0}, reprobados[3] = {0};

    do {
        printf("\n--- MENÚ PRINCIPAL ---\n");
        printf("1. Ingresar estudiantes y asignaturas\n");
        printf("2. Ingresar notas\n");
        printf("3. Mostrar resultados por estudiante\n");
        printf("4. Mostrar resultados por asignatura\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        while (getchar() != '\n');

        switch (opcion) {
            case 1:
                if (datos_ingresados) {
                    printf("\nAtención: si vuelve a ingresar estudiantes y asignaturas, todos los datos anteriores (incluyendo las notas) serán reemplazados.\n");
                    printf("¿Desea continuar? (s/n): ");
                    char confirm;
                    scanf(" %c", &confirm);
                    while (getchar() != '\n');
                    if (confirm != 's' && confirm != 'S') {
                        printf("Operación cancelada. Los datos existentes se mantienen.\n");
                        break;
                    }
                }

                do {
                    printf("¿Cuántos estudiantes desea ingresar? (1 a 5): ");
                    scanf("%d", &num_estudiantes);
                    while (getchar() != '\n');
                } while (num_estudiantes < 1 || num_estudiantes > max_estudiantes);

                do {
                    printf("¿Cuántas asignaturas desea ingresar? (1 a 3): ");
                    scanf("%d", &num_asignaturas);
                    while (getchar() != '\n');
                } while (num_asignaturas < 1 || num_asignaturas > max_asignaturas);

                printf("\nIngrese los nombres de los %d estudiantes:\n", num_estudiantes);
                for (i = 0; i < num_estudiantes; i++) {
                    printf("Estudiante %d: ", i + 1);
                    fgets(nombres[i], sizeof(nombres[i]), stdin);
                    size_t len = strlen(nombres[i]);
                    if (len > 0 && nombres[i][len - 1] == '\n') {
                        nombres[i][len - 1] = '\0';
                    }
                }

                printf("\nIngrese los nombres de las %d asignaturas:\n", num_asignaturas);
                for (j = 0; j < num_asignaturas; j++) {
                    printf("Asignatura %d: ", j + 1);
                    fgets(asignaturas[j], sizeof(asignaturas[j]), stdin);
                    size_t len = strlen(asignaturas[j]);
                    if (len > 0 && asignaturas[j][len - 1] == '\n') {
                        asignaturas[j][len - 1] = '\0';
                    }
                }

                datos_ingresados = 1;
                notas_ingresadas = 0;
                printf("Datos ingresados correctamente.\n");
                break;

            case 2:
                if (!datos_ingresados) {
                    printf("Primero debe ingresar estudiantes y asignaturas (opción 1).\n");
                    break;
                }

                if (notas_ingresadas) {
                    printf("\nAtención: si vuelve a ingresar notas, se reemplazarán las notas anteriores.\n");
                    printf("¿Desea continuar? (s/n): ");
                    char confirm2;
                    scanf(" %c", &confirm2);
                    while (getchar() != '\n');
                    if (confirm2 != 's' && confirm2 != 'S') {
                        printf("Operación cancelada. Se mantienen las notas anteriores.\n");
                        break;
                    }
                }

                for (i = 0; i < num_estudiantes; i++) {
                    printf("\nNotas para %s:\n", nombres[i]);
                    for (j = 0; j < num_asignaturas; j++) {
                        int valido = 0;
                        while (!valido) {
                            printf("  Ingrese calificación para %s (0-10): ", asignaturas[j]);
                            int resultado = scanf("%f", &calificaciones[i][j]);
                            if (resultado != 1) {
                                printf("  Error: debe ingresar un número válido.\n");
                                while (getchar() != '\n');
                            } else if (calificaciones[i][j] < 0 || calificaciones[i][j] > 10) {
                                printf("  Calificación fuera de rango.\n");
                            } else {
                                valido = 1;
                            }
                        }
                    }
                    while (getchar() != '\n');
                }
                notas_ingresadas = 1;
                printf("Notas registradas correctamente.\n");
                break;

            case 3:
                if (!notas_ingresadas) {
                    printf("Primero debe ingresar las notas (opción 2).\n");
                    break;
                }

                for (i = 0; i < num_estudiantes; i++) {
                    suma_estudiante = 0;
                    max_estudiante[i] = calificaciones[i][0];
                    min_estudiante[i] = calificaciones[i][0];
                    for (j = 0; j < num_asignaturas; j++) {
                        suma_estudiante += calificaciones[i][j];
                        if (calificaciones[i][j] > max_estudiante[i])
                            max_estudiante[i] = calificaciones[i][j];
                        if (calificaciones[i][j] < min_estudiante[i])
                            min_estudiante[i] = calificaciones[i][j];
                    }
                    promedio_estudiante[i] = suma_estudiante / num_asignaturas;
                }

                printf("\n--- Resultados por estudiante ---\n");
                for (i = 0; i < num_estudiantes; i++) {
                    printf("%s - Promedio: %.2f, Max: %.2f, Min: %.2f\n",
                        nombres[i], promedio_estudiante[i], max_estudiante[i], min_estudiante[i]);
                }
                break;

            case 4:
                if (!notas_ingresadas) {
                    printf("Primero debe ingresar las notas (opción 2).\n");
                    break;
                }

                for (j = 0; j < num_asignaturas; j++) {
                    suma_asignatura = 0;
                    max_asignatura[j] = calificaciones[0][j];
                    min_asignatura[j] = calificaciones[0][j];
                    aprobados[j] = 0;
                    reprobados[j] = 0;
                    for (i = 0; i < num_estudiantes; i++) {
                        suma_asignatura += calificaciones[i][j];
                        if (calificaciones[i][j] > max_asignatura[j])
                            max_asignatura[j] = calificaciones[i][j];
                        if (calificaciones[i][j] < min_asignatura[j])
                            min_asignatura[j] = calificaciones[i][j];
                        if (calificaciones[i][j] >= 6.0)
                            aprobados[j]++;
                        else
                            reprobados[j]++;
                    }
                    promedio_asignatura[j] = suma_asignatura / num_estudiantes;
                }

                printf("\n--- Resultados por asignatura ---\n");
                for (j = 0; j < num_asignaturas; j++) {
                    printf("%s - Promedio: %.2f, Max: %.2f, Min: %.2f\n",
                        asignaturas[j], promedio_asignatura[j], max_asignatura[j], min_asignatura[j]);
                    printf("  Aprobados: %d, Reprobados: %d\n", aprobados[j], reprobados[j]);
                }
                break;

            case 5:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }

    } while (opcion != 5);

    return 0;
}
