Experiencia de aprendizaje 1. ¿Este curso para qué?
======================================================

Introducción
--------------

Esta unidad tiene un propósito claro y es que nos embarcaremos 
en un viaje exploratorio para responder a una pregunta 
fundamental: ¿Este curso para qué? Esta pregunta no solo 
guiará nuestra primera experiencia de aprendizaje, sino que 
también sentará las bases para todo lo que aprenderemos y 
desarrollaremos a lo largo del semestre.

Quiero que te sumerjas en las posibilidades que ofrece el 
diseño y el arte generativo. Estas disciplinas no solo son 
fascinantes desde un punto de vista técnico y estético, sino 
que también tienen el potencial de transformar y fortalecer 
tus habilidades y perfil profesional. Y por qué no, también 
pueden ser una fuente de inspiración para tu vida personal.

Investigación
-----------------------

Realizaremos juntos las actividades 1 a 4. Durante este tiempo, 
exploraremos de manera introductoria algunas herramientas y conceptos. 
Te pido que no tomes notas en este momento; simplemente disfruta del proceso 
y presta la máxima atención posible. Después de este ejercicio grupal, 
tendrás la oportunidad de realizar las actividades de memoria y 
preguntar en tiempo real cualquier duda o dificultad que surja. 
¿Listo? Vamos a empezar.

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

* Desconecta el micro:bit de la aplicación, de nuevo en los tres puntos al 
  lado de Send to micro:bit, pero esta vez seleccionarás Disconnect.
* Vas a descargar y descomprimir la aplicación ScriptCommunicator que 
  encontrarás `aquí <https://sourceforge.net/projects/scriptcommunicator/files/latest/download>`__.
* Conecta el micro:bit al computador.
* Abre la aplicación ScriptCommunicator y selecciona el menú Settings. 
* Selecciona la ventana serial port. En port selecciona el puerto serial que el sistema 
  operativo le asignó al micro:bit. En BaudRate coloca 115200.
* Presiona el botón Connect.
* Si no hay mensajes de error y la conexión es exitosa (¿Cómo lo puedes verificar?), presiona el 
  botón A del micro:bit. ¿Qué pasa?
* Presiona el botón B. ¿Qué pasa?
* Sacude el micro:bit sin desconectarlo del PC. ¿Qué pasa?
* Selecciona de nuevo el menú Settings y configura console options. En new line at byte y en 
  send on enter key coloca None. Y cierra el menú de Settings.
* En la caja de texto inferior escribe la letra ``h``. Presiona send. ¿Qué pasa?
* Finalmente, desconecta el micro:bit de la aplicación. Si no lo haces no podrás conectar otras 
  aplicaciones.

Actividad 3
*************

* ¿Desconectaste el micro:bit de la aplicación anterior? No olvides hacer esto siempre que quieras 
  usar una aplicación diferente. No es posible tener dos aplicaciones interactuando al mismo tiempo
  con el micro:bit.
* El micro:bit en este punto debe seguir conectado al PC, pero desconectado de la aplicación anterior.
* Busca el editor online de la plataforma de programación creativa `p5.js <https://p5js.org/es/>`__.
* Explora la interfaz y gana familiaridad con el entorno.
* Abre el archivo index.html e incluye las siguiente línea antes de la tag ``link``.

.. code-block:: html

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

Vamos a poner bajo control de versión los programas de p5.js y el 
programa de micro:bit.


Actividad 5
*************

Vas a realizar las actividades 1 a 4 de manera individual. Reporta en tu bitácora 
el resultado. Si tienes dudas, no dudes en preguntar. Estoy aquí para ayudarte. Y 
esa es la idea de esta actividad.

Actividad 6
*************

Explora el sitio `p5.js <https://p5js.org/es/>`__.

Ejecuta en el editor online un ejemplo del sitio. Coloca 
en tu bitácora el enlace a este código, una imagen del resultado y una corta 
explicación de cómo funciona el ejemplo.


Actividad 7
*************

Explora el sitio `openprocessing <https://openprocessing.org/>`__.

Selecciona un ejemplo que te guste y documenta en tu bitácora cuál 
es el ejemplo y cómo crees que funcione.

Actividad 8
*************

Ve al sitio del `Patrik Hübner <https://www.patrik-huebner.com/>`__. 

En tu bitácora:

* Puedes explicar uno de los casos de diseño generativo desarrollado 
  por Patrik?
* Explica el marco de trabajo que propone Patrik para realizar proyectos 
  de diseño generativo.

Reto 
------

En tu bitácora vas a escribir un texto donde explores los siguientes asuntos:

* ¿Este curso para qué?
* ¿Cómo crees que el diseño y arte generativo se pueda aplicar 
  al perfil profesional que quieres desarrollar?
* Vas a proponer conceptualmente una experiencia de diseño generativo para una marca 
  o institución. Utiliza como referente el marco propuesto por Patrik Hübner.
