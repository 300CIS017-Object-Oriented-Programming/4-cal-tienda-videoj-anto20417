#include "Tienda_Juegos.h"

#include <iostream>
using namespace std;

#include "tienda_juegos.h"
#include <iostream>
using namespace std;

// =============================
// Implementación de Juego
// =============================
Juego::Juego() : codigo(0), nombre(""), precio(0), plataforma(""), categoria("") {}

Juego::Juego(int c, string n, double p, string plat, string cat)
    : codigo(c), nombre(n), precio(p), plataforma(plat), categoria(cat) {}

int Juego::getCodigo() const { return codigo; }
string Juego::getNombre() const { return nombre; }
double Juego::getPrecio() const { return precio; }
string Juego::getPlataforma() const { return plataforma; }
string Juego::getCategoria() const { return categoria; }

// =============================
// Implementación de Tienda
// =============================
Tienda::Tienda() : totalJuegos(0), totalCarrito(0) {}

void Tienda::agregarJuegoACatalogo(int codigo, string nombre, double precio, string plataforma, string categoria) {
    if (totalJuegos < MAX_JUEGOS) {
        catalogo[totalJuegos++] = Juego(codigo, nombre, precio, plataforma, categoria);
    }
}

void Tienda::mostrarCatalogo() {
    cout << "Catalogo de Juegos:\n";
    for (int i = 0; i < totalJuegos; i++) {
        cout << catalogo[i].getCodigo() << ". " << catalogo[i].getNombre()
             << " - $" << catalogo[i].getPrecio()
             << " - " << catalogo[i].getPlataforma()
             << " - " << catalogo[i].getCategoria() << endl;
    }
}

int Tienda::buscarIndicePorCodigo(int codigo) {
    for (int i = 0; i < totalJuegos; i++) {
        if (catalogo[i].getCodigo() == codigo) return i;
    }
    return -1;
}

void Tienda::agregarAlCarrito(int codigo, int cantidad) {
    if (totalCarrito >= MAX_CARRITO) {
        cout << "Carrito lleno. No puede agregar más juegos.\n";
        return;
    }
    for (int i = 0; i < totalCarrito; i++) {
        if (carritoCodigos[i] == codigo) {
            carritoCantidades[i] += cantidad;
            return;
        }
    }
    carritoCodigos[totalCarrito] = codigo;
    carritoCantidades[totalCarrito] = cantidad;
    totalCarrito++;
}

void Tienda::mostrarCarrito() {
    cout << "Carrito:\n";
    double subtotal = 0;
    for (int i = 0; i < totalCarrito; i++) {
        int idx = buscarIndicePorCodigo(carritoCodigos[i]);
        if (idx != -1) {
            double precioUnit = catalogo[idx].getPrecio();
            double totalJuego = precioUnit * carritoCantidades[i];
            subtotal += totalJuego;
            cout << catalogo[idx].getNombre() << " x" << carritoCantidades[i]
                 << " = $" << totalJuego << endl;
        }
    }
    cout << "Subtotal: $" << subtotal << "\n";
}

double Tienda::obtenerDescuentoPorTipoCliente(int tipoCliente) {
    switch(tipoCliente) {
        case 1: return DESCUENTO_ORO;
        case 2: return DESCUENTO_PLATA;
        default: return DESCUENTO_REGULAR;
    }
}

double Tienda::calcularDescuentoAdicional() {
    double descuentoAdicional = 0;
    for (int i = 0; i < totalCarrito; i++) {
        int idx = buscarIndicePorCodigo(carritoCodigos[i]);
        if (idx != -1) {
            if (catalogo[idx].getPlataforma() == "PS5" || catalogo[idx].getCategoria() == "Accion") {
                descuentoAdicional += catalogo[idx].getPrecio() * carritoCantidades[i] * 0.05;
            }
        }
    }
    return descuentoAdicional;
}

double Tienda::calcularTotalFinal(double subtotal, double descuentoCliente, double descuentoAdicional) {
    return subtotal * (1 - descuentoCliente) - descuentoAdicional;
}

void Tienda::limpiarCarrito() {
    totalCarrito = 0;
    cout << "Carrito limpiado.\n";
}

void Tienda::cargarCompraDemo() {
    limpiarCarrito();
    agregarAlCarrito(101, 2);
    agregarAlCarrito(202, 1);
    cout << "Compra demo cargada.\n";
}

// =============================
// Main
// =============================
int main() {
    Tienda tienda;

    // Cargar catálogo con ejemplos reales
    tienda.agregarJuegoACatalogo(101, "Spider-Man 2", 69.99, "PS5", "Accion");
    tienda.agregarJuegoACatalogo(102, "Sea of Thieves", 49.99, "Xbox", "Aventura");
    tienda.agregarJuegoACatalogo(201, "FIFA 23", 39.99, "PC", "Deportes");
    tienda.agregarJuegoACatalogo(202, "Fire Emblem: Three Houses", 59.99, "Switch", "Estrategia");

    tienda.mostrarCatalogo();

    // Agregar al carrito
    tienda.agregarAlCarrito(101, 1);
    tienda.agregarAlCarrito(202, 2);

    tienda.mostrarCarrito();

    double subtotal = 69.99 * 1 + 59.99 * 2;
    int tipoCliente = 1; // Oro
    double descuentoCliente = tienda.obtenerDescuentoPorTipoCliente(tipoCliente);
    double descuentoAdicional = tienda.calcularDescuentoAdicional();

    double totalFinal = tienda.calcularTotalFinal(subtotal, descuentoCliente, descuentoAdicional);

    cout << "Total final con descuentos: $" << totalFinal << "\n";

    return 0;
}
