Unidad 2. Protocolos ASCII
==========================================

Introducción 
-------------

En la unidad anterior te has concentrado en
la construcción de software para sistemas embebidos.
En esta unidad aprenderás como integrar a una plataforma
de cómputo interactiva dichos sistemas embebidos mediante
el uso de protocolos de comunicación ASCII.

Propósitos de aprendizaje
*****************************

Construir aplicaciones interactivas que integren información 
del mundo exterior mediante el intercambio de información 
codificada en ASCII.

Temas
********

* Repaso rápido de algunos concepto de la programación orientada 
  a objetos.
* Técnicas de programación del lado del embebidos y el PC.
* Construcción de aplicaciones interactivas en el computador.

Trayecto de actividades
---------------------------

Ejercicios
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

.. warning:: ALERTA DE SPOLIER

    Una posible solución al problema de una mala clonación de perritos.

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

Ejercicio 2: comunicación computador-controlador
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

La idea de este ejercicio es comunicar a través del puerto serial
un computador con un controlador, en este caso un ESP32. La aplicación del computador 
la construirás usando una plataforma de creación de contenido digital interactivo llamada 
Unity 2021 LTS.

Estudia con detenimiento el código para el controlador y para el computador. Busca la definición 
de todas las funciones usadas en la documentación de Arduino y de Microsoft.

* ¿Quién debe comenzar primero, el computador o el controlador? ¿Por qué?

Programa el ESP32 con este código:

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

Prueba la aplicación con ScriptCommunicator. ¿Cómo funciona?

Ahora crea un proyecto en Unity 2021 LTS. Antes de continuar 
con la escritura del código configura:

* La herramienta que usarás para editar tus programas. En este caso 
  usarás Rider. Recuerda que este paso lo puedes hacer en el menú 
  Edit, Preferences, External Tools y seleccionar Rider en la opción 
  External Script Editor. Si estás trabajando en Windows puedes seleccionar 
  Visual Studio.
* Configura un scripting backend que permita soportar las comunicaciones 
  seriales con el controlador. Ve al menú Edit, Project Settings, Player, 
  Other Settings, busca la opción Scripting backend y selecciona Mono, luego 
  busca API Compatibility Level y seleccionar .NET Framework.  

Crea un nuevo C# Script y un Game Object. Añade el Script al GameObject. 
Ve al menu Assets y luego selecciona Open C# Project. 

.. code-block:: csharp
  
    using UnityEngine;
    using System.IO.Ports;
    public class Serial : MonoBehaviour
    {
        private SerialPort _serialPort = new SerialPort();
        private byte[] buffer = new byte[32];

        void Start()
        {
            _serialPort.PortName = "/dev/ttyUSB0";
            _serialPort.BaudRate = 115200;
            _serialPort.DtrEnable = true;
            _serialPort.Open();
            Debug.Log("Open Serial Port");
        }

        void Update()
        {

            if (Input.GetKeyDown(KeyCode.A))
            {
                byte[] data = {0x31}; // or byte[] data = {'1'};
                _serialPort.Write(data,0,1);
                Debug.Log("Send Data");
            }

            if (Input.GetKeyDown(KeyCode.B))
            {
                if (_serialPort.BytesToRead >= 16)
                {
                    _serialPort.Read(buffer, 0, 20);
                    Debug.Log("Receive Data");
                    Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
                }
            }

        }
    }

Analiza:

* ¿Por qué es importante considerar las propiedades PortName y BaudRate?
* ¿Qué relación tienen las propiedades anteriores con el ESP32?

Ejercicio 3: experimento
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
(Si quires ver antes unos videos cortos donde te explico
un poco más el ejercicio te dejo 
`este <https://youtube.com/playlist?list=PLX4ZVWZsOgzST9kfU9_ohOUYp_oDo2z48>`__ link).

Ahora realiza este experimento. Modifica la aplicación del PC así:

