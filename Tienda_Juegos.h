#ifndef TIENDA_JUEGOS_H
#define TIENDA_JUEGOS_H

#include string
using namespace std;

#ifndef TIENDA_JUEGOS_H
#define TIENDA_JUEGOS_H

#include <string>
using namespace std;

// =============================
// Clase Juego
// =============================
class Juego {
private:
    int codigo;
    string nombre;
    double precio;
    string plataforma;
    string categoria;

public:
    Juego();
    Juego(int c, string n, double p, string plat, string cat);

    int getCodigo() const;
    string getNombre() const;
    double getPrecio() const;
    string getPlataforma() const;
    string getCategoria() const;
};

// =============================
// Clase Tienda
// =============================
const int MAX_JUEGOS = 50;
const int MAX_CARRITO = 20;

const double DESCUENTO_ORO = 0.15;
const double DESCUENTO_PLATA = 0.08;
const double DESCUENTO_REGULAR = 0.0;

class Tienda {
private:
    Juego catalogo[MAX_JUEGOS];
    int totalJuegos;

    int carritoCodigos[MAX_CARRITO];
    int carritoCantidades[MAX_CARRITO];
    int totalCarrito;

    int buscarIndicePorCodigo(int codigo);

public:
    Tienda();

    void agregarJuegoACatalogo(int codigo, string nombre, double precio, string plataforma, string categoria);
    void mostrarCatalogo();
    void agregarAlCarrito(int codigo, int cantidad);
    void mostrarCarrito();
    double obtenerDescuentoPorTipoCliente(int tipoCliente);
    double calcularDescuentoAdicional();
    double calcularTotalFinal(double subtotal, double descuentoCliente, double descuentoAdicional);
    void limpiarCarrito();
    void cargarCompraDemo();
};

#endif //TIENDA_JUEGOS_H
