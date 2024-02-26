Unidad 2. Protocolos ASCII
==========================================

Introducción
--------------

En la unidad anterior te has concentrado en la construcción de software para sistemas embebidos. 
En esta unidad aprenderás como integrar a una plataforma de cómputo interactiva dichos sistemas 
embebidos mediante el uso de protocolos de comunicación ASCII.


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
* Debes usar el modelo cliente-servidor para comunicar las 
  plataformas anteriores, pero el rol no es estático, puede 
  cambiar en función de la necesidades; sin embargo, una plataforma 
  siempre debe solicitar información antes de recibirla.
* Debes utilizar un protocolo de comunicación ASCII.
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
    el micro:bit. La integración se realizará mediante protocolos ASCII utilizando 
    una arquitectura cliente-servidor.

* En tu bitácora evidenciarás la exploración y análisis de varios referentes que 
  seleccionarás según tus intereses. La idea es explorar e inspirarte. ¿Qué 
  te motivaría construir?
* Vuelve a escribir el reto en tu bitácora así:

.. note:: RETO PERSONALIZADO

    Personaliza el reto cambiando los signos ¿? por tu personalización.

    Diseñaré e implementaré una aplicación interactiva para explorar ¿?  
    mediante la integración de los siguientes sensores: ¿? y estos actuadores 
    ¿?. La integración se realizará mediante protocolos ASCII utilizando 
    una arquitectura cliente-servidor.

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

.. warning:: ¿Ya personalizaste tu reto?

    No inicies esta etapa sin personalizar el reto. Está en la sección anterior, 
    en comprometerse.

.. warning:: ¿Ya reportaste en la bitácora los referentes usados para personalizar 
    el reto?

    .. code-block:: python

        En el mundo de código y creación,  
        donde p5.js y micro:bit son una sensación,  
        recuerda este consejo, es una gran visión:  
        "No inicies la etapa de investigación sin inspiración".  

        Antes de programar, busca esa chispa de emoción,  
        que en cada línea de código, brille tu imaginación.  
        Así en la ciencia y arte, encontrarás unión,  
        y tu proyecto brillará con pura innovación.  

        :)


Considera el siguiente código para el micro:bit:

.. code-block:: python

    from microbit import *

    uart.init(baudrate=115200)

    BUFFER_SIZE = 256
    buffer = bytearray(BUFFER_SIZE)
    end = 0

    while True:
        if accelerometer.was_gesture('shake'):
            display.show(Image.HAPPY)
            uart.write('hello world\n')
            sleep(500)
            display.show(Image.HEART)
        if uart.any():
            data = uart.read(1)
            if data:
                if data[0] == ord('\n'):
                    display.show(Image.HAPPY)
                    sleep(500)
                    line = bytes(buffer[:end]).decode('utf-8').strip()
                    NumOfChars = len(line)
                    display.show(line)
                    sleep(500)
                    display.show(Image.HEART)
                    sleep(500)
                    display.show(NumOfChars)
                    sleep(500)
                    end = 0
                else:
                    buffer[end] = data[0]
                    end +=1


* ¿Cuántos y cuáles estados tiene este programa?
* ¿Cuántos y cuáles son los eventos que tiene este programa?
* ¿Hay condiciones guarda? ¿Cuáles son esas condiciones 
  de guarda?
* Analiza el código con detenimiento.

Ahora considera esto:

Estas hablando con tu tía por celular y ella te está dice que 
te va a dictar una cadena de números. ¿Cómo haces para saber 
que tu tía ya terminó de dictarte toda la cadena de números?

¿Qué relación tiene el caso de tu tía con la siguiente línea de código?

.. code-block:: python

    if uart.any():
        data = uart.read(1)
        if data:
            if data[0] == ord('\n'):

¿Para qué sirve esta línea de código?

.. code-block:: python
    
    line = bytes(buffer[:end]).decode('utf-8').strip()

