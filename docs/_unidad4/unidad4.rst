Unidad 4. Plataformas de software interactivas de tiempo real
===================================================================

Introducción 
-------------

Llegaste al final del curso. En esta unidad aplicarás todos los conceptos que has 
aprendido para la construcción de aplicaciones interactivas que integren sistemas 
embebidos con plataformas de cómputo interactivas. 

Propósitos de aprendizaje
****************************

Aplicar los conceptos y procedimientos aprendidos en el curso para resolver un problema 
que requiera la integración de una plataforma de tiempo real con un sistema microcontrolado.


Evaluación de la Unidad 4
---------------------------

.. warning:: FECHA MÁXIMA DE ENTREGA

    Recuerda que el curso termina en la última sesión de la semana 16.


Enunciado
***********

Acabas de llegar a un nuevo estudio que desarrolla EXPERIENCIAS INTERACTIVAS y te encargan 
que DISEÑES e IMPLEMENTES una EXPERIENCIA INTERACTIVA que combine un desarrollo anterior (unidad 3) 
con algunos de los conceptos implementados en un plugin llamado 
`Ardity <https://github.com/DWilches/Ardity>`__. Mira, el equipo de desarrollo del estudio simplemente 
quiere mejorar el proyecto anterior pero sin depender de un plugin de un 
tercero. Tu misión será entonces entender los conceptos del plugin y transferirlos al desarrollo 
de la unidad 3. En particular deberás realizar un refactoring del proyecto de la unidad 3 así:


* El código que maneja el puerto serial debe estar en su propio Thread o hilo.
* El thread del serial debe comunicarse con el thread del motor utilizando una queue. 
  Debes garantizar acceso único a la queue a cada thread para evitar posibles 
  ``condiciones de carrera``.
* Debes gestionar excepciones: abrir un puerto serial que no esta disponible, el cable 
  serial se desconectó.
* La aplicación debe recuperarse de una excepción y volver a funcionar una vez se restablezcan 
  las condiciones. Esto debe ocurrir sin necesidad de reiniciarla.
* La mayor parte de código de manejo del puerto serial debe estar en una clase abstracta. Utiliza 
  una clase para implementar los métodos para enviar y recibir el mensaje serial tal como 
  lo muestra Ardity con los métodos SendToWire y ReadFromWire.

¿Qué debes entregar?
***********************

* Vas a realizar tu entrega en `este <https://classroom.github.com/a/rOd7jm0I>`__ repositorio.
* Sigue los pasos de la unidad anterior para entregar tu proyecto de Unity.
* Ahora crea el archivo README.md en el repositorio y escribe allí para la 
  aplicación de Arduino: 

    #. ¿Cuáles son los estados y por qué definiste esos estados?
    #. ¿Cuáles son los eventos y por qué definiste esos eventos?

  Para la aplicación en Unity:

    #. Muestra y explica cómo usaste el concepto de Thread
    #. Muestra y explica cómo usaste el concepto de Queue o cola.
    #. Muestra y explica cómo usaste la gestión de excepciones.

* Incluye un enlace a un video de Youtube donde muestres la aplicación funcionando. 
  RECUERDA que es un enlace, NO el video.


Trayecto de actividades
-------------------------

Ejercicios
*************

Ejercicio 1: caso de estudio-plugin Ardity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Lo primero que te propondré es que pongas a funcionar el demo del plugin. Todo lo relacionado 
con el plugin estará en `este <https://github.com/DWilches/Ardity>`__ repositorio. 
Comienza leyendo el archivo README.md.

Cuando te sientas listo para comenzar a experimentar ten presente que la versión de Unity 
con la cual se realizó el proyecto fue la 2018.2. Tu estás usando la versión 2021 LTS. Abre 
el proyecto con tu versión de Unity.

¿Por dónde comienzo? Ve a la carpeta Scenes y comienza a analizar cada una de las escenas 
DemoScene. Son en total 5. En uno de los ejercicios que vienen vamos a analizar juntos la scene 
DemoScene_UserPoll_ReadWrite. Tu debes decidir luego cuál scene se podría ajustar mejor 
a tu encargo y tratar de analizarla a fondo tal como lo haremos a continuación.

.. warning:: TE DIGO ALGO PARA QUE NO TE FRUSTRES

    Mira, esta unidad toma tiempo. Entre más frescos e interiorizados tengas los conceptos 
    de este curso y del curso de programación orientada a objetos más rápido podrás realizar 
    el análisis. Piensa en esta unidad como la oportunidad de realizar un ejercicio 
    de retrieval practice y aclarar con la ayuda de tu profesor algunos vacíos conceptuales 
    que aún tengas. Quiero insistir con algo. Esta unidad no es trivial, tendrás que analizar 
    a fondo y ser autocrítico.

