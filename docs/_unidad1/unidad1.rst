Unidad 1. Software para sistemas embebido
==============================================

Introducción
--------------

En esta unidad vamos a aprender técnicas para programar 
los sistemas embebidos que permitirán capturar y/o generar información 
desde y hacia el mundo exterior de la aplicación interactiva.

Propósito de aprendizaje
^^^^^^^^^^^^^^^^^^^^^^^^^^

Analizar la plataforma de hardware y software del controlador que se empleará
como interfaz entre los sensores-actuadores y las plataformas de software
interactivas a utilizar en el curso.

Construir aplicaciones simples para el controlador con el fin de explorar algunas
posibilidades y características de su plataforma de software.

Modelar el software del controlador, mediante el uso de máquinas
de estado, para poder establecer escenarios que permitan
documentar y verificar su funcionamiento.

Implementar el software del controlador mediante las técnicas de
programación adecuadas que permitan sacarle el máximo provecho a
dicho controlador. 

Verificar el software del controlador por medio de la
comparación de resultados de funcionamiento con los posibles
escenarios o vectores de prueba definidos en el modelado.


Temas
^^^^^^

* Herramientas del framework de arduino: toolchain, bootloader.
* Código fuente del framework de arduino: estructura y modificaciones
  simples.
* Introducción a la programación NO BLOQUEANTE.
* Técnicas de programación: encapsulamiento mediante tareas, programación
  concurrente.
* Framework de arduino: uso de clases en C++ en un ambiente de programación
  para sistemas embebidos.
* Introducción a los punteros.
* Modelamiento y programación utilizando máquinas de estado.
* Manejo del puerto serial, medidas de tiempo y retardos
  utilizando técnicas de programación no bloqueantes.


Lecturas, ejercicios y proyecto
---------------------------------

Ejercicio 1: introducción y ambiente de trabajo
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Vamos a revisar entre todos este `material introductorio <https://docs.google.com/presentation/d/1lx-4htbKwA1fpIUZ6SpGnAnS5YY3VExF1jMdmARkGYk/edit?usp=sharing>`__.

El material anterior cubre los pasos necesarios para instalar y configurar el entorno de
desarrollo de software bajo el framework de arduino. En este escenario se utilizan los 
lenguajes C y C++.

Ejercicio 2: flujo de trabajo 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

El flujo de trabajo para realizar aplicaciones con arduino será:

* Crear un archivo nuevo. Este archivo inicia con dos funciones: ``setup()`` y ``loop()``.
* La función setup se ejecuta solo una vez al momentos de energizar el ESP32 o cuando se presiona el botón de reset.
* La función loop será llamada constantemente por el framework de arduino.
* Una vez escrita la parte de la aplicación que se desea probar, se debe compilar. El proceso de compilación verifica que 
  el programa no tenga errores sintácticos y genera el código de máquina que posteriormente se cargará en la memoria de
  programa del ESP32. Para realizar la verificación y compilación se selecciona el primer ícono en la parte superior izquierda.
* Una vez compilada la aplicación se procede a grabar la memoria del microcontrolador. Esto se realiza con el segundo ícono
  de la parte superior izquierda.
* Finalmente se selecciona el ícono del monitor serial en la esquina superior derecha. Este ícono permite abrir la terminal
  serial por medio la cual se podrán visualizar los mensajes que el ESP32 le enviará al computador utilizando el 
  objeto ``Serial``.

Vamos a probar todos los pasos anteriores con este programa:

.. code-block:: cpp

    void setup() {
      Serial.begin(115200);
    }

    void loop() {
      Serial.print("Hello from ESP32\n");  
      delay(1000);  
    }


Ejercicio 3: hardware de prueba
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Inicialmente vas a simular todo los dispositivos de hardware tanto el microcontrolador como 
los periféricos que le conectarás a este. Harás mientras te tomas confianza y tienes tiempo de 
ir consiguiendo algunas partes para el curso.

Este ejercicio lo realizaremos juntos. Consiste en explorar la plataforma 
de simulación `tinkercad <https://www.tinkercad.com>`__.

Ejercicio 4: API de arduino 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

En `este enlace <https://www.arduino.cc/reference/en/>`__ se pueden consultar muchas de las funciones disponibles para
realizar programas usando el API de Arduino.

El siguiente programa permite encender y apagar un LED conectado a un puerto de entrada salida:

.. code-block:: cpp

    void setup()
    {
      pinMode(2, OUTPUT);
    }
    
    void loop()
    {
      digitalWrite(2, HIGH);
      delay(1000); // Wait for 1000 millisecond(s)
      digitalWrite(2, LOW);
      delay(1000); // Wait for 1000 millisecond(s)
    }

El siguiente programa permite leer un puerto digital y encender y apagar un LED:

