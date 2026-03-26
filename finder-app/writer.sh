#!/bin/bash

# Validar número de argumentos
if [ $# -ne 2 ]; then
    echo "Error: Se requieren exactamente 2 argumentos."
    exit 1
fi

writefile=$1
writestr=$2

# Obtener directorio
dir=$(dirname "$writefile")

# Crear directorio si no existe
mkdir -p "$dir"

# Escribir contenido en el archivo
echo "$writestr" > "$writefile"

# Validar si se creó correctamente
if [ $? -ne 0 ]; then
    echo "Error: No se pudo crear el archivo."
    exit 1
fi
