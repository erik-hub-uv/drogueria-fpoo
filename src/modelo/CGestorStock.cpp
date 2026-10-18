/*
    Proyecto: Drogueria - FPOO - Universidad del Valle
    Módulo: Stock y ventas (GRUPO 7)

    ESTE ARCHIVO ES TUYO: reemplaza los STUB por la implementación real.
*/
#include "CGestorStock.h"

CGestorStock::CGestorStock(CInventario& inventario)
    : inventario(inventario)
{
}

ResultadoStock CGestorStock::vender(int id, int cantidad)
{
    if (cantidad <= 0)
        return ResultadoStock::CANTIDAD_INVALIDA;

    auto& medicamentos = inventario.getMedicamentos();

    for (auto& medicamento : medicamentos)
    {
        if (medicamento.getId() == id)
        {
            if (cantidad > medicamento.getCantidadDisponible())
                return ResultadoStock::STOCK_INSUFICIENTE;

            medicamento.setCantidadDisponible(
                medicamento.getCantidadDisponible() - cantidad
            );

            return ResultadoStock::OK;
        }
    }

    return ResultadoStock::NO_EXISTE;
}

ResultadoStock CGestorStock::reabastecer(int id, int cantidad)
{
    if (cantidad <= 0)
        return ResultadoStock::CANTIDAD_INVALIDA;

    auto& medicamentos = inventario.getMedicamentos();

    for (auto& medicamento : medicamentos)
    {
        if (medicamento.getId() == id)
        {
            medicamento.setCantidadDisponible(
                medicamento.getCantidadDisponible() + cantidad
            );

            return ResultadoStock::OK;
        }
    }

    return ResultadoStock::NO_EXISTE;
}

bool CGestorStock::esStockBajo(int id, int umbral) const
{
    const auto& medicamentos = inventario.getMedicamentos();

    for (const auto& medicamento : medicamentos)
    {
        if (medicamento.getId() == id)
            return medicamento.getCantidadDisponible() <= umbral;
    }

    return false;
}