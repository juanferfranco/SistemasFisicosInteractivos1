Unidad 2. Protocolos ASCII
==========================================

Introducción 
-------------

En la unidad anterior te has concentrado en
la construcción de software para sistemas embebidos.
En esta unidad aprenderás como integrar a una plataforma
de cómputo interactiva dichos sistemas embebidos mediante
el uso de HILOS y protocolos de comunicación ASCII.

Propósitos de aprendizaje
*****************************

Construir aplicaciones interactivas utilizando múltiples hilos
para la producción y el prototipado de experiencias interactivas.

Integrar controladores con aplicaciones interactivas mediante
el uso de protocolos seriales ASCII.

Temas
********

* Repaso de tipos de dato valor y tipos referencia en C#.
* Concepto de hilo y programación básica.
* Conceptos básicos de sincronización de hilos.
* Introducción al concepto de máquina virtual y su uso
  en la plataforma interactiva Unity.
* Construcción de aplicaciones tipo consola que hagan uso del
  puerto serial.
* Protocolos de comunicación ASCII.

Trayecto de actividades
---------------------------

Sesión 1
***********

Ejercicio 1: repaso rápido de POO
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Piensa en las siguientes preguntas:

* ¿Cuál es la diferencia entre una clase y un objeto?

* Asume que dentro de un método tienes lo siguiente:

  .. code-block:: csharp 

    classType var= new classType()

  * ¿En qué parte de la memoria queda almacenada var?
  * ¿En qué parte de la memoria queda almacenado el objeto?
  * ¿Para qué sirve new?
  * ¿Para qué sirve el constructor de una clase?

Considera el siguiente código donde crearemos dos perros Huskies. 
Uno se llamará Pepe y el otro Tom. El color de los ojos de Pepe 
será azul. A Tom lo crearemos copiando a Pepe y luego le cambiaremos el 
color de los ojos a café.

Al ejecutar el código el resultado es:

.. code-block:: bash

    pepe has a brown color on his right eye, and a brown color on his left eye.                                                                                                            
    tom has a brown color on his right eye, and a brown color on his left eye.

* ¿Por qué ocurre esto?
* ¿Cómo podrías independizar los objetos?

.. code-block:: csharp

      using System;
        
      public class Eye
      {
          public string Color;
      }
  
      public class Husky
      {
          public string Name;
          public Eye RightEye;
          public Eye LeftEye;
            
          public Husky CopyHusky()
          {
              var newDog = new Husky {Name = Name, LeftEye = LeftEye, RightEye = RightEye};
              return newDog;
          }
  
          public string ToStringDog()
          {
                return String.Format("{0} has a {1} color on his right eye, and a {2} color on his left eye.", Name,RightEye.Color,LeftEye.Color);
          }
      }
  
      static class MainClass
      {
          public static void Main()
          {
              var pepe = new Husky {Name = "Pepe", LeftEye = new Eye(), RightEye = new Eye()};
              pepe.LeftEye.Color = pepe.RightEye.Color = "blue";
              
              var tom = pepe.CopyHusky();
              tom.Name = "Tom";
              tom.LeftEye.Color = tom.RightEye.Color = "brown";
              
              
              Console.WriteLine(pepe.ToStringDog());
              Console.WriteLine(tom.ToStringDog());
              Console.ReadKey();
      
          }
      }

Ejercicio 2: introducción al concepto de hilo
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Lee `este blog <http://www.albahari.com/threading/>`__ hasta la la sección que dice 
Join and Sleep y reproduce los ejemplos que están allí. Analiza con detenimiento cada
ejemplo.


Ejercicio 3: comunicación computador-controlador
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

La idea de este ejercicio es comunicar a través del puerto serial
un computador con un controlador, en este caso un ESP32. La aplicación del computador será tipo consola 
.NET framework.

Estudia con detenimiento el código para el controlador y para el computador. Busca la definición 
de todas las funciones usadas en la documentación de Arduino y de Microsoft.

* ¿Quién debe comenzar primero, el computador o el controlador? ¿Por qué?

Programa el arduino con este código:

.. code-block:: cpp

  void setup() {
    Serial.begin(115200);
  }

  void loop() {
    if(Serial.available()){
      if(Serial.read() == '1'){
        Serial.print("Hello from ESP32");
      }
    }
  }

Y este es el código para el computador:

.. code-block:: csharp
  
    using System;
    using System.IO.Ports;

    namespace hello_serialport{
        class Program{
            static void Main(string[] args)
            {
              SerialPort _serialPort = new SerialPort();
              // Allow the user to set the appropriate properties.
              _serialPort.PortName = "/dev/ttyUSB0";
              _serialPort.BaudRate = 115200;
              _serialPort.DtrEnable = true;
              _serialPort.Open();

              byte[] data = {0x31}; // or byte[] data = {'1'};
              _serialPort.Write(data,0,1);
              byte[] buffer = new byte[20];

              while(true){
                  if(_serialPort.BytesToRead > 0){
                      _serialPort.Read(buffer,0,20);
                      Console.WriteLine(System.Text.Encoding.ASCII.GetString(buffer));
                      Console.ReadKey();
                      _serialPort.Write(data,0,1);
                  }
              }
            }
        }
    }

