#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "PROMOTORES_Y_TELEFONOS.h"

void calcularImporteYComision(tyPromotor promotores[], int topeProm, tyTelefono telefonos[], int topeTel, tyVenta venta, float &importeTotal, float &comision);
void incrementarAcumuladorFacturasPorDia(int contFactPorDia[], int dia);
void mostrarFacturaYComision(tyVenta venta, float importeTotal, float comision);
void mostrarCantFacturasPorDia(int contFactPorDia[], int topeDias);

int main(){
    mostrarTitulo("Ejercicio 5");

    tyTelefono telefonos[CANT_TEL];
    tyPromotor promotores[CANT_PROM];
    int contFactPorDia[CANT_DIAS];
    tyVenta venta;
    int i = 0, size = sizeof(venta);
    float importeTotal, comision;
    FILE *fichero = NULL;
    bool result, finDeArchivo;
    char op[] = "rb";

    // char rutaVentas[] = "ventas.dat";
    char rutaTelefonos[] = "telefonos.dat";
    char rutaPromotores[] = "promotores.dat";
    char rutaVentasValidas[] = "ventasValidas.dat";
    // char rutaVentasErroneas[] = "ventasErroneas.dat";

    inicializarArrayNumerico(contFactPorDia, CANT_DIAS);
    cargarTelefonos(telefonos, CANT_TEL, rutaTelefonos);
    cargarPromotores(promotores, CANT_PROM, rutaPromotores);

    // mostrarVentas(rutaVentas); // DEBUG - Mostrar ventas
    // mostrarVentas(rutaVentasValidas); // DEBUG - Mostrar ventas validas
    // mostrarVentas(rutaVentasErroneas); // DEBUG - Mostrar ventas erroneas
 
    abrirArchivo(rutaVentasValidas, op, fichero, result);
    if (result) {
        leerArchivo(fichero, &venta, size, finDeArchivo, result);
        while (result and not finDeArchivo) {
            calcularImporteYComision(promotores, CANT_PROM, telefonos, CANT_TEL, venta, importeTotal, comision);
            incrementarAcumuladorFacturasPorDia(contFactPorDia, venta.dia);
            mostrarFacturaYComision(venta, importeTotal, comision);

            leerArchivo(fichero, &venta, size, finDeArchivo, result);
        }
        cerrarArchivo(fichero, result);
    } 
    mostrarCantFacturasPorDia(contFactPorDia, CANT_DIAS);


	return EXIT_SUCCESS;
}

void calcularImporteYComision(tyPromotor promotores[], int topeProm, tyTelefono telefonos[], int topeTel, tyVenta venta, float &importeTotal, float &comision) {
    int posTel = buscarTelefono(telefonos, topeTel, venta.descripcion);
    int posProm = buscarPromotor(promotores, topeProm, venta.promotor);
    importeTotal = telefonos[posTel].precio * venta.cantidad;
    comision = promotores[posProm].comision * importeTotal / 100;
}

void incrementarAcumuladorFacturasPorDia(int contFactPorDia[], int dia) {
    contFactPorDia[dia - 1]++;
}

void mostrarFacturaYComision(tyVenta venta, float importeTotal, float comision) {
    mostrarTitulo("Factura");

    cout << "Nombre del promotor     : " << venta.promotor << endl;
    cout << "Descripcion del telefono: " << venta.descripcion << endl;
    cout << "Cantidad Vendida        : " << venta.cantidad << endl;
    cout << "Importe total           : $ " <<  importeTotal << endl;
    cout << "Comision promotor       : $ " << comision << endl << endl;
}

void mostrarCantFacturasPorDia(int contFactPorDia[], int topeDias) {
    mostrarTitulo("Cantidad de facturas por dia");
    bool hayResultados = false;
    int i;
    for (i = 0; i < topeDias; i++) {
        if (contFactPorDia[i] > 0) {
            cout << "El dia " << i + 1 << " se realizaron " << contFactPorDia[i] << " facturas." << endl;
            hayResultados = true;
        }
    }
    if (not hayResultados) {
        cout << "No se realizaron ventas";
    }
    cout << endl;
}