Unidad 2. Protocolos ascii
==========================================

Introducción 
-------------

En la unidad anterior te has concentrado en
la construcción de software para sistemas embebidos.
En esta unidad aprenderás como integrar a una plataforma
de cómputo interactiva dichos sistemas embebidos mediante
el uso de HILOS y protocolos de comunicación ASCII.

Propósitos de aprendizaje
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Construir aplicaciones interactivas utilizando múltiples hilos
para la producción y el prototipado de experiencias interactivas.

Integrar controladores con aplicaciones interactivas mediante
el uso de protocolos seriales ascii.

Temas
^^^^^^

* Repaso de tipos de dato valor y tipos referencia en C#.
* Concepto de hilo y programación básica.
* Conceptos básicos de sincronización de hilos.
* Introducción al concepto de máquina virtual y su uso
  en la plataforma interactiva Unity.
* Construcción de aplicaciones tipo consola que hagan uso del
  puerto serial.
* Protocolos de comunicación ASCII.

Lecturas, ejercicios y proyecto
---------------------------------

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

Lectura 1: introducción al concepto de hilo
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Lee `este blog <http://www.albahari.com/threading/>`__ hasta la la sección que dice 
Join and Sleep y reproduce los ejemplos que están allí. Analiza con detenimiento cada
ejemplo.

Lectura 2: .NET code
^^^^^^^^^^^^^^^^^^^^^^^^

Hasta este punto del curso hemos utilizado .NET para la construcción de aplicaciones
interactivas. En este ejercicio te propongo que indagues un poco más sobre la plataforma
de software que estamos usando:

* `¿Qué es el .NET? <https://dotnettutorials.net/lesson/dotnet-framework/>`__
* `¿Qué es el CLR? <https://dotnettutorials.net/lesson/common-language-runtime-dotnet/>`__
* `¿Cómo se ejecuta un programa .NET? <https://dotnettutorials.net/lesson/dotnet-program-execution-process/>`__

Lectura 3: relación entre .NET y Unity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Al finalizar el curso estaremos utilizando el motor Unity para construir aplicaciones 
interactivas a las que se integren sensores y actuadores.

Profundiza un poco más sobre la relación entre .NET, código compilado y Unity:

* `IL2CPP <https://docs.unity3d.com/Manual/IL2CPP.html>`__
* `¿Cómo funciona IL2CPP <https://docs.unity3d.com/Manual/IL2CPP-HowItWorks.html>`__

Ejercicio 2: comunicación computador-controlador
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

La idea del ejercicio es comunicar a través del puerto serial
el computador con un controlador, en este caso un ESP32 o el arduino que tengas a la mano. 
En este punto ya no te sirve Tinkercad. La aplicación del computador será tipo consola 
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

Ejercicio 3: comunicación y operaciones de I/O bloqueantes en el computador
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Ahora programa tanto el controlador como el PC con los siguientes
códigos.

NO OLVIDES! analiza el código con detenimiento, entiéndelo por favor 
antes de ejecutarlo. Escribe qué hace el código, cómo se comunicarán ambos 
controladores. Realiza un diagrama de secuencia que muestre un escenario 
de prueba. Luego ejecuta el código y compara tu hipótesis de funcionamiento 
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

.. code-block:: cpp

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

RETO 2: protocolo ascii
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Este reto está compuesto de dos partes: aplicación para el PC y aplicación para 
el microcontrolador.

Aplicación para el PC:

* Debe tener dos hilos. Uno de los hilos se debe ejecutar a 10 frames por segundo imprimiendo 
  el valor de un contador de frames. El otro hilo se debe encargar de las comunicaciones seriales.

Aplicación para el microcontrolador:

La aplicación del microcontrolador debe tener dos tareas. La tarea uno debe encender 
y apagar un LED a una frecuencia de 1Hz. La segunda tarea debe enviar al PC el estado 
de un sensor digital, un sensor analógico y el estado de una de sus salidas.

Protocolo de comunicación:

* El PC SIEMPRE inicia la comunicación solicitando información al microcontrolador.
* Desde el PC se enviarán tres posible comandos: ``"read"``, ``"outON"``, ``"outOFF"``.
* Para enviar los comandos anteriores se presionará en el PC las teclas r,i,o respectivamente.
* El framerate NO DEBE CAERSE al leer las teclas por tanto debes usar la técnica no 
  bloqueante de lectura del teclado usada en el ejercicio anterior.
* El microcontrolador enviará los siguientes mensajes de respuesta a cada comando:
  
  * Respuesta a ``"read"``: ``"valorSensorDigital,valorSensorAnalógico,estadoSalida"``
  * Respuesta a ``"outON"`` y ``"outOFF"``: ``estadoSalida``. Es decir, el microcontrolador recibe el 
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

  #define DIGITAL_IN 19
  #define ANALOG_IN 34
  #define DIGITAL_OUT 5
  #define LED 18

  void setup() {

    Serial.begin(115200);
    pinMode(DIGITAL_IN, INPUT_PULLUP);
    digitalWrite(DIGITAL_OUT, true);
    pinMode(DIGITAL_OUT, OUTPUT);
    
    pinMode(LED, OUTPUT);
    analogReadResolution(10);
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

Proyecto evaluativo de la unidad 2
-------------------------------------

Esta evaluación la puedes realizar con otro compañero o de manera individual si no 
encuentras con quién trabajar.

¿Qué debes hacer?
^^^^^^^^^^^^^^^^^^

Para esta evaluación te voy a proponer que realices una modificación a una aplicación 
interactiva desarrollada por Zachary Patten a la cual le hice unas pequeñas modificación.

El reto consiste en controlar el personaje de la aplicación usando 4 sensores digitales.

* En `este <https://github.com/juanferfranco/dotnet-console-games/tree/main/Projects/Snake>`__ 
  enlace vas a encontrar dos archivos: Program.cs y arduinoKeyboard.ino que serán los archivos 
  sobre los cuales realizarás tu trabajo, uno para el PC y el otro para el arduino respectivamente.
* Vas a definir un protocolo ASCII con el cual ambas aplicaciones se comunicarán.
* La aplicación del PC SIEMPRE deberá solicitar primero la información que necesite del microcontrolador.
* El microcontrolador tendrá conectados los 4 sensores digitales (pulsadores), leerá su estado 
  y reportará dicho estado a la aplicación del PC una vez este se lo solicite.

Al final se verá algo como `esto <https://youtu.be/hR9nPCNaFIk>`__.

¿Cómo vas a entregar la evaluación?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

La evaluación consta de dos partes:

#. Vas a explicar con tus propias palabras cómo funciona el ejercicios 4: RETO protocolos ASCII. 
   Debes grabar un video con una duración máxima de 5 minutos. 
#. Vas a realizar el RETO propuesto. Debes grabar un video con una duración máxima de 5 minutos, donde 
   expliques cómo solucionaste la aplicación del PC y la del microcontrolador. Finalmente, 
   `muestra las aplicaciones funcionando <https://youtu.be/hR9nPCNaFIk>`__ 
   de manera conjunta, es decir, en la misma pantalla, la aplicación interactiva y el accionamiento 
   de los sensores. 

Sube a `este <https://www.dropbox.com/request/MpzVuXWbHnH0ecJPWO11>`__ enlace un .pdf con 
los nombres y ID de los miembros del equipo de trabajo y las dos URLs de los videos de youtube 
solicitados. NO OLVIDES, POR FAVOR, 5 minutos MÁXIMO cada video. Recuerda que puedes trabajar 
solo si así lo deseas

Criterios de evaluación
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#. Parte 1: 2 unidades.
#. Parte 2: 3 unidades.