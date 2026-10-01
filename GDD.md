# GDD — Apex (Unreal Engine 5)

## Core loop (une phrase)
Piloter une voiture à la limite de l'adhérence sur un circuit, lire le grip et le
transfert de charge, et battre son propre chrono tour après tour.

## Pilier
**Sensation de conduite hardcore + photoréalisme.** Le feeling vient de Chaos Vehicles
bien réglé (pneus, suspension, boîte) ; le réalisme visuel de Lumen + matériaux PBR.

## 3–5 systèmes clés
1. **Physique véhicule (Chaos Vehicles)** — suspension par roue, modèle de pneu,
   moteur à courbe de couple, boîte manuelle séquentielle, différentiel RWD.
2. **Contrôle & feedback** — Enhanced Input (clavier + manette, volant plus tard),
   HUD télémétrie (vitesse/RPM/rapport), caméra poursuite.
3. **Chrono & course** — temps au tour, secteurs via triggers, delta.
4. **Assists réglables** — ABS, TC, aide au braquage (off par défaut en hardcore).
5. **Rendu photoréaliste** — Lumen (GI/réflexions), Nanite (env), post-process, PBR.

## Scope MVP
- 1 voiture pilotable (Chaos réglé hardcore), clavier **et** manette.
- 1 circuit simple avec collision + sol.
- Caméra poursuite, HUD, reset position.
- Chrono tour mono-voiture.

## Plus tard (hors MVP)
- IA adverses, plusieurs circuits, garage (setups), dégâts, volant + force feedback,
  replays, multijoueur (Chaos + replication = gros morceau).

## Choix tranchés
- **Moteur : Unreal 5** (photoréalisme natif, Chaos Vehicles). Pivot depuis Unity.
- **Transmission : RWD, boîte manuelle séquentielle** d'abord (hardcore).
- **Substepping physique ON** (6 substeps) pour la stabilité à haute vitesse.
