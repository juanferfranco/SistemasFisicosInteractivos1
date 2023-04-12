Unidad 3. Protocolos binarios 
=========================================================

Introducción 
--------------

En esta unidad seguiremos profundizando en la integración de 
dispositivos periféricos a aplicaciones interactivas, pero esta vez usando 
protocolos binarios.

Propósitos de aprendizaje
*********************************

Integrar aplicaciones interactivas y periféricos utilizando 
protocolos seriales binarios.


Evaluación de la unidad
--------------------------

.. warning:: SUSTENTACIÓN 

  No olvides que la evaluación solo se considera entregada cuando la 
  sustentes. Antes de sustentarla, toda la información 
  solicitada debe estar en el repositorio. Verifica con tus compañeros de equipo 
  que todos los requisitos se cumplen antes de sustentar.

Enunciado
**********

Vas a modificar el proyecto de la unidad anterior para cumplir los siguientes 
requisitos:

* Vas a utilizar un protocolo binario para comunicar la aplicación del PC y el 
  microcontrolador.
* Para leer las variables del microcontrolador, el PC enviará un BYTE (tu decides cuál).
  El microcontrolador responderá la solicitud con la información de ``TODAS`` las variables.
  ¿Qué información tendrá la respuesta? Para cada variable dirá el valor actual, si está 
  habilitada, el intervalo de cambio y el delta del cambio. Adicionalmente, deberás 
  incluir un byte extra al final que cambiará en función de la información que envíes. 
  La idea con este byte es que el receptor pueda verificar que la información recibida 
  no se dañó en el camino. A esta idea se le conoce como checksum. NO PIERDAS DE VISTA 
  que el mensaje reporta TODAS las variables, ya no puedes tener mensajes para cada 
  variable. Profe ¿Cómo calculo el checksum? (internet, chatgpt, Bingchat).
* Ten presente que ahora las variables son números en punto flotante y el delta de cambio 
  ya no es UNO, sino un número en punto flotante.
* Para modificar las variables del microcontrolador, el PC deberá enviar una trama 
  igual a la anterior. Es decir, en un solo mensaje ENVIAR TODA la información de las 
  variables.
* Vas a simular un CASO de error, es decir, un caso en el cual el checksum calculado 
  por el PC y el microcontrolador no es el mismo. Visualiza el resultado de esta simulación 
  de manera creativa. Puedes simular este caso usando un botón en la GUI de la aplicación o 
  como tu quieras.
* El microcontrolador deberá mantener un LED funcionando a una frecuencia de 0.5 Hz. El 
  objetivo de este LED es que verifiques de manera visual que la aplicación en el 
  microcontrolador NUNCA se bloquea.

Entrega
*********

.. warning:: LEE PRIMERO

  Lee primero todos los pasos antes de comenzar el proceso.

* Vas a realizar tu entrega en `este <https://classroom.github.com/a/TLgo0t9g>`__ repositorio.
* Sigue los pasos de la unidad anterior para entregar tu proyecto de Unity.
* Ahora crea el archivo README.md en el repositorio y escribe allí para cada aplicación (Arduino y Unity):

    #. ¿Cuáles son los estados y por qué definiste esos estados?
    #. ¿Cuáles son los eventos y por qué definiste esos eventos?
    #. Incluye un enlace a un video de Youtube donde muestres la aplicación funcionando. 
       RECUERDA que es un enlace, NO el video.

Trayecto de Actividades
-------------------------

Ejercicios
*************

Ejercicio 1: introducción a los protocolos binarios - caso de estudio
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

¿Cómo se ve un protocolo binario? Para explorar este concepto te voy a 
mostrar una hoja de datos de un sensor comercial que usa un protocolo de 
comunicación binario. La idea es que explores tanto como quieras, pero 
te quiero invitar a que mires con detenimiento hasta la página 5.

Para responder la pregunta vas a utilizar como ejemplo
`este sensor <http://www.chafon.com/productdetails.aspx?pid=382>`__.
Cuyo manual del fabricante se encuentra `aquí <https://drive.google.com/open?id=1uDtgNkUCknkj3iTkykwhthjLoTGJCcea>`__

Te recuerdo la pregunta:

* ¿Cómo se ve un protocolo binario?
* ¿Puedes describir las partes de un mensaje?
* ¿Para qué sirve cada parte del mensaje?

Ejercicio 2: API de arduino para implementar comunicaciones binarias
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

En `este <https://www.arduino.cc/reference/en/language/functions/communication/serial/>`__ 
enlace vas a mirar los siguientes métodos. Te pediré que los tengas a mano porque 
te servirán para resolver problemas.

.. code-block:: cpp

   Serial.available()
   Serial.read()
   Serial.readBytes(buffer, length)
   Serial.write()

Nota que la siguiente función no está en el repaso:

.. code-block:: cpp

   Serial.readBytesUntil() 

La razón es que en un protocolo binario usualmente no tenemos
un carácter de FIN DE MENSAJE, como si ocurre con los protocolos
ASCII, donde usualmente el último carácter es el ``\n``.

Ejercicio 3: ¿Qué es el endian?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Analicemos el siguiente asunto:

