# 🔮 Mysticaland

> **A gothic boutique audio plugin ecosystem shell.**  
> VST/AU/CLAP host — Plugin Rack — Instrument Browser — DAW Bridge

[![Vercel](https://img.shields.io/badge/Deployed-Vercel-black?logo=vercel)](https://vercel.com/monolith-vi)
[![License](https://img.shields.io/badge/License-MIT-crimson)](LICENSE)

---

## What is Mysticaland?

Mysticaland is a **unified audio plugin ecosystem** in the spirit of Output Arcade, Waves Central, and Native Instruments Komplete Kontrol — but with a dark, ornate, gothic luxury identity built for modern creators.

It acts as:
- A **standalone hub app** to browse, install, and manage plugin suites (EQ, Compression, Reverb, Synths, Drums...)
- A **single VST3/AU/CLAP shell** that DAWs (Ableton, FL Studio, Logic, Reaper) load on a mixer channel — which then hosts all Mysticaland instruments and effects internally

## Color Identity
- **Background:** `#0a0808` — Void Black
- **Accent:** `#8b1a1a` — Deep Crimson
- **Glow:** `#d4821a` — Candle Amber
- **Text:** `#e8d5c0` — Warm Parchment

## Stack
- **Web Hub:** Vite + React → Vercel
- **Auth & DB:** Supabase
- **Standalone Shell:** Electron
- **Audio Engine:** Web Audio API + WebAssembly DSP
- **DAW Bridge:** VST3 / AU / CLAP (C++ shell, Phase 3)

## Project Structure
```
mysticaland/
├── src/
│   ├── pages/          # Hub pages (Home, Plugins, Instruments, Library, Store)
│   ├── components/     # Shared UI components
│   ├── engine/         # Audio engine core
│   ├── plugins/        # Official plugin modules
│   └── styles/         # Design tokens & global styles
├── public/             # Static assets
├── index.html
└── vite.config.js
```

## Roadmap
- [x] Phase 0 — Foundation (Repo, Vercel, Design System)
- [ ] Phase 1 — The Web Hub Shell
- [ ] Phase 2 — DSP Core & First Plugins (Nebula EQ, Pressor)
- [ ] Phase 3 — Electron Standalone + DAW Bridge (VST3/AU)
- [ ] Phase 4 — Community Marketplace & Plugin SDK

---

*"Stars can't shine without darkness."*
