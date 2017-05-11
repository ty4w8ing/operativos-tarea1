# MultiDisplay Animation
Estudiantes:
- Mauricio Arce.
- José Gustavo González González.

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

El presente proyecto se realizará sobre GNU/Linux usando el compilador de *GCC* para código en lenguaje *C*.

## Estructuras de datos usadas y funciones

El proyecto consta de 2 partes claramente definidas, la biblioteca myPthread y el programa de la animación.

### Biblioteca myPthread

Para esta biblioteca se implemtó lo siguiente.

#### timer.h

Esto controla el timer y manda un signal de *Alert*, esto para ser utilizado en los cambios de contexto más adelante. Entre sus funciones encontramos:

##### setTimer

Función que inicializa el timer.

##### getTimer

Funcion que retorna el tiempo transcurrido y para la alarma.

##### stopTimer

Funcion que detiene el timer.

#### simpleThread.h

Es una estructura de datos que contiene los atributos principales de los threads que se van a crear. Estos atributos son:

- thread_id: ID del thread.
- thread_state: estado del thread (DONE, READY, BLOCKED).
- stack: tamaño del hilo.
- thread_function: funcion que recibe el hilo.
- arguments: argumentos de esa funcion.
- environment: para almacenar el contexto del hilo.
 - joined_to: Hilo que esta esperando a que termine.
 - joined_thread: El hilo que está esperando a que este termine.
 
#### lotto.h

En este header se genera un random probabilistico donde se le asigna más probabilidad a un proceso con más tiquetes. Entre sus funciones encontramos:

### ganador

Funcion encargada de generar el random probabilistico.

#### [scheduling]_list.h

Es la lista que contiene la estructura principal para almacenar el algoritmo de scheduling.

#### round_robin.h

Para el *rr* (*round robin*), utilizamos una lista enlazada circular, donde el *head* es el proceso que se encuentra en ejecución. Para ceder el procesador, el siguiente proceso que toma este recurso sería el siguiente de la lista.

#### sorteo.h

Para sorteo, se asignan tiquetes a cada proceso al ingresar en la lista enlazada, y el siguiente proceso sería tomado al azar, usando un random probabilístico. De esta manera nos aseguramos que apenas acabe el quantum, un nuevo proceso entra.

### Animación
Animación...

## Instrucciones para ejecutar el programa

`$ Animación...`

## Actividades realizadas por estudiante

Se desglosan en el formato: 

Fecha – Cantidad Horas Invertidas - Tarea - Estudiante

- `15 al 25 de Abril - 10 horas - Investigación sobre la biblioteca pthread- Gustavo`. 
- `26 al 30 de Abril - 15 horas - Creación de las bases (schedulers) de la biblioteca myPthread exeptuando tiempo real - Gustavo`. 
- `10 Mayo - 2 hora - Documentación - Gustavo y Mauricio`. 

## Comentarios finales (estado del programa)

Animación...

Para la biblioteca myPthread se logró incorporar con éxito los algoritmos de scheduling, pero no así las funciones de pthread asociadas a la biblioteca pthread ni los mutex. No se encontró suficiente información para su implementación, pese a que si se tenía en claro como debían de funcionar estos.

## Conclusiones

Animación...

Pese a la no implementación de la biblioteca, se obtuvo un conocimiento bastante valioso de la biblioteca pthread y de los mutex para implementaciónes futuras. A la vez que se aprendió sobre scheduling a nivel de procesos y cambios de contexto.

## Bibliografía

- Markdown Cheatsheet. (2016, Febrero 26). Obtenido de https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet 
- SetJump para cambios de contexto. Obtenido de https://es.wikipedia.org/wiki/Setjmp.h 
- Margaret Rouse. (2010). Round Robin. Obtenido el 26/Abril/2017, de Techtarget Sitio web: http://whatis.techtarget.com/definition/round-robin
