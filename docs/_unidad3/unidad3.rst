Unidad 3. Protocolos binarios 
=========================================================


Introducción
--------------

En esta unidad seguirás profundizando en la integración de dispositivos periféricos 
a aplicaciones interactivas, pero esta vez usando protocolos binarios.


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
* Debes usar esta vez un modelo de comunicación por eventos, es decir, 
  a diferencia del modo anterior, ya no deberás preguntar por los datos.
  Cuando los datos estén disponibles esto serán enviados. PERO TEN MUCHO 
  cuidado con la cantidad de datos que envías por unidad de tiempo 
  porque esto puede hacer que satures la infraestructura de comunicación 
  de cada parte.
* Debes utilizar un protocolo de comunicación binario.
* Debes usar al menos 2 sensores diferentes y dos actuadores diferentes, 
  es decir, no cuenta usar 2 pulsadores o dos LEDs.
* La aplicación en p5.js debe recibir la información de múltiples 
  sensores del micro:bit en un solo mensaje.
* El micro:bit debe recibir ordenes de activación de múltiples actuadores 
  en un solo mensaje.

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
    el micro:bit. La integración se realizará mediante protocolos BINARIOS utilizando 
    una arquitectura por EVENTOS.

* En tu bitácora evidenciarás la exploración y análisis de varios referentes que 
  seleccionarás según tus intereses. La idea es explorar e inspirarte. ¿Qué 
  te motivaría construir?
* Vuelve a escribir el reto en tu bitácora así:

.. note:: RETO PERSONALIZADO

    Personaliza el reto cambiando los signos ¿? por tu personalización.

    Diseñaré e implementaré una aplicación interactiva para explorar ¿?  
    mediante la integración de los siguientes sensores: ¿? y estos actuadores 
    ¿?. La integración se realizará mediante un protocolo BINARIO utilizando 
    una arquitectura por EVENTOS.

¿Qué recursos guía puedes usar?

* Puedes pedirle ideas a ChatGPT.
* Puedes buscar en Google.
* Puedes ver los `ejemplos de p5.js <https://p5js.org/examples/>`__.
* Busca referentes en sitios web educativos, por ejemplo `aquí <https://makeabilitylab.github.io/physcomp/communication/p5js-paint-io.html#paintio-design-requirements>`__. 
* Busca referentes en YouTube. Puedes usar las palabras de búsqueda: microbit, arduino, p5.js, animation, videogames, game, data art, o 
  el tema que te intereses. Algunos ejemplos:

    * `Serial Communication from Arduino to p5.js <https://youtu.be/PItzUs3gk_0?si=f5_Vah8hDK3qGhQ9>`__.
    * `Arduino P5js <https://youtube.com/playlist?list=PLBmutH_cv0Fmgj4YNrxLkxIRr3puwu8dG&si=rE0X1AYt_L30RhTs>`__.
    * `Painting Demo Using Arduino Leonardo as Mouse/Keyboard Input to p5js <https://youtu.be/jnZWHbsNSUk?si=6BEbgoy8MnLBaLTx>`__.
    * `Theremin P5JS on Microbit <https://www.youtube.com/shorts/WsIhLJInnio>`__.
    * `Control pong in p5 using a MicroBit <https://youtu.be/L_8aCJKhN5Q?si=_7NOKJHj5lrjkeJu>`__.
    * `Project Ultrasonic Radar with micro:bit and p5.js <https://youtu.be/YDc243BO9oQ?si=-tQhwZLwVHr8vido>`__.
    * `ml5.js Serial <https://makeabilitylab.github.io/physcomp/communication/ml5js-serial.html>`__.
    * `HandPose Serial <https://makeabilitylab.github.io/physcomp/communication/handpose-serial.html>`__.

Investigación
*******************

Actividad 1
###############

.. warning:: ¿Ya personalizaste tu reto?

    No inicies esta etapa sin personalizar el reto. Está en la sección anterior, 
    en comprometerse.

.. warning:: ¿Ya reportaste en la bitácora los referentes usados para personalizar 
    el reto?

Actividad 2
###############

Para esta actividad te pediré que abras una terminal y ejecutes el interprete de python. 
Luego escribe los siguientes comandos:

.. code-block:: bash

    import struct
    s1=1.23
    s2=2.45
    s3=3.76

    data = struct.pack('>3f',s1,s2,s3)
    info = [i for i in data]
    hexinfo = [hex(i) for i in info]

    data
    info
    hexinfo


Toma atenta nota de los datos que ves en el arreglo hexinfo.

Ahora abre `este <https://www.h-schmidt.net/FloatConverter/IEEE754.html>`__ sitio. Ingresa 
en el campo ``Decimal Representation`` los números s1, s2, s3. Con cada número observa 
el campo ``Hexadecimal Representation``. Compara lo que ves con ``hexinfo``.

