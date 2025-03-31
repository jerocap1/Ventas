#include <stdio.h>

int main() {
    int id, stock = 0, cantidad = 0, opcion;
    float precio, total_ganancias = 0;
    char nombre[30];
    int producto_registrado = 0;
    int val = 0;

    do {
        printf("\nMenu de Opciones:\n");
        printf("1. Registrar producto\n");
        printf("2. Vender producto\n");
        printf("3. Reabastecer producto\n");
        printf("4. Mostrar información del producto\n");
        printf("5. Mostrar total de ganancias\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        if (opcion != 1 && !producto_registrado && opcion != 6) {
            printf("Primero debe registrar un producto antes de seleccionar esta opción.\n");
        } else {
            switch (opcion) {
                case 1:
                    printf("Ingrese el ID del producto: ");
                    scanf("%d", &id);

                    printf("Ingrese el nombre del producto: ");
                    while (getchar() != '\n');
                    fgets(nombre, 30, stdin);

                    do {
                        printf("Ingrese la cantidad inicial del stock: ");
                        val = scanf("%d", &stock);
                        if (val != 1 || stock <= 0) {
                            printf("La cantidad debe ser un número mayor que 0 y sin letras. Intente nuevamente.\n");
                            while (getchar() != '\n');
                        }
                    } while (val != 1 || stock <= 0);

                    do {
                        printf("Ingrese el precio unitario del producto: ");
                        val = scanf("%f", &precio);
                        if (val != 1 || precio <= 0) {
                            printf("El precio debe ser un número mayor que 0 y sin letras. Intente nuevamente.\n");
                            while (getchar() != '\n');
                        }
                    } while (val != 1 || precio <= 0);

                    producto_registrado = 1;
                    break;

                case 2:
                    do {
                        printf("Ingrese la cantidad a vender: ");
                        val = scanf("%d", &cantidad);
                        if (val != 1 || cantidad <= 0) {
                            printf("La cantidad debe ser un número entero mayor que 0 y sin letras. Vuelva a intentarlo.\n");
                            while (getchar() != '\n');
                        }
                    } while (val != 1 || cantidad <= 0);

                    if (stock >= cantidad) {
                        stock -= cantidad;
                        printf("Gracias por su compra!\n");

                        float total_sin_descuento = cantidad * precio;
                        float total_con_descuento = total_sin_descuento;

                        if (cantidad >= 10) {
                            total_con_descuento *= 0.85;
                            printf("Se ha aplicado un descuento del 15%% por compras de 10 unidades o más.\n");
                            printf("Total sin descuento: $%.2f\n", total_sin_descuento);
                            printf("Total con descuento: $%.2f\n", total_con_descuento);
                        } else {
                            printf("Total a pagar: $%.2f\n", total_con_descuento);
                        }

                        total_ganancias += total_con_descuento;

                        printf("Stock disponible quedan: %d\n", stock);
                        printf("Ganancia de esta venta: $%.2f\n", total_con_descuento);
                    } else {
                        printf("No hay suficiente stock. Solo hay %d unidades disponibles.\n", stock);
                    }
                    break;

                case 3:
                    do {
                        printf("Ingrese la cantidad a agregar al stock: ");
                        val = scanf("%d", &cantidad);
                        if (val != 1 || cantidad <= 0) {
                            printf("La cantidad debe ser un número entero mayor que 0 y sin letras. Vuelva a intentarlo.\n");
                            while (getchar() != '\n');
                        }
                    } while (val != 1 || cantidad <= 0);

                    stock += cantidad;
                    printf("El stock se ha actualizado. Stock actual: %d\n", stock);
                    break;

                case 4:
                    printf("\nInformacion del producto:\n");
                    printf("ID: %d\n", id);
                    printf("Nombre: %s", nombre);
                    printf("Stock disponible: %d\n", stock);
                    printf("Precio unitario: %.2f\n", precio);
                    break;

                case 5:
                    printf("Total de ganancias: $%.2f\n", total_ganancias);
                    break;

                case 6:
                    printf("Saliendo del programa...\n");
                    break;

                default:
                    printf("Opción inválida. Intente nuevamente.\n");
            }
        }
    } while (opcion != 6);

    return 0;
}
