# Particle Simulation 2D

**Proyecto académico de simulación de partículas 2D**

Este repositorio contiene el código fuente de un proyecto de C++ desarrollado en el primer año de la carrera de Ingeniería Informática, durante la asignatura Metodología de la Programación. El programa modela partículas en un plano 2‑D que deben ser eliminadas por la aspiradora que actuá como otra partícula pero de mayor tamaño. Puedes mover la aspiradora con las teclas direccionales del teclado, y el programa incluye operaciones de movimiento, colisión y rebote entre las partículas. El radio de la aspiradora y el número de partículas se pueden elegir al ejecutar el programa, puedes añadir más particulas pulsando la tecla ENTER.

---

## 📋 Contenido del repositorio

- `src/` – Implementación de las clases y de los *test*.
- `include/` – Cabeceras de las clases (`Vector2D`, `Particula`, `ConjuntoParticulas`).
- `lib/` – Bibliotecas externas precompiladas (Raylib) que el proyecto enlaza en la fase de *linking*.
- `Makefile` – Construye los ejecutables y los test.
- `LICENSE` – Licencia MIT (ya incluida).
- `README.md` – Este documento.

---

## 🛠️ Requisitos

| Herramienta | Versión mínima | Comentario |
|-------------|----------------|------------|
| **g++** (o clang++) | C++11 compatible | Compilador GNU/Clang.
| **make** | cualquier versión | Necesario para el `Makefile`.
| **Raylib** | 4.x | Biblioteca gráfica usada por `main_raylib.cpp`. La versión precompilada ya está incluida en la carpeta `lib/`, por lo que **no es necesario instalarla** en el sistema. Sólo en caso de que quieras usar Raylib en otros proyectos o compilar una versión distinta, puedes instalarla mediante el gestor de paquetes de tu OS.


> **Nota**: Si trabajas en Windows y no tienes `make`, puedes instalar **MinGW‑Make** o usar **WSL** para ejecutar los comandos tal cual aparecen a continuación.

---

## 🚀 Compilación y ejecución

```bash
# Clonar el repositorio (si aún no lo has hecho)
git clone <repo-url>
cd proyecto

# Compilar todos los ejecutables
make all
```

Esto generará los siguientes binarios dentro de `bin/`:
- `test0`, `test1`, `test2` – Ejecutables con los *unit tests*.
- `test_raylib` – Ejecutable que muestra la simulación usando Raylib.

### Ejecutar los tests

```bash
./bin/test0   # Vector2D tests
./bin/test1   # Particula tests (con ConjuntoParticulas)
./bin/test2   # Test más completo
```

### Ejecutar la simulación gráfica

```bash
./bin/test_raylib <radio> <num_particulas>
```

---

## 📦 Limpieza del proyecto

```bash
make clean
```

---

## 📄 Licencia

Este proyecto está licenciado bajo la **MIT License** (ver el archivo `LICENSE`).

---

## ✏️ Contribuciones

Si deseas contribuir, puedes hacer un *pull request* describiendo los cambios. Se agradece mantener el estilo de código y actualizar los tests cuando sea necesario.


