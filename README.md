# CLUSTER_RASPBERRY

<p align="center">
<image width="460" src="/Raspberry_Cluster/LOGO_PI.png" alt="Raspberry Pi Arquitecturas Paralelas" caption="Raspberry Pi Arquitecturas Paralelas">
</p>
    
### Autores:
    - Álvaro Palacios Criado
    - Rafael Carlos Díaz Mata
    - Adolfo Fernández Gil

Tenemos 3 Raspberry Pi, con las cuales queremos montar un cluster e instalar y configurar un NSF (Network System File).

## HARDWARE

### Modelos de Raspberry

Tenemos los siguientes modelos y los siguientes sistemas operativos:

    - Raspberry Pi Model A+: Raspberry Pi OS (32-bits) Desktop
    - Raspberry Pi 2 Model B: Raspberry Pi OS (32-bits) Desktop
    - Raspberry Pi 4 Model B: Raspberry Pi OS (32-bits) Desktop

## SOFTWARE

### Instalación y configuración básica SO

Para comenzar vamos a seguir los siguiente pasos:

1. Instalamos en nuestra máquina *Raspberry Pi Imager* este software nos permitira cargar en nuestras tarjetas SD el Sistema Operativo.
   1. <https://www.raspberrypi.com/software/>
2. Para instalar el programa usaremos **sudo apt install ./imager_1.7.4_amd64.deb**
3. Instalamos en cada una de las tarjetas los S.O comentados anteriormente.
   1. Operating System: Sistema operativo a elegir.
   2. Storage: almacenamiento, en nuestro caso SD.
   3. Configuración adicional: indicamos zona horaria.
   4. Write: escribimos el S.O en la SD.
4. Una vez terminada la instalación del S.O, procedemos encender nuestra Raspberry y configurar el sistema.
5. Una vez encendida nuestra Raspberry con la SD introducida y un teclado puesto, podemos configurar parametros básicos:
   1. Podemos configurar parámetros como zona horaria, teclado y usuario/contraseña:
      1. Usuario: ap
      2. Password: ap2023

### Configuracion SSH

Para configurar y habilitar ssh, usaremos el comando **sudo raspi-config** de esta manera entramos a la configuracion del sistema, y nos movemos al apartado *Interface Options* y habilitamos el SSH. Aceptamos todas las preguntas. Para terminar verificamos el estado del ssh con **sudo systemctl status ssh**

Ahora configuraremos los ssh de las maquinas para que de esta manera podamos conectarnos y pasar archivos entre los hosts sin necesidad de credenciales.

    - ssh-keygen -t rsa -C <hostname>:<username>
    - ssh-copy-id <remotehostname> (Para copiarlo a los demas hosts)

### Entorno

Para comenzar con la demo, debemos asegurarnos de que nuestras Raspberrys tengan acceso a la red con salida a Internet. Para ello las conectamos por wifi o ethernet.

Siguiente paso es la instalación de los paquetenes necesarios:

- Generales: bluid-essential, mpich, mpich-doc, libmpich2-3, limbmpich-dev, mpi.
- Python: pip install mpi4py.

Ahora para la configuración de lo host y sus IPs usaremos el fichero **/etc/hosts/**  con el formato. <ip> <hostname>

Estos pasos los hacemos en cada uno de los hosts.

### Servidor NFS (Modelo 4)

Creamos una carpeta que compartan todos los hosts en la red, y será donde coloquemos los ficheros:
    
    - ssh-keygen -t rsa -C <hostname>:<username>
    - ssh-copy-id <remotehostname> (En los demas hosts)
    
Creamos una entrada en **/etc/exports**

    - sudo nano /etc/exports

Y agregamos al final:
    
    - /home/ap/cloud *(rw,sync,no_root_squash,no_subtree_check)

Y a continuacion hacemos **sudo exportfs -a** o podemos reiniciar el servicio **sudo service nfs-kernel-server restart**

### Cliente NFS (Modelo 2 y 1)

En los demas hosts hay que configurar el cliente nfs:

    - sudo apt-get install nfs-common
    - mkdir ~/cloud
    - sudo mount -t nfs <serverhostname>:/home/ap/cloud ~/cloud


### Machinefile

Machinefile es un fichero en el que indicaremos el numero de procesos que ejcutara cada máquina, con el siguiente formato (en el directorio *~/cloud* **nano machinefile**):

    - <hostname>:<numero_de_procesos>

### Compilacion y ejecucion

Primero tenemos que pasar el fichero de codigo al servidor nfs con scp:

    - scp fichero <username_servidor>@<serverhosts>:/home/ap/cloud

Para compilar usaremos lo siguiente (lo compilaremos en el servidor):

- C: usando mpicc
- Python: chmod u+x

Para ejecutar usaremos lo siguiente:

- C: mpirun o mpiexec -f machinefile <ejecutable>
- Python: mpiexec -f machinefile python <ejecutable> 