.. code-block:: csharp

    using UnityEngine;
    using System.IO.Ports;
    using TMPro;

    public class Serial : MonoBehaviour
    {
        private SerialPort _serialPort = new SerialPort();
        private byte[] buffer = new byte[32];

        public TextMeshProUGUI myText;

        private static int counter = 0;
        
        void Start()
        {
            _serialPort.PortName = "/dev/ttyUSB0";
            _serialPort.BaudRate = 115200;
            _serialPort.DtrEnable = true;
            _serialPort.Open();
            Debug.Log("Open Serial Port");
        }

        void Update()
        {
            myText.text = counter.ToString();
            counter++;
            
            if (Input.GetKeyDown(KeyCode.A))
            {
                byte[] data = {0x31}; // or byte[] data = {'1'};
                _serialPort.Write(data,0,1);
                int numData = _serialPort.Read(buffer, 0, 20);
                Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
                Debug.Log("Bytes received: " + numData.ToString());
            }
        }
    }

Debe adicionar a la aplicación un elemento de GUI tipo Text - TextMeshPro y 
y luego arrastrar una referencia a este elemento a myText (si no sabes 
cómo hacerlo llama al profe).

Y la aplicación del ESP32:

.. code-block:: cpp

  void setup() {
    Serial.begin(115200);
  }

  void loop() {
    if(Serial.available()){
      if(Serial.read() == '1'){
        delay(3000);
        Serial.print("Hello from ESP32");
      }
    }
  }

Ejecuta la aplicación en Unity. Verás un número cambiar rápidamente 
en pantalla. Ahora presiona la tecla A (no olvides dar click en 
la pantalla Game). ¿Qué pasa? ¿Por qué crees que ocurra esto?

.. tip:: MUY IMPORTANTE

    ¿Viste entonces que la aplicación se bloquea? Este comportamiento 
    es inaceptable para una aplicación interactiva de tiempo real.

¿Cómo podemos corregir el comportamiento anterior?

Prueba con el siguiente código, luego ANALIZA CON DETENIMIENTO.

.. code-block:: csharp

    using UnityEngine;
    using System.IO.Ports;
    using TMPro;

    public class Serial : MonoBehaviour
    {
        private SerialPort _serialPort = new SerialPort();
        private byte[] buffer = new byte[32];

        public TextMeshProUGUI myText;

        private static int counter = 0;
        
        void Start()
        {
            _serialPort.PortName = "/dev/ttyUSB0";
            _serialPort.BaudRate = 115200;
            _serialPort.DtrEnable = true;
            _serialPort.Open();
            Debug.Log("Open Serial Port");
        }

        void Update()
        {
            myText.text = counter.ToString();
            counter++;
            
            if (Input.GetKeyDown(KeyCode.A))
            {
                byte[] data = {0x31}; // or byte[] data = {'1'};
                _serialPort.Write(data,0,1);
            }

            if (_serialPort.BytesToRead > 0)
            {
                int numData = _serialPort.Read(buffer, 0, 20);
                Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
                Debug.Log("Bytes received: " + numData.ToString());
            }
        }
    }

¿Funciona? ¿Qué pasaría si al momento de ejecutar la instrucción 
``int numData = _serialPort.Read(buffer, 0, 20);`` solo han llegado 
10 de los 16 bytes del mensaje? ¿Cómo puede hacer tu programa para 
saber que ya tiene el mensaje completo?

¿Cómo podrías garantizar que antes de hacer la operación Read tengas 
los 16 bytes listos para ser leídos?

Y si los mensajes que envía el ESP32 tienen tamaños diferentes ¿Cómo 
haces para saber que el mensaje enviado está completo o faltan 
bytes por recibir?

Ejercicio 4: eventos externos
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Nota que en los experimentos anteriores el PC primero le pregunta al 
ESP32 (le manda un ``1``) por datos. ¿Y si el PC no pregunta? Realiza 
el siguiente experimento. Programa ambos códigos y analiza su funcionamiento.

