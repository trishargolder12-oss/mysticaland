# Build Instructions — Mysticaland

## Prerequisites
- **CMake** (v3.22 or newer)
- **C++20 Compiler** (MSVC 2022 or Clang/LLVM)
- **Git** (for automatic JUCE fetching)

## Build Commands

### 1. Configure
```cmd
cmake -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
```
Or with Visual Studio generator:
```cmd
cmake -B build -G "Visual Studio 17 2022" -A x64
```

### 2. Compile VST3 & Standalone
```cmd
cmake --build build --config Release
```

### 3. Build Artefacts
Upon completion, the binaries are generated at:
- **VST3 Plugin**: `build/Products/Shell/MysticalandShell_artefacts/Release/VST3/Mysticaland Shell.vst3`
- **Standalone**: `build/Products/Shell/MysticalandShell_artefacts/Release/Standalone/Mysticaland Shell.exe`

## Installation to Windows System
To test in FL Studio, Ableton, Reaper, or Cubase, copy `Mysticaland Shell.vst3` to:
```
C:\Program Files\Common Files\VST3\
```
Run `scripts/install_vst3.bat` as Administrator for automated backup and installation.