.. code-block:: cpp

    void setup()
    {
      pinMode(2, OUTPUT);
      pinMode(3,INPUT);
      
    }
    
    void loop()
    {
      if(digitalRead(3) == HIGH){
        digitalWrite(2, HIGH);  
      }
      else{
        digitalWrite(2, LOW);
      }
    }

Ejercicio 5: RETO
^^^^^^^^^^^^^^^^^^^^^

Realiza un programa que lea el estado de dos switches y encienda solo
uno de 4 LEDs (un LED para cada combinación posible de los suiches).

No olvides realizar el montaje en tinkercad.


Ejercicio 6: puerto serial
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

En el siguiente ejercicio vas a explorar, de manera básica el puerto 
serial del microcontrolador. Lee el programa, entiéndelo, realiza 
el montaje de hardware necesario y verifica su funcionamiento. Tinkercad 
te permite también simular el puerto serial.

.. code-block:: cpp

    void setup()
    {
      pinMode(2, OUTPUT);
      pinMode(3,INPUT);
      Serial.begin(115200);
      
    }
    
    void loop()
    {
      if(digitalRead(3) == HIGH){
        digitalWrite(2, HIGH);  
        Serial.println("LED ON");
      }
      else{
        digitalWrite(2, LOW);
        Serial.println("LED OFF");
      }
    }

Ejercicio 7: RETO 
^^^^^^^^^^^^^^^^^^^^

Modifique el código del reto anterior para indicar por el puerto serial
cuál de los 4 LEDs está encendido.

Ejercicio 8: Convertidor análogo a digital
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

El siguiente programa lee una señal análoga y la convierte a digital.

.. code-block:: cpp

    void setup()
    {
      pinMode(2, OUTPUT);
      pinMode(3,INPUT);
      Serial.begin(115200);
    }
    
    void loop()
    {
        
        Serial.println(analogRead(A0));
        delay(1000);
    }

Realiza un montaje en tinkercad que te permita simular la señal analógica. Puedes 
usar un potenciómetro.

Ejercicio 9: RETO
^^^^^^^^^^^^^^^^^^^^

Realiza el montaje en tinkercad y un programa para el microcontrolador que 
lea el valor de una entrada analógica. Si la entrada es menor
a 340 enciende un led verde y envía por el puerto serial solo una
vez LED_VERDE. Si es mayor a 340 pero menor a 700 enciende solo 
el LED amarillo y envía por el puerto serial solo una vez LED_AMARILLO.
Finalmente, si es mayor a 700 enciende solo el LED rojo y envía por
el puerto serial solo una vez LED_ROJO. Ten en cuenta que al entrar
a cada rango se debe enviar solo una vez el mensaje por el puerto
serial.

Ejercicio 10: salidas analógicas
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Hasta ahora hemos explorado varias maneras de interactuar con
dispositivos externos por medio de puertos de entrada salida usando:

* Salidas digitales
* Entradas digitales
* Entradas analógicas

Ahora en este ejercicio vamos a explorar las salida analógicas. Dichas
salidas, en principio son digitales pero moduladas en ancho de pulso
o de PWM. Para ello usamos esta función:

.. code-block:: cpp

    analogWrite(pin, value)

``analogWrite`` produce una señal cuadra con un duty cycle dado por ``value``,
como se muestra en la figura de `este <https://www.arduino.cc/en/tutorial/PWM>`__
sitio. 


Analiza el siguiente ejemplo:

.. code-block:: cpp

    #define ledPin 3
    #define analogPin 0

    uint16_t counter = 0;
    int8_t direction = 1;

    void setup() {
        Serial.begin(115200);
        pinMode(ledPin, OUTPUT);
    }


    void loop() {
        analogWrite(ledPin, counter); 
        counter = (counter + direction);
        if(counter == 0) direction = 1;
        if(counter == 129) direction = -1;

        Serial.println(counter);
        delay(20);

    }

Ejercicio 11: RETO 
^^^^^^^^^^^^^^^^^^^^^^^^

Monta un circuito (en tinkercad) o tanto mejor si tienes hardware real 
y realiza un programa que permita controlar el brillo de un LED mediante un potenciómetro.

Ten en presente que el valor del potenciómetro va de 0 hasta 5V, en tinkercad, 
o 0 a 3.3V si tienes hardware real, y este se convierte a un valor entre 0 y 1023, es decir, 
la conversión se realiza en 10 bits.

Considera que el valor del PWM puede ir de 0 a 255. Para garantizar que
``value`` estará en ese rango podemos emplear una de las funciones matemáticas
que ofrece el API de arduino:

.. code-block:: cpp

    map(value, fromLow, fromHigh, toLow, toHigh)

En este caso map toma ``fromLow`` y lo convierte a ``toLow`` y
``fromHigh`` y lo convierte a ``toHigh``. Los valores intermedios son mapeados de
manera lineal.

NOTA: para el ESP32 se debe usar una función diferente para el PWM. Ver
`este <https://techexplorations.com/guides/esp32/begin/pwm/>`__ enlace.

