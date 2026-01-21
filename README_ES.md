# GenesisV - Proyecto de Aprendizaje OpenGL

Este es un proyecto simple para aprender OpenGL desde cero. Tiene varios ejemplos que van de lo más básico a cosas más complicadas.

## ¿Qué es esto?

GenesisV es una colección de ejemplos de OpenGL escritos en C++. Cada ejemplo muestra algo diferente y van aumentando de dificultad poco a poco. El primero es solo un triángulo que rota, y los últimos ya tienen texturas y efectos más avanzados.

## ¿Qué necesito para usarlo?

- Windows (porque usa las librerías de OpenGL de Windows)
- MinGW instalado (para compilar con g++)
- Un poco de paciencia si nunca has compilado algo en C++

## ¿Cómo lo compilo?

Lo más fácil es usar el menú de compilación. Abre una terminal en la carpeta GenesisV y ejecuta:

```
compilar_menu.bat
```

Te saldrá un menú con todos los ejemplos. Solo elige el número del que quieres ver y listo. El programa se compilará y se ejecutará automáticamente.

Si prefieres compilar manualmente, hay instrucciones en los archivos COMPILAR.md y COMPILAR_CON_MINGW.md.

## ¿Qué ejemplos hay?

Hay 15 ejemplos más uno base:

**Ejemplos básicos (001-005):**
- 001: Un triángulo simple que rota
- 002: Un cuadrado con colores
- 003: Un cubo hecho solo con líneas (wireframe)
- 004: Un cubo sólido con colores
- 005: Varios objetos rotando a la vez

**Ejemplos con texturas (006-015):**
- 006: Un cuadrado con textura de madera
- 007: Un cubo con textura
- 008: Cubo con diferentes texturas en cada cara
- 009: Textura que se mueve (animada)
- 010: Diferentes tipos de filtrado de texturas
- 011: Uso de tiles de una imagen grande
- 012: Varios objetos con diferentes texturas
- 013: Texturas con iluminación
- 014: Escena más compleja con varias cosas
- 015: Efectos avanzados con texturas

El ejemplo base (GenesisV.cpp) es una pirámide que rota.

## Controles

En todos los ejemplos funcionan igual:
- **ESC**: Salir
- **F1**: Pantalla completa / Ventana

Algunos ejemplos tienen controles extra, como el 010 que tiene una tecla para cambiar el filtro.

## Estructura del proyecto

- `GenesisCORE.h` y `GenesisCORE.cpp`: El código que maneja la ventana y OpenGL. No necesitas tocarlo.
- `GenesisV.cpp`: El ejemplo base
- `GenesisV-001.cpp` hasta `GenesisV-015.cpp`: Los ejemplos
- `TextureLoader.h` y `TextureLoader.cpp`: Código para cargar texturas (JPG y BMP)
- `images/`: Carpeta con las texturas que usan los ejemplos
- `compilar_menu.bat`: El script para compilar fácilmente

## ¿Por dónde empiezo?

Si nunca has usado OpenGL, empieza por el 001 y ve en orden. Cada ejemplo explica conceptos nuevos. Si ya sabes algo, puedes saltar a los que te interesen.

## Notas

- Todos los ejemplos están bien comentados en español
- El código es simple y fácil de entender
- Puedes modificar cualquier ejemplo para experimentar
- Las texturas deben estar en la carpeta `images` junto al ejecutable

## Problemas comunes

Si no compila:
- Verifica que MinGW esté instalado y en el PATH
- Asegúrate de estar en la carpeta GenesisV cuando ejecutas el script

Si no carga las texturas:
- Verifica que la carpeta `images` esté en el mismo lugar que el .exe
- Los archivos deben ser JPG o BMP

## Licencia

Este es un proyecto educativo. Úsalo como quieras para aprender.
