// Pruebas de CGestorStock. Responsable: GRUPO 7
#include "minitest.h"
#include "CGestorStock.h"

int main(){
    CInventario inv("Drogas La Especial", "07-10-2026");
    inv.adicionarMedicamento(CMedicamento(1, "Acetaminofen 60Mg", 1, 100, 1000, 2000));
    inv.adicionarMedicamento(CMedicamento(2, "Ibuprofeno 30x20 Caja", 2, 5, 500, 2500));
    CGestorStock gestor(inv);

    SECCION("CGestorStock: vender");
    CHECK(gestor.vender(1, 10) == ResultadoStock::OK);
    CHECK_EQ(inv.getMedicamentos()[0].getCantidadDisponible(), 90);

    CHECK(gestor.vender(2, 6) == ResultadoStock::STOCK_INSUFICIENTE);
    CHECK_EQ(inv.getMedicamentos()[1].getCantidadDisponible(), 5);   // no cambia

    CHECK(gestor.vender(1, 0) == ResultadoStock::CANTIDAD_INVALIDA);
    CHECK(gestor.vender(99, 1) == ResultadoStock::NO_EXISTE);

    SECCION("CGestorStock: reabastecer");
    CHECK(gestor.reabastecer(2, 20) == ResultadoStock::OK);
    CHECK_EQ(inv.getMedicamentos()[1].getCantidadDisponible(), 25);
    CHECK(gestor.reabastecer(2, -5) == ResultadoStock::CANTIDAD_INVALIDA);

    SECCION("CGestorStock: esStockBajo");
    CHECK(gestor.esStockBajo(1, 100));
    CHECK(!gestor.esStockBajo(1, 10));
    CHECK(!gestor.esStockBajo(99, 1000));

        SECCION("CGestorStock: pruebas adicionales");


    CHECK(gestor.vender(2, 25) == ResultadoStock::OK);
    CHECK_EQ(inv.getMedicamentos()[1].getCantidadDisponible(), 0);


    CHECK(gestor.vender(2, 1) == ResultadoStock::STOCK_INSUFICIENTE);
    CHECK_EQ(inv.getMedicamentos()[1].getCantidadDisponible(), 0);


    CHECK(gestor.reabastecer(99, 10) == ResultadoStock::NO_EXISTE);


    CHECK(gestor.vender(1, -5) == ResultadoStock::CANTIDAD_INVALIDA);
    CHECK_EQ(inv.getMedicamentos()[0].getCantidadDisponible(), 90);


    CHECK(gestor.reabastecer(1, 0) == ResultadoStock::CANTIDAD_INVALIDA);

    return RESUMEN();
}
