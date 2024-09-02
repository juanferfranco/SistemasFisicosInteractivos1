Experiencia de aprendizaje 4. Conectando mundos (comunicación serial)
========================================================================

Introducción
--------------

En esta experiencia de aprendizaje vas a comenzar a explorar las posibilidades de 
comunicación entre un microcontrolador y un computador.

Investigación
-----------------------

Actividad 1
*************

Vas a ingresar al sitio openprocessing y buscar ejemplos que te inspiren y despierten tu curiosidad.
Selecciona una de los ejemplos considerando que tenga algún o algunos parámetros que puedas variar 
con el mouse o el teclado. Analiza el código y experimenta con él. Identifica cómo funciona, 
cuáles son los elementos que lo componen, tal vez puedas hacer algunas modificaciones para experimentar.

En la bitácora:

* Escribe qué descubriste.
* Enlace al recurso.
* ¿Qué aprendiste?

Actividad 2
*************

Considera el siguiente código para el micro:bit:

.. code-block:: python

    from microbit import *

    uart.init(baudrate=115200)

    BUFFER_SIZE = 256
    buffer = bytearray(BUFFER_SIZE)
    end = 0

    while True:
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

Nota que el código anterior lee un caracter a la vez y cuando recibe un salto de línea, muestra en la pantalla del micro:bit 
un mensaje con el número de caracteres recibidos.

Ahora considera esto:

Estas hablando con tu tía por celular y ella te está dice que te va a dictar una cadena de números. 
¿Cómo haces para saber que tu tía ya terminó de dictarte toda la cadena de números?

¿Qué relación tiene el caso de tu tía con la siguiente línea de código?

.. code-block:: python

    if uart.any():
        data = uart.read(1)
        if data:
            if data[0] == ord('\n'):


¿Para qué sirve esta línea de código?

.. code-block:: python

    line = bytes(buffer[:end]).decode('utf-8').strip()


En tu bitácora:

* Analiza con ScriptCommunicator.
* Experimenta con este código.
* ¿Qué aprendiste?

Actividad 3
*************

Vas a revisar de nuevo una aplicación que ya conoces. La aplicación tiene dos partes, 
una para el micro:bit y otra para el computador. Vas a analizar el código de ambas partes.


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

Prueba con ScriptCommunicator el código anterior, asegúrate de entender cómo funciona.

.. warning::

    Asegúrate de tener instalado el módulo p5.webserial.js. ¿Recuerdas que tenías que modificar
    el archivo index.html?

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

Prueba la aplicación anterior. Asegúrate de entender cómo funciona.

* ¿Qué es p5.webserial.js?
* ¿Cómo hago para incluir en mi proyecto de p5.js a p5.webserial.js?
* ¿Cómo se crea un objeto que represente el puerto serial?
* ¿Es necesario abrir y cerrar el puerto serial? ¿Por qué? ¿Qué pasa si no lo hago?
* ¿Cómo hago para enviar datos el micro:bit desde p5.js y desde p5.js a micro:bit?

Reto 
------

Luego de los experimentos realizados vas a modificar la aplicación 
que seleccionaste en la actividad 1 y vas a modificar uno de sus parámetros 
usando el micro:bit.

En tu bitácora
***************

* Explica qué modificaste.
* ¿Cómo lo hiciste?
* El código que usaste.
* Un enlace a un video que muestre la aplicación funcionando.