* ¿Qué conclusión puedes sacar hasta este punto? Escribe tu análisis en la bitácora.
* Nota en la línea ``data = struct.pack('>3f',s1,s2,s3)`` el signo ``>``. Repite todos los pasos anteriores
  pero esta vez cambia ``>`` por ``<``. ¿Qué conclusión sacas hasta ahora.
* Vas a buscar qué es BIG ENDIAN y LITTLE ENDIAN.
* En el caso anterior puedes decir cuál es el ENDIAN para ``>`` y para ``<``.

Actividad 3 
#############

Vas a realizar un experimento para investigar a fondo la comunicación en binario. 

Primera para el microbit programa:

.. code-block:: python

    from microbit import *
    import struct

    uart.init(baudrate=115200)

    BUFFER_SIZE = 256
    buffer = bytearray(BUFFER_SIZE)
    end = 0
    sensor1 = 1.23
    sensor2 = 2.45
    sensor3 = 3.76
    data = struct.pack('>3f',sensor1,sensor2,sensor3)

    while True:
        if button_a.is_pressed():
            uart.write(data)
            sleep(500)

* Abre la WebTerminal que usaste la semana de introducción al flujo de trabajo. 
* Experimenta con el código anterior.
* Realiza modificaciones para asegurar que estás entendiendo lo que ocurre.
* ¿Qué puedes concluir?

Actividad 4
################

Ahora investiga un poco del lado de p5.js:

.. code-block:: javascript

    let port;
    let connectBtn;


    function setup() {
    createCanvas(400, 400);
    background(220);
    port = createSerial();
    connectBtn = createButton('Connect to Arduino');
    connectBtn.position(80, 200);
    connectBtn.mousePressed(connectBtnClick);
    let sendBtn = createButton('Send hello');
    sendBtn.position(220, 200);
    sendBtn.mousePressed(sendBtnClick);
    
    }

    function draw() {
    
    if(port.availableBytes() >= 12){
        let arr = port.readBytes(12);
        print(arr);
        background(220);
        const sensors = bytesToFloats(arr);
        sensor1 = sensors[0].toFixed(2);
        sensor2 = sensors[1].toFixed(2);
        sensor3 = sensors[2].toFixed(2);
        print(sensor1);
        print(sensor2);
        print(sensor3);
        
        text(sensor1, 10, height-60);
        text(sensor2, 10, height-40);
        text(sensor3, 10, height-20);
        
    }
    
    if (!port.opened()) {
        connectBtn.html('Connect to Arduino');
    } else {
        connectBtn.html('Disconnect');
    }
    }

    function connectBtnClick() {
    if (!port.opened()) {
        port.open('MicroPython', 115200);
    } else {
        port.close();
    }
    }

    function sendBtnClick() {
    port.write("Hello from p5.js\n");
    }

    function bytesToFloats(bytes) {
        const buffer = new Uint8Array(bytes).buffer;
        const view = new DataView(buffer);
        const floats = [];

        for (let i = 0; i < bytes.length; i += 4) {
            floats.push(view.getFloat32(i));
        }

        return floats;
    }

* Analiza detenidamente cada parte del código anterior. 
* Realiza experimentos simples que te permitan comprender cómo funciona.
* ¿Notaste en la función ``draw()`` la línea ``if(port.availableBytes() >= 12)``? 
  ¿De dónde sale ese número 12?
* Y si la cantidad de datos que envía el micro:bit es variable?

Actividad 5
################

Si observas detenidamente las dos actividades anteriores notarás que el micro:bit 
no está recibiendo información y p5.js envía información pero en ASCII. El reto 
de esta actividad es que integres los dos programas anteriores de tal manera 
que el ambos reciban y envíen información en binario usando un arquitectura por eventos.

* ¿Cuál es la diferencia entre el modelo de comunicación por eventos y el modelo 
  cliente-servidor?

Aplicación 
-----------

Una vez termines la fase de investigación y tengas todos los fundamentos necesarios puedes 
comenzar la etapa de aplicación. En este etapa construirás las aplicaciones para 
resolver el reto personalizado.

Compartir
-----------

Vas a evidenciar tu proceso con las siguientes evidencias que compartirás en 
el archivo README.md de esta unidad:

#. Bitácoras de las 3 sesiones de trabajo de cada semana.
#. Documentación de cierre del resultado y archivos finales con tu solución al reto.
#. El archivo README.md de la carpeta `Unidad3` del repositorio deberá tener dichas bitácoras.
#. Para la documentación final de tu solución:

    * Explica en qué consiste la aplicación que diseñaste e implementaste.
    * Explica el protocolo de integración entre p5.js y el micro:bit.
    * Muestra las partes del código donde implementaste el protocolo.
    * Realiza un video DEMOSTRATIVO, sin explicar, donde muestres el funcionamiento 
      de la aplicación y la interacción con el micro:bit. Trata de hacer este 
      video con la MEJOR CALIDAD que puedas.