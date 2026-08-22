#!/bin/bash

# Validar argumento
if [ -z "$1" ]; then
    echo "Uso: ./new_module.sh <nombre_modulo>"
    exit 1
fi

MODULE_NAME="$1"
SRC_DIR="src"
HPP_FILE="${SRC_DIR}/${MODULE_NAME}.hpp"
CPP_FILE="${SRC_DIR}/${MODULE_NAME}.cpp"
COMPILE_SCRIPT="compile.sh"

# Asegurar que la carpeta exista
mkdir -p "$SRC_DIR"

# 1. Crear el .hpp si no existe
if [ ! -f "$HPP_FILE" ]; then
    cat <<EOF > "$HPP_FILE"
#pragma once

// Declaraciones para ${MODULE_NAME}
EOF
    echo "[OK] Creado: $HPP_FILE"
else
    echo "[WARN] $HPP_FILE ya existe, no se modifico."
fi

# 2. Crear el .cpp si no existe
if [ ! -f "$CPP_FILE" ]; then
    cat <<EOF > "$CPP_FILE"
#include "${MODULE_NAME}.hpp"

// Implementaciones para ${MODULE_NAME}
EOF
    echo "[OK] Creado: $CPP_FILE"
else
    echo "[WARN] $CPP_FILE ya existe, no se modifico."
fi

# 3. Insertar el .cpp en compile.sh en la seccion de fuentes (despues de g++ -o ./bin/ecu.exe)
if grep -q "${CPP_FILE}" "$COMPILE_SCRIPT"; then
    echo "[INFO] ${CPP_FILE} ya estaba registrado en $COMPILE_SCRIPT"
else
    # Inserta una nueva linea con "  ./src/<modulo>.cpp \" justo despues de g++ -o ./bin/ecu.exe \
    sed -i "/g++ -o \.\/bin\/ecu\.exe/a \  ./${CPP_FILE} \\\\" "$COMPILE_SCRIPT"
    echo "[OK] Agregado correctamente a $COMPILE_SCRIPT"
fi
