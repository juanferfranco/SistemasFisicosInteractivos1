¿Qué herramientas necesito para el curso?
==========================================

En este curso vamos a trabajar con el sistema operativo Linux. Hay muchas maneras de 
tener el sistema operativo; sin embargo, nosotros vamos a instalar el sistema 
operativo en una memoria USB y lo ejecutaremos desde allí como un disco externo.

En las clases presenciales yo te prestaré una memoria con el sistema instalado. Si quieres 
tener una copia de la memoria para trabajar en tu casa, puedes comprarla 
`aquí <https://www.amazon.com/-/es/gp/product/B015CH1NAQ/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&th=1>`__ 
y con todo gusto te la copio.

Si te preguntas cómo hago la memoria y la copio, te cuento aquí cómo se hace.


.. warning:: ESTO NO LO TIENES QUE HACER

   Las instrucciones que te voy a dejar aquí son solo para los interesados en reproducir las herramientas 
   que usaremos en el curso.


¿Cómo instalar Linux en una memoria USB?
--------------------------------------------------

#. Lo primero es comprar una memoria USB de alta velocidad que permita 
   correr de manera fluida el sistema operativo. Luego de buscar en varios foros 
   encontré una memoria que ofrece una excelente relación costo beneficio 
   `aquí <https://www.amazon.com/-/es/gp/product/B015CH1NAQ/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&th=1>`__.
#. Sigue las instrucciones de `este <https://wiki.mattzab.com/pub/how-to-make-a-pop-os-persistent-live-usb>`__ 
   sitio.

Instalación de las herramientas del curso (y extras)
------------------------------------------------------

Ahora voy a listar varias de las herramientas que serán usadas en el curso más otras 
que se usan en los cursos de sistemas físicos interactivos 1 y 2, sistemas operativos y 
scripting.

* zsh::
  
   sudo apt update
   sudo apt install zsh

* `Oh My ZSH! <https://ohmyz.sh/>`__
* `Github CLI <https://cli.github.com/>`__
* Toolchain para compilar y depurar programas en C::
  
      sudo apt update
      sudo apt install build-essential
      sudo apt install gdb

* Java JDK::
  
   sudo apt install default-jdk

* `Digital <https://github.com/juanferfranco/SistemasComputacionales/tree/main/docs/_static/Digital.zip>`__
* `Nand2tetris Software Suite <https://www.nand2tetris.org/software>`__
* `Visual Studio code <https://code.visualstudio.com/>`__
* `Extensión de C/C++ de visual Studio Code <https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools>`__
* Instalar también la C/C++ Extension Pack.
* Herramientas varias::

      sudo apt-get install git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
      sudo usermod -a -G dialout $USER
      python3 -m pip install pyserial

* `Arduino IDE 1.8.X <https://www.arduino.cc/en/software>`__
* Instalación del `soporte para el ESP32 <https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html>`__ 
  en el Arduino IDE
* En la versión de popOS 22.04 aparece una nueva regla para el sistema braille que incluye entre sus reglas 
  en ``/usr/lib/udev/rules.d/85-brltty.rules`` soporte para un dispositivo basado en el chip cp210x (en mi caso los datos del 
  chip son: idVendor=10c4, idProduct=ea60) que convierte de USB a RS232. Este chip lo tienen varios sistemas de desarrollo de Arduino. 
  Una solución simple a este problema es comentar la regla que señala al chip, salvar el archivo 85-brltty.rules y reiniciar.
* `Extensión Arduino <https://github.com/microsoft/vscode-arduino>`__ para Visual Studio Code. No olvidar 
  configurar el path donde está instalado el IDE de Arduino.
* En visual studio code, en los settings, se recomienda deshabilitar el pegado del contenido del clipboard con el botón del medio del mouse: 
  "editor.selectionClipboard": false  
* `ScriptCommunicator <https://sourceforge.net/projects/scriptcommunicator/>`__
* `.NET sdk <https://docs.microsoft.com/en-us/dotnet/core/install/linux-ubuntu>`__
* `Extensión para C# en visual studio <https://marketplace.visualstudio.com/items?itemName=ms-dotnettools.csharp>`__
* `Mono <https://www.mono-project.com/download/stable/#download-lin-ubuntu>`__::

   sudo apt install gnupg ca-certificates
   sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
   echo "deb https://download.mono-project.com/repo/ubuntu stable-focal main" | sudo tee /etc/apt/sources.list.d/mono-official-stable.list
   sudo apt install mono-complete   


