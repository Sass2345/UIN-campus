# UIN-Campus (C++23)

Projet C++23 modulaire développé dans le cadre du TP UIN-Campus, axé sur la qualité du code, les tests unitaires et la sécurité mémoire.

## 🚀 Fonctionnalités & Prérequis

- **Standard C++** : C++23 (`cxx_std_23`)
- **Compilateur** : GCC 15.2.0 (ou supérieur) / Clang
- **Système de build** : CMake (v3.22+) & Ninja
- **Tests unitaires** : Catch2 (v3.5.0) via `FetchContent`
- **Analyse mémoire** : AddressSanitizer (ASan) & options de compilation strictes (`-Wall -Wextra -Wpedantic -Werror`)

---

## 📁 Arborescence du Projet

```text
UIN-Campus/
├── app/                  # Point d'entrée principal (main.cpp)
├── include/uincampus/    # En-têtes publics (.hpp)
├── src/                  # Implémentations (.cpp)
├── tests/                # Tests unitaires avec Catch2
├── CMakeLists.txt        # Configuration CMake principale
└── CMakePresets.json     # Presets de configuration et build