Ejercicio 2: concepto de hilo
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Observa y analiza `este <https://youtu.be/5wpSidCEJn4>`__ video donde te explicarán rápidamente 
el concepto de hilo.

Te voy a pedir que veas `este <https://youtu.be/nv1NUR-qjcU>`__ video corto de 15 minutos donde 
verás aplicado el concepto de hilo y por qué es necesario.

Ahora, no te voy a pedir que hagas lo siguiente ya, claro, a menos que seas una persona muy curiosa y 
además tengas tiempo. En `este <https://learn.microsoft.com/en-us/dotnet/standard/threading/managed-threading-basics>`__ 
sitio puedes profundizar sobre el concepto de hilo.

Ejercicio 3: análisis del plugin
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Ahora, vamos a analizar más detalladamente una de las escenas demo de Ardity:
DemoScene_UserPoll_ReadWrite

Primero, vamos a analizar rápidamente el código de arduino (para un protocolo ASCII):

.. code-block:: cpp

    uint32_t last_time = 0;
    
    void setup()
    {
        Serial.begin(9600);
    }
    
    void loop()
    {
        // Print a heartbeat
        if ( (millis() - last_time) >  2000)
        {
            Serial.print("Arduino is alive!!");
            Serial.print('\n');
            last_time = millis();
        }
    
        // Send some message when I receive an 'A' or a 'Z'.
        switch (Serial.read())
        {
            case 'A':
                Serial.print("That's the first letter of the abecedarium.");
                Serial.print('\n');
                break;
            case 'Z':
                Serial.print("That's the last letter of the abecedarium.");
                Serial.print('\n');
                break;
        }
    }

Consideraciones a tener presentes con este código:

* La velocidad de comunicación es de 9600. Esa misma velocidad se tendrá que configurar
  del lado de Unity para que ambas partes se puedan entender.
* Nota que no estamos usando la función delay(). Estamos usando millis para medir tiempos
  relativos. Nota que cada dos segundos estamos enviando un mensaje indicando que el
  arduino está activo:  ``Arduino is alive!!``
* Observa que el buffer del serial se lee constantemente. NO estamos usando
  el método available() que usualmente utilizamos. ¿Recuerdas lo anterior? Con available()
  nos aseguramos que el buffer de recepción tiene al menos un byte para leer; 
  sin embargo, cuando usamos Serial.read() sin verificar antes que tengamos datos en el
  buffer, es muy posible que el método devuelva un -1 indicando que no había nada en el
  buffer de recepción. NO OLVIDES ESTO POR FAVOR.
* Por último nota que todos los mensajes enviados por arduino finalizan con:: 
    
    Serial.print('\n');

  ¿Recuerdas en la unidad 2 para qué hacemos esto? ¿Podrías desde ahora predecir que 
  tipo de protocolo utilizará este demo (ASCII o binario)? Si tienes dudas llama a tu profe.

Ahora analicemos la parte de Unity/Ardity. Para ello, carguemos una de las escenas ejemplo:
DemoScene_UserPoll_ReadWrite

.. image:: ../_static/scenes.jpg
   :scale: 100%
   :align: center
   :alt: scenes

|

Nota que la escena tiene 3 gameObjects: Main Camera, SerialController y SampleUserPolling_ReadWrite.

Veamos el gameObject SampleUserPolling_ReadWrite. Este gameObject tiene dos components, un transform
y un script. El script tiene el código como tal de la aplicación del usuario.

.. image:: ../_static/user_code.jpg
   :scale: 100%
   :align: center
   :alt: user_code

|

Nota que el script expone una variable pública: serialController. Esta variable es del tipo SerialController.

.. image:: ../_static/serialControllerVarCode.jpg
   :scale: 100%
   :align: center
   :alt: controller

|

Esa variable nos permite almacenar la referencia a un objeto tipo SerialController. ¿Donde estaría ese
objeto? Pues cuando el gameObject SerialController es creado nota que uno de sus componentes es un objeto
de tipo SerialController:

.. image:: ../_static/serialControllerGO_Components.jpg
   :scale: 100%
   :align: center
   :alt: serial controller GO

|

Entonces desde el editor de Unity podemos arrastrar el gameObject SerialController al campo SerialController
del gameObject SampleUserPolling_ReadWrite y cuando se despliegue la escena, automáticamente se inicializará
la variable serialController con la referencia en memoria al objeto SerialController:

.. image:: ../_static/serialControllerUnityEditor.jpg
   :scale: 100%
   :align: center
   :alt: serial controller unity editor