Trabajo autónomo 1
*********************
(Tiempo estima: 1 horas 20 minutos)

Reproduce el ejercicio 3 y analiza con detenimiento su funcionamiento. Repite 
de memoria el ejercicio considerando que cada vez que el PC manda el carácter ``1`` 
el microcontrolador debe responder con la cadena ``Hello from ESP32``.


Sesión 2
************

Ejercicio 4: comunicación y operaciones de I/O bloqueantes en el computador
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Ahora programa tanto el controlador como el PC con los siguientes
códigos.

NO OLVIDES! analiza el código con detenimiento, entiéndelo por favor 
antes de ejecutarlo. Escribe qué hace el código, cómo se comunicarán ambos 
controladores. Luego ejecuta el código y compara tu hipótesis de funcionamiento 
con la ejecución. 

Este es el código para programar en el arduino:

.. code-block:: cpp

    void setup() {
      Serial.begin(115200);
    }

    void loop() {

      if(Serial.available()){
        if(Serial.read() == '1'){
          delay(1000);
          Serial.print("Hello from ESP32\n");
        }
      }
    }

Este es el código para programar el computador

.. code-block:: csharp

    using System;
    using System.IO.Ports;
    using System.Threading;

    namespace serialTestBlock
    {
    class Program{
            static void Main(string[] args)
            {
                SerialPort _serialPort = new SerialPort();
                _serialPort.PortName = "/dev/ttyUSB0";
                _serialPort.BaudRate = 115200;
                _serialPort.DtrEnable = true;
                _serialPort.Open();

                byte[] data = {0x31};
                byte[] buffer = new byte[20];
                int counter = 0;

                while(true){
                    if(Console.KeyAvailable == true){
                        Console.ReadKey(true);
                        _serialPort.Write(data,0,1);
                        string message = _serialPort.ReadLine();
                        Console.WriteLine(message);
                    }
                    Console.WriteLine(counter);
                    counter = (counter + 1) % 100;
                    Thread.Sleep(100);
                } 
            }   
        }
    }

* Conecta el controlador.
* Modifica el código del computador asignando el puerto
  serial correcto.
* Ejecuta el código del computador.
* Al presionar cualquier tecla qué pasa?

RETO 1: operaciones bloqueantes vs frame rate de la aplicación
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Te diste cuenta que al presionar una tecla, el conteo se detiene
un momento?

Al construir aplicaciones interactivas no te puedes dar este lujo.
Piensa en esto: ¿Y si en vez de imprimir un contador estás
renderizando una escena? Por tanto, las comunicaciones con el
controlador y el proceso de impresión del contador en la pantalla deben
ser dos flujos independientes, es decir, dos hilos.

Regresa al ejercicio 2 donde se introduce el uso de hilos. Ahora trata 
tu mismo de crear dos hilos. Uno para imprimir el valor del contador en 
pantalla a 10 fps (100 ms por frame) y otro hilo solo para manejar las 
comunicaciones seriales.

.. warning::
  Alerta de spoiler

  El siguiente código muestra una posible solución al reto

.. code-block:: csharp

    using System;
    using System.IO.Ports;
    using System.Threading;

    namespace SerialTest
    {
        class Program
        {
            static void Main(string[] args)
            {

                int counter = 0;

                Thread t = new Thread(readKeyboard);
                t.Start();

                while (true)
                {
                    Console.WriteLine(counter);
                    counter = (counter + 1) % 100;
                    Thread.Sleep(100);
                }
            }

            static void readKeyboard()
            {

                SerialPort _serialPort = new SerialPort(); ;
                _serialPort.PortName = "COM4";
                _serialPort.BaudRate = 115200;
                _serialPort.DtrEnable = true;
                _serialPort.Open();

                byte[] data = { 0x31 };

                while (true) {     
                    if (Console.KeyAvailable == true)
                    {
                        Console.ReadKey(true);
                        _serialPort.Write(data, 0, 1);
                        string message = _serialPort.ReadLine();
                        Console.WriteLine(message);
                    }
                }
            }
        }
    }

RETO 2: protocolo ASCII
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Este reto está compuesto de dos partes: aplicación para el PC y aplicación para 
el microcontrolador.

Aplicación para el PC:

* Debe tener dos hilos. Uno de los hilos se debe ejecutar a 10 frames por segundo imprimiendo 
  el valor de un contador que se incrementará cada 100 ms. El otro hilo se debe encargar de las comunicaciones seriales.

Aplicación para el microcontrolador:

La aplicación del microcontrolador debe tener dos tareas. La tarea uno debe encender 
y apagar un LED a una frecuencia de 1Hz. La segunda tarea debe enviar al PC el estado 
de un sensor digital (pulsador) y modificar una salida digital (LED) con la información 
recibida desde el PC.

