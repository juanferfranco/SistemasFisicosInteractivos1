Unidad 3. Protocolos binarios 
=========================================================

Introducción 
--------------

En esta unidad seguiremos profundizando en la integración de 
dispositivos periféricos a aplicaciones interactivas 
utilizando hilos y protocolos binarios.

Propósitos de aprendizaje
*********************************

Integrar aplicaciones interactivas y periféricos utilizando hilos y 
protocolos seriales binarios.

Temas 
************

* Protocolos binarios.
* Diferencia entre los protocolos binarios y los protocolos ASCII.
* Técnicas de programación basadas en máquinas de estado.

Trayecto de acciones
-----------------------

Sesión 1
*************

Ejercicio 1: introducción a los protocolos binarios - caso de estudio
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

¿Cómo se ve un protocolo binario?

Para responder esta pregunta vamos a utilizar como ejemplo
`este sensor <http://www.chafon.com/productdetails.aspx?pid=382>`__.
Cuyo manual del fabricante se encuentra `aquí <https://drive.google.com/open?id=1uDtgNkUCknkj3iTkykwhthjLoTGJCcea>`__

Explora la documentación, pero lee con mucho detalle hasta la página 5.

Ejercicio 2: API de arduino para implementar comunicaciones binarias
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Recuerda el `API de arduino <https://www.arduino.cc/reference/en/language/functions/communication/serial/>`__
para el manejo del serial. En particular los siguientes métodos:

.. code-block:: cpp

   Serial.available()
   Serial.read()
   Serial.readBytes(buffer, length)
   Serial.write()

Nota que la siguiente función no está en el repaso:

.. code-block:: cpp

   Serial.readBytesUntil() 

La razón es que en un protocolo binario usualmente no tenemos
un carácter de fin de trama, como si ocurre con los protocolos
ASCII, donde usualmente el último carácter es el ``\n``.

Analiza de nuevo el API, en particular los métodos resaltados.

Ejercicio 3: aplicación para depurar las comunicaciones binarias
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Mira `este <https://drive.google.com/file/d/1iVr2Fiv8wXLqNyShr_EOplSvOJBIPqJP/view>`__
documento del fabricante del sensor. Podrás ver unos ejemplos de tramas. 

Utiliza `ScriptCommunicator <https://sourceforge.net/projects/scriptcommunicator/>`__ para reproducir 
al menos un par de tramas. ¿Qué tienes que hacer para enviar por el serial 
las tramas? (Explora y pregúntale a tu profesor).

¿Qué busco que practiques en este caso? Que explores ScriptCommunicator

Trabajo autónomo 1
********************
(Tiempo estimado: 1 horas 20 minutos)

RETO 1: técnica de programación del controlador
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

En una experiencia interactiva se requiere comunicar un controlador
con una aplicación interactiva (AI). El controlador maneja varios
sensores y varios actuadores.

Para este reto vas a simular la AI usando 
`ScriptCommunicator <https://sourceforge.net/projects/scriptcommunicator/>`__.

Profe ¿Por qué no puedo usar el programa MONITOR de arduino?

ScriptCommunicator te permite controlar de manera precisa el
byte que deseas transmitir. Recuerda que al usar una terminal como
la de arduino, todos los bytes que transmites están codificados en
ASCII y por tanto cuando escribes el carácter '1' realmente estás
transmitiendo el byte 31 en base 16, es decir, la codificación ASCII
del '1'.

Los PASOS para realizar la comunicación son:

* La AI inicia una transacción enviando el byte 3E.
* El controlador deberá responder con el byte 4A.
* La AI no podrá continuar hasta no recibir la respuesta
  del controlador.
* Una vez el controlador responda, la AI enviará una secuencia
  de ``n+1`` bytes. 
* Cada byte tendrá la siguiente función:

  Byte 1: indica la longitud de la secuencia de bytes.

  Byte 2: byte reservado
  
  Byte 3: indica el comando que deseamos que el controlador realice.
  
  Byte 4 a n: aquí están los datos relacionados con el comando enviado
  
  Byte n+1: checksum

* El byte de ckecksum será calculado mediante una ``XOR`` realizada 
  entre todos los bytes que serán transmitidos, menos el último, que es 
  el checksum. En lenguaje C el operador ``XOR`` es ``^``. Por tanto, 
  la operación a realizar será algo como esto: ``Byte1 ^ Byte2 ^ … ^ Byten``.

