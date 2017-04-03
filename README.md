# MultiDisplay Animation
Estudiantes:
- Mauricio Arce.
- Gustavo González.
- áéíóúñ para copy paste - quitar

## Introducción
### Objetivo

Realizar una re-implementación de algunas de las funciones de la biblioteca de pthreads de C del Sistema Operativo GNU/Linux. 

### Requerimientos Funcionales
#### MyPthreads

Se realizará la re-implementación de la biblioteca de pthreads, llamada **mypthreads**, de las siguientes funciones: 
- `my_thread_create`
- `my_thread_end`
- `my_thread_yield`
- `my_thread_join`
- `my_thread_detach`
- `my_mutex_init`
- `my_mutex_destroy`
- `my_mutex_lock`
- `my_mutex_unlock`
- `my_mutex_trylock`

Además de las funciones por defecto de phtreads es necesario implementar los siguientes métodos:

- `my_thread_chsched`: Se encarga de cambiar el tipo scheduling del hilo.

#### Schedulers

Los schedulers se debe de establecer al momento de crear los threads. O sea, es necesario agregar un parámetro a la función `my_thread_create` que establezca el scheduler que utilizará ese hilo. Además este método debe ser compatible con una definición de pthreads estándar, o sea. Es posible compilar cualquier código que utilice phtreads, y que éste utilice la nueva biblioteca.

El scheduler por defecto en caso que no se especifique será RoundRobin.

A continuación se definen los tipos de schedulers que soportará la biblioteca. 

##### Scheduler RoundRobin

Se debe de realizar la implementación del scheduler siguiendo un algoritmo de RoundRobin.

##### Scheduler Sorteo

Se debe de realizar la implementación del scheduler siguiendo un algoritmo de Sorteo. Los hilos creados para este scheduler puede que necesiten parámetros extra, por ejemplo cantidad de tiquetes inciales. 

##### Scheduler de Tiempo Real

Se debe de realizar la implementación del scheduler siguiendo un algoritmo de Tiempo Real. Los hilos creados para este scheduler puede que necesiten parámetros extra, por ejemplo límites de tiempo. 

#### Animación

El sistema de animación consiste en una especie de Flash para ASCII que permite crear animaciones que corren en un canvas que estará distribuido en varios monitores.

##### Lenguaje

Se deberá de describir un lenguaje común que permita la descripción de cualquier tipo de animación. En este lenguaje se tendrán conceptos como:

- Restricciones de tiempo de inicio y final.
- Establecer el tamaño del canvas.
- Descripción de Objetos.
- Límite de espacio de Objetos.
- Descripción de movimiento de Objetos.

##### Monitores de despliegue

La aplicación permitirá correrse en distintas PCs. Cada PC aportará su monitor como mecanismo de despliegue. La comunicación entre se realizará utilizando sockets y un protocolo de comunicación definido por el estudiante.

Además es importante establecer el orden de los monitores.

##### Tamaño del canvas

Se deberá de poder establecer el tamaño del canvas, este tamaño incluye: que sección del canvas corresponde a cual de los monitores. Estos monitores se debieron de asociar previamente a través de la aplicación. 

###### Tipos

Se establecerá un mecanismo para definir el tipo de objeto. El tipo de objeto está directamente relacionado con el tipo de Scheduler a utilizar en este caso se dispondrá de RoundRobin y de Sorteo. 

###### Forma

El lenguaje permitirá la creación de nuevas formas, basadas en ASCII art, que se animarán. Un ejemplo de una posible forma es como se muestra a continuación.

<div class="highlight"><pre><span></span>            | | |x| | | 
            | |x|x|x| | 
            |x|x|x|x|x| 
            | |x|x|x| | 
            | |x|x|x| | 
</pre></div>

##### Restricciones de tiempo de inicio y final

Esta descripción consiste en el momento en que el objeto entra en escena y cuando es el momento máximo para que el objeto salga de la escena. En caso que el objeto no respete el tiempo máximo de salida. Este deberá de **explotar**.

##### Descripción de movimiento de Objetos

Los objetos podrán moverse en cualquier dirección en el canvas, además se podrán realizar rotaciones de 0, 90, 180, 270 grados. Los movimientos consisten en una posición inicial y una posición final. Además de un ángulo inicial y un ángulo final.

##### Límite de espacio de Objetos

Ningún objeto puede utilizar el espacio, en el canvas, que otro objeto ya posea. Para ello se deben de implementar mutex o semáforos. En caso que el espacio se encuentre ocupado, el objeto deberá esperar hasta que el espacio esté libre.

##### Creación de una animación de prueba

Se debe de crear una animación de prueba que permita mostrar el funcionamiento de todos los requerimientos anteriores.

#### Otras consideraciones

Además de las definiciones anteriores tome en cuenta:

- Todo el sistema de Animación es gobernado por el Scheduler de TiempoReal, que hace que se cumplan los límites de tiempo. Este le da más prioridad a un hilo cambiándolo temporalmente de scheduler a uno más eficiente. Por ejemplo se deberá de elegir el sorteo y darle más tiquetes al hilo.
- Todos los animadores corren en modo listening.
- La arquitectura de la federación de monitores es distribuida formando un grafo. Este grafo puede ser: una lista enlazada, en forma de estrella o cualquier otra forma.

#### Extra

Establecer un lenguaje común donde dos proyectos funcionen como si fuera uno. O sea que sea posible la federación de dos proyectos diferentes. 

## Ambiente de desarrollo
## Estructuras de datos usadas y funciones
## Instrucciones para ejecutar el programa
## Actividades realizadas por estudiante

Se desglosan en el formato: 

Fecha – Cantidad Horas Invertidas - Tarea - Estudiante

- `2 Abril - 1 hora - Creación del Git, inicio del README.md - Gustavo`. 

## Comentarios finales (estado del programa)
## Conclusiones
## Bibliografía