Protocolo de comunicación:

* El PC SIEMPRE inicia la comunicación solicitando información al microcontrolador. Es decir, desde 
  la aplicación del PC siempre se solicita información y el microcontrolador responde.
* Desde el PC se enviarán tres solicitudes: ``read``, ``outON``, ``outOFF``.
* Para enviar los comandos anteriores se presionará en el PC las teclas r,i,o respectivamente.
* El framerate NO DEBE CAERSE al leer las teclas por tanto debes usar la técnica no 
  bloqueante de lectura del teclado usada en el ejercicio anterior.
* El microcontrolador enviará los siguientes mensajes de respuesta a cada solicitud:
  
  * Respuesta a ``read``: ``estadoPulsador,estadoLED``
  * Respuesta a ``outON`` y ``outOFF``: ``estadoSalida``. Es decir, el microcontrolador recibe el 
    el comando, realiza la orden solicitada y devuelve el estado en el cual quedó la salida 
    luego de la orden.
    
* No olvides que DEBES terminar TODOS los mensajes con el carácter NEWLINE (``\n``) para que 
  ambas partes sepan que el mensaje está completo.

.. warning:: ALERTA DE SPOILER

  Te dejo aquí una posible solución al problema.

El código del PC:

.. code-block:: csharp

    using System;
    using System.IO.Ports;
    using System.Threading;

    namespace un2_reto_ej4_2021_20
    {
        class Program
        {
            static void Main(string[] args)
            {
                int counter = 0;

                Thread t = new Thread(serialCom);
                t.Start();

                while (true)
                {
                    Console.WriteLine(counter);
                    counter = (counter + 1);
                    Thread.Sleep(100);
                }
            }

            static void serialCom()
            {
                SerialPort _serialPort = new SerialPort(); ;
                _serialPort.PortName = "/dev/ttyUSB0";
                _serialPort.BaudRate = 115200;
                _serialPort.DtrEnable = true;
                _serialPort.Open();

                while (true)
                {
                    if (Console.KeyAvailable == true)
                    {
                        ConsoleKeyInfo key;
                        key = Console.ReadKey(true);

                        if (key.Key == ConsoleKey.R)
                        {
                            _serialPort.WriteLine("read");
                            string message = _serialPort.ReadLine();
                            Console.WriteLine(message);
                            
                        }else if (key.Key == ConsoleKey.I)
                        {
                            _serialPort.WriteLine("outON");
                            string message = _serialPort.ReadLine();
                            Console.WriteLine(message);
                            
                        }else if (key.Key == ConsoleKey.O)
                        {
                            _serialPort.WriteLine("outOFF");
                            string message = _serialPort.ReadLine();
                            Console.WriteLine(message);
                        }
                    }
                }
            }
        }
    }


El código del microcontrolar:

.. code-block:: cpp

  #define DIGITAL_IN 32
  #define DIGITAL_OUT 25
  #define LED 14

  void setup() {

    Serial.begin(115200);
    pinMode(DIGITAL_IN, INPUT_PULLUP);
    digitalWrite(DIGITAL_OUT, true);
    pinMode(DIGITAL_OUT, OUTPUT);
    pinMode(LED, OUTPUT);
  }


  void Task1() {
    static uint32_t previousMillis = 0;
    const uint32_t interval = 500;
    static bool ledState = false;

    uint32_t currentMillis = millis();

    if ( (currentMillis - previousMillis) >= interval) {
      previousMillis = currentMillis;

      if (ledState == false) {
        ledState = true;
      } else {
        ledState = false;
      }
      digitalWrite(LED, ledState);
    }
  }

  void Task2() {
    static bool outState = false;

    
    if (Serial.available() > 0) {
      String dato = Serial.readStringUntil('\n');
      if(dato == "read"){
        Serial.print(digitalRead(DIGITAL_IN)); // se envía un 0 o un 1
        Serial.print(',');
        Serial.print(analogRead(ANALOG_IN));
        Serial.print(',');
        Serial.print(outState);
        Serial.print('\n');
              
      }else if(dato == "outOFF"){
        outState = false;
        digitalWrite(DIGITAL_OUT,!outState);
        Serial.print(outState);
        Serial.print('\n');
      }else if(dato == "outON"){
        outState = true;
        digitalWrite(DIGITAL_OUT,!outState);
        Serial.print(outState);
        Serial.print('\n');
      }
    }
  }

  void loop() {
    Task1();
    Task2();
  }

Trabajo autónomo 2
*********************
(Tiempo estima: 1 horas 20 minutos)

Estudia en detalle los dos retos anteriores. Entiende cómo funcionan. Una vez lo hagas,
vuelve a hacerlos pero esta vez de memoria, no veas la solución.


Evaluación de la unidad
--------------------------

.. warning:: REGRESA AQUÍ EN LA SEMANA 9

    No olvides presionar F5 para actualizar esta sección.