.. code-block:: cpp

    void task()
    {
      enum class TaskStates
      {
        INIT,
        WAIT_INIT,
        SEND_EVENT
      };
      static TaskStates taskState = TaskStates::INIT;
      static uint32_t previous = 0;
      static u_int32_t counter = 0;

      switch (taskState)
      {
      case TaskStates::INIT:
      {
        Serial.begin(115200);
        taskState = TaskStates::WAIT_INIT;
        break;
      }
      case TaskStates::WAIT_INIT:
      {
        if (Serial.available() > 0)
        {
          if (Serial.read() == '1')
          {
            previous = 0; // Force to send the first value immediately
            taskState = TaskStates::SEND_EVENT;
          }
        }
        break;
      }
      case TaskStates::SEND_EVENT:
      {
        uint32_t current = millis();
        if ((current - previous) > 2000)
        {
          previous = current;
          Serial.print(counter);
          counter++;
        }

        if (Serial.available() > 0)
        {
          if (Serial.read() == '2')
          {
            taskState = TaskStates::WAIT_INIT;
          }
        }

        break;
      }
      default:
      {
        break;
      }
      }
    }

    void setup()
    {
      task();
    }

    void loop()
    {
      task();
    }

.. code-block:: csharp

    using UnityEngine;
    using System.IO.Ports;
    using TMPro;

    enum TaskState
    {
        INIT,
        WAIT_START,
        WAIT_EVENTS
    }

    public class Serial : MonoBehaviour
    {
        private static TaskState taskState = TaskState.INIT;
        private SerialPort _serialPort;
        private byte[] buffer;
        public TextMeshProUGUI myText;
        private int counter = 0;
        
        void Start()
        {
            _serialPort = new SerialPort();
            _serialPort.PortName = "/dev/ttyUSB0";
            _serialPort.BaudRate = 115200;
            _serialPort.DtrEnable = true;
            _serialPort.Open();
            Debug.Log("Open Serial Port");
            buffer = new byte[128];
        }

        void Update()
        {
            myText.text = counter.ToString();
            counter++;
            
            switch (taskState)
            {
                case TaskState.INIT:
                    taskState = TaskState.WAIT_START;
                    Debug.Log("WAIT START");
                    break;
                case TaskState.WAIT_START:
                    if (Input.GetKeyDown(KeyCode.A))
                    {
                        byte[] data = {0x31}; // start
                        _serialPort.Write(data,0,1);
                        Debug.Log("WAIT EVENTS");
                        taskState = TaskState.WAIT_EVENTS;
                    }
                    
                    break;
                case TaskState.WAIT_EVENTS:
                    if (Input.GetKeyDown(KeyCode.B))
                    {
                        byte[] data = {0x32}; // stop
                        _serialPort.Write(data,0,1);
                        Debug.Log("WAIT START");
                        taskState = TaskState.WAIT_START;
                    }
            
                    if (_serialPort.BytesToRead > 0)
                    {
                        int numData = _serialPort.Read(buffer, 0, 128);
                        Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
                    }
                    break;
                default:
                    Debug.Log("State Error");
                    break;
            }
        }
    }

¿Recuerdas las preguntas del otro experimento? Aquí nos pasa lo mismo.
Analicemos el asunto. Cuando preguntas ``_serialPort.BytesToRead > 0`` lo 
que puedes asegurar es que al MENOS tienes un byte del mensaje, pero 
no puedes saber si tienes todos los bytes que lo componen. Una idea 
para resolver esto sería hacer que todos los mensajes tengan el mismo 
tamaño. De esta manera solo tendrías que preguntar 
``_serialPort.BytesToRead > SIZE``, donde SIZE sería el tamaño fijo; sin 
embargo, esto le resta flexibilidad al protocolo de comunicación. 
Nota que esto mismo ocurre en el caso del programa del ESP32 con 
``Serial.available() > 0``.

¿Cómo podrías solucionar este problema?

Ejercicio 5: carácter de fin de mensaje
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Ahora vas a analizar cómo puedes resolver el problema anterior.

Analiza el siguiente programa del ESP32:

