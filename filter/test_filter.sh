#!/bin/bash

# Script de batería de tests para filter.c
# Compila el programa y ejecuta varios tests con diferentes frases y palabras

# Compilar el programa
echo "Compilando filter.c..."
gcc filter.c -o filter
if [ $? -ne 0 ]; then
    echo "Error al compilar. Saliendo."
    exit 1
fi

echo "Programa compilado exitosamente."
echo "=================================="

# Función para ejecutar un test
run_test() {
    local frase="$1"
    local palabra="$2"
    local descripcion="$3"
    echo "Test: $descripcion"
    echo "Frase: '$frase'"
    echo "Palabra: '$palabra'"
    echo "Output:"
    ./filter "$frase" "$palabra"
    echo "----------------------------------"
}

# Tests
run_test "hola mundo" "hola" "Palabra encontrada al inicio"
run_test "hola mundo" "mundo" "Palabra encontrada al final"
run_test "esto es una prueba de busqueda" "una" "Palabra encontrada en medio"
run_test "hola mundo hola" "hola" "Palabra encontrada múltiples veces"
run_test "hola mundo" "adios" "Palabra no encontrada"
run_test "abc" "abcd" "Palabra más larga que la frase"
run_test "hola" "" "Palabra vacía"
run_test "" "hola" "Frase vacía"
run_test "a" "a" "Frase y palabra de un carácter, coinciden"
run_test "a" "b" "Frase y palabra de un carácter, no coinciden"
run_test "palabra" "palabra" "Palabra igual a la frase"
run_test "palabra larga" "palabra" "Palabra al inicio de frase más larga"
run_test "esto no es una palabra" "es" "Substring simple"

echo "Batería de tests completada."