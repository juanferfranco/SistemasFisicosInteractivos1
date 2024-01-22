Introducción al flujo de trabajo del curso 
===========================================

Introducción
--------------

En estas sesiones del curso vas a tener un primer contacto con las herramientas 
que utilizarás para desarrollarlo así como el flujo de trabajo para 
documentar tu proceso de aprendizaje y evidenciar el desarrollo 
del resultado de aprendizaje.

Duración de esta etapa 
-----------------------

Consulta en la sección :ref:`cronograma` la duración de esta etapa.

Trayecto de actividades
-------------------------

Actividad 1
*************

* Abre una versión actualizada de Google chrome o Microsogt edge.
* Ahora abre el editor de código del dispositivo `micro:bit <https://python.microbit.org/>`__.
* Copia en el editor el siguiente código:

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

* Conecta el micro:bit a un puerto USB del computador.
* Al lado del botón Send to micro:bit hay tres puntos. Selecciona Connect.
* Selecciona el puerto USB lógico asignado por el sistema operativo al micro:bit. En este
  caso ``mbed Serial Port``.
* Si no hay errores. Presiona Send to micro:bit y espera que aparezca una mariposa en el display de este.
  Eso quiere decir que el programa anterior ya estará cargado en la memoria del micro:bit.


Actividad 2
*************

* Desconecta el micro:bit de la aplicación, de nuevo en los tres puntos al lado de Send to micro:bit, 
  pero esta vez seleccionarás Disconnect.
* Abre la aplicación Web Serial Terminal que encontrarás `aquí <https://capuf.in/web-serial-terminal/>`__.
* En Port Settings configura BaudRate a 115200.
* Conecta el micro:bit al computador.
* Presiona el botón Connect.
* En la ventana emergente selecciona el puerto de comunicación asignado 
  por el sistema operativo de tu computador al micro:bit. En este caso se llamará mbed Serial Port.
* Si no hay mensajes de error y la conexión es exitosa, presiona el botón A del micro:bit. ¿Qué pasa?
* Presiona el botón B. ¿Qué pasa?
* Sacude el micro:bit sin desconectarlo del PC. ¿Qué pasa?
* Al lado izquierdo de uno de los botones Send encontrarás una caja de texto. Borra el contenido y 
  escribe la letra ``h``. Presiona Send. ¿Qué pasa?
* Una vez logres realizar exitosamente todos los experimentos anteriores presiona el mismo botón 
  que usaste para conectarte al micro:bit, pero esta vez, esa operación lo desconectará de 
  la aplicación WebTerminal.

Actividad 3
*************

* ¿Desconectaste el micro:bit de la aplicación anterior? No olvides hacer esto siempre que quieras 
  usar una aplicación diferente. No es posible tener dos aplicaciones interactuando al mismo tiempo
  con el micro:bit.
* El micro:bit en este punto debe seguir conectado al PC, pero desconectado de la aplicación anterior.
* Busca el editor online de la plataforma de programación creativa `p5.js <https://p5js.org/es/>`__.
* Explora la interfaz y gana familiaridad con el entorno.
* Abre el archivo index.html e incluye las siguiente línea antes de la tag ``link``.

    .. code-block:: javascript 
    
        <script src="https://unpkg.com/@gohai/p5.webserial@^1/libraries/p5.webserial.js"></script>

* En el archivo sketch.js copia el siguiente código

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

* Dale click a Play sketch.
* Dale ahora click a Connect to micro:bit
* Selecciona el puerto mbed Serial Port.
* Presiona los botones A y B del micro:bit. ¿Qué pasa?
* Sacude el micro:bit. ¿Qué pasa?
* Presiona el botón Send Love. ¿Qué pasa?

Actividad 4
*************

Vas a poner bajo control de versión el programa de p5.js y el 
programa de micro:bit.

Actividad 5
*************

.. warning::
    PREGUNTA GUÍA

    #. Explica e implementa ¿Cómo puedes hacer para que el círculo use colores diferentes?
    #. Explica e implementa ¿Cómo puedes cambiar el fondo del canvas?
    #. Explica e implementa ¿Cómo puedes cambiar la figura que se pinta en pantalla?
    #. Explica e implementa ¿Cómo puedes cambiar las imágenes que muestra el micro:bit?

    * Muestras imágenes de los resultados de tus experimentos en la bitácora.
    * Realiza commits nuevos en el repositorio con los cambios al código 
      en p5.js y para el micro:bit.

Evidencias
-------------

#. Bitácoras de las sesiones de trabajo en aula e independientes.
#. El archivo README.md de la carpeta `Introduccion` del repositorio deberá tener dichas bitácoras.
#. No olvides responder las preguntas guía.