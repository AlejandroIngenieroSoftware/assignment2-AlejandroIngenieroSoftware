#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Error: Se requieren exactamente 2 argumentos."
    exit 1
fi

filesdir=$1
searchstr=$2

# Si el directorio no existe → valores en 0
if [ ! -d "$filesdir" ]; then
    file_count=0
    match_count=0
else
    file_count=$(find "$filesdir" -type f | wc -l)
    match_count=$(grep -r "$searchstr" "$filesdir" | wc -l)
fi

echo "The number of files are $file_count and the number of matching lines are $match_count"