* Si la AI se demora más de un 1 segundo en enviar la secuencia,
  el controlador enviará a la AI el byte 3D y la AI deberá iniciar
  de nuevo la secuencia de comunicación desde el paso 1.

* Tanto el controlador como la AI deben calcular el checksum. La AI 
  debe hacerlo para poder transmitirlo y el controlador para comparar si el valor 
  que obtiene es el mismo que recibe. De esta manera el controlador puede identificar 
  si los datos recibidos llegaron bien o no.

* Si controlador detecta que el byte de ckecksum no corresponde, deberá enviar a la AI 
  byte 3F y la AI deberá reenviar el paquete.

* Si el controlador recibe bien el paquete deberá responder a la AI con
  el byte 4A y luego enviar la siguiente secuencia de bytes:

  Byte 1: longitud de la secuencia de bytes que enviará

  Byte 2 a Byte m: corresponden a los bytes 4 al byte n recibidos desde la AI

  Byte m+1: checksum.

* El checksum en este caso se calcula desde el byte 1 hasta el byte m.

* Si la AI recibe correctamente el paquete deberá responder con el byte 4A.

* El controlador quedará preparado para volver al paso 1,
  es decir, iniciar una nueva transacción.

* Si pasado 1 segundo el controlador no recibe el 4A, entonces este
  deberá retransmitir el paquete a la AI. Este comportamiento solo 
  se detendrá una vez la AI envié el 4A.

.. warning:: ALERTA DE SPOILER

    Te dejo una posible solución al reto

Un posible modelo de la solución es este:

.. image:: ../_static/parcial2SM.jpg
   :scale: 100%
   :align: center
   :alt: state machine example

Y una posible implementación del modelo es este otro modelo en C++:

.. code-block:: cpp 


    void taskCom();

    void setup() {
      taskCom();
    }

    void loop() {
      taskCom();
    }
    
    void taskCom() {
      enum class StateTaskCom {INIT, WAIT_INIT, WAIT_PACKET, WAIT_ACK};
      static StateTaskCom state = StateTaskCom::INIT;
      static uint8_t bufferRx[20] = {0};
      static uint8_t dataCounter = 0;
      static uint32_t timerOld;
      static uint8_t bufferTx[20];
    
      switch (state) {
        case StateTaskCom::INIT:{
          Serial.begin(115200);
          state = StateTaskCom::WAIT_INIT;
        break;
        }

        case  StateTaskCom::WAIT_INIT:{
          if (Serial.available()) {
            if (Serial.read() == 0x3E) {
              Serial.write(0x4A);
              dataCounter = 0;
              timerOld = millis();
              state = StateTaskCom::WAIT_PACKET;
            }
          }
    
          break;
          }
    
        case StateTaskCom::WAIT_PACKET:{
    
          if ( (millis() - timerOld) > 1000 ) {
            Serial.write(0x3D);
            state = StateTaskCom::WAIT_INIT;
          }
          else if (Serial.available()) {
            uint8_t dataRx = Serial.read();
            if (dataCounter >= 20) {
              Serial.write(0x3F);
              dataCounter = 0;
              timerOld = millis();
              state = StateTaskCom::WAIT_PACKET;
            }
            else {
              bufferRx[dataCounter] = dataRx;
              dataCounter++;
    
              // is the packet completed?
              if (bufferRx[0] == dataCounter - 1) {
    
                // Check received data
                uint8_t calcChecksum = 0;
                for (uint8_t i = 1; i <= dataCounter - 1; i++) {
                  calcChecksum = calcChecksum ^ bufferRx[i - 1];
                }
                if (calcChecksum == bufferRx[dataCounter - 1]) {
                  bufferTx[0] = dataCounter - 3; //Length
                  calcChecksum = bufferTx[0];
    
                  // Calculate Tx checksum
                  for (uint8_t i = 4; i <= dataCounter - 1; i++) {
                    bufferTx[i - 3] = bufferRx[i - 1];
                    calcChecksum = calcChecksum ^ bufferRx[i - 1];
                  }
    
                  bufferTx[dataCounter - 3] = calcChecksum;
                  Serial.write(0x4A);
                  Serial.write(bufferTx, dataCounter - 2);
                  timerOld = millis();
                  state = StateTaskCom::WAIT_ACK;
                }
                else {
                  Serial.write(0x3F);
                  dataCounter = 0;
                  timerOld = millis();
                  state = StateTaskCom::WAIT_PACKET;
                }
              }
            }
          }
    
          break;
          }

        case StateTaskCom::WAIT_ACK:{
          if ( (millis() - timerOld) > 1000 ) {
            timerOld = millis();
            Serial.write(bufferTx, dataCounter - 2);
          } else if (Serial.available()) {
            if (Serial.read() == 0x4A) {
              state = StateTaskCom::WAIT_INIT;
            }
          }
    
          break;
          }
      }
    }


