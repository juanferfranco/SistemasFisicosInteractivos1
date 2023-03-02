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

Evaluación
---------------------------

.. warning:: TODO 

  Regresa en unos días a esta sección (te prometo que no será muy larga
  la espera). PERO NO OLVIDES por favor que el trayecto de actividades 
  está alineado con la evaluación. ¿Qué quiere decir esto? Que los 
  ejercicios del trayecto te servirán para poder solucionar la evaluación 
  ya sea porque te explican un concepto o porque te dan herramientas 
  para corregir posibles errores que aparecerán en el proceso de solución 
  de la evaluación.

Trayecto de actividades
---------------------------

Ejercicios
***********

Ejercicio 1: comunicación computador-controlador
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

La idea de este ejercicio es comunicar a través del puerto serial
un computador con un controlador. La aplicación del computador 
la construirás usando una plataforma de creación de contenido digital interactivo llamada 
Unity 2021 LTS.

Estudia con detenimiento el código para el controlador y para el computador. Busca la definición 
de todas las funciones usadas en la documentación de Arduino y de Microsoft.

* ¿Quién debe comenzar primero, el computador o el controlador? ¿Por qué?

Programa el controlador con este código:

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
  usarás Visual Studio. Recuerda que este paso lo puedes hacer en el menú 
  Edit, Preferences, External Tools y seleccionar Visual Studio en la opción 
  External Script Editor.
* Configura un scripting backend que permita soportar las comunicaciones 
  seriales con el controlador. Ve al menú Edit, Project Settings, Player, 
  Other Settings, busca la opción Scripting backend y selecciona Mono, luego 
  busca API Compatibility Level y seleccionar .NET Framework.  

.. warning:: MUY IMPORTANTE

  Siempre que trabajes con comunicaciones seriales y Unity es necesario 
  seleccionar .NET Framework como el Scripting backend de lo contrario tendrás 
  un error de compilación relacionado con el puerto Serial.

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
* ¿Qué relación tienen las propiedades anteriores con el controlador?

Ejercicio 2: experimento
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. warning:: ESTE SEMESTRE CAMBIAMOS DE controlador

  Los videos que te mostraré utilizan un controlador y editor diferente para 
  escribir los programas de este. NO HAY PROBLEMA. Puedes usar el mismo 
  código para experimentar con el controlador que tienes ahora y con el IDE 
  de Arduino.

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

.. warning:: Ojo con el puerto serial

  Ten cuidado con el programa anterior. Nota esta línea:

    _serialPort.PortName = "/dev/ttyUSB0";
  
  En tu sistema operativo debes averiguar en qué puerto está el controlador 
  y cómo se llama. En Windows se usa COMx donde x es el número del puerto 
  serial asignado por el sistema operartivo a tu controlador.

Debe adicionar a la aplicación un elemento de GUI tipo Text - TextMeshPro y 
y luego arrastrar una referencia a este elemento a myText (si no sabes 
cómo hacerlo llama al profe).

Y la aplicación del controlador:

.. code-block:: cpp

  void setup() {
    Serial.begin(115200);
  }

  void loop() {
    if(Serial.available()){
      if(Serial.read() == '1'){
        delay(3000);
        Serial.print("Hello from Raspi");
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

Prueba con el siguiente código, luego ANALIZA CON DETENIMIENTO (no olvides) 
cambiar el puerto serial. 

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

Y si los mensajes que envía el controlador tienen tamaños diferentes ¿Cómo 
haces para saber que el mensaje enviado está completo o faltan 
bytes por recibir?

.. tip:: Piensa antes de continuar

  Por favor piensa antes de continuar; sin embargo, no te preocupes 
  porque te voy a contar en un momento qué puedes hacer para 
  responder las preguntas anteriores.

Ejercicio 3: eventos externos
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Nota que en los experimentos anteriores el PC primero le pregunta al 
controlador (le manda un ``1``) por datos. ¿Y si el PC no pregunta? Realiza 
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
Nota que esto mismo ocurre en el caso del programa del controlador con 
``Serial.available() > 0``.

¿Cómo podrías solucionar este problema?

.. tip:: PIENSA primero

   El siguiente ejercicio te servirá para responder esta pregunta.

Ejercicio 4: carácter de fin de mensaje
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Ahora vas a analizar cómo puedes resolver el problema anterior.

Analiza el siguiente programa del controlador:

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

Ejercicio 5: retrieval practice
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Con todo lo que has aprendido hasta ahora vas a volver a darle 
una mirada al material desde el ejercicio 1. Una iteración más. Pero 
la idea de este ejercicio es que le expliques a un compañero 
cada ejercicio. Y la misión de tu compañero será hacerte preguntas.

RETO: protocolo ASCII
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

El reto consiste en implementar un sistema que permita, mediante una 
interfaz gráfica en Unity interactuar con el controlador. La idea 
será que puedas leer el estado de una variable que estará 
cambiando en el controlador y cambiar el estado del LED verde del 
controlador. Ten presente que aunque este ejercicio usa 
un controlador simple, los conceptos asociados a su manejo pueden fácilmente 
extrapolarse a dispositivos y sistemas más complejos. 

Este reto está compuesto por dos partes: aplicación para el PC y aplicación para 
el controlador.

Aplicación para el PC:

* Debes gestionar las comunicaciones seriales y al mismo tiempo mostrar 
  un contenido digital dinámica que permita observar fácilmente caídas 
  en el framerate. Si quieres puedes usar la estrategia del contador que 
  se incremente en cada frame o cambiar por algo que te guste más.
* Implementa una interfaz de usuario compuesta por botones y cajas de texto 
  para controlar y visualizar.

Aplicación para el controlador:

* Programa un tarea que espere solicitudes de datos por parte de la aplicación 
  interactiva. Por favor, recuerda de los ejercicios del trayecto de actividades 
  cómo se hace esto.
* La tarea debe incrementar cada segundo un contador.
* La tarea debe poder modificar el estado del LED por solicitud de la aplicación 
  interactiva.

Protocolo de comunicación:

* El PC SIEMPRE inicia la comunicación solicitando información al 
  controlador. Es decir, desde la aplicación del PC siempre se solicita 
  información y el controlador responde.
* Desde el PC se enviarán tres solicitudes: ``read``, ``outON``, ``outOFF``.
* Para enviar los comandos anteriores usarás los botones 
  de la interfaz de usuario.
* El controlador enviará los siguientes mensajes de respuesta a cada solicitud:
  
  * Respuesta a ``read``: ``estadoContador,estadoLED``. Por ejemplo, una posible 
    respuesta será: ``235,OFF``. Quiere decir que el contador está en 235 y el LED 
    está apagado.
  * Respuesta a ``outON`` y ``outOFF``: ``estadoLED``. Es decir, el 
    controlador recibe el comando, realiza la orden solicitada y devuelve 
    el estado en el cual quedó el LED luego de la orden.
    
* No olvides que DEBES terminar TODOS los mensajes con el carácter NEWLINE (``\n``) para que 
  ambas partes sepan que el mensaje está completo.
