# ROADMAP — Apex · Sim de course hyper-réaliste (Unreal Engine 5 / Chaos Vehicles)

Cible : simulation de conduite crédible (pneus, transfert de charge, boîte réaliste,
aéro), solo, photoréalisme via Lumen/Nanite. RWD par défaut.

| Phase | État | Résumé |
|-------|------|--------|
| P0 GDD | [x] | Core loop, systèmes clés, scope MVP. Voir `GDD.md`. |
| P1 Architecture | [x] | Pawn Chaos + caméra + Enhanced Input + HUD. Voir `ARCHITECTURE.md`. |
| P2 Squelette C++ | [x] | Projet UE5 compilable : `AApexVehiclePawn`, roues AV/AR, GameMode, HUD. `Source/`. |
| P3 Câblage éditeur | [ ] | **TA machine** : compiler, BP véhicule, Wheel Setups, Enhanced Input, valeurs Chaos. Voir `SETUP-UNREAL.md`. |
| P4 Assets | [ ] | Voiture skeletal riggée, piste, HDRI, matériaux PBR, son moteur. CC0 d'abord (`/asset`). |
| P5 Systèmes MVP | [ ] | Chrono tour (triggers), secteurs, assists (ABS/TC via SetThrottle clamp), setups. |
| P6 Rendu / photoréalisme | [ ] | Lumen, Nanite env, post-process, clear coat carrosserie. |
| P7 Optimisation + Build | [ ] | Substeps, LODs, IL2... (UE: shipping build), profiling (Insights). |

## Fait ici (sans Unreal)
Squelette C++ complet + docs. Compile dès generate project files + build (voir SETUP).

## Exige TA machine (éditeur Unreal + compilateur C++)
Compiler le module, créer le Blueprint véhicule, assigner mesh/os de roues, créer les
assets Enhanced Input, régler la physique Chaos, PIE/test. Tout est dans `SETUP-UNREAL.md`.

## Note pivot
Projet initialement prévu Unity (kit uploadé conservé : `setup-unity-dispatch.sh`,
`GUIDE-COMPLET.md`, `.claude/`). **Choix retenu : Unreal 5** pour le photoréalisme
natif + Chaos Vehicles. Le kit Unity reste dans le dépôt mais n'est plus la voie active.