* Instalar una biblioteca necesaria para correr UnityHub y el editor de Unity::

   wget "http://security.ubuntu.com/ubuntu/pool/main/o/openssl1.0/libssl1.0.0_1.0.2n-1ubuntu5.10_amd64.deb"
   sudo dpkg -i libssl1.0.0_1.0.2n-1ubuntu5.10_amd64.deb
   
* `Unity Hub <https://docs.unity3d.com/hub/manual/InstallHub.html#install-hub-linux>`__
* Unity 2021 LTS
* Crear una cuenta educativa en jetbrains y descargar Rider.
* En Unity se debe configurar el editor para que abra los proyectos con Rider.

¿Cómo clonar la memoria USB?
------------------------------

Los pasos para clonar la memoria USB los he tomado de 
`aquí <https://www.cyberciti.biz/faq/linux-copy-clone-usb-stick-including-partitions/>`__.

¿Hardware para el curso?
--------------------------

En este curso vas a conectar dispositivos periféricos a sistemas de cómputo. 
¿Qué debes conseguir?

#. Un sistema de desarrollo para el ESP32. Puedes conseguir uno de 
   `estos kits <https://www.didacticaselectronicas.com/index.php/sistemas-de-desarrollo/espressif-systems/esp32/tarjeta-de-desarrollo-esp32-wrover-b-tarjetas-modulos-de-desarrollo-de-con-wifi-y-bluetooth-esp32u-comunicaci%C3%B3n-wi-fi-bluetooth-esp32u-iot-esp32-nodemcu-wrover-devkit-detail>`__.
#. Para conectar el sistema de desarrollo anterior, necesitarás un cable micro USB de BUENA CALIDAD.
   Te recomiendo `este <https://www.panamericana.com.co/cable-micro-usb-a-usb-a-1m-belkin-color-negro-609919/p>`__.
#. Protoboard de 840, o de 830 puntos, o 2 pequeños de 400 puntos de inserción.
#. Cables `conexión fácil macho a macho <https://www.didacticaselectronicas.com/index.php/cables-conectores-y-accesorios/conexion-facil/kit-cables-conexion-facil-mm-premium-10pcs-1-dupont-arduino-cables-de-conexion-f%C3%A1cil-macho-macho-dupont-header-easy-conection-arduino-r%C3%A1pida-1852-detail>`__: 
   paquete de 20.
#. `LED amarillo <https://www.didacticaselectronicas.com/index.php/optoelectronica/diodos-led/dip/5mm/led-5mm-difuso-amarillo-diodos-leds-difusos-de-5mm-iluminaci%C3%B3n-through-hole-dip-amarillos-detail>`__, 
   `LED rojo <https://www.didacticaselectronicas.com/index.php/optoelectronica/diodos-led/dip/5mm/led-5mm-difuso-rojo-diodos-leds-difusos-de-5mm-iluminaci%C3%B3n-through-hole-dip-rojos-detail>`__, 
   `LED azul <https://www.didacticaselectronicas.com/index.php/optoelectronica/diodos-led/dip/5mm/led-5mm-difuso-azul-diodos-leds-difusos-de-5mm-iluminaci%C3%B3n-through-hole-dip-azules-detail>`__, 
   `LED verde <https://www.didacticaselectronicas.com/index.php/optoelectronica/diodos-led/dip/5mm/led-5mm-difuso-verde-diodos-leds-difusos-de-5mm-iluminaci%C3%B3n-through-hole-dip-verdes-detail>`__. 
#. 4 resistencias de 1000 ohm.
#. 4 `pulsadores <https://www.didacticaselectronicas.com/index.php/suiches-y-conectores/suiches/pulsadores/pulsador-peque%C3%B1o-2-pines-2mm-interruptores-botones-switch-suiches-pulsadores-cuadrados-de-2-pines-6mm-x-5mm-momentaneos-moment%C3%A1neo-sw-6x5-2p-sw-057b-de-montaje-through-hole-detail>`__ 
   de patas largas para introducir en el protobard.