Cuando trabajamos con protocolos binarios es necesario
transmitir variables que tienen una longitud mayor a un byte.
Por ejemplo, los números en punto flotante cumplen con el
`estándar IEEE754 <https://www.h-schmidt.net/FloatConverter/IEEE754.html>`__
y se representan con 4 bytes.

Algo que debemos decidir al trabajar con número como los anteriormente
descritos es el orden en cual serán transmitidos sus bytes. En principio
tenemos dos posibilidades: transmitir primero el byte de menor peso (little endian)
o transmitir primero el byte de mayor peso (big endian). Al diseñar un protocolo
binario debes escoger una de las dos posibilidades.

Ejercicio 4: transmitir números en punto flotante
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. note:: Desempolva ScriptCommunicator

    Para este ejercicio vas a necesitar una herramienta 
    que te permita ver los bytes que estás transmitiendo 
    sin interpretarlos como caracteres ASCII. Usa ScriptCommunicator 
    en Windows y Linux y CoolTerm en MacOS (te soporta la arquitectura 
    Mx).

¿Cómo transmitir un número en punto flotante?

Veamos dos maneras:

.. code-block:: cpp

    void setup() {
        Serial.begin(115200);
    }
    
    void loop() {
        // 45 60 55 d5
        // https://www.h-schmidt.net/FloatConverter/IEEE754.html
        static float num = 3589.3645;
     
        if(Serial.available()){
            if(Serial.read() == 's'){
                Serial.write ( (uint8_t *) &num,4);
            }
        }
    }

Y esta otra forma. Aquí primero se copia la información que se desea 
transmitir a un buffer o arreglo:

.. code-block:: cpp

    void setup() {
        Serial.begin(115200);
    }
    
    void loop() {
        // 45 60 55 d5
        // https://www.h-schmidt.net/FloatConverter/IEEE754.html
        static float num = 3589.3645;
        static uint8_t arr[4] = {0};
    
        if(Serial.available()){
            if(Serial.read() == 's'){
                memcpy(arr,(uint8_t *)&num,4);
                Serial.write(arr,4);
            }
        }
    }

* ¿En qué endian estamos transmitiendo el número?
* Y si queremos transmitir en el endian contrario?


.. note:: ALERTA DE SPOILER

    Te dejo una posible solución a la pregunta anterior.

.. code-block:: cpp

    void setup() {
        Serial.begin(115200);
    }
    
    void loop() {
        // 45 60 55 d5
        // https://www.h-schmidt.net/FloatConverter/IEEE754.html
        static float num = 3589.3645;
        static uint8_t arr[4] = {0};
    
        if(Serial.available()){
            if(Serial.read() == 's'){
                memcpy(arr,(uint8_t *)&num,4);
                for(int8_t i = 3; i >= 0; i--){
                  Serial.write(arr[i]);  
                }
            }
        }
    }

Ejercicio 5: envía tres números en punto flotante
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Ahora te voy a pedir que practiques. La idea es que transmitas 
dos números en puntos flotante en ambos endian.

Ejercicio 6: aplicación interactiva
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Te voy a pedir dos cosas en este punto:

* Que repases (de la unidad anterior o en la documentación de C# de Microsoft) 
  para qué sirven los siguientes fragmentos de código y qué están haciendo:


  .. code-block:: csharp

      SerialPort _serialPort = new SerialPort();
      _serialPort.PortName = "/dev/ttyUSB0";
      _serialPort.BaudRate = 115200;
      _serialPort.DtrEnable = true;
      _serialPort.Open();

  .. code-block:: csharp

      byte[] data = { 0x01, 0x3F, 0x45};
      _serialPort.Write(data,0,1);

  .. code-block:: csharp
      
      byte[] buffer = new byte[4];
      .
      .
      .

      if(_serialPort.BytesToRead >= 4){
          
          _serialPort.Read(buffer,0,4);
          for(int i = 0;i < 4;i++){
              Console.Write(buffer[i].ToString("X2") + " ");
          }
      }


.. note:: A PRACTICAR

    Inventa una aplicación en Unity que utilice TODOS los métodos anteriores. 
    Ten presente que necesitarás inventar también la aplicación del microcontrolador.

Ejercicio 7: RETO
^^^^^^^^^^^^^^^^^^^

Vas a enviar 2 números en punto flotante desde un microcontrolador a una aplicación en 
Unity usando comunicaciones binarias. Inventa una aplicación en Unity que modifique 
dos dimensiones de una game object usando los valores recibidos.

.. tip:: Te voy a dejar una ayuda

  ¿Para qué puede servir el siguiente código?

.. code-block:: csharp

    byte[] buffer = new byte[4];
    .
    .
    .
    if(_serialPort.BytesToRead >= 4){
      _serialPort.Read(buffer,0,4);
      Console.WriteLine(System.BitConverter.ToSingle(buffer,0));


.. note:: PRESTA ESPECIAL ATENCIÓN

    Presta especial atención System.BitConverter.ToSingle. Te pediré 
    que busques en la documentación de Microsoft de C# qué más 
    te ofrece System.BitConverter