Un ejemplo de una escenario de prueba:

.. image:: ../_static/vector1.jpg
   :scale: 100%
   :align: center
   :alt: test vector


Sesión 2
*********

Ejercicio 4: análisis grupal del RETO 1
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Vamos a analizar juntos el RETO 1


Ejercicio 5: análisis individual del RETO 1
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Ahora te daré unos minutos para que revises de nuevo el RETO 1 y 
preguntes tus dudas.

Ejercicio 6: ¿Qué es el endian?
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
binario deberemos escoger una de las dos posibilidades.

Ejercicio 7: transmitir números de 16 bits
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

¿Cómo transmitir un número de 16 bits?

.. code-block:: cpp

    void setup() {
      Serial.begin(115200);
    
    }
    
    void loop() {
      //vamos a transmitir el 16205
      static uint16_t x = 0x3F4D;  
    
      if (Serial.available()) {
        if (Serial.read() == 's') {
          Serial.write((uint8_t)( x & 0x00FF));
          Serial.write( (uint8_t)( x >> 8 ));
        }
      }
    }    

* ¿Qué endian estamos utilizando en este caso?

Ejercicio 8: transmitir números en punto flotante
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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

Es posible que queramos copiar los bytes que componen el número
previamente en un arreglo:

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

Ejercicio 9: aplicación interactiva
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Y ¿Cómo hacemos para recibir la información en la aplicación 
interactiva?

En este punto ya sabemos hacer varias cosas:

* Inicializar el puerto
* Enviar bytes
* Saber si hay datos en el puerto serial
* Leer los bytes

Por ejemplo, el siguiente código utiliza las cosas que ya
sabemos usar y permite leer los bytes que se están enviando
desde el arduino (programa en ell arduino el código del ejercicio anterior).

.. code-block:: csharp

    using System;
    using System.IO.Ports;

    namespace serialRFID
    {
        class Program{
                static void Main(string[] args)
                {
                    SerialPort _serialPort = new SerialPort();
                    _serialPort.PortName = "/dev/ttyUSB0";
                    _serialPort.BaudRate = 115200;
                    _serialPort.DtrEnable = true;
                    _serialPort.Open();
                    byte[] data = {0x73};
                    _serialPort.Write(data,0,1);
                    byte[] buffer = new byte[4];

                    while(true){
                        if(_serialPort.BytesToRead >= 4){
                            _serialPort.Read(buffer,0,4);
                            for(int i = 0;i < 4;i++){
                                Console.Write(buffer[i].ToString("X2") + " ");
                            }
                            Console.ReadKey();
                            _serialPort.Write(data,0,1);
                        }
                    }
                }
            }
    }

Ejercicio 10: ¿Cómo convertir los bytes recibidos a un número?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Y si queremos que la aplicación interactiva lea los 4 bytes y lo
convierta al número en punto flotante?

Pero antes de comenzar, ¿En qué endian se envía el número en punto flotante
del ejercicio 8?

.. code-block:: csharp

    using System;
    using System.IO.Ports;

    namespace serialRFID
    {
        class Program{
                static void Main(string[] args)
                {
                    SerialPort _serialPort = new SerialPort();
                    // Allow the user to set the appropriate properties.
                    _serialPort.PortName = "/dev/ttyUSB0";
                    _serialPort.BaudRate = 115200;
                    _serialPort.DtrEnable = true;
                    _serialPort.Open();
                    byte[] data = {0x73};
                    _serialPort.Write(data,0,1);
                    byte[] buffer = new byte[4];

                    while(true){
                        if(_serialPort.BytesToRead >= 4){
                            _serialPort.Read(buffer,0,4);
                            
                            for(int i = 0;i < 4;i++){
                                Console.Write(buffer[i].ToString("X2") + " ");
                            }
                            Console.WriteLine();

                            Console.WriteLine(System.BitConverter.ToSingle(buffer,0));
                            byte [] bufferReverse = new byte[4];
                            for(int i = 3; i>= 0; i--) bufferReverse[3-i] = buffer[i];
                            Console.WriteLine(System.BitConverter.ToSingle(bufferReverse,0));    

                            Console.ReadKey();
                            _serialPort.Write(data,0,1);
                        }
                    }
                }
            }
    }