Ejercicio 12: variables static
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Vamos a explorar un poco más el lenguaje de programación.

Analiza el siguiente código:

.. code-block:: cpp

    void setup() {
       Serial.begin(115200);

    }


    void loop() {

      uint8_t counter = 20;

      counter++;

      Serial.println(counter);

      delay(100);

    }

Compara el código anterior con este:

.. code-block:: cpp

    void setup() {
       Serial.begin(115200);

    }


    void loop() {

      static uint8_t counter = 20;

      counter++;

      Serial.println(counter);

      delay(100);

    }

Ahora compara con este otro código:

.. code-block:: cpp

	uint8_t counter = 5;

    void setup() {
       Serial.begin(115200);

    }


    void incCounter() {
      static uint8_t counter = 10;
      counter++;
      Serial.print("Counter in incCounter: ");
      Serial.println(counter);

    }

    void loop() {
      static uint8_t counter = 20;
      counter++;
	    Serial.print("Counter in loop: ");
      Serial.println(counter);
      incCounter();
      Serial.print("Counter outside loop: ");
      Serial.println(::counter);
      ::counter++;
      delay(500);
    }

¿Qué puedes concluir?

Ejercicio 13: introducción al código no bloqueante
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Analiza el siguiente ejemplo:

.. code-block:: cpp

    const uint8_t ledPin =  3;
    uint8_t ledState = LOW;
    uint32_t previousMillis = 0;
    const uint32_t interval = 1000;

    void setup() {
      // set the digital pin as output:
      pinMode(ledPin, OUTPUT);
    }
    
    void loop() {
      uint32_t currentMillis = millis();
    
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
    }

¿Qué hace este programa?

Ejercicio 14: RETO 
^^^^^^^^^^^^^^^^^^^^^^

Realice un programa que encienda y apague tres LEDs a
1 Hz, 5 Hz y 7 Hz respectivamente utilizando la técnica vista en
el ejercicio anterior.

Ejercicio 15: arreglos
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Vamos a analizar uno de los ejemplos que vienen con el
SDK de arduino. Este ejemplo nos permite ver cómo podemos
hacer uso de los arreglos para manipular varios LEDs:

.. code-block:: cpp
    
    int timer = 100;           // The higher the number, the slower the timing.
    int ledPins[] = {
      2, 7, 4, 6, 5, 3
    };       // an array of pin numbers to which LEDs are attached
    int pinCount = 6;           // the number of pins (i.e. the length of the array)
    
    void setup() {
      // the array elements are numbered from 0 to (pinCount - 1).
      // use a for loop to initialize each pin as an output:
      for (int thisPin = 0; thisPin < pinCount; thisPin++) {
        pinMode(ledPins[thisPin], OUTPUT);
      }
    }
    
    void loop() {
      // loop from the lowest pin to the highest:
      for (int thisPin = 0; thisPin < pinCount; thisPin++) {
        // turn the pin on:
        digitalWrite(ledPins[thisPin], HIGH);
        delay(timer);
        // turn the pin off:
        digitalWrite(ledPins[thisPin], LOW);
    
      }
    
      // loop from the highest pin to the lowest:
      for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
        // turn the pin on:
        digitalWrite(ledPins[thisPin], HIGH);
        delay(timer);
        // turn the pin off:
        digitalWrite(ledPins[thisPin], LOW);
      }
    }


Ejercicio 16: encapsulamiento en tareas
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

El siguiente código muestra cómo podemos encapsular completamente
el código del RETO anterior en tareas.

.. code-block:: cpp

    void setup() {
      task1();
      task2();
    }

    void task1(){
      static uint32_t previousMillis = 0;
      static const uint32_t interval = 1250;
      static bool taskInit = false;
      static const uint8_t ledPin =  3;
      static uint8_t ledState = LOW;
      
      if(taskInit == false){
        pinMode(ledPin, OUTPUT);	
        taskInit = true;
      }
      
      uint32_t currentMillis = millis();	
      if ( (currentMillis - previousMillis) >= interval) {
        previousMillis = currentMillis;
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
        digitalWrite(ledPin, ledState);
      }
    }

    void task2(){
      static uint32_t previousMillis = 0;
      static const uint32_t interval = 370;
      static bool taskInit = false;
      static const uint8_t ledPin =  5;
      static uint8_t ledState = LOW;
      
      if(taskInit == false){
        pinMode(ledPin, OUTPUT);	
        taskInit = true;
      }
      
      uint32_t currentMillis = millis();	
      if ( (currentMillis - previousMillis) >= interval) {
        previousMillis = currentMillis;
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
        digitalWrite(ledPin, ledState);
      }
    }

    void loop() {
      task1();
      task2();
    }

Una de las ventajas del código anterior es que favorece el trabajo
en equipo. Nota que se puede entregar a cada persona del equipo una
tarea. Finalmente, uno de los miembros del equipo podrá integrar
todas las tareas así:

