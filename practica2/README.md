# Práctica 2 Sistemas-Operativos-II

Compilar todos los archivos:
    
    make

Ejecutar el primer ejemplo:

    make run-example1

Ejecutar el segundo ejemplo:

    make run-example2

Ejecutar el código con error:

    make run-error

Limpiar los archivos:

    make clean

#### Diseño de la práctica
Para el diseño de esta práctica hemos tenido en cuenta diversos diseños para llevar a cabo una gestión de hilos de forma coordinada y ordenada al mismo tiempo. Para ello hemos empleado tres estruturas de datos diferentes:

    std::vector<std::thread> g_vhilos /*Estructura para instanciar los hilos*/
    
    std::map <int,std::vector<LineResult>> result /*Mapa para guardar las ocurrencias de un hilo*/
    
    std::vector<LineResult> line_result /*Estructura para almacenar el conjunto de ocurrencias de cda hilo*/
    
En primer lugar cada uno de los hilos serás almacenados en una estructura de datos (g_vhilos) que instanciarán un método del "Manager" (find_word) para poder realizar de forma paralela la búsqueda de las ocurrencias de la palabra indicada y luego almacenarlas en una estrutura de datos general que es común para todos los hilos (result). Dicha estructura de datos se realizá a traves de un "map". Un map en C++ es una estructura de datos que se basa en clave-valor. Esto permite que cuando los hilos hayan terminado con la búsqueda de las ocurrencias de la palabra en un intervalo del fichero, guardará en la estructura de datos general (result), el conjunto de ocurrencias que han almacenados de forma independiente (line_result).

Para poder mantener la exclusión mútua con la estructura de datos geneal (result) utilizamos el patrón mutex, con un semáforo, aunque en esta práctica podemos prescindir de él.  
    
    std::mutex semaphore /*Semáforo*/
    
Para el diseño de la función principal, "find_word", hemos utilizado una librería "regex", que nos permite definir expresiones regulares. Esta expresión regular permite que podamos buscar cada una de las ocurrencias de una palabra sin tener en cuenta los acentos en esta práctica en concreto:

    std::string expr_regular_general = "\\b" + word + "\\b"
    
Finalmente una vez encontrada las ocurrencias, se realiza un doble filtrado que permite indicar que las ocurrencias encontradas se relacionan con la expresión regular definida.