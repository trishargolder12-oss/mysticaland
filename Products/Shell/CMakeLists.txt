# CMake configuration for Mysticaland Shell Plugin & Standalone

juce_add_plugin(MysticalandShell
    PRODUCT_NAME "Mysticaland Shell"
    COMPANY_NAME "Mysticaland Audio"
    BUNDLE_ID "com.mysticaland.shell"
    PLUGIN_MANUFACTURER_CODE Myst
    PLUGIN_CODE Mshl
    FORMATS VST3 Standalone
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    VST3_CATEGORIES Fx
)

target_sources(MysticalandShell PRIVATE
    Processor/MysticalandShellAudioProcessor.h
    Processor/MysticalandShellAudioProcessor.cpp
    Editor/MysticalandShellAudioProcessorEditor.h
    Editor/MysticalandShellAudioProcessorEditor.cpp
    Workspace/MysticalandWorkspace.h
    Workspace/MysticalandWorkspace.cpp
)

target_include_directories(MysticalandShell PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(MysticalandShell PRIVATE
    mysticaland_shared
    juce::juce_audio_utils
    juce::juce_dsp
)

juce_generate_juce_header(MysticalandShell)
