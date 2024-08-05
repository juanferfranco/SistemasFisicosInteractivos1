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

Experimento 4 
**************

¿Cómo se envía información serial desde el micro:bit?

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

Experimento 9
***************

* ¿Cómo es posible estructurar una aplicación usando una máquina de estados para poder atender varios 
  eventos de manera concurrente?
* Vamos a construir juntos un experimento para explorar esta pregunta.

Experimento 10
***************

Te voy a dar un enunciado y vas a construir una máquina de estados para resolverlo. 

Reto 
------
