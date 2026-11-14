# Shared Library for Mysticaland Ecosystem

add_library(mysticaland_shared STATIC
    Theme/MysticalandColors.h
    Theme/MysticalandLookAndFeel.h
    Theme/MysticalandLookAndFeel.cpp
    Branding/MysticalandBranding.h
    Branding/MysticalandBranding.cpp
    Components/NavigationItem.h
    Components/NavigationItem.cpp
    Components/MysticalandHeader.h
    Components/MysticalandHeader.cpp
    Components/MysticalandSidebar.h
    Components/MysticalandSidebar.cpp
    Components/EmptyStateComponent.h
    Components/EmptyStateComponent.cpp
)

target_include_directories(mysticaland_shared PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mysticaland_shared PUBLIC
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_graphics
    juce::juce_audio_processors
)