.. warning:: ¿Ya experimentaste?

    Es ahora de hacer experimentos con el código anterior. Usa 
    la terminal web.

¿Recuerdas el código de la semana 1? Te voy a mostrar de nuevo 
los programas, PERO te ruego que regreses a la micro unidad Flujo 
de trabajo y recuerdes cómo configuraste todo para ver funcionando
la cosa.

Para el micro:bit:

.. code-block:: python

    from microbit import *

    uart.init(baudrate=115200)
    display.show(Image.BUTTERFLY)

    while True:
        if button_a.is_pressed():
            uart.write('A')
            sleep(500)
        if button_b.is_pressed():
            uart.write('B')
            sleep(500)
        if accelerometer.was_gesture('shake'):
            uart.write('C')
            sleep(500)
        if uart.any():
            data = uart.read(1)
            if data:
                if data[0] == ord('h'):
                    display.show(Image.HEART)
                    sleep(500)
                    display.show(Image.HAPPY)


Para el PC con p5.js:

.. code-block:: javascript 

    let port;
    let connectBtn;

    function setup() {
        createCanvas(400, 400);
        background(220);
        port = createSerial();
        connectBtn = createButton('Connect to micro:bit');
        connectBtn.position(80, 300);
        connectBtn.mousePressed(connectBtnClick);
        let sendBtn = createButton('Send Love');
        sendBtn.position(220, 300);
        sendBtn.mousePressed(sendBtnClick);
        fill('white');
        ellipse(width / 2, height / 2, 100, 100);
    }

    function draw() {
    
        if(port.availableBytes() > 0){
            let dataRx = port.read(1);
            if(dataRx == 'A'){
                fill('red');   
            }
            else if(dataRx == 'B'){
                fill('yellow'); 
            }
            else{
                fill('green'); 
            }
            background(220);
            ellipse(width / 2, height / 2, 100, 100);
            fill('black');
            text(dataRx, width / 2, height / 2);
        }    


        if (!port.opened()) {
            connectBtn.html('Connect to micro:bit');
        } 
        else {
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
        port.write('h');
    }


* ¿Qué es p5.webserial.js?
* ¿Cómo hago para incluir en mi proyecto de p5.js a p5.webserial.js?
* ¿Cómo se crea un objeto que represente el puerto serial?
* ¿Es necesario abrir y cerrar el puerto serial? ¿Por qué? ¿Qué pasa 
  si no lo hago? 
* ¿Cómo hago para enviar datos el micro:bit desde p5.js y desde 
  p5.js a micro:bit?

.. warning:: ¿Y dónde está el investigador que hay en tu interior?

    .. code-block::

        En el reino del código y la electrónica,
        donde micro:bit y p5.js bailan la macarena,
        os invito, oh valientes aprendices, a una misión:
        ¡Experimentad sin miedo, que es la mejor lección!

        Con dos programas en mano, uno en cada estación,
        uno habla en ASCII, ¡qué curiosa conversación!
        Pero no os quedéis solo mirando la pantalla,
        ¡hurgad, cambiad, que la experimentación es canalla!

        ¿Qué pasa si este bit lo giras al revés?
        ¿Y si este código en p5.js le das la vuelta a la vez?
        Quizá el micro:bit haga un baile sin igual,
        o p5.js dibuje en el aire, ¡un arte digital!

        No temáis al error, ni al "bug" traicionero,
        pues en cada fallo, hay un aprendizaje sincero.
        Haced que los programas conversen en su lenguaje,
        y descubriréis secretos, ¡es todo un viaje!

        Así que tocad, probad, y poned todo patas arriba,
        en esta aventura, la risa siempre os motiva.
        Recordad, jóvenes sabios, en esta exploración:
        ¡La clave del éxito es la divertida experimentación!

Ahora es momento de recordar a tu tía. Ella te dictó una cadena 
de número. Ahora es tu turno. Le debes dictar tres cadenas números 
a ella. Además, tu tía debe tener claro cuando terminaste 
de dictar la tercer cadena.

* ¿Cómo solucionarías esto haciendo incluyendo entre cada cadena 
  una palabra especial?
* ¿Cómo harías para hacerle saber a tu tía que ya terminaste con 
  la última cadena?

Finalmente, para esta etapa de investigación te pediré que hagas 
realidad esta historia:

.. code-block:: python
    
    '''
    El Gran Concurso de Colores de Bitville

    En el pintoresco pueblo de Bitville, donde los micro:bits y las computadoras conviven en 
    armoniosa tecnología, se celebraba el más extraordinario y colorido 
    evento del año: ¡El Gran Concurso de Colores!

    Cada año, los astutos habitantes de Bitville, los micro:bits, participaban en 
    este concurso para mostrar su habilidad en crear los colores más vibrantes y únicos. 
    Pero esta vez, había un giro emocionante: ¡los micro:bits debían colaborar con 
    las computadoras p5.js para crear un espectáculo de colores nunca antes visto!

    El alcalde de Bitville, un micro:bit experimentado llamado Byte, hizo un anuncio especial: 
    "¡Queridos micro:bits y computadoras p5.js! Este año, la competencia será diferente. 
    Las computadoras p5.js iniciarán la comunicación, solicitando información de 
    nuestros sensores. ¡Y nosotros, los micro:bits, responderemos con un mensaje 
    que contenga datos de tres de nuestros sensores!"

    Los aprendices de Bitville, pequeños y brillantes micro:bits en formación, estaban 
    emocionados pero nerviosos. Nunca antes habían colaborado de esta manera con las 
    computadoras p5.js. Era un reto que requería de su ingenio y creatividad.

    La pequeña micro:bit Bitly dijo con entusiasmo: "¡Imagínense! Nuestros datos de 
    sensores se transformarán en colores RGB en la pantalla de p5.js. Podríamos crear 
    una paleta de colores tan vibrante como el arcoíris".

    El ingenioso Byte les animó: "¡Exactamente, Bitly! Pero para lograrlo, necesitamos 
    que ustedes, aprendices, experimenten y exploren nuevas formas de comunicación entre 
    nosotros y las computadoras p5.js. ¡Es una oportunidad para ser creativos y 
    aprender experimentando!"

    Los aprendices se pusieron manos a la obra. Iniciaron la comunicación desde las 
    computadoras p5.js, y los micro:bits respondían con datos de sus sensores. Al 
    presionar un botón, inclinar o agitar un micro:bit, enviaban información que las 
    computadoras p5.js convertían en magníficos colores RGB, pintando figuras en sus pantallas.

    El día del concurso, Bitville se iluminó con las más espectaculares y vibrantes 
    figuras de colores. Los aprendices habían logrado una sinfonía de colores, un baile 
    de luces y sombras, que dejó a todos los habitantes de Bitville boquiabiertos.

    El alcalde Byte, con una sonrisa de circuito a circuito, anunció: "¡Este ha sido el 
    mejor Concurso de Colores de la historia de Bitville! Aprendices, han demostrado que 
    cuando combinamos experimentación y colaboración, ¡los resultados son simplemente deslumbrantes!"

    Desde ese día, los aprendices de Bitville supieron que con curiosidad, trabajo en 
    equipo y un poco de experimentación, podrían lograr cualquier cosa, incluso convertir 
    datos en un espectacular despliegue de colores.
    '''
    
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
#. El archivo README.md de la carpeta `Unidad2` del repositorio deberá tener dichas bitácoras.
#. Para la documentación final de tu solución:

    * Explica en qué consiste la aplicación que diseñaste e implementaste.
    * Explica el protocolo de integración entre p5.js y el micro:bit.
    * Muestra las partes del código donde implementaste el protocolo.
    * Realiza un video DEMOSTRATIVO, sin explicar, donde muestres el funcionamiento 
      de la aplicación y la interacción con el micro:bit. Trata de hacer este 
      video con la MEJOR CALIDAD que puedas.