.. code-block:: cpp

    String btnState(uint8_t btnState){
      if(btnState == HIGH){
        return "OFF";
      }
      else return "ON";
    }

    void task()
    {
      enum class TaskStates
      {
        INIT,
        WAIT_COMMANDS
      };
      static TaskStates taskState = TaskStates::INIT;
      constexpr uint8_t led = 25;
      constexpr uint8_t button1Pin = 12;
      constexpr uint8_t button2Pin = 13;
      constexpr uint8_t button3Pin = 32;
      constexpr uint8_t button4Pin = 33;

      switch (taskState)
      {
      case TaskStates::INIT:
      {
        Serial.begin(115200);
        pinMode(led, OUTPUT);
        digitalWrite(led, LOW);
        pinMode(button1Pin, INPUT_PULLUP);
        pinMode(button2Pin, INPUT_PULLUP);
        pinMode(button3Pin, INPUT_PULLUP);
        pinMode(button4Pin, INPUT_PULLUP);
        taskState = TaskStates::WAIT_COMMANDS;
        break;
      }
      case TaskStates::WAIT_COMMANDS:
      {
        if (Serial.available() > 0)
        {
          String command = Serial.readStringUntil('\n');
          if (command == "ledON")
          {
            digitalWrite(led, HIGH);
          }
          else if (command == "ledOFF")
          {
            digitalWrite(led, LOW);
          }
          else if (command == "readBUTTONS")
          {
            
            Serial.print("btn1: ");
            Serial.print(btnState(digitalRead(button1Pin)).c_str());
            Serial.print(" btn2: ");
            Serial.print(btnState(digitalRead(button2Pin)).c_str());
            Serial.print(" btn3: ");
            Serial.print(btnState(digitalRead(button3Pin)).c_str());
            Serial.print(" btn4: ");
            Serial.print(btnState(digitalRead(button4Pin)).c_str());
            Serial.print('\n');
          }
        }
        break;
      }
      default:
      {
        break;
      }
      }
    }

    void setup()
    {
      task();
    }

    void loop()
    {
      task();
    }

Analiza el siguiente programa del PC:

.. code-block:: csharp

    using UnityEngine;
    using System.IO.Ports;
    using TMPro;

    enum TaskState
    {
        INIT,
        WAIT_COMMANDS
    }

    public class Serial : MonoBehaviour
    {
        private static TaskState taskState = TaskState.INIT;
        private SerialPort _serialPort;
        private byte[] buffer;
        public TextMeshProUGUI myText;
        private int counter = 0;
        
        void Start()
        {
            _serialPort = new SerialPort();
            _serialPort.PortName = "/dev/ttyUSB0";
            _serialPort.BaudRate = 115200;
            _serialPort.DtrEnable = true;
            _serialPort.NewLine = "\n";
            _serialPort.Open();
            Debug.Log("Open Serial Port");
            buffer = new byte[128];
        }

        void Update()
        {
            myText.text = counter.ToString();
            counter++;
            
            switch (taskState)
            {
                case TaskState.INIT:
                    taskState = TaskState.WAIT_COMMANDS;
                    Debug.Log("WAIT COMMANDS");
                    break;
                case TaskState.WAIT_COMMANDS:
                    if (Input.GetKeyDown(KeyCode.A))
                    {
                        _serialPort.Write("ledON\n");
                        Debug.Log("Send ledON");
                    }
                    if (Input.GetKeyDown(KeyCode.S))
                    {
                        _serialPort.Write("ledOFF\n");
                        Debug.Log("Send ledOFF");
                    }

                    if (Input.GetKeyDown(KeyCode.R))
                    {
                        _serialPort.Write("readBUTTONS\n");
                        Debug.Log("Send readBUTTONS");
                        
                    }
                    if (_serialPort.BytesToRead > 0)
                    {
                        string response = _serialPort.ReadLine(); 
                        Debug.Log(response);
                    }
                    
                    break;
                default:
                    Debug.Log("State Error");
                    break;
            }
        }
    }

Ejercicio 6: retrieval practice
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Con todo lo que has aprendido hasta ahora vas a volver a darle 
una mirada al material desde el ejercicio 1. Una iteración más. Pero 
la idea de este ejercicio es que le expliques a un compañero 
cada ejercicio. Y la misión de tu compañero será hacerte preguntas.


RETO 1: protocolo ASCII
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

El reto consiste es implementar un sistema que permita, mediante una 
interfaz gráfica, leer y modificar el estado de unos dispositivos externos 
a una aplicación interactiva. En este caso los dispositivos serán 
un pulsador y un LED. Ten presente que aunque este ejercicio usa 
dispositivos simples los conceptos asociados a su manejo pueden fácilmente 
extrapolarse a dispositivos y sistemas más complejos. 

Este reto está compuesto de dos partes: aplicación para el PC y aplicación para 
el microcontrolador.

Aplicación para el PC:

* Debes gestionar las comunicaciones seriales y al mismo tiempo mostrar 
  un contenido digital dinámica que permita observar fácilmente caídas 
  en el framerate. Si quieres puedes usar la estrategia del contador que 
  se incremente en cada frame o cambiar por algo que te guste más.
* Implementa una interfaz de usuario compuesta de botones y cajas de texto 
  para controlar y visualizar.

Aplicación para el microcontrolador:

La aplicación del microcontrolador debe tener dos tareas. La tarea uno 
debe encender y apagar un LED a una frecuencia de 1Hz. La segunda tarea 
debe enviar al PC el estado de un sensor digital (pulsador) y modificar 
una salida digital (LED) con la información recibida desde el PC.

Protocolo de comunicación:

* El PC SIEMPRE inicia la comunicación solicitando información al 
  microcontrolador. Es decir, desde la aplicación del PC siempre se solicita 
  información y el microcontrolador responde.
* Desde el PC se enviarán tres solicitudes: ``read``, ``outON``, ``outOFF``.
* Para enviar los comandos anteriores usarás los botones 
  de la interfaz de usuario.
* El microcontrolador enviará los siguientes mensajes de respuesta a cada solicitud:
  
  * Respuesta a ``read``: ``estadoEntrada,estadoSalida``. Donde estadoEntrada y 
    estadoSalida serán 0 o 1 dependiendo del estado del sensor digital y el estado 
    actual de la salida.
  * Respuesta a ``outON`` y ``outOFF``: ``estadoSalida``. Es decir, el 
    microcontrolador recibe el comando, realiza la orden solicitada y devuelve 
    el estado en el cual quedó la salida luego de la orden.
    
* No olvides que DEBES terminar TODOS los mensajes con el carácter NEWLINE (``\n``) para que 
  ambas partes sepan que el mensaje está completo.

..
  Evaluación de la unidad
  --------------------------

  .. warning:: FECHA MÁXIMA DE ENTREGA

      Martes 22 de marzo a las 11:59 p.m.

  .. warning:: MONTAJE

      En el archivo de sensores.ino te entregaré un template con la definición de NOMBRE
      de los puertos y PUERTOS. NO lo modifiques, si llegas a hacerlo hay una penalidad 
      de 1 unidad en la nota final.

  Enunciado 
  **************

  Debes modificar una aplicación interactiva para permitir que se controle de dos maneras.
  La forma uno es usando el teclado con las teclas flecha arriba,
  abajo, izquierda y derecha. Dicha forma ya está implementada. La forma 2 con 4 pulsadores 
  externos que serán leídos por un microcontrolador. Tu debes implementar esta segunda forma de modo 
  que ambas formas puedan convivir en la aplicación. DEBES adicionar un pulsador más a tu montaje.  
  La aplicación que debes modificar es de autoría de `Zachary Patten <https://github.com/ZacharyPatten/dotnet-console-games>`__, 
  pero le hice unas cuantas modificaciones.

  ¿Cómo es el protocolo ASCII de comunicación?

  La aplicación interactiva debe enviar el request ``inputs``. 
  El microcontrolador responde con el estado de cada pulsador 
  separado por ``,`` y en este orden: 
  ``estado_UP,estado_DOWN,estado_LEFT,estado_RIGHT``. Estos son 
  ejemplos de posibles respuestas:

  * ``1,1,1,1\n`` todos los sensores están relajados.
  * ``1,1,1,0\n`` todos los sensores están relajados menos RIGHT

  ¿Que debes hacer?
  *******************

  #. Clona tu repositorio que está `aquí <https://classroom.github.com/a/umNREJE_>`__.
  #. Modifica SOLO los archivos Program.cs y sensores.ino
  #. Realiza commits y push frecuentemente.

