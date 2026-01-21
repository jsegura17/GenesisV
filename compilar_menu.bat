@echo off
REM IMPORTANTE: Este script debe ejecutarse desde CMD, no desde PowerShell
REM Si estas en PowerShell, ejecuta: cmd /c compilar_menu.bat

REM Cambiar a codepage 850 para mejor compatibilidad
chcp 850 >nul 2>&1

:menu
cls
echo ========================================
echo    GenesisV - Menu de Compilacion
echo ========================================
echo.
echo Selecciona el ejemplo a compilar:
echo.
echo    [0] GenesisV (Base - Piramide)
echo    [1] GenesisV-001 (Triangulo Simple)
echo    [2] GenesisV-002 (Cuadrado Coloreado)
echo    [3] GenesisV-003 (Cubo Wireframe)
echo    [4] GenesisV-004 (Cubo Solido Coloreado)
echo    [5] GenesisV-005 (Multiples Objetos)
echo    [6] GenesisV-006 (Quad Texturizado)
echo    [7] GenesisV-007 (Cubo Texturizado)
echo    [8] GenesisV-008 (Multiples Texturas)
echo    [9] GenesisV-009 (Texturas Animadas)
echo   [10] GenesisV-010 (Filtrado de Texturas)
echo   [11] GenesisV-011 (Tiles de Texturas)
echo   [12] GenesisV-012 (Objetos Multi-Textura)
echo   [13] GenesisV-013 (Texturas con Iluminacion)
echo   [14] GenesisV-014 (Escena Compleja)
echo   [15] GenesisV-015 (Efectos Avanzados)
echo   [16] Limpiar archivos compilados
echo   [17] Salir
echo.
set opcion=
set /p "opcion=Ingresa tu opcion (0-17): "

REM Eliminar espacios en blanco
set opcion=%opcion: =%

if "%opcion%"=="" (
    echo.
    echo No se ingreso ninguna opcion. Presiona cualquier tecla para continuar...
    pause >nul
    goto menu
)

if "%opcion%"=="0" goto compilar_base
if "%opcion%"=="1" goto compilar_001
if "%opcion%"=="2" goto compilar_002
if "%opcion%"=="3" goto compilar_003
if "%opcion%"=="4" goto compilar_004
if "%opcion%"=="5" goto compilar_005
if "%opcion%"=="6" goto compilar_006
if "%opcion%"=="7" goto compilar_007
if "%opcion%"=="8" goto compilar_008
if "%opcion%"=="9" goto compilar_009
if "%opcion%"=="10" goto compilar_010
if "%opcion%"=="11" goto compilar_011
if "%opcion%"=="12" goto compilar_012
if "%opcion%"=="13" goto compilar_013
if "%opcion%"=="14" goto compilar_014
if "%opcion%"=="15" goto compilar_015
if "%opcion%"=="16" goto limpiar
if "%opcion%"=="17" goto salir

echo.
echo Opcion invalida! Presiona cualquier tecla para continuar...
pause >nul
goto menu

:compilar_base
set SOURCE=GenesisV.cpp
set OUTPUT=GenesisV.exe
set TITLE=GenesisV (Base - Piramide)
goto compilar

:compilar_001
set SOURCE=GenesisV-001.cpp
set OUTPUT=GenesisV-001.exe
set TITLE=GenesisV-001 (Triangulo Simple)
goto compilar

:compilar_002
set SOURCE=GenesisV-002.cpp
set OUTPUT=GenesisV-002.exe
set TITLE=GenesisV-002 (Cuadrado Coloreado)
goto compilar

:compilar_003
set SOURCE=GenesisV-003.cpp
set OUTPUT=GenesisV-003.exe
set TITLE=GenesisV-003 (Cubo Wireframe)
goto compilar

:compilar_004
set SOURCE=GenesisV-004.cpp
set OUTPUT=GenesisV-004.exe
set TITLE=GenesisV-004 (Cubo Solido Coloreado)
goto compilar

:compilar_005
set SOURCE=GenesisV-005.cpp
set OUTPUT=GenesisV-005.exe
set TITLE=GenesisV-005 (Multiples Objetos)
goto compilar

:compilar_006
set SOURCE=GenesisV-006.cpp
set OUTPUT=GenesisV-006.exe
set TITLE=GenesisV-006 (Quad Texturizado)
goto compilar

:compilar_007
set SOURCE=GenesisV-007.cpp
set OUTPUT=GenesisV-007.exe
set TITLE=GenesisV-007 (Cubo Texturizado)
goto compilar

:compilar_008
set SOURCE=GenesisV-008.cpp
set OUTPUT=GenesisV-008.exe
set TITLE=GenesisV-008 (Multiples Texturas)
goto compilar

:compilar_009
set SOURCE=GenesisV-009.cpp
set OUTPUT=GenesisV-009.exe
set TITLE=GenesisV-009 (Texturas Animadas)
goto compilar

:compilar_010
set SOURCE=GenesisV-010.cpp
set OUTPUT=GenesisV-010.exe
set TITLE=GenesisV-010 (Filtrado de Texturas)
goto compilar

:compilar_011
set SOURCE=GenesisV-011.cpp
set OUTPUT=GenesisV-011.exe
set TITLE=GenesisV-011 (Tiles de Texturas)
goto compilar

:compilar_012
set SOURCE=GenesisV-012.cpp
set OUTPUT=GenesisV-012.exe
set TITLE=GenesisV-012 (Objetos Multi-Textura)
goto compilar

:compilar_013
set SOURCE=GenesisV-013.cpp
set OUTPUT=GenesisV-013.exe
set TITLE=GenesisV-013 (Texturas con Iluminacion)
goto compilar

:compilar_014
set SOURCE=GenesisV-014.cpp
set OUTPUT=GenesisV-014.exe
set TITLE=GenesisV-014 (Escena Compleja)
goto compilar

:compilar_015
set SOURCE=GenesisV-015.cpp
set OUTPUT=GenesisV-015.exe
set TITLE=GenesisV-015 (Efectos Avanzados)
goto compilar

:compilar
cls
echo ========================================
echo Compilando: %TITLE%
echo ========================================
echo.
setlocal enabledelayedexpansion

REM Buscar MinGW en ubicaciones comunes
set "MINGW_PATH="
if exist "C:\MinGW\bin\g++.exe" (
    set "MINGW_PATH=C:\MinGW\bin"
)
if exist "C:\mingw64\bin\g++.exe" (
    set "MINGW_PATH=C:\mingw64\bin"
)
if exist "C:\msys64\mingw64\bin\g++.exe" (
    set "MINGW_PATH=C:\msys64\mingw64\bin"
)
if exist "C:\Program Files\MinGW\bin\g++.exe" (
    set "MINGW_PATH=C:\Program Files\MinGW\bin"
)
set "TEMP_PATH=C:\Program Files (x86)\MinGW\bin\g++.exe"
if exist "!TEMP_PATH!" (
    set "MINGW_PATH=C:\Program Files (x86)\MinGW\bin"
)
set "TEMP_PATH="

REM Verificar si g++ está en el PATH
where g++ >nul 2>&1
if %errorlevel% equ 0 (
    set USE_PATH=1
) else (
    if not "!MINGW_PATH!"=="" (
        set "PATH=!MINGW_PATH!;%PATH%"
        set USE_PATH=1
    ) else (
        echo ERROR: MinGW no encontrado!
        echo.
        echo Por favor, agrega MinGW al PATH o especifica la ruta manualmente.
        echo.
        pause
        goto menu
    )
)

REM Verificar herramientas necesarias
g++ --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: g++ no disponible.
    pause
    goto menu
)

windres --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: windres no disponible.
    pause
    goto menu
)

REM Limpiar archivos anteriores del ejemplo seleccionado
set OBJFILE=%SOURCE:.cpp=.o%
del /Q %OBJFILE% %OUTPUT% 2>nul

REM Compilar recurso
echo [1/4] Compilando recurso (icono)...
windres GenesisV_private.rc -o GenesisV_private.res -O coff
if %errorlevel% neq 0 (
    echo ERROR al compilar el recurso.
    pause
    goto menu
)

REM Compilar archivo fuente
echo [2/4] Compilando %SOURCE%...
g++ -c %SOURCE% -o %OBJFILE% -Wall -O2 -DWIN32 -DNDEBUG -D_WINDOWS -D_MBCS
if %errorlevel% neq 0 (
    echo ERROR al compilar %SOURCE%.
    pause
    goto menu
)

REM Compilar GenesisCORE si no existe
if not exist GenesisCORE.o (
    echo [3/5] Compilando GenesisCORE.cpp...
    g++ -c GenesisCORE.cpp -o GenesisCORE.o -Wall -O2 -DWIN32 -DNDEBUG -D_WINDOWS -D_MBCS
    if %errorlevel% neq 0 (
        echo ERROR al compilar GenesisCORE.cpp.
        pause
        goto menu
    )
) else (
    echo [3/5] GenesisCORE.o ya existe, omitiendo...
)

REM Compilar TextureLoader si no existe (para ejemplos con texturas)
set NEED_TEXTURE=0
if "%SOURCE%"=="GenesisV-006.cpp" set NEED_TEXTURE=1
if "%SOURCE%"=="GenesisV-007.cpp" set NEED_TEXTURE=1
if "%SOURCE%"=="GenesisV-008.cpp" set NEED_TEXTURE=1
if "%SOURCE%"=="GenesisV-009.cpp" set NEED_TEXTURE=1
if "%SOURCE%"=="GenesisV-010.cpp" set NEED_TEXTURE=1
if "%SOURCE%"=="GenesisV-011.cpp" set NEED_TEXTURE=1
if "%SOURCE%"=="GenesisV-012.cpp" set NEED_TEXTURE=1
if "%SOURCE%"=="GenesisV-013.cpp" set NEED_TEXTURE=1
if "%SOURCE%"=="GenesisV-014.cpp" set NEED_TEXTURE=1
if "%SOURCE%"=="GenesisV-015.cpp" set NEED_TEXTURE=1

if "%NEED_TEXTURE%"=="1" (
    echo [4/5] Compilando TextureLoader.cpp...
    g++ -c TextureLoader.cpp -o TextureLoader.o -Wall -O2 -DWIN32 -DNDEBUG -D_WINDOWS -D_MBCS
    if %errorlevel% neq 0 (
        echo ERROR al compilar TextureLoader.cpp.
        pause
        goto menu
    )
) else (
    echo [4/5] TextureLoader no necesario para este ejemplo...
)

REM Enlazar
echo [5/5] Enlazando ejecutable...
if "%NEED_TEXTURE%"=="1" (
    g++ %OBJFILE% GenesisCORE.o TextureLoader.o GenesisV_private.res -o %OUTPUT% -mwindows -lopengl32 -lglu32 -lgdi32 -lgdiplus -luser32 -lkernel32
) else (
    g++ %OBJFILE% GenesisCORE.o GenesisV_private.res -o %OUTPUT% -mwindows -lopengl32 -lglu32 -lgdi32 -luser32 -lkernel32
)
if %errorlevel% neq 0 (
    echo ERROR al enlazar.
    pause
    goto menu
)

echo.
echo ========================================
echo Compilacion exitosa!
echo ========================================
echo.
echo Ejecutable creado: %OUTPUT%
echo.
echo.
echo Ejecutando %OUTPUT%...
echo.
%OUTPUT%

endlocal
echo.
goto menu

:limpiar
cls
echo ========================================
echo Limpiando archivos compilados...
echo ========================================
echo.
del /Q *.o *.res *.exe 2>nul
echo Archivos compilados eliminados.
echo.
pause
goto menu

:salir
echo.
echo Saliendo...
exit /b 0