Trabajo autónomo 2
********************
(Tiempo estimado 1 hora 20 minutos)

RETO 2
^^^^^^^
REPASA todo lo visto hasta ahora. Una vez lo hagas resuelve el reto.

Para este reto vas a implementar dos aplicaciones: microcontrolador y aplicación 
interactiva (tipo consola aún) que realicen el siguiente protocolo:

* La aplicación interactiva solicita datos con el byte C4.
* El microcontrolador le responde con un paquete compuestos de tres números 
  en punto flotante, un entero con signo de 32 bits más un checksum que se 
  calcula como en el reto 1. Por tanto, se estará transmitiendo un 
  paquete con un tamaño total de 17 bytes.
* Si el paquete llega correcto a la aplicación interactiva, esta responde 
  con un 3E, de lo contrario manda un B0 y el microcontrolador deberá reenviar 
  de nuevo el mismo paquete.
* Si esto se repite 3 veces el microcontrolador colocará un LED a 
  prender y apagar a 500Hz para marcar un el ERROR durante 3 segundos. 
  Luego regresará a esperar por solicitud de datos, es decir, a esperar de 
  nuevo el C4. Eso quiere decir que la aplicación interactiva tendrá que 
  renunciar al paquete y pedir uno nuevo.

Sesión 3
************

En esta sesión vas a terminar el RETO 2. Nota que no hay alerta de spoiler 
para este reto. LA IDEA es que te comprometas a solucionarlo por tu propia 
cuenta.

Trabajo autónomo 3
*******************

Termina y repasa el RETO 2. Será súper IMPORTANTE que lo termines para poder 
realizar la evaluación.

Evaluación de la Unidad 3
----------------------------
(Tiempo total estimado: 5 horas).

Enunciado
***********
Vas a trabajar solo o con otra persona.

Vas a realizar dos aplicaciones interactivas. Una para el PC tipo consola 
y la otra para el microcontrolador. Las aplicaciones deben intercambiar 
información usando únicamente un protocolo binario. 

Considera:

* La aplicación interactiva solo tendrá un hilos, pero este usará la técnica de programación 
  no bloqueante mediante máquinas de estados y eventos.
* La aplicación interactiva solicita datos con el byte 2A.
* El microcontrolador le responde con un paquete compuestos de tres números 
  en punto flotante, un entero con signo de 32 bits más un checksum que se 
  calcula como en el reto 1. Por tanto, se estará transmitiendo un 
  paquete con un tamaño total de 17 bytes.
* Si el paquete llega correcto a la aplicación interactiva, esta responde 
  con el byte 3E, de lo contrario manda el byte B0 y el microcontrolador 
  deberá reenviar de nuevo el mismo paquete.
* Al tercer envía del byte B0 el microcontrolador ya no enviará el paquete sino que
  colocará un LED a prender y apagar a 1Hz para marcar el ERROR durante 3 segundos.
  Luego regresará a esperar por solicitud de datos, es decir, a esperar de 
  nuevo el 2A. Eso quiere decir que la aplicación interactiva tendrá que 
  renunciar al paquete y pedir uno nuevo.
* Usa little endian para las comunicaciones.
* La velocidad de comunicación entre las aplicaciones será de 115200.
* Para verificar el cálculo del checksum puedes utilizar 
  `este <https://www.scadacore.com/tools/programming-calculators/online-checksum-calculator/>`__ sitio.
* La aplicación interactiva simulará un escenario bueno con la tecla R. En este 
  escenario enviará el byte 2A, calculará el checksum, mostrará en pantalla si es 
  correcto y luego enviará el byte 3E.
* La aplicación interactiva simulará un escenario con errores mediante la tecla E. En 
  este caso solicitará datos con el byte 2A y luego enviará tres veces el byte B0 para 
  inducir el error en el microcontrolador. Finalmente volverá a esperar 
  la simulación de un nuevo escenario.




Criterios de calificación
****************************

* Prueba con la aplicación interactiva del profesor: 2.5
* Prueba con el microcontrolador del profesor: 2.5