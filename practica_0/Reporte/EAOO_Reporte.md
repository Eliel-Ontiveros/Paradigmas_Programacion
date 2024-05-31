**Introducción**
Markdown es un lenguaje de marcado ligero y fácil de usar que se utiliza para formatear texto de manera sencilla y legible. Es ampliamente utilizado en la documentación de proyectos, especialmente en plataformas de desarrollo colaborativo como GitHub. GitHub es un servicio de alojamiento de repositorios que permite a los desarrolladores almacenar y gestionar su código. GitBash es una interfaz de línea de comandos que permite a los usuarios de Windows utilizar comandos de Git en un entorno similar a Unix. En esta práctica, aprenderás a crear un archivo en Markdown, subirlo a un repositorio de GitHub utilizando GitBash y gestionar tus archivos de manera eficiente.

**Desarrollo**
Subir Archivos a GitHub Utilizando GitBash

1. **Instalación de Git y GitBash**: Asegúrate de tener Git y GitBash instalados en tu sistema. Puedes descargarlo desde [aquí](https://git-scm.com/).
2. **Configuración Inicial**: Abre GitBash y configura tu nombre de usuario y correo electrónico:

    ```bash
    git config --global user.name "Tu Nombre"
    git config --global user.email "tu_email@example.com"
    ```

3. **Inicialización del Repositorio**: Navega a la carpeta de tu proyecto y convierte la carpeta en un repositorio de Git:

    ```bash
    cd ruta/a/tu/proyecto
    git init
    ```

4. **Añadir Archivos y Hacer un Commit**:

    ```bash
    git add README.md
    git commit -m "Añadir archivo README.md"
    ```

5. **Crear un Repositorio en GitHub**: Ve a [GitHub](https://github.com/) y crea un nuevo repositorio. Copia la URL del repositorio.

6. **Conectar el Repositorio Local con GitHub**:

    ```bash
    git remote add origin https://github.com/tu_usuario/tu_repositorio.git
    ```

7. **Subir los Archivos al Repositorio Remoto**:

    ```bash
    git push -u origin master
    ```

**Conclusión**
En esta práctica, has aprendido a utilizar Markdown para crear y formatear documentos de texto de manera sencilla y efectiva. Además, has aprendido a utilizar GitBash para inicializar un repositorio local, añadir archivos, hacer commits y subir tu trabajo a un repositorio en GitHub. Estas habilidades son fundamentales para cualquier desarrollador que trabaje en proyectos colaborativos y quiera mantener un flujo de trabajo organizado y eficiente. Ahora puedes documentar tus proyectos y compartirlos con la comunidad de desarrolladores en GitHub.    