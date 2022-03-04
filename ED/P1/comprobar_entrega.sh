#!/bin/bash
#Version: 1.0
#Utiliza este script para ver si tu entrega cumple con la normativa.
#Se asume que tienes una instalación Linux estándar. Este script ha sido probado en
#en la plataforma de referencia que es ThinStation de la Uco.
#
#Para ejecutarlo debes activar el permiso de ejecución primero con el comando:
#
#   chmod +x comprobar_entrega.sh
#
#Después ejecuta el script de la forma:
#
#./comprobar_entrega.sh
#
#Se asume que está el fichero zip con la entrega a comprobar en la misma carpeta.
#


set -u
set +e
CDIR="$(pwd)"
echo "Has comprobado que has usado la última vesión liberada de las fuentes? "
read -p "[s|n]: " resp
if [ "$resp" = "s" ]; then :
else
   echo "Entonces, comprueba la versión CHANGELOG.TXT de moodle con la tuya."
   exit 0
fi
read LOGIN
echo "Cual es tu login (p.ej. i02pelur): "
read LOGIN
FZIP="${LOGIN}.zip"
if [ ! -f "$FZIP" ]; then
   echo "Error: no encuentro el fichero con la practica [${FZIP}]."
   exit -1
fi
WDIR="/tmp/check_assigment_${$}_${RANDOM}"
echo "Usando el directorio temporal: $WDIR"
mkdir $WDIR
if [ $? != 0 ]; then
   echo "Error: no puedo crear el directorio temporal $WDIR"
   exit -1
fi
cp -f $FZIP $WDIR/.
if [ $? != 0 ]; then
   echo "Error: no puedo copiar la entrega al directorio temporal $WDIR"
   exit -1
fi
cd $WDIR
unzip $FZIP
echo "Como se llama la practica (p.ej. check_brackets): "
read ASSIG
if [ ! -d "$ASSIG" ]; then
   echo "Error: al descomprimir la entrega no encuentro la carpeta '$ASSIG'"
   exit -1
fi
cd $ASSIG
md5sum -c DO_NOT_MODIFY.TXT
if [ $? != 0 ]; then
   echo "Error: hay archivos modificados de los que no deben ser modificados. Ver"
   echo "md5sum -c DO_NOT_MODIFY.TXT y reemplazar por los originales."
   exit -1
fi
if [ -d "build" ]; then
   echo "Error: la carpeta 'build' no puede existir en la entrega.'"
   exit -1
fi
mkdir build
cd build
cmake ..
if [ $? != 0 ]; then
   echo "Error: No se puede generar el proyecto con cmake."
   echo "Revisa los archivos indicados en CMakeList.txt"
   exit -1
fi
make
if [ $? != 0 ]; then
   echo "Error: No se compila el proyecto. Revisa los errores de"
   echo "compilación".
   exit -1
fi
cd "$CDIR"
rm -rf "$WDIR"
echo "OK! puedes enviar el fichero."
exit 0

