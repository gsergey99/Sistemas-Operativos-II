# Práctica 1 Sistemas-Operativos-II

Compilar todos los archivos:
    
    make

Ejecutar el programa:

    make run

Limpiar los archivos:

    make clean

#### Diseño de la práctica
Esta práctica consistira en el manejo de llamadas al sistema y al tratamiento de señales. El **MANAGER** lanzará y coordinará una serie de procesos que realizarán tareas independientes. En esta práctica se aportará una serie de materiales para nuestra práctica:

    -DNI del estudiante.
    -Modelos de examen que debe de realizar.
    -Nota que obtuvo en el examen anterior.
    
El proceso **A** crea los directorios de cada uno uno de los estudiantes. Cuando éste termine se le notificará al **MANAGER**. El proceso **B** trabajará de forma independiente con el proceoso **C**. Además, ambos se realizarán a la misma vez. El proceso **B** añadirá al directorio de cada alumno su modelo de examen y el proceso **C** calculará la última que debe obtener el alumno para aprobar la asignatura y la media de todos los alumnos. 
En el caso de que el usuario pulse CTRL-C, el programa finalizará.

**NOTA: Toda la información se registrará en un archivo "log.txt"**