.. code-block:: cpp

	  void task1(){
    .
    .
    .
    }
    
    void task2(){
    .
    .
    .
    }

    void task3(){
    .
    .
    .
    }

    void setup() {
	    task1();
	    task2();
      task3();
	  }

	  void loop() {
	    task1();
	    task2();
      task3();
	  }


Ejercicio 17: introducción a las clases
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Observa detenidamente el código de ambas tareas. Verás que es muy similar.
En este ejercicio veremos una construcción interesante de
C++ que favorece el reuso de código. Nota que el código de las tareas
1 y 2 es prácticamente el mismo, solo que está actuando sobre diferentes datos. 

¿Cómo así?

Analicemos por partes. Primero, la inicialización de la tarea:

Para la tarea 1 (task1):

.. code-block:: cpp

    if(taskInit == false){
	  	pinMode(ledPin, OUTPUT);	
	    taskInit = true;
	  }

Para la tarea 2 (task2):

.. code-block:: cpp

    if(taskInit == false){
	  	pinMode(ledPin, OUTPUT);	
	    taskInit = true;
	  }


En el código anterior cada tarea tiene una variable que permite
activar el código solo un vez, es decir, cuando taskInit es false.
Esto se hace así para poder inicializar el puerto de salida donde
estará el led conectado. Recuerde que esto se haga solo una vez.
¿Cuándo ocurrirá? Cuando llamemos taskX() (X es 1 o 2) en la función
setup().

Segundo, el código que se llamará repetidamente en la función loop:

Para la tarea 1:

.. code-block:: cpp

	   if ( (currentMillis - previousMillis) >= interval) {
	     previousMillis = currentMillis;
	     if (ledState == LOW) {
	       ledState = HIGH;
	     } else {
	       ledState = LOW;
	     }
	     digitalWrite(ledPin, ledState);
	   }


Para la tarea 2:

.. code-block:: cpp

	  uint32_t currentMillis = millis();	
	   if ( (currentMillis - previousMillis) >= interval) {
	     previousMillis = currentMillis;
	     if (ledState == LOW) {
	       ledState = HIGH;
	     } else {
	       ledState = LOW;
	     }
	     digitalWrite(ledPin, ledState);
	   }

Nota que los datos sobre los que actúa cada código, aunque
tienen el mismo nombre son datos distintos:

Para la tarea 1:

.. code-block:: cpp

	  static uint32_t previousMillis = 0;
	  static const uint32_t interval = 1250;
	  static bool taskInit = false;
	  static const uint8_t ledPin =  3;
	  static uint8_t ledState = LOW;

Para la tarea 2:

.. code-block:: cpp

	  static uint32_t previousMillis = 0;
	  static const uint32_t interval = 370;
	  static bool taskInit = false;
	  static const uint8_t ledPin =  5;
	  static uint8_t ledState = LOW;

Pero ¿Por qué son distintos? porque estamos declarando las variables
como estáticas dentro de cada tarea.
Esto implica que las variables son privadas a cada función pero
viven en memoria como si se tratara de variables globales.

Esto introduce la siguiente pregunta: ¿Qué tal si pudiéramos tener
el mismo código, pero cada vez que lo llamemos indicarle sobre
que datos debe actuar? Pues lo anterior es posible en C++ usando
una construcción conocida como clase.

La clase nos permite definir un nuevo tipo dato y los algoritmos
que se pueden aplicar a ese nuevo tipo de dato. En este caso,
necesitamos que cada tarea pueda tener sus propias variables para
previousMillis, interval, ledPin, ledState.

.. code-block:: cpp

    class LED{
        private:
            uint32_t previousMillis;
            const uint32_t interval;
            const uint8_t ledPin;
            uint8_t ledState = LOW;
	  };

De esta manera en cada tarea podremos crear un nuevo LED así:

.. code-block:: cpp

    void task1(){
        static LED led;
    }

.. code-block:: cpp

    void task2(){
        static LED led;
    }

A cada nuevo LED se le conoce como un objeto. led es
la variable por medio de las cuales podremos acceder a cada
uno de los objetos creados en task1 y task2.

Notas:

* Cada objeto es independiente, es decir, cada objeto tiene su propia
  copia de cada variable definida en la clase.
  ¿Cuál es el contenido de cada objetos? el contenido es un uint32_t,
  un const uint32_t, un const uint8_t y uint8_t a los cuales les
  hemos dado nombres: previousMillis, interval, ledPin y ledState
  respectivamente.
* Las variables led definidas en task1 y task2 NO SON OBJETOS,
  son variables de tipo LED que permiten acceder al contenido de cada objeto. 
* led es una variable propia de cada tarea.
* Nota que las variables definidas en LED son privadas (private). Esto
  quiere decir que no vamos a acceder a ellas directamente. Ya veremos
  más abajo cómo modificar sus valores.

Nuestro nuevo tipo LED tiene un problema y es que no permite definir para cada
LED creado el intervalo y el puerto donde se conectará. Para resolver lo anterior
se introduce el concepto de constructor de la clase. El constructor,
permite definir los valores iniciales de cada objeto.

.. code-block:: cpp
  

    class LED{
        private:
            uint32_t previousMillis;
            const uint32_t interval;
            const uint8_t ledPin;
            uint8_t ledState = LOW;

        public:
            LED(uint8_t _ledpin, uint32_t _interval): ledPin(_ledpin), interval(_interval) {
                pinMode(_ledpin, OUTPUT);
                previousMillis = 0;
            }
	  };

El constructor de la clase es un método que recibe los valores
iniciales del objeto y no devuelve nada.

Ahora si podemos definir cada objeto:

.. code-block:: cpp

    void task1(){
        static LED led(3,725);
    }

.. code-block:: cpp

    void task2(){
        static LED led(5, 1360);

.. code-block:: cpp

    class LED{

    private:
      uint32_t previousMillis;
      const uint32_t interval;
      const uint8_t ledPin;
      uint8_t ledState = LOW;

    public:
      LED(uint8_t _ledpin, uint32_t _interval): ledPin(_ledpin), interval(_interval) {
       pinMode(_ledpin, OUTPUT);
       previousMillis = 0;
      }

      void toggleLED(){
       uint32_t currentMillis = millis();	
       if ( (currentMillis - previousMillis) >= interval) {
         previousMillis = currentMillis;
         if (ledState == LOW) {
           ledState = HIGH;
         } else {
           ledState = LOW;
         }
         digitalWrite(ledPin, ledState);
       }
      }
    };   


Finalmente, al llamar toggleLED debemos indicar sobre qué objeto
deberá actuar:

.. code-block:: cpp

    void task1(){
        static LED led(3,725);

        led.toggleLED();
    }

.. code-block:: cpp

    void task2(){
        static LED led(5, 1360);
        led.toggleLED();
    }

La versión final del código será:

.. code-block:: cpp

    class LED{

      private:
        uint32_t previousMillis;
        const uint32_t interval;
        const uint8_t ledPin;
        uint8_t ledState;

      public:
        LED(uint8_t _ledpin, uint32_t _interval): ledPin(_ledpin), interval(_interval) {
          pinMode(_ledpin, OUTPUT);
          previousMillis = 0;
          ledState = LOW;
        }

        void toggleLED(){
          
          uint32_t currentMillis = millis();	
          if ( (currentMillis - previousMillis) >= interval) {
            previousMillis = currentMillis;
            if (ledState == LOW) {
              ledState = HIGH;
            } else {
              ledState = LOW;
            }
            digitalWrite(ledPin, ledState);
          }
        }
    };

	  void task1(){
	    static LED led(3,1250);
	    led.toggleLED();
	  }

	  void task2(){
	    static LED led(5,375);
	    led.toggleLED();
	  }

	  void setup() {
	    task1();
	    task2();
	  }

	  void loop() {
	    task1();
	    task2();
	  }

Ejercicio 18: de nuevo arreglos
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Podemos llevar un paso más allá el ejercicio anterior si añadimos
el concepto de arreglo. ¿Para qué? Observa que el código de
task1 y task2 es muy similar. Tal vez podamos resolver el problema
usando únicamente una tarea:

.. code-block:: cpp

    class LED{

      private:
        uint32_t previousMillis;
        const uint32_t interval;
        const uint8_t ledPin;
        uint8_t ledState = LOW;

      public:
        LED(uint8_t _ledpin, uint32_t _interval): ledPin(_ledpin), interval(_interval) {
        pinMode(_ledpin, OUTPUT);
        previousMillis = 0;
      }

      void toggleLED(){
       uint32_t currentMillis = millis();	
       if ( (currentMillis - previousMillis) >= interval) {
         previousMillis = currentMillis;
         if (ledState == LOW) {
           ledState = HIGH;
         } else {
           ledState = LOW;
         }
         digitalWrite(ledPin, ledState);
       }
      }
    };

    void setup() {
      task();
    }

    void task(){
      static LED leds[2] = {{3,725},{5,1300}};

      for(int i= 0; i < 2; i++){
        leds[i].toggleLED();
      }

    }

    void loop() {
        task();
    }


Ejercicio 19: punteros
^^^^^^^^^^^^^^^^^^^^^^^

Ahora vamos a explorar un concepto fundamental en C y C++: los punteros.

¿Qué son los punteros? para entenderlos vamos a dar un salto mortal
en complejidad analizando este ejemplo:

.. code-block:: cpp

    void setup(){
        Serial.begin(115200);
    }


    void processData(uint8_t *pData, uint8_t size, uint8_t *res){
      uint8_t sum = 0;

      for(int i= 0; i< size; i++){
        sum = sum + *(pData+i) - 0x30;
      }
      *res =  sum;
    }

    void loop(void){
      static uint8_t rxData[10];
      static uint8_t dataCounter = 0;  

      if(Serial.available() > 0){
          rxData[dataCounter] = Serial.read();
          dataCounter++;
        if(dataCounter == 5){
           uint8_t result = 0;
           processData(rxData, dataCounter, &result);
           dataCounter = 0;
           Serial.println(result);
        }
      }
    }


Ejercicio 20: comunicaciones seriales
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 

Observa `este <https://www.youtube.com/embed/nm0EdjXEBGQ>`__ video corto que introducirá como
funcionan las comunicaciones seriales entre un sistema embebidos y una
plataforma de cómputo interactiva.

.. raw:: html

    <div style="position: relative; padding-bottom: 5%; height: 0; overflow: hidden; max-width: 100%; height: auto;">
        <iframe width="100%" height="315" src="https://www.youtube.com/embed/nm0EdjXEBGQ" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
    </div>


Ejercicio 21: un poco más sobre el serial 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Ahora lee el material de `este <https://learn.sparkfun.com/tutorials/serial-communication/all>`__
sitio y responde las siguientes preguntas:

* ¿Cuál es la diferencia entre una interfaz de comunicación paralela y una serial?
* ¿Cuál es la diferencia entre un protocolo serial sincrónico y asincrónico?
* En el caso de arduino ¿Qué tipo de protocolo usamos?
* Si el protocolo serial asíncrono que usaremos es de 8 bits, un bit de arranque,
  un bit de parada, sin bit de paridad y a 9600 bps dibuja los diagramas de tiempo cuando
  se transmite el byte 0x01 y el carácter '1'
* ¿Es lo mismo transmitir el byte 0x01 que el byte '1'?


Ejercicio 22: api serial de arduino
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

¿Dónde encuentro el API de arduino para el manejo del serial?

`Aquí <https://www.arduino.cc/reference/en/language/functions/communication/serial/>`__

Las siguientes preguntas las responderemos en los próximos ejercicios, pero por ahora
lee algunas de las funciones del API del serial y responde:

* ¿Cual es la diferencia entre print y println?
* ¿Cuál es la diferencia entre print y write?
* ¿Qué pasa si utilizas read() cuando available() te devuelva cero?
* ¿Cuál es la diferencia entre readBytes? y readBytesUntil()?
* ¿Qué pasa si quieres leer 10 bytes con readBytes pero solo se han recibido 3?

Ejercicio 23: análisis del api serial (investigación: hipótesis-pruebas)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Qué crees que ocurre cuando:

* ¿Qué pasa cuando hago un Serial.available()?
* ¿Qué pasa cuando hago un Serial.read()?
* ¿Qué pasa cuando hago un Serial.read() y no hay nada en el buffer de
  recepción?
* Un patrón común al trabajar con el puerto serial es este:

.. code-block:: cpp

    if(Serial.available() > 0){
        int dataRx = Serial.read() 
    }

* ¿Cuántos datos lee Serial.read()?
* ¿Y si quiero leer más de un dato? No olvides que no se pueden leer más datos
  de los disponibles en el buffer de recepción, claramente porque no hay
  más datos que los que tenga allí.

Ejercicio 24: buffer de recepción
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Vamos a leer 3 datos del puerto serial:

.. code-block:: cpp

    if(Serial.available() >= 3){
        int dataRx1 = Serial.read()
        int dataRx2 = Serial.read() 
        int dataRx3 = Serial.read() 
    }

Vas a comparar el programa anterior con el que sigue: 


Ejercicio 25: análisis, hipótesis, pruebas
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

¿Qué escenarios podría tener en este caso?

.. code-block:: cpp

    if(Serial.available() >= 2){
        int dataRx1 = Serial.read()
        int dataRx2 = Serial.read() 
        int dataRx3 = Serial.read() 
    }

Compara el este ejercicio con el anterior. Realiza pruebas, experimenta. 
¿Qué puedes concluir? discute tus resultados con el profesor.


Ejercicio 26: miniRETO
^^^^^^^^^^^^^^^^^^^^^^^

Piense cómo podrías hacer lo siguiente:

.. code-block:: cpp

    void taskSerial(){
        // Esta tarea tiene su propio buffer de recepción,
        // es decir, su propio vector. Nadie más tiene acceso
    }
    void loop(){
        taskSerial();
    }

* Almacenar los datos en su propio buffer de recepción
  (el buffer será un arreglo).
* El buffer debe estar encapsulado en la tarea
* Los datos almacenados en el buffer no se pueden perder
  entre llamados a taskSerial(). La función taskSerial() se llama
  en la función loop.  
* ¿Qué debes hacer para saber, en cualquier parte del código de taskSerial(),
  cuántos datos tienes guardados en el buffer de recepción?


Ejercicio 27: terminal serial
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Vamos a detenernos un momento en el software del lado del
computador: el terminal. Veamos dos de ellas, la terminal
de arduino y `esta <https://sourceforge.net/projects/scriptcommunicator/>`__
otra (scriptcommunicator)

* ¿Qué es un programa terminal? 
* ¿Para qué sirve?

Discute tus resultados con el profesor y tus compañeros.

Ejercicio 28: enviar datos por el puerto serial 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Considera el siguiente programa

.. code-block:: cpp

    void setup()
    {
      Serial.begin(9600);
    }
    void loop()
    {
      if(Serial.available() > 0){
        Serial.read();
        int8_t var = -1;
        Serial.println("Inicio de la prueba");
        Serial.write(var);
        Serial.print("\n");
        Serial.print(var);
        Serial.print('\n');
        Serial.println("Fin de la prueba"); 
      }
    }

Ejecuta el programa

¿Qué observas en la terminal de arduino justo en estas dos líneas?

.. code-block:: cpp

    Serial.write(var);
    Serial.print(var);

¿Qué observas en Scriptcommunicator para las dos líneas anteriores?

En la siguiente parte del código:

.. code-block:: cpp

    if(Serial.available() > 0){
        Serial.read();

Comenta la línea Serial.read() en esta parte del código:

.. code-block:: cpp

    if(Serial.available() > 0){
        //Serial.read();

¿Qué ocurre? ¿Por qué ocurre esto?

En la siguiente parte del código:

.. code-block:: cpp

    Serial.println("Inicio de la prueba");
    Serial.write(var);
    Serial.print("\n");
    Serial.print(var);
    Serial.print('\n');
    Serial.println("Fin de la prueba"); 

¿Cuál es la diferencia entre estas dos líneas de código?

.. code-block:: cpp

  Serial.print("\n");
  Serial.print('\n');

Ejercicio 29: miniRETO
^^^^^^^^^^^^^^^^^^^^^^^

Considera el siguiente código para analizar en Scriptcommunicator:

.. code-block:: cpp

    void setup()
    {
      Serial.begin(9600);
    }

    void loop()
    {
      if(Serial.available() > 0){
        Serial.read();
        int8_t var = 255;
        int8_t var2 = 0xFF;
        Serial.write(var);
        Serial.print(var);
        Serial.write(var2);
        Serial.print(var2);
      }
    }

Explica qué está ocurriendo en cada caso.

Ejercicio 30: máquinas de estado
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Este ejercicio lo vamos a realizar todos juntos:

Una aplicación interactiva posee un sensor que produce ruido eléctrico al
cambiar de estado. La siguiente figura, capturada con un osciloscopio
muestra la señal del sensor.

.. image:: ../_static/bounce.jpg
  :alt: bounce

En la figura se observa el ruido generado en la transición de la señal
al pasar del estado alto al estado bajo; sin embargo, el
mismo fenómeno ocurre al cambiar del estado bajo al alto. Nota que
además pueden ocurrir falsos positivos en la señal, que se manifiestan
como pulsos de muy corta duración.
Un ingeniero electrónica experto nos indica que podemos considerar un
cambio de estado en el sensor siempre que la señal esté estable por
lo menos durante 100 ms, es decir, sin ruido y sin falsos positivos.
Se debe realizar una aplicación que filtre el comportamiento ruidoso
del sensor y reporte por un puerto serial únicamente los valores
estables de la señal.

Para este ejercicio debes:

* Realizar un diagrama con el modelo en máquinas de estado para la aplicación
* Definir escenarios de prueba usando diagramas de secuencias.
* Implementar el modelo.
* Verificar los escenarios definidos

Ejercicio 31: miniRETO
^^^^^^^^^^^^^^^^^^^^^^^^^

En un escape room se requiere construir una aplicación para controlar una bomba temporizada.
La siguiente figura ilustra la interfaz de la bomba. El circuito de control
de la bomba está compuesto por tres sensores digitales,
en este caso pulsadores, denominados UP, DOWN, ARM (los simularemos con el PC),
un display (LCD) y una salida digital para activar la bomba
(simularemos la salida y el display con el PC).

.. note:: NO ES NECESARIO SIMULAR EL HARDWARE 
    
    Te propongo que hagas simulaciones del hardware por costos, pero si quieres realizar 
    el montaje real sería GENIAL! Habla con el profesor para que te recomiende qué 
    materiales puedes usar. 

El controlador funciona así:

.. image:: ../_static/bomb.png
  :alt: bomba

* Inicia en modo de configuración, es decir, no cuenta aún, la bomba está
  ``desarmada``. El valor inicial del conteo regresivo es de 20 segundos.
* En el modo de configuración, los pulsadores UP y DOWN permiten
  aumentar o disminuir el tiempo inicial de la bomba.
* El tiempo se puede programar entre 10 y 60 segundos con cambios de 1 segundo.
* El tiempo de configuración se debe visualizar en el LCD (enviamos el
  valor al PC).
* El pulsador ARM arma la bomba.
* Una vez armada la bomba, comienza la cuenta regresiva que será visualizada
  en el LCD en por medio de una cuenta regresiva en segundos.
* La bomba explotará (se activa la salida de activación de la bomba) cuando
  el tiempo llegue a cero. En este punto el control regresará al modo de
  configuración.
* Una vez la bomba esté armada es posible desactivarla ingresando un código
  de seguridad. El código será la siguiente secuencia de pulsadores
  presionados uno después de otro:  UP, DOWN, DOWN, UP, UP, ARM.
* Si la secuencia se ingresa correctamente el controlador pasará de nuevo
  al modo de configuración de lo contrario continuará la fatal cuenta
  regresiva.


Para este ejercicio debes:

* Realizar un diagrama con el modelo en máquinas de estado para la aplicación
* Definir escenarios de prueba usando diagramas de secuencias.
* Implementar el modelo.
* Verificar los escenarios definidos

.. Solución a ejercicios
  
  `Aquí <https://github.com/juanferfranco/sensores1/tree/master/docs/_semana5/bomb.ino>`__ una solución de 2020-10 al problema:

  .. code-block:: cpp 
    :lineno-start: 1

    uint32_t Timer = 20;

    enum class BOMBEVS {UP, DOWN, EVTIMER, ARM};
    BOMBEVS bombEvs;
    bool bombEvsFlag = false;


    bool timerInitCount = false;
    uint32_t timeOld = 0;

    void setup() {
      Serial.begin(115200);
    }

    void initCount() {
      timerInitCount = true;
      timeOld = millis();
    }

    void stopCount() {
      timerInitCount = false;
      Timer = 20;
    }

    void taskBomb() {
      enum class BombStates {SETTING, COUNTING};
      static BombStates stateVar =  BombStates::SETTING;
      static uint32_t keyInput[5] = {1, 2, 3, 4, 5};
      static uint8_t counter = 0;
      static uint32_t keyCode = 0;

      switch (stateVar) {
          case BombStates::SETTING: {
            if (bombEvs == BOMBEVS::UP) {
                if (Timer < 60) {
                Timer++;
                Serial.println(Timer);
                }
            } else if (bombEvs == BOMBEVS::DOWN) {
                if (Timer > 10) {
                Timer--;
                Serial.println(Timer);
                }

            } else if (bombEvs == BOMBEVS::ARM) {
                initCount();
                stateVar = BombStates::COUNTING;
            }

            break;
          }

          case BombStates::COUNTING:{
            if (bombEvs == BOMBEVS::EVTIMER) {

                Timer--;

                if (Timer == 0) {
                Serial.println("RIP");
                for (;;);
                }
                else {

                Serial.println(Timer);
                }
            }
            else if (bombEvs == BOMBEVS::UP) {
                if (counter < 5) {
                keyCode = keyCode + 8 * keyInput[counter];
                counter++;
                }
            } else if (bombEvs == BOMBEVS::DOWN) {
                if (counter < 5) {
                keyCode = keyCode + 17 * keyInput[counter];
                counter++;
                }
            } else if (bombEvs == BOMBEVS::ARM) {
                if(keyCode == 165){
                        keyCode = 0;
                        counter = 0;  
                        Serial.println(":)");
                        stopCount();
                        stateVar = BombStates::SETTING;
                }
                else{
                    counter = 0;
                    keyCode = 0;
                }
            }

            break;
          }
      }
    }

    void taskInputSerial() {

      if (Serial.available()) {
          int dataRx = Serial.read();
          if (dataRx == 'u') {
            bombEvs  = BOMBEVS::UP;
            bombEvsFlag = true;
          }
          else if (dataRx == 'd') {
            bombEvs  = BOMBEVS::DOWN;
            bombEvsFlag = true;
          }
          else if (dataRx == 'a') {
            bombEvs  = BOMBEVS::ARM;
            bombEvsFlag = true;
          }


      }
    }

    void taskTime() {
      if (timerInitCount == true) {
          uint32_t timeNow = millis();
          if ( (timeNow - timeOld) >= 1000 ) {
            timeOld = timeNow;
            bombEvs = BOMBEVS::EVTIMER;
            bombEvsFlag = true;
          }
      }
    }

    void loop() {


    taskInputSerial();

    taskTime();

    if (bombEvsFlag == true) {
        bombEvsFlag = false;
        taskBomb();
    }

    }

  Un ejercicio extra para practicar: se propone implementar el modelo que muestra en
  esta imagen:

  .. image:: ../_static/SM.jpeg
    :alt: state machine


PROYECTO EVALUATIVO
^^^^^^^^^^^^^^^^^^^^^

El proyecto se publicará en la semana de evaluación. Por tanto, te recomiendo que termines 
la mayor cantidad de ejercicios que puedas, ojalá todos, antes de la semana de evaluación.