|

De esta manera logramos que el objeto SampleUserPolling_ReadWrite tenga acceso a la información
del objeto SerialController.

Observemos ahora qué datos y qué comportamientos tendría un objeto de tipo SampleUserPolling_ReadWrite:

.. code-block:: csharp

    /**
     * Ardity (Serial Communication for Arduino + Unity)
     * Author: Daniel Wilches <dwilches@gmail.com>
     *
     * This work is released under the Creative Commons Attributions license.
     * https://creativecommons.org/licenses/by/2.0/
     */

    using UnityEngine;
    using System.Collections;

    /**
     * Sample for reading using polling by yourself, and writing too.
     */
    public class SampleUserPolling_ReadWrite : MonoBehaviour
    {
        public SerialController serialController;

        // Initialization
        void Start()
        {
            serialController = GameObject.Find("SerialController").GetComponent<SerialController>();

            Debug.Log("Press A or Z to execute some actions");
        }

        // Executed each frame
        void Update()
        {
            //---------------------------------------------------------------------
            // Send data
            //---------------------------------------------------------------------

            // If you press one of these keys send it to the serial device. A
            // sample serial device that accepts this input is given in the README.
            if (Input.GetKeyDown(KeyCode.A))
            {
                Debug.Log("Sending A");
                serialController.SendSerialMessage("A");
            }

            if (Input.GetKeyDown(KeyCode.Z))
            {
                Debug.Log("Sending Z");
                serialController.SendSerialMessage("Z");
            }


            //---------------------------------------------------------------------
            // Receive data
            //---------------------------------------------------------------------

            string message = serialController.ReadSerialMessage();

            if (message == null)
                return;

            // Check if the message is plain data or a connect/disconnect event.
            if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_CONNECTED))
                Debug.Log("Connection established");
            else if (ReferenceEquals(message, SerialController.SERIAL_DEVICE_DISCONNECTED))
                Debug.Log("Connection attempt failed or disconnection detected");
            else
                Debug.Log("Message arrived: " + message);
        }
    }

Vamos a realizar una prueba. Pero antes configuremos el puerto serial en el cual está conectado
el arduino. El arduino ya debe estar corriendo el código que te mostré al comienzo.

.. image:: ../_static/serialControllerCOM.jpg
   :scale: 100%
   :align: center
   :alt: serial controller COM

|

En este caso el puerto es COM4.

Corre el programa, abre la consola y selecciona la ventana Game del Editor de Unity. Con la ventana
seleccionada (click izquierdo del mouse), escribe las letras A y Z. Notarás los mensajes que aparecen
en la consola:

.. image:: ../_static/unityConsole.jpg
   :scale: 100%
   :align: center
   :alt: unity console

|

Una vez la aplicación funcione nota algo en el código de SampleUserPolling_ReadWrite:

.. code-block:: csharp

    serialController = GameObject.Find("SerialController").GetComponent<SerialController>();

Comenta esta línea y corre la aplicación de nuevo. Funciona?

Ahora, elimina el comentario de la línea y luego borra la referencia al SerialController
en el editor de Unity:

.. image:: ../_static/removeSerialControllerUnityEditor.jpg
   :scale: 100%
   :align: center
   :alt: remove serial controller

|

Corre de nuevo la aplicación.

* ¿Qué puedes concluir?
* ¿Para qué incluyó esta línea el autor del plugin?

Ahora analicemos el código del método Update de SampleUserPolling_ReadWrite:

.. code-block:: csharp

    // Executed each frame
    void Update()
    {
      .
      .
      .
      serialController.SendSerialMessage("A");
      .
      .
      .
      string message = serialController.ReadSerialMessage();
      .
      .
      .
    }

¿Recuerdas cada cuánto se llama el método Update? 

Update se llama en cada frame. Lo llama automáticamente el motor de Unity

Nota los dos métodos que se resaltan:

.. code-block:: csharp

    serialController.SendSerialMessage("A");
    string message = serialController.ReadSerialMessage();

Ambos métodos se llaman sobre el objeto cuya dirección en memoria está guardada en
la variable serialController.

El primer método permite enviar la letra A y el segundo permite recibir una cadena
de caracteres.

* ¿Cada cuánto se envía la letra A o la Z?
* ¿Cada cuánto leemos si nos llegaron mensajes desde el arduino?

Ahora vamos a analizar cómo transita la letra A desde el SampleUserPolling_ReadWrite hasta
el arduino.

Para enviar la letra usamos el método SendSerialMessage de la clase SerialController. Observa
que la clase tiene dos variables protegidas importantes:

