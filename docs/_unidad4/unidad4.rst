Unidad 4. Programación con múltiples hilos
===================================================================

Introducción
--------------

Llegaste a la última unidad del curso. En esta unidad aplicarás los conceptos
aprendidos en el curso construyendo una aplicación interactiva que integre 
sensores y actuadores del micro:bit con la plataforma de programación creativa y 
además explorarás la programación con múltiples hilos.

Duración de esta etapa 
-----------------------

Consulta en la sección :ref:`cronograma` la duración de esta etapa.


Metodología de trabajo de la unidad
-------------------------------------

Esta unidad está compuesta por 4 momentos que se desplegarán en este 
orden:

#. Comprometerse: leerás con detenimiento el reto. Notarás que está 
   redactado de manera genérica, es decir, es necesario que lo personalices.
#. Investigar: vas a construir las bases conceptuales para resolver 
   el reto. Evita la ansiedad de saltar a la fase siguiente. La idea 
   es que primero alimentes tu curiosidad, explores y experimentes.
#. Aplicar: una vez has explorado los conceptos vas a aplicarlos en 
   la solución del reto.
#. Compartir: finalmente realizarás un ejercicio de síntesis donde 
   organizarás los resultados de tu proceso.

Restricciones
----------------

* Debes usar el sistema embebido micro:bit V2.
* Debes usar la plataforma de programación creativa p5.js
* Esta vez tu seleccionas el protocolo de comunicación entre el micro:bit y p5.js.
* Esta vez tu seleccionas el modelo de comunicación entre el micro:bit y p5.js.

Trayecto de actividades
------------------------

Comprometerse
*******************

.. note:: GRAN IDEA

    Conectar el mundo físico con mundos virtuales.

.. note:: PREGUNTA ESENCIAL

    ¿Cómo conectar el mundo físicos con mundos virtuales mediante 
    la construcción de aplicaciones interactivas?

.. note:: RETO

    Diseña e implementa una aplicación interactiva que te permite 
    explorar tus intereses (animación, videojuego, experiencia interactiva, arte 
    generativo, data art, educación, entre otros) y que además interactúe 
    con el mundo exterior mediante el uso de sensores y actuadores que provee 
    el micro:bit. La integración entre el micro:bit y la aplicación se realizará 
    mediante un protocolo de comunicación que tu selecciones. La arquitectura 
    de la comunicación también la seleccionas tu. Para la construcción de 
    esta aplicación vas a explorar la programación con múltiples hilos. Tu seleccionarás 
    el algoritmo que realizará el hilo secundario. El hilo principal deberá mostrar 
    siempre una animación fluida y el hilo secundario deberá interactuar con el.

Escribe en tu bitácora la descripción de la aplicación que deseas construir respondiendo 
estas preguntas:

* ¿Qué quieres lograr con la aplicación?
* ¿Qué tipo de interacción con el usuario deseas que tenga la aplicación?
* ¿Qué tipo de sensores y actuadores del micro:bit deseas usar?
* ¿Qué tipo de protocolo de comunicación deseas usar?
* ¿Cómo será la arquitectura de la comunicación entre el micro:bit y p5.js?
* ¿Qué tipo de algoritmo deseas implementar en el hilo secundario?
* ¿Qué tipo de animación deseas mostrar en el hilo principal?

Investigación
*******************

.. warning:: IMPORTANTE

    Para esta unidad no utilizarás el editor online de p5.js. Necesitarás 
    entonces instalar visual studio code y un servidor local.

Actividad 1
###############

Esta será una actividad guiada en clase. Te mostraré lo que necesitas para 
configurar tu entorno de desarrollo y cómo instalar un servidor local.

Actividad 2
###############

Ahora te voy a mostrar el concepto de hilo en acción. Considera esta animación:

.. code-block:: javascript

   let x = 0;
   let speed = 3;
   let circleSize = 50;

   function setup() {
      createCanvas(400, 400);
   }

   function draw() {
      background(220);
      ellipse(x, height / 2, circleSize, circleSize);
      x = (x + speed) % width;
   }

   function mousePressed() {
      heavyComputation();
   }

   function heavyComputation() {
      let result = 0;
      for (let j = 0; j < 1000000000; j++) {  
         result += Math.sqrt(j);
      }
      circleSize = random(20,70);
      console.log(circleSize);
   }

* ¿Qué sucede cuando presionas el mouse?
* ¿Por qué la animación se detiene?

.. warning:: ALERTA DE SPOILER

   En la próxima actividad te cuento, pero por fa trata de analizarlo 
   tu mismo.

Actividad 2
###############

Analicemos lo que está pasando con el programa anterior. Tu programa en p5.js 
tiene una función draw() que se ejecuta continuamente para actualizar 
la animación en el canvas, moviendo un círculo de izquierda a derecha. 
La función mousePressed() se activa cuando el usuario hace clic en el 
canvas y ejecuta la función heavyComputation(), que realiza un cálculo 
matemático muy intensivo.

**En términos de hilos**

* El hilo principal: toda la ejecución de tu script de p5.js, incluyendo draw() 
  y mousePressed(), se está llevando a cabo en un único hilo (el hilo 
  principal de JavaScript en el navegador web). Esto significa que mientras se 
  está ejecutando heavyComputation(), todas las demás operaciones, incluyendo 
  la actualización de la animación con draw(), deben esperar hasta que 
  heavyComputation() haya terminado.

**Problema de Bloqueo**

Dado que JavaScript en el navegador es de ejecución única por hilo, el cálculo 
intensivo en heavyComputation() bloquea el hilo principal. Esto significa 
que no se pueden procesar más frames de draw() ni otros eventos de usuario 
hasta que el cálculo haya finalizado. El resultado es que la animación se 
congela y la interfaz parece no responder.

¿Cómo solucionar el problema anterior? 

Actividad 3 
#############

Una solución para evitar este bloqueo es usar un web worker. Los web worker 
permiten ejecutar scripts en hilos de fondo separados del hilo principal de 
la página web. Esto significa que puedes realizar cálculos pesados sin 
interrumpir la interfaz de usuario.

Para utilizar un web worker en tu ejemplo, necesitarías:

#. Crear un archivo separado para el web worker, por ejemplo, worker.js.
#. Mover el código de heavyComputation() a worker.js.
#. Desde mousePressed(), enviar un mensaje al web worker para iniciar el cálculo.
#. El web worker realiza el cálculo y devuelve el resultado al script principal.

Aquí tienes un ejemplo de cómo se vería el código. El código de tu sketch:

.. code-block:: javascript

   let x = 0;
   let speed = 3;
   let circleSize = 50;

   // 1. Crear un nuevo web worker.
   // guardas la referencia en worker
   let worker = new Worker('worker.js');

   function setup() {
   createCanvas(400, 400);

   // 2. El web worker generará mensajes 
   // que serán atendidos por este callback

   worker.onmessage = function(event) {
      circleSize = event.data;
      console.log(circleSize);
   };  
   }

   function draw() {
   background(220);
   ellipse(x, height / 2, circleSize, circleSize);
   x = (x + speed) % width;
   }

   function mousePressed() {
      // 3. Cada que se presiona el mouse le mandas
      // un mensaje al web worker.
      worker.postMessage('start');
   }
   
Y el código del worker.js sería:

.. code-block:: javascript

   onmessage = function (e) {
      if (e.data === 'start') {
         heavyComputation();
      }
   }


   function heavyComputation() {
      let result = 0;
      for (let j = 0; j < 1000000000; j++) {
         result += Math.sqrt(j);
      }
      postMessage(Math.random()*50 + 20);
   }

* ¿Qué sucede ahora cuando presionas el mouse?
* ¿Por qué la animación no se detiene?
* ¿La pelota cambia de tamaño inmediatamente o hay un retraso?
* ¿Por qué hay un retraso?
* ¿Qué sucede si presionas el mouse varias veces seguidas?

Actividad 4 
#############

En el worker.js cambia Math.random por random. ¿Qué sucede?

Observa en la consola y notarás que hay un error. Este se debe a que la función 
random() de p5.js no puede usarse en un web worker debido a que p5.js está 
diseñado para funcionar en el contexto del hilo principal de un navegador, 
donde tiene acceso al DOM (Document Object Model) y a las funcionalidades 
relacionadas con el entorno de renderizado del navegador. Los web workers, 
por otro lado, se ejecutan en un entorno completamente separado y no tienen 
acceso al DOM ni a las bibliotecas o funciones que dependen de este, como p5.js.

**Contexto de Ejecución de web workers**

* Aislamiento del hilo principal: los web workers se ejecutan en un contexto de 
  ejecución separado del hilo principal del navegador. Esto significa que tienen 
  su propio espacio de ejecución independiente y no pueden interferir directamente 
  con el DOM ni con el entorno de ejecución visual de la página web.
