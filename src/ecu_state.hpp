#pragma once
#include<string>

// ============================================================
//  La maquina de estados solo debe responder una sola pregunta:
//  estando en este estado, puedo pasar a ese otro?
//  la de control decide que estado
//  quiere, pero la maquina de estados decide si desde donde esta se puede
// ============================================================


enum class ECUState {
  INIT,          // inicializacion de variables y configuracion
  SELF_TEST,     // prueba
  OPERATIONAL,   // todas las señales validas y normales
  DEGRADED,      // existe advertencia o falla menor
  SAFE_STATE,    // existe una condicion critica
  SHUTDOWN       // apagado
};

// Tabla de transiciones, cada return es una flecha del diagrama
bool isTransitionAllowed(ECUState from, ECUState to);

// Aplica el cambio solo si la tabla lo permite, caso contrario se conserva el estado actual
ECUState applyTransition(ECUState current_state, ECUState requested_state);

// Traduce el estado a texto plano
std::string ecuStateToText(ECUState state);
