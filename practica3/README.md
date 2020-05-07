# Práctica 3 Sistemas-Operativos-II

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
Para el diseño de esta práctica hemos tenido en cuenta diversos diseños para llevar a cabo una gestión de hilos de forma coordinada y sincronizada. Para ello hemos empleado varias estruturas de datos diferentes:



    std::vector<std::thread> queue_client_request;/*Cola de espera de entrada al cine de cada uno de los clientes*/
    
    std::vector<std::thread> g_snack_stall; /*Cola donde se guarda los hilos de los puestos de comidas*/
       
    std::vector<std::thread> queue_snack_stall; /*Cola donde se mueve de la cola de tickets a la cola de puestos de comida*/

    std::vector<std::thread> clients_served;/*Cola donde incluiremos los clientes servidos*/
    
    std::queue<TicketMsg> queue_tickets;/*Cola donde se almacena los peticiones de los tickets*/
    
    std::queue<Food_DrinkMsg>queue_food_drink;/*Cola donde se almacena las peticiones de la comida y bebida*/
    
    std::queue<PayMsg>queue_pay_ticket_request;/*Cola para las peticiones de pago de tickets*/
    
    std::queue<PayMsg>queue_pay_f_d_request;/*Cola para las peticiones de pago de comida y bebida*/

    
En cuanto al flujo de datos del programa, el **MANAGER** será el encargado de ejecutar una serie de peticiones de clientes que la **TAQUILLA** será la encargada de asignarle las entradas que el **CLIENTE** solicita. Tanto el la asignación de entradas como el **SISTEMA DE PAGO** se realizará de forma simultánea y exclusiva. Una vez acabado con un **CLIENTE**, tendremos que comprobar si el mismo puede dirigirse o no a un **PUESTO DE COMIDA** dependiendo si ha conseguido las entradas o si ya no quedaban más y entonces se ha quedado sin entradas.

Habrá 3 **PUESTOS DE COMIDA** y una cola de espera, es decir, cuando el cliente esté en la cola se dirigirá al **PUESTO DE COMIDA** que quede libre. El **CLIENTE** solicitará un número de bebidas y de palomitas. El **PUESTO DE COMIDA** comprueba que existe suficiente stock para satisfacer la petición del **CLIENTE**. En caso contrario, se procederá al aviso de un **REPONEDOR** cuyo objetivo es de reponer el stock de dicho **PUESTO DE COMIDA**. Una vez que haya terminado de reponer el stock, el cliente podrá seguir continuando con la compra a través del **SISTEMA DE PAGO**. Se trata de un **SISTEMA DE PAGO** con prioridad a los cliente de la **TAQUILLA**. Es decir, si hubiera dos solicitudes de pago al mismo tiempo, dependiendo del porcentaje que haya sido asignado pues se atenderá con más preferencia a los clientes de la **TAQUILLA** que a los cliente del **PUESTO DE COMIDA**. Una vez que se haya realizado el **SISTEMA DE PAGO**, el cliente podrá entrar en la sala de cine para disfrutar de su película. 
