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

.. warning:: FECHA MÁXIMA DE ENTREGA

    jueves 13 de octubre de 2022 (semana 13) en la segunda sesión de clase. La evaluación
    debe estar en el repositorio y sustentada.

Enunciado 
**************

Considera el siguiente fragmento de `este <https://youtu.be/KMhbV1p3MWk?t=16>`__ video que va desde el segundo 16 hasta el 34. 
También puede usar como referencia `este <https://youtu.be/L4WfHT_58Dg>`__ otro video.
Tu misión será reproducir lo que ves allí bajo estas restricciones:

#. Usa Unity.
#. Usa el sensor ADXL345 o MPU-6050 que puedes comprar `aquí <https://www.didacticaselectronicas.com/index.php/sensores/acelerometros-gyros/m%C3%B3dulo-gy-291-tarjetas-sensores-acelerometros-3-ejes-3-grados-3dof-3-dof-adxl345-detail>`__ 
   o `aquí <https://www.didacticaselectronicas.com/index.php/sensores/acelerometros-gyros/acelerometro-y-giroscopio-mpu-6050-mpu6050-tarjetas-sensores-acelerometros-giroscopios-de-6-ejes-imu-mpu6050-mpu-6050-detail>`__.
#. Debes usar un protocolo de comunicación BINARIO.


¿Qué debes entregar?
***********************

El código fuente de las aplicaciones para el microcontrolador y para Unity en 
`este <https://classroom.github.com/a/eWHjsSqp>`__ repositorio. Documentar 
en el archivo README.md cómo funciona el proceso de integración de los valores 
que entrega el sensor con el contenido digital de la aplicación interactiva.

Trayecto de Actividades
-------------------------

Ejercicios
*************

Ejercicio 1: introducción a los protocolos binarios - caso de estudio
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

¿Cómo se ve un protocolo binario? Para explorar este concepto te voy a 
mostrar una hoja de datos de un sensor comercial que usa un protocolo de 
comunicación binario. La idea es que explores tanto como quieras, pero 
te quiero invitar que mires con detenimiento hasta la página 5.

Para responder esta pregunta vamos a utilizar como ejemplo
`este sensor <http://www.chafon.com/productdetails.aspx?pid=382>`__.
Cuyo manual del fabricante se encuentra `aquí <https://drive.google.com/open?id=1uDtgNkUCknkj3iTkykwhthjLoTGJCcea>`__


Ejercicio 2: API de arduino para implementar comunicaciones binarias
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

En `este <https://www.arduino.cc/reference/en/language/functions/communication/serial/>`__ enlace
vas a mirar los siguientes métodos. Te pediré que los tengas a mano porque te servirán 
para resolver problemas.

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

Ejercicio 5: aplicación interactiva
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Te voy a pedir dos cosas en este punto:

* Que repases (de la unidad anterior o en la documentación de C# de Microsoft) 
  para qué sirven los siguientes fragmentos de código:


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

* Inventa una aplicación en Unity que utilice TODOS los métodos anteriores. Ten presente 
  que necesitarás inventar también la aplicación del microcontrolador.


Ejercicio 6: RETO
^^^^^^^^^^^^^^^^^^^

Vas a enviar 2 números en punto flotante desde un microcontrolador a una aplicación en Unity usando comunicaciones 
binarias. Inventa una aplicación en Unity que modifique dos dimensiones de una game object usando los valores 
recibidos.

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