* Acceso restringido a funciones y objetos del navegador: aunque los web workers 
  pueden realizar operaciones como cálculos intensivos y manejo de I/O (entrada/salida) 
  sin bloquear la interfaz de usuario, no tienen acceso a ciertos objetos y 
  funciones del navegador que requieren una interacción directa con la interfaz de 
  usuario o el DOM. Esto incluye muchas de las capacidades gráficas y de manipulación 
  del DOM que proporciona p5.js.
* Uso de bibliotecas: para utilizar una biblioteca como p5.js dentro de un web worker, 
  esa biblioteca tendría que estar diseñada específicamente para ser ejecutada en 
  ese contexto, lo que generalmente implicaría no depender del DOM o de elementos 
  visuales. Dado que p5.js está intensamente centrada en la creación y manipulación 
  de elementos visuales en la página web, no es adecuada para el entorno de un 
  web worker.

**Alternativas para Uso en web workers**

* JavaScript vanilla: para realizar tareas que incluyen generación de números 
  aleatorios, cálculos matemáticos, y otras operaciones de procesamiento de datos 
  dentro de un web worker, puedes usar JavaScript puro (vanilla JS). Esto incluye 
  el uso de Math.random() para la generación de números aleatorios, y otras 
  funciones de JavaScript que no requieren acceso al DOM. 
* Transferencia de datos: puedes usar mensajes para enviar datos entre el hilo 
  principal y el web worker. Por ejemplo, si necesitas realizar cálculos o 
  procesamiento de datos en el worker y luego utilizar p5.js para visualizar esos 
  datos, puedes calcularlos en el worker y enviar los resultados al hilo principal 
  para ser renderizados con p5.js.

Actividad 5 
#############

¿Por qué el web worker está tan restringido?

Los web workers están diseñados para ejecutar código JavaScript en un hilo 
separado del hilo principal de un navegador, lo cual tiene múltiples ventajas, 
especialmente en términos de rendimiento y experiencia del usuario. Sin embargo, 
estas ventajas vienen con restricciones específicas por varias razones de seguridad, 
simplicidad y eficiencia.

**Seguridad**

* Prevención de manipulación del DOM: dado que el DOM puede ser modificado por 
  el hilo principal, permitir que los web workers accedan al DOM podría resultar 
  en condiciones de carrera y conflictos de datos. Por ejemplo, si un worker 
  y el hilo principal intentan modificar el mismo elemento del DOM simultáneamente, 
  podría llevar a inconsistencias y a comportamientos impredecibles.
* Aislamiento de código: al mantener el código del worker aislado del entorno global 
  del navegador, se minimizan los riesgos de ataques de scripts, como Cross-Site 
  Scripting (XSS). Los Workers no tienen acceso a cookies, localStorage ni a la 
  sesión, reduciendo la superficie de ataque para potenciales exploits.

**Rendimiento**

* Sin bloqueo de UI: una de las principales razones para usar web workers es evitar 
  que operaciones intensivas en recursos bloqueen el hilo principal, que maneja 
  la interfaz de usuario y la respuesta a interacciones del usuario. Si los 
  workers pudieran interactuar con el DOM o realizar operaciones que afecten el 
  rendimiento del hilo principal, se perdería este beneficio.
* Eficiencia de ejecución: al ejecutar en un hilo separado sin acceso a los objetos 
  del navegador de alto nivel, los workers pueden realizar cálculos o procesar datos 
  de manera eficiente sin las sobrecargas asociadas con la actualización de la 
  interfaz de usuario o la gestión de eventos del DOM.

**Simplicidad**

Al limitar lo que los workers pueden hacer, 
el modelo de programación se simplifica, ya que los desarrolladores no tienen 
que manejar la sincronización entre múltiples hilos que interactúan con el 
mismo DOM o estados de aplicación. Esto reduce la complejidad y las posibles 
fuentes de errores en aplicaciones web.

**Independencia del entorno de renderizado**

Los Web Workers están destinados a realizar tareas que no necesitan información 
sobre el estado actual del renderizado de la página, como cálculos matemáticos 
puros o procesamiento de datos en segundo plano. Esto asegura que tales 
operaciones no interfieran con la renderización de la página.

Actividad 6 
#############

Notaste en la actividad anterior que las restricciones del worker permiten 
evitar las condiciones de carrera y conflictos de datos.

¿Qué quiere decir esto?

Las condiciones de carrera ocurren en situaciones donde dos o más hilos acceden 
a recursos compartidos y tratan de cambiarlos al mismo tiempo. Si la secuencia 
en la que se accede y se modifica el recurso no se maneja correctamente, 
puede llevar a resultados inesperados o incorrectos. Esto es crucial en 
programación concurrente y sistemas donde múltiples tareas se ejecutan al mismo 
tiempo, dependiendo del orden de ejecución que, si no se controla, puede ser 
impredecible.

**Ejemplo simple de una condición de carrera**

Imagina que tienes dos hilos que incrementan el mismo contador:

* Hilo A: lee el valor del contador (supongamos que es 0), lo incrementa en 1 y 
  tiene la intención de guardar el valor 1.
* Hilo B: también lee el valor del contador mientras sigue siendo 0, lo incrementa 
  en 1 y también tiene la intención de guardar el valor 1.

Si ambos hilos leen el valor \"al mismo tiempo\" antes de que cualquiera de ellos 
escriba su resultado, ambos terminarán escribiendo el valor 1 en el contador, 
aunque la intención era incrementar el contador dos veces. Así, el valor final 
del contador será 1 en vez de 2.

¿Qué problemas causan las condiciones de carrera?

* Corrupción de datos: si no se controlan, las condiciones de carrera pueden 
  corromper el estado de los datos, llevando a resultados erróneos y a un 
  comportamiento no determinista del software.
* Fallos de seguridad: en aplicaciones críticas, especialmente en sistemas que 
  manejan información sensible, las condiciones de carrera pueden ser explotadas 
  para eludir controles de seguridad.
* Difíciles de detectar y reproducir: a menudo, las condiciones de carrera son 
  intermitentes y dependen de la secuencia exacta de eventos, lo que las hace 
  difíciles de detectar y reproducir, especialmente durante las pruebas.

Actividad 7 
#############

Ahora que has explorado los conceptos de hilos y web workers, te propondré 
otro ejemplo para que practiques. 

* Implementa el siguiente código.
* Observa el comportamiento.
* ¿Qué sucede cuando presionas el mouse?
* ¿Esta aplicación está aprovechando los web workers?

El código del sketch:

.. code-block:: javascript

   let particles = [];
   let worker;

   function setup() {
   createCanvas(800, 600);
   for (let i = 0; i < 100; i++) {
      particles.push(new Particle(random(width), random(height)));
   }
   frameRate(60);
   worker = new Worker("Tarea.js");
   worker.onmessage = function (event) {
      console.log("Receive");
      let updatedParticles = event.data;
      updatedParticles.forEach((data, index) => {
         particles[index].vx = data.vx;
         particles[index].vy = data.vy;
      });
   };
   }

   function draw() {
   background(0);
   particles.forEach((p) => {
      p.update();
      p.display();
   });
   }

   function mousePressed() {
   worker.postMessage(
      particles.map((p) => ({ x: p.x, y: p.y, vx: p.vx, vy: p.vy }))
   );
   console.log("Send");
   }

   class Particle {
   constructor(x, y) {
      this.x = x;
      this.y = y;
      this.vx = random(-1, 1);
      this.vy = random(-1, 1);
   }

   update() {
      this.x += this.vx;
      this.y += this.vy;
      if (this.x < 0 || this.x > width) this.vx *= -1;
      if (this.y < 0 || this.y > height) this.vy *= -1;
   }

   display() {
      stroke(255);
      ellipse(this.x, this.y, 20, 20);
   }
   }

El código del worker.js:

.. code-block:: javascript

   onmessage = function(event) {
   let particles = event.data;
   calculateForces(particles);
   postMessage(particles);
   }

   function calculateForces(particles) {
   particles.forEach(p => {
      p.vx += Math.random(-1, 1);
      p.vy += Math.random(-1, 1);
   });
   }

Aplicación 
*******************

Una vez termines la fase de investigación y tengas todos los fundamentos necesarios 
puedes comenzar la etapa de aplicación. En este etapa vas a diseñar e implementar la 
solución al reto propuesto en la fase de compromiso.

Compartir
*******************

Vas a escribir en tu bitácora:

* ¿En qué consiste la aplicación que diseñaste e implementaste?
* Explica el protocolo de integración entre p5.js y el micro:bit.
* Explica la arquitectura de la comunicación entre el micro:bit y p5.js.
* Explica el algoritmo que implementaste en el hilo secundario.
* Realiza un video DEMOSTRATIVO, sin explicar, donde muestres el funcionamiento 
  de la aplicación, la interacción con el usuario y la interacción con el micro:bit.
* ¿Qué aprendiste en esta unidad?

