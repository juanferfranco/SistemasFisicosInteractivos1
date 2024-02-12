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
* Aquí les dejo una solución a un problema similar al de la bomba usando C++:

.. code-block:: cpp

    #include "SSD1306Wire.h"

    #define BOMB_OUT 25
    #define LED_COUNT 26
    #define UP_BTN 13
    #define DOWN_BTN 32
    #define ARM_BTN 33

    void taskSerial();
    void taskButtons();
    void taskBomb();

    void setup() {
      taskSerial();
      taskButtons();
      taskBomb();
    }

    bool evButtons = false;
    uint8_t evButtonsData = 0;

    void loop() {
      taskSerial();
      taskButtons();
      taskBomb();
    }

    void taskSerial() {
      enum class SerialStates {INIT, WAITING_COMMANDS};
      static SerialStates serialState =  SerialStates::INIT;

      switch (serialState) {
        case SerialStates::INIT: {
            Serial.begin(115200);
            serialState = SerialStates::WAITING_COMMANDS;
            break;
          }
        case SerialStates::WAITING_COMMANDS: {

            if (Serial.available() > 0) {
              int dataIn = Serial.read();
              if (dataIn == 'u') {
                Serial.println("UP_BTN");
                evButtons = true;
                evButtonsData = UP_BTN;
              }
              else if (dataIn == 'd') {
                Serial.println("DOWN_BTN");
                evButtons = true;
                evButtonsData = DOWN_BTN;
              }
              else if (dataIn == 'a') {
                Serial.println("ARM_BTN");
                evButtons = true;
                evButtonsData = ARM_BTN;
              }

            }

            break;
          }
        default:
          break;


      }


    }

    void taskButtons() {
      enum class ButtonsStates {INIT, WAITING_PRESS, WAITING_STABLE, WAITING_RELEASE};
      static ButtonsStates buttonsState =  ButtonsStates::INIT;
      static uint8_t lastButton = 0;
      static uint32_t referenceTime;
      const uint32_t STABLETIMEOUT = 100;

      switch (buttonsState) {
        case ButtonsStates::INIT: {
            pinMode(UP_BTN, INPUT_PULLUP);
            pinMode(DOWN_BTN, INPUT_PULLUP);
            pinMode(ARM_BTN, INPUT_PULLUP);
            buttonsState = ButtonsStates::WAITING_PRESS;
            break;
          }
        case ButtonsStates::WAITING_PRESS: {
            if (digitalRead(UP_BTN) == LOW) {
              buttonsState = ButtonsStates::WAITING_STABLE;
              lastButton = UP_BTN;
              referenceTime = millis();
            }
            else if (digitalRead(DOWN_BTN) == LOW) {
              buttonsState = ButtonsStates::WAITING_STABLE;
              lastButton = DOWN_BTN;
              referenceTime = millis();
            }
            else if (digitalRead(ARM_BTN) == LOW) {
              buttonsState = ButtonsStates::WAITING_STABLE;
              lastButton = ARM_BTN;
              referenceTime = millis();
            }
            break;
          }

        case ButtonsStates::WAITING_STABLE: {
            if (digitalRead(lastButton) == HIGH) {
              buttonsState = ButtonsStates::WAITING_PRESS;
            }
            else if ( (millis() - referenceTime) >= STABLETIMEOUT ) {
              buttonsState = ButtonsStates::WAITING_RELEASE;
            }
            break;
          }

        case ButtonsStates::WAITING_RELEASE: {
            if (digitalRead(lastButton) == HIGH) {
              buttonsState = ButtonsStates::WAITING_PRESS;
              evButtons = true;
              evButtonsData = lastButton;
              printf("Btn press: %d\n", lastButton);
            }

            break;
          }
        default:
          break;

      }

    }

    void taskBomb() {
      static SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_64_48);
      enum class BombStates {INIT, WAITING_CONFIG, COUNTING};
      static BombStates bombState =  BombStates::INIT;
      static uint8_t bombCounter = 20;
      static uint8_t secret[7] = {UP_BTN, UP_BTN, DOWN_BTN, DOWN_BTN, UP_BTN, DOWN_BTN, ARM_BTN};
      static uint8_t password[7] = {0};
      static uint8_t passwordCounter = 0;

      static uint32_t referenceTimeBombCounter;
      const uint32_t BOMBINTERVAL = 1000;
      static uint32_t referenceTimeLEDBombCounter;
      const uint32_t LEDBOMBINTERVAL = 500;
      static uint8_t ledBombCountState = LOW;


      switch (bombState) {
        case BombStates::INIT: {
            pinMode(BOMB_OUT, OUTPUT);
            pinMode(LED_COUNT, OUTPUT);

            display.init();
            display.setContrast(255);
            display.clear();

            display.setTextAlignment(TEXT_ALIGN_LEFT);
            display.setFont(ArialMT_Plain_16);
            display.clear();
            display.drawString(10, 20, String(bombCounter));
            display.display();

            digitalWrite(BOMB_OUT, LOW);
            ledBombCountState = HIGH;
            digitalWrite(LED_COUNT, ledBombCountState);


            bombState = BombStates::WAITING_CONFIG;

            break;
          }
        case BombStates::WAITING_CONFIG: {

            if (evButtons == true) {
              evButtons = false;

              if (evButtonsData == UP_BTN) {
                if (bombCounter < 60) {
                  bombCounter++;
                }
                display.clear();
                display.drawString(10, 20, String(bombCounter));
                display.display();
              }
              else if (evButtonsData == DOWN_BTN) {
                if (bombCounter > 10) {
                  bombCounter--;
                }
                display.clear();
                display.drawString(10, 20, String(bombCounter));
                display.display();
              }
              else if (evButtonsData == ARM_BTN) {
                referenceTimeBombCounter = millis();
                referenceTimeLEDBombCounter = millis();
                passwordCounter = 0;
                bombState = BombStates::COUNTING;
              }
            }

            break;
          }
        case BombStates::COUNTING: {

            if (evButtons == true) {
              evButtons = false;

              password[passwordCounter] = evButtonsData;
              passwordCounter++;

              if (passwordCounter == 7) {
                bool disarm = true;
                for (int i = 0; i < 7; i++) {
                  if (password[i] != secret[i]) {
                    passwordCounter = 0;
                    disarm = false;
                    break;
                  }
                }
                if (disarm == true) {
                  bombCounter = 20;
                  display.clear();
                  display.drawString(10, 20, String(bombCounter));
                  display.display();
                  digitalWrite(BOMB_OUT, LOW);
                  ledBombCountState = HIGH;
                  digitalWrite(LED_COUNT, ledBombCountState);
                  bombState = BombStates::WAITING_CONFIG;
                }
              }
            }

            if ( (millis() - referenceTimeLEDBombCounter) >= LEDBOMBINTERVAL ) {
              referenceTimeLEDBombCounter = millis();
              ledBombCountState = !ledBombCountState;
              digitalWrite(LED_COUNT, ledBombCountState);
            }

            if ( (millis() - referenceTimeBombCounter) >= BOMBINTERVAL) {
              referenceTimeBombCounter = millis();
              bombCounter--;
              if (bombCounter > 0 ) {
                display.clear();
                display.drawString(10, 20, String(bombCounter));
                display.display();
              }
              else {
                bombCounter = 20;
                digitalWrite(BOMB_OUT, HIGH);
                display.clear();
                display.drawString(10, 20, "BOOM");
                display.display();
                delay(3000);
                bombCounter = 20;
                display.clear();
                display.drawString(10, 20, String(bombCounter));
                display.display();
                digitalWrite(BOMB_OUT, LOW);
                ledBombCountState = HIGH;
                digitalWrite(LED_COUNT, ledBombCountState);
                bombState = BombStates::WAITING_CONFIG;
              }
            }

            break;
          }

        default:
          break;
      }
    }

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