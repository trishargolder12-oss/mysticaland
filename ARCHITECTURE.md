# Architecture Documentation — Mysticaland Audio Ecosystem

## 1. Overview
Mysticaland is designed as a modular professional audio software ecosystem. The initial release is **Mysticaland Shell**, a genuine VST3 audio effect plugin and standalone application built on JUCE 8/9, C++20, and CMake.

## 2. Directory Structure
```
Mysticaland/
├── CMakeLists.txt                  # Root project configuration
├── Shared/                         # Modular shared infrastructure
│   ├── CMakeLists.txt
│   ├── Theme/                      # Color tokens, LookAndFeel, styling
│   │   ├── MysticalandColors.h
│   │   ├── MysticalandLookAndFeel.h
│   │   └── MysticalandLookAndFeel.cpp
│   ├── Branding/                   # Vectors, emblem, wordmark, textures
│   │   ├── MysticalandBranding.h
│   │   └── MysticalandBranding.cpp
│   └── Components/                 # Reusable UI widgets
│       ├── NavigationItem.h/.cpp
│       ├── MysticalandHeader.h/.cpp
│       ├── MysticalandSidebar.h/.cpp
│       └── EmptyStateComponent.h/.cpp
│
└── Products/
    └── Shell/                      # Mysticaland Shell Product
        ├── CMakeLists.txt
        ├── Processor/              # MysticalandShellAudioProcessor
        ├── Editor/                 # MysticalandShellAudioProcessorEditor
        └── Workspace/              # MysticalandWorkspace (Extension point)
```

## 3. Extensibility & Future Products
Each upcoming product (e.g. `Mysticaland EQ`, `Mysticaland Compressor`, `Mysticaland Synth`) will reside under `Products/Effects/` or `Products/Instruments/` as an independent target linking to `mysticaland_shared`.

The `MysticalandWorkspace` class contains explicit extension hooks:
```cpp
void mountPluginEditor(std::unique_ptr<juce::Component> pluginUI);
void clearMountedPlugin();
```
This enables mounting future DSP panels dynamically without altering the shell foundation.

## 4. Audio Processing Safety
- Audio pass-through is implemented in `processBlock` with zero heap allocations, zero locking, and zero latency.
- State serialization uses versioned XML metadata (`MysticalandShellState`, v0.1.0) ready for DAW session persistence.