.. image:: ../_static/serialControllerUMLClass.jpg
   :scale: 35%
   :align: center
   :alt: serial controller UML class

|

.. code-block:: csharp

   protected Thread thread;
   protected SerialThreadLines serialThread;

Con esas variables vamos a administrar un nuevo hilo y vamos a almacenar una referencia 
a un objeto de tipo SerialThreadLines.

En el método onEnable de SerialController tenemos:

.. code-block:: csharp

   serialThread = new SerialThreadLines(portName, baudRate, reconnectionDelay, maxUnreadMessages);
   thread = new Thread(new ThreadStart(serialThread.RunForever));
   thread.Start();

Aquí vemos algo muy interesante, el código del nuevo hilo que estamos creando será RunForever y
ese código actuará sobre los datos del objeto cuya referencia está almacenada en serialThread.

Vamos a concentrarnos ahora en serialThread que es un objeto de la clase SerialThreadLines:

.. code-block:: csharp

    public class SerialThreadLines : AbstractSerialThread
    {
        public SerialThreadLines(string portName,
                                 int baudRate,
                                 int delayBeforeReconnecting,
                                 int maxUnreadMessages)
            : base(portName, baudRate, delayBeforeReconnecting, maxUnreadMessages, true)
        {
        }

        protected override void SendToWire(object message, SerialPort serialPort)
        {
            serialPort.WriteLine((string) message);
        }

        protected override object ReadFromWire(SerialPort serialPort)
        {
            return serialPort.ReadLine();
        }
    }

Al ver este código no se observa por ningún lado el método RunForever, que es el código
que ejecutará nuestro hilo. ¿Dónde está? Observa que SerialThreadLines también es un
AbstractSerialThread. Entonces es de esperar que el método RunForever esté en la clase
AbstractSerialThread.

Por otro lado nota que para enviar la letra A usamos el método SendSerialMessage también
sobre los datos del objeto referenciado por serialThread del cual ya sabemos que es un
SerialThreadLines y un AbstractSerialThread

.. code-block:: csharp

    public void SendSerialMessage(string message)
    {
        serialThread.SendMessage(message);
    }

Al igual que RunForever, el método SendMessage también está definido en AbstractSerialThread.

Veamos entonces ahora qué hacemos con la letra A:

.. code-block:: csharp

    public void SendMessage(object message)
    {
        outputQueue.Enqueue(message);
    }

Este código nos da la clave. Lo que estamos haciendo es guardar la letra A 
que queremos transmitir en una COLA. Esta estructura de datos permite 
PASAR información de un HILO a otro HILO.

¿Cuáles hilos?

Pues tenemos en este momento dos hilos: el hilo del motor y el nuevo hilo que creamos antes.
El hilo que ejecutará el código RunForever sobre los datos del objeto de tipo
SerialThreadLines:AbstractSerialThread. Por tanto, observa que la letra A la estamos
guardando en la COLA del SerialThreadLines:AbstractSerialThread

Si observas con detenimiento el código de RunForever:

.. code-block:: csharp

    public void RunForever()
    {
        try
        {
            while (!IsStopRequested())
            {
                ...
                try
                {
                    AttemptConnection();
                    while (!IsStopRequested())
                        RunOnce();
                }
                catch (Exception ioe)
                {
                ...
                }
            }
        }
        catch (Exception e)
        {
        ...
        }
    }

Los detalles están en RunOnce():

.. code-block:: csharp

    private void RunOnce()
    {
        try
        {
            // Send a message.
            if (outputQueue.Count != 0)
            {
                SendToWire(outputQueue.Dequeue(), serialPort);
            }
            object inputMessage = ReadFromWire(serialPort);
            if (inputMessage != null)
            {
                if (inputQueue.Count < maxUnreadMessages)
                {
                    inputQueue.Enqueue(inputMessage);
                }
            }
        }
        catch (TimeoutException)
        {
        }
    }

Y en este punto vemos finalmente qué es lo que pasa. Para enviar la letra
A, el código del hilo pregunta si hay mensajes en la cola. Si los hay,
nota que el mensaje se saca de la cola y se envía:

.. code-block:: csharp

   SendToWire(outputQueue.Dequeue(), serialPort);

Si buscamos el método SendToWire en AbstractSerialThread vemos:

.. code-block:: csharp
   
   protected abstract void SendToWire(object message, SerialPort serialPort);

Y aquí es donde se conectan las clases SerialThreadLines con AbstractSerialThread, ya
que el método SendToWire es abstracto, SerialThreadLines tendrá que implementarlo

.. code-block:: csharp

    public class SerialThreadLines : AbstractSerialThread
    {
        ...
        protected override void SendToWire(object message, SerialPort serialPort)
        {
            serialPort.WriteLine((string) message);
        }
        ...
    }

Aquí vemos finalmente el uso de la clase SerialPort de C# con el método
`WriteLine <https://docs.microsoft.com/en-us/dotnet/api/system.io.ports.serialport.writeline?view=netframework-4.8>`__ 

Finalmente, para recibir datos desde el serial, ocurre el proceso contrario:

.. code-block:: csharp


    public class SerialThreadLines : AbstractSerialThread
    {
        ...
        protected override object ReadFromWire(SerialPort serialPort)
        {
            return serialPort.ReadLine();
        }
    }

`ReadLine <https://docs.microsoft.com/en-us/dotnet/api/system.io.ports.serialport.readline?view=netframework-4.8>`__
también es la clase SerialPort. Si leemos cómo funciona ReadLine queda completamente claro la razón de usar otro
hilo:

.. warning::

  By default, the ReadLine method will block until a line is received. If this behavior is undesirable, set the
  ReadTimeout property to any non-zero value to force the ReadLine method to throw a TimeoutException if
  a line is not available on the port.

  Note that while this method does not return the NewLine value, the NewLine value is removed from the input buffer.


Por tanto, volviendo a RunOnce:

.. code-block:: csharp

    private void RunOnce()
    {
        try
        {
            if (outputQueue.Count != 0)
            {
                SendToWire(outputQueue.Dequeue(), serialPort);
            }

           object inputMessage = ReadFromWire(serialPort);
            if (inputMessage != null)
            {
                if (inputQueue.Count < maxUnreadMessages)
                {
                    inputQueue.Enqueue(inputMessage);
                }
                else
                {
                    Debug.LogWarning("Queue is full. Dropping message: " + inputMessage);
                }
            }
        }
        catch (TimeoutException)
        {
            // This is normal, not everytime we have a report from the serial device
        }
    }

Vemos que se envía el mensaje: 

.. code-block:: csharp

    SendToWire(outputQueue.Dequeue(), serialPort);

Y luego el hilo se bloquea esperando por una respuesta:

.. code-block:: csharp

    object inputMessage = ReadFromWire(serialPort);

Nota que primero se envía y luego el hilo se bloquea. NO SE DESBLOQUEARÁ HASTA que no envíe
una respuesta desde Arduino o pasen 100 ms que es el tiempo que dura bloqueada la función
antes de generar una excepción de timeout de lectura.

¿Cómo sabemos que son 100 ms? 

Mira con detenimiento el código. La siguiente línea te dará una pista.

.. code-block:: csharp

   // Amount of milliseconds alloted to a single read or connect. An
    // exception is thrown when such operations take more than this time
    // to complete.
    private const int readTimeout = 100;

Ejercicio 4: excepciones
^^^^^^^^^^^^^^^^^^^^^^^^^^

¿Cómo puedes identificar la gestión de excepciones en el código? El código 
que considera las posibles excepciones está arropado con la estructura de control 
try catch. 

Regresa al método ``RunForever``. Observa AttemptConnection. ¿Qué pasa al ejecutar 
serialPort.Open(); si no tienes un microcontrolador conectado o el puerto serial 
configurado no el correcto?

En este punto quiero que veas un poco de documentación. ¿Cómo hago para saber 
si un método puede generar excepciones? Eso te lo dice la documentación. Te dejo 
un ejemplo `aquí <https://learn.microsoft.com/en-us/dotnet/api/system.io.ports.serialport.open?view=netframework-4.8.1#exceptions>`__ 
para el método Open.

Preguntas para que pienses:

* Luego de ver la documentación podrías decir si ¿Es posible determinar que la excepción 
  está ocurriendo porque el nombre del puerto no comienza por la palabra COM?
* ¿Serial posible indicarle al usario que el puerto no puede abrirse porque otro programa 
  ya lo tiene abierto?
* En la scene DemoScene_UserPoll_ReadWrite ¿Qué pasa si desconectas el microcontrolador? y ¿Qué 
  pasa si lo vuelves a conectar?
* Explica tan detallado como puedas qué ocurre con la aplicación al desconectar y luego volver 
  a conectar el microcontrolador.

Ejercicio 5: evaluación formativa
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Crea un proyecto nuevo en Unity.
* Configura el soporte para el puerto serial.
* OJO, no instales el paquete Ardity. SI YA LO HICISTE, vuelve a comenzar.
* Ahora toma únicamente LOS SCRIPTS de Ardity necesarios (SOLO LOS NECESARIOS)
  para hacer que la aplicación DEMO del ejercicio anterior funcione.