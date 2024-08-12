Experiencia de aprendizaje 2. Computadores embebidos
======================================================

Introducción
--------------

En esta experiencia de aprendizaje vas a explorar el uso de microcontroladores 
en la programación creativa. La idea es que puedas familiarizarte con algunos 
conceptos básicos de programación de microcontroladores y puedas aplicarlos en 
la creación de proyectos creativos que impliquen la lectura y escritura de datos 
a través de un microcontrolador hacia el mundo físico.

Investigación
---------------

Vas a realizar una serie de experimentos para indagar algunas preguntas. Es 
muy importante que documentes cada uno de los experimentos en tu bitácora. Esto 
lo usarás como una herramienta de reflexión y aprendizaje. También será 
la evidencia de tu trabajo en esta experiencia de aprendizaje para la fase de 
investigación.

Recursos guía 
**************

* Puedes utilizar modelos del lenguaje para generar código, pero debes analizar 
  el código, preguntarle al modelo tus dudas y hacer los experimentos que permitan 
  validar si el código generado por el modelo es correcto o no. No olvides 
  darle contexto al modelo antes de tus preguntas. Dile qué microcontrolador 
  estás usando, en qué lenguaje de programación estás trabajando. Te recomiendo 
  que no le pidas que genere todo el programa, sino que le pidas ayuda en partes. 
  Prueba las partes que te genere el modelo y luego sigue adelante.
* La documentación para el micro:bit la encuentras `aquí <https://microbit.org/get-started/user-guide/introduction/>`__.
* La documentación del lenguaje de programación del micro:bit la encuentras 
  `aquí <https://microbit-micropython.readthedocs.io/en/latest/>`__.
* En el `editor online <https://python.microbit.org/v/3>`__ de micropython para micro:bit encontrarás 
  una ``Referencia`` con información muy útil para experimentar.

Experimento 1
***************

¿Cómo se leen los pulsadores A y B?

Experimento 2
***************

¿Cómo se leen el botón virtual que está en el logo del micro:bit?

Experimento 3
***************

¿Cómo se lee información serial que llega al micro:bit?

.. warning:: ALERTA DE SPOILER

    Si no puedes resolver este experimento, no te preocupes. Te mostraré 
    ahora una posible solución

Este programa lee un carácter que llega por el puerto serial y si es la letra 
``h`` muestra un corazón en la pantalla de LED.

.. code-block:: python

    if uart.any():
        data = uart.read(1)
        if data:
            if data[0] == ord('h'):
                display.show(Image.HEART)

Experimento 4 
**************

¿Cómo se envía información serial desde el micro:bit?

.. warning:: ALERTA DE SPOILER

    Si no puedes resolver este experimento, no te preocupes. Te mostraré 
    ahora una posible solución

Este programa envía la letra ``A`` por el puerto serial. No olvides inicializar 
el puerto serial antes del loop principal (``uart.init(baudrate=115200)``)

.. code-block:: python

  uart.write('A')

Experimento 5
***************

¿Cómo dibujar en la pantalla de LED?

Experimento 6
***************

¿Cómo hacer para producir sonidos con el speaker?

Experimento 7
***************

Analiza con mucho detenimiento este código:

.. code-block:: python

    from microbit import *
    import utime

    class Pixel:
        def __init__(self,pixelX,pixelY,initState,interval):
            self.state = "Init"
            self.startTime = 0
            self.interval = interval
            self.pixelX = pixelX
            self.pixelY = pixelY
            self.pixelState = initState

        def update(self):

            if self.state == "Init":
                self.startTime = utime.ticks_ms()
                self.state = "WaitTimeout"
                display.set_pixel(self.pixelX,self.pixelY,self.pixelState)

            elif self.state == "WaitTimeout":
                currentTime = utime.ticks_ms()
                if utime.ticks_diff(currentTime,self.startTime) > self.interval:
                    self.startTime = currentTime
                    if self.pixelState == 9:
                        self.pixelState = 0
                    else:
                        self.pixelState = 9
                    display.set_pixel(self.pixelX,self.pixelY,self.pixelState)

    pixel1 = Pixel(0,0,0,1000)
    pixel2 = Pixel(4,4,0,500)

    while True:
        pixel1.update()
        pixel2.update()

* Describe detalladamente cómo funciona este ejemplo.
* ¿Puedes identificar algunos estados? 
* Del contexto del ejemplo ¿Qué son los estados?
* Del contexto del ejemplo ¿Qué son los eventos?
* Del contexto del ejemplo ¿Qué son las acciones?

Experimento 8
***************

* ¿Qué es una máquina de estados en programación?
* ¿Qué son eventos en una máquina de estados?
* ¿Qué son las acciones?
* ¿Cuál sería la estructura de un programa modelado con una máquina de estados?

.. code-block:: python

  from microbit import *
  import utime

  # Estados
  STATE_INIT = 0
  STATE_A = 1
  STATE_B = 2

  # Variables disponibles para todos los estados
  current_state = STATE_INIT
  start_time = 0

  while True:
      # Psudoestado inicial
      if current_state == STATE_INIT:
          # Acciones para preparar el estado
          # siguiente:

          # Cambio de estado

      elif current_state == STATE_A:
          # Evento 1
          if condition:
              # Acciones para el evento

              # Acciones para preparar el estado siguiente:

              # Cambio de estado

          # Evento 2
          if condition:
              # Acciones para el evento

              # Acciones para preparar el estado siguiente:

              # Cambio de estado

        elif current_state == STATE_B:
            # Evento 1
            if condition:
                # Acciones para el evento

                # Acciones para preparar el estado siguiente:

                # Cambio de estado

            # Evento 2
            if condition:
              # Acciones para el evento

              # Acciones para preparar el estado siguiente:

              # Cambio de estado
            

Experimento 9
***************

* ¿Cómo es posible estructurar una aplicación usando una máquina de estados para poder atender varios 
  eventos de manera concurrente?
* ¿Cómo haces para probar que el programa está correcto? Debes definir 
  vectores de prueba y el resultado esperado con cada uno.
* Vamos a construir juntos un experimento para explorar esta pregunta.

Enunciado:

Imagina un programa para el micro:bit que muestra diferentes expresiones en 
la pantalla según un ciclo de tiempo, pero que también reacciona de 
inmediato si presionas un botón. Al iniciar, se muestra una cara feliz 
durante un segundo y medio. Después, el micro:bit cambia a una expresión 
sonriente que dura un segundo. Luego, aparece una cara triste durante 
dos segundos, y el ciclo vuelve a comenzar.

Sin embargo, si en cualquier momento se presiona el botón A mientras 
la cara feliz o la sonriente están en pantalla, el micro:bit interrumpe 
el ciclo y muestra inmediatamente la cara triste o feliz, respectivamente. 
Si se presiona el botón A mientras la cara triste está en pantalla, el 
dispositivo cambia a la expresión sonriente. Así, el programa combina 
una secuencia visual predefinida con la capacidad de responder rápidamente 
a la interacción del usuario.
 
.. warning:: MUY IMPORTANTE

    En este programa no puedes usar sleep() para hacer la espera. ¿Por qué?

.. warning:: ALERTA DE SPOILER

    Si no puedes resolver este experimento, no te preocupes. Te mostraré 
    ahora una posible solución

.. code-block:: python

  from microbit import *
  import utime

  STATE_INIT = 0
  STATE_HAPPY = 1
  STATE_SMILE = 2
  STATE_SAD = 3

  HAPPY_INTERVAL = 1500
  SMILE_INTERVAL = 1000
  SAD_INTERVAL = 2000

  current_state = STATE_INIT
  start_time = 0
  interval = 0

  while True:
      if current_state == STATE_INIT:
          display.show(Image.HAPPY)
          start_time = utime.ticks_ms()
          interval = HAPPY_INTERVAL
          current_state = STATE_HAPPY
      elif current_state == STATE_HAPPY:
          if button_a.was_pressed():
              # Acciones para el evento
              display.show(Image.SAD)
              # Acciones para el siguiente estado
              start_time = utime.ticks_ms()
              interval = SAD_INTERVAL
              current_state = STATE_SAD
          if utime.ticks_diff(utime.ticks_ms(), start_time) > interval:
              # Acciones para el evento
              display.show(Image.SMILE)
              # Acciones para el siguiente estado
              start_time = utime.ticks_ms()
              interval = SMILE_INTERVAL
              current_state = STATE_SMILE
      elif current_state == STATE_SMILE:
          if button_a.was_pressed():
              display.show(Image.HAPPY)
              start_time = utime.ticks_ms()
              interval = HAPPY_INTERVAL
              current_state = STATE_HAPPY
          if utime.ticks_diff(utime.ticks_ms(), start_time) > interval:
              display.show(Image.SAD)
              start_time = utime.ticks_ms()
              interval = SAD_INTERVAL
             current_state = STATE_SAD
      elif current_state == STATE_SAD:
          if button_a.was_pressed():
              display.show(Image.SMILE)
              start_time = utime.ticks_ms()
              interval = SMILE_INTERVAL
              current_state = STATE_SMILE
          if utime.ticks_diff(utime.ticks_ms(), start_time) > interval:
              display.show(Image.HAPPY)
              start_time = utime.ticks_ms()
              interval = HAPPY_INTERVAL
              current_state = STATE_HAPPY

Reto 
------

Para implementar este reto ES REQUISITO utilizar la arquitectura de 
máquina de estados. Si vas a programar con ChatGPT asegura que el código 
generado por el modelo esté estructurado como una máquina de estados.

Enunciado
**********

En un escape room se requiere construir una aplicación para controlar 
una bomba temporizada. La siguiente figura ilustra la interfaz de la bomba. 
El circuito de control de la bomba está compuesto por tres sensores,
denominados UP (botón A), DOWN (botón B) y ARMED 
(el gesto de shake de acelerómetro). Tiene dos actuadores o dispositivos 
de salida que serán un display (la pantalla de LEDs) y un speaker.

.. image:: ../_static/bomb.png
  :alt: bomba

|

El controlador funciona así:

* Inicia en modo de ``configuración``, es decir, sin hacer cuenta regresiva aún, 
  la bomba está ``desarmada``. El valor inicial del conteo regresivo es de 20 
  segundos.
* En el modo de configuración, los pulsadores UP y DOWN permiten
  aumentar o disminuir el tiempo inicial de la bomba.
* El tiempo se puede programar entre 10 y 60 segundos con cambios de 1 segundo.
  No olvides usar utime.ticks_ms() para medir el tiempo. Además 1 segundo 
  equivale a 1000 milisegundos.
* Cada que se modifique el tiempo de configuración se debe enviar por el serial 
  el tiempo y lo debes visualizar en la aplicación ScriptCommunicator.
* Hacer shake (ARMED) arma la bomba, es decir, inicia el ``conteo regresivo``.
* Una vez armada la bomba, comienza la cuenta regresiva que será visualizada
  en la pantalla de LED y enviada por el serial.
* La ``bomba explotará`` (speaker) cuando el tiempo llegue a cero. Para 
  volver a modo de configuración deberás hacer un shake.
* Una vez la bomba esté ``armada`` es posible desactivarla con 
  la secuencia botón A, botón B.
* Si la secuencia se ingresa correctamente la bomba pasará de nuevo
  al modo de configuración de lo contrario continuará la fatal cuenta
  regresiva.
* También podrás controlar la bomba desde el serial. El carácter ``u`` 
  para simular el botón UP, ``d`` para simular el botón DOWN y ``s`` 
  para simular ARMED (shake).

Bitácora
**********

Crea en la carpeta de la unidad 2 un archivo micro.py y mantén 
bajo control de versión de tu programa. Cuando me muestres 
funcionando el reto, me mostrarás también el historial de versiones 
de tu programa en tu repositorio.

1. Dibuja la máquina de estados que modela el comportamiento de la bomba.
2. Enumera los estados.
3. Enumera los eventos de cada estado.
4. Enumera las acciones de cada estado.
5. Define TODOS los vectores de prueba que puedas. Realiza una tabla 
   con los vectores de prueba y el resultado esperado con cada uno.
   Esta tabla es el CONTRATO de tu programa. Es decir, aquí estás 
   capturando el comportamiento esperado de tu programa.
6. Coloca en tu bitácora el código fuente final de tu programa.
   
