Unidad 1. Software para sistemas embebidos
==============================================

Introducción
--------------

En esta unidad vas a explorar y profundizar en el uso del sistema embebido 
que utilizarás como computador externo a la aplicación interactiva (micro:bit).

Duración de esta etapa 
-----------------------

Consulta en la sección :ref:`cronograma` la duración de esta etapa.


Reto 
------

En un escape room se requiere construir una aplicación para controlar 
una bomba temporizada. La siguiente figura ilustra la interfaz de la bomba. 
El circuito de control de la bomba está compuesto por tres sensores digitales,
en este caso pulsadores, denominados UP (botón A), DOWN (botón B), ARMED (LOGO, touch). 
Tiene dos actuadores o dispositivos de salida que serán un display 
(la pantalla de LEDs) y un speaker.

.. image:: ../_static/bomb.png
  :alt: bomba

|

El controlador funciona así:

* Inicia en modo de ``configuración``, es decir, sin hacer cuenta regresiva aún, 
  la bomba está ``desarmada``. El valor inicial del conteo regresivo es de 20 segundos.
* En el modo de configuración, los pulsadores UP y DOWN permiten
  aumentar o disminuir el tiempo inicial de la bomba.
* El tiempo se puede programar entre 10 y 60 segundos con cambios de 1 segundo.
* Cada que se modifique el tiempo de configuración se debe enviar por el serial 
  y visualizar en la aplicación `web serial terminal <https://capuf.in/web-serial-terminal/>`__ 
  que usaste en la primera semana de clases.
* El pulsador ARMED arma la bomba, es decir, inicia el conteo regresivo.
* Una vez armada la bomba, comienza la cuenta regresiva que será visualizada
  en la pantalla de LED y enviada por el serial.
* La bomba explotará (speaker) cuando el tiempo llegue a cero. Para volver a modo 
  de configuración se tendrá que tocar el botón ARMED.
* Una vez la bomba esté armada es posible desactivarla ingresando un código
  de seguridad. El código será la siguiente secuencia de pulsadores
  presionados uno después de otro:  UP, DOWN, UP, DOWN, UP, UP, ARMED.
* Si la secuencia se ingresa correctamente la bomba pasará de nuevo
  al modo de configuración de lo contrario continuará la fatal cuenta
  regresiva.
* Debes almacenar la clave de desarmado de la bomba en un arreglo.
* Toda la funcionalidad de la bomba debe poderse simular desde Web Serial Terminal. 
  Envía por el serial los caracteres ``u`` para simular el botón UP, ``d`` para 
  simular el botón DOWN y ``a`` para simular ARMED.

Investigación
--------------

Aún no debes comenzar a construir la aplicación que resuelvan el reto. Antes 
de hacerlo deberás investigar los conceptos y experimentar. Para ello te propondré 
unas pregunta guía iniciales que deberás responder en la bitácora de trabajo. En 
el proceso te surgirán nuevas preguntas ¿Qué pasaría si...? ¿Por qué ...?
¿Cómo sería si en vez de ... hago ...?

En esta etapa debes hacer EXPERIMENTOS para responder tus preguntas. Mira, la idea es 
que descubras la solución a tus preguntas, no que la busques.

Preguntas guía iniciales 
**************************

Recuerda siempre acompañar la solución a cada pregunta con una actividad guía que será 
un experimento donde ilustres la respuesta.

#. ¿Cómo se leen los pulsadores A y B?
#. ¿Cómo se leen el botón virtual que está en el logo del micro:bit?
#. ¿Cómo se lee información serial que llega al micro:bit?
#. ¿Cómo se envía información serial desde el micro:bit?
#. ¿Cómo dibujar en la pantalla de LED?
#. ¿Cómo hacer para producir sonidos con el speaker?
#. ¿Qué es una máquina de estados?
#. ¿Qué son eventos en una máquina de estados?
#. ¿Qué son las acciones?
#. ¿Cuáles son los estados, eventos y acciones en el reto propuesto?
#. ¿Cómo es posible estructurar una aplicación usando una máquina de estados 
   para poder atender varios eventos de manera concurrente?
#. ¿Cuáles son los eventos que pueden ocurrir de manera simultánea en 
   el problema planteado en el reto?
#. Construye una aplicación que muestre en la pantalla de LED dos imágenes 
   diferentes que se alternarán cada 2 segundos, pero sin usar la función 
   bloqueante sleep(). Investiga las funciones ticks_ms() y ticks_diff() 
   de la biblioteca utime. ¿Cómo puedes utilizar las dos funciones 
   anteriores para resolver el problema de las imágenes que alternan?

Actividad guía
**************************

Analiza detenidamente el siguiente ejemplo:

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

#. ¿Cómo funciona este ejemplo?
#. ¿Qué relación tiene este ejemplo con las preguntas guía?

Recursos guía iniciales 
**************************

* Puedes utilizar inteligencias artificiales generativas para generar el código que 
  necesites.
* La documentación para el micro:bit la encuentras `aquí <https://microbit.org/get-started/user-guide/introduction/>`__.
* La documentación del lenguaje de programación del micro:bit 
  la encuentras `aquí <https://microbit-micropython.readthedocs.io/en/latest/>`__.
* En el `editor online <https://python.microbit.org/>`__ de micropython para micro:bit encontrarás una ``Referencia`` 
  con información muy útil para experimentar. 

Aplicación 
-----------

Una vez termines la fase de investigación y tengas todos los fundamentos necesarios puedes 
comenzar la etapa de aplicación. En este etapa construirás las aplicaciones para 
resolver el reto.


Compartir
-----------

Vas a evidenciar tu proceso con las siguientes evidencias que compartirás en 
el archivo README.md de esta unidad:

#. Bitácoras de las 3 sesiones de trabajo de cada semana.
#. Documentación de cierre del resultado y archivos finales con tu solución al reto.
#. El archivo README.md de la carpeta `Unidad1` del repositorio deberá tener dichas bitácoras.
#. No olvides responder las preguntas guía.
#. No olvides mantener bajo control de versión el código del micro:bit y de los programas 
   con los cuales experimentes.