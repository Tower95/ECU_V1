#include "simulator.hpp"
#include "ecu_gateway.hpp"
#include <random>

static std::mt19937 generador (42);

static double generarNumeroAleatorio(double minimo, double maximo)
{
  std::uniform_real_distribution<double> distribucion (minimo, maximo);

  return  distribucion(generador);
}

// Implementaciones para simulator

DatosVehiculo generarDatosIniciales()
{
DatosVehiculo datos;
  
    datos.speed_kmh= 0.0;
    datos.rpm= 800;
    datos.temp_c= 19.0;
    datos.voltage_v= 13.6;
    datos.throttle_pct= 0.0;

    return datos;
 
}

DatosVehiculo actualizarSimulador(const DatosVehiculo & datosActuales){
    DatosVehiculo datos = datosActuales;

    datos.speed_kmh += generarNumeroAleatorio(0.0, 5.0);
   
    if(datos.speed_kmh < 0){
        datos.speed_kmh = 0.0;

    }

    if(datos.speed_kmh > 180){
        datos.speed_kmh = 180;
    }

    datos.rpm = 800 + static_cast<int> (datos.speed_kmh  *30.0) + static_cast<int>(generarNumeroAleatorio(-150,150));

    if(datos.rpm < 750){
        datos.rpm = 750;
    }

    if(datos.rpm>7000){
        datos.rpm = 7000;
    }


    if(datos.temp_c < 90.0 ){
        datos.temp_c += generarNumeroAleatorio(0.1, 0.5 ); 
    }

    else {
        datos.temp_c += generarNumeroAleatorio(-0.2, 0.2);
    }

    datos.voltage_v = 13.7 + generarNumeroAleatorio(-0.15, 0.15);
    datos.throttle_pct = (datos.speed_kmh / 180.0) * 100.0;
    
    return datos;
}
