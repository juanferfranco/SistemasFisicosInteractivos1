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

Ejercicio 4: comunicación entre hilos
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. note:: MATERIAL EN CONSTRUCCIÓN.

    Vuelve a unos días a este ejercicio y presiona F5 para que sea cargado.


RETO 2: comunicación entre hilos
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. note:: MATERIAL EN CONSTRUCCIÓN.

    Vuelve a unos días a este RETO y presiona F5 para que sea cargado.

Lectura 4: protocolos ASCII
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. note:: MATERIAL EN CONSTRUCCIÓN.

    Vuelve a unos días a este aquí y presiona F5 para que sea cargado.

Ejercicio 5: protocolos ASCII
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    
.. note:: MATERIAL EN CONSTRUCCIÓN.

    Vuelve a unos días a este aquí y presiona F5 para que sea cargado.

Proyecto evaluativo de la unidad 2
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. warning:: REGRESA AQUÍ EN LA SEMANA DE EVALUACIÓN

    No olvides presionar F5 para cargar de nuevo la paǵina con la evaluación 
    en la semana correspondiente.

..
    Debes realizar un sistema interactivo compuesto por una aplicación en el PC y
    un controlador al cual se conectan varios sensores y actuadores.

    Para el controlador tienes:

    * Dos sensores digitales
    * Dos sensores analógicos: valores de 0 a 1023
    * Dos actuadores digitales.
    * Dos actuadores analógicos (pwm)

    El controlador se conecta a un computador a través del puerto USB y se comunica 
    utilizando la interfaz Serial.

    Realiza un programa, para le controlador, que haga las siguientes tareas 
    concurrentes:

    * Recibir comandos a través de la interfaz Serial
    * Enciende y apaga un LED a una frecuencia de 10 Hz
    * Enciende y apaga un LED a una frecuencia de 5 Hz.

    Los comandos recibidos por el puerto serial serán los siguientes:

    * read D1. Este comando hace que se envíe al PC el valor del sensor digital 1. 
      El controlador devuelve la cadena:  D1 estado. Donde estado puede ser 1 o 0.

    * read D2: enviar al PC el valor del sensor digital 2.  
      El controlador devuelve la cadena: D2 estado. Donde estado puede ser 1 o 0.

    * read A1: enviar el PC el valor del sensor analógico 1.  
      El controlador devuelve la cadena A1 valor. Donde valor está entre 0 y 1023.

    * read A2: enviar el PC el valor del sensor analógico 2. 
      El controlador devuelve la cadena A2 valor. Donde valor está entre 0 y 1023.

    * write O1 estado: donde estado puede ser 1 o 0. 
      Activa o desactiva la salida digital 1 

    * write O2 estado: donde estado puede ser 1 o 0. 
      Activa o desactiva la salida digital 2 

    * write P1 valor: donde valor puede ser de 0 a 255. 
      Escribir un valor de PWM igual a valor en el actuador analógico 1. 

    * write P2 valor: donde valor puede ser de 0 a 255. 
      Escribir un valor de PWM igual a valor en el actuador analógico 2.

    La aplicación interactiva en el PC es tipo consola en C# y debe tener:

    * Dos hilos.
    * Un hilo debe imprimir cada 100 ms el valor de un contador.
    * El otro hilo estará atento a los eventos del teclado producidos por el usuario.
    * Asigne una tecla a cada comando que será enviado al controlador.
    * Indicar si el controlador entendió o no entendió el comando, es decir,
      mostrar el NACK o el ACK (abajo la explicación de esto)

    .. note::

      Para cualquiera de los comandos tipo write el controlador debe devolver los caraceres
      ACK si reconoce el comando y NACK si no los reconoce. 

      Debes decidir, dados los requisitos
      de la aplicación, si requieres introducir caracteres de nueva línea y/o retorno de carro. 
      TEN PRESENTE que LOS LEDs deben funcionar SIEMPRE a 5 Hz y 10 HZ como se declaró previamente, 
      ese decir, su funcionamiento no puede ser interrumpido por las operaciones del puerto serial
