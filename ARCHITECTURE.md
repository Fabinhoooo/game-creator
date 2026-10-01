# Architecture — Apex (Unreal Engine 5 / Chaos Vehicles)

## Principe
On s'appuie sur **Chaos Vehicles** (plugin Epic) plutôt que de réécrire la physique :
`AWheeledVehiclePawn` fournit déjà un `UChaosWheeledVehicleMovementComponent` qui gère
suspension, pneus, moteur, boîte, différentiel. On configure ; on ne réimplémente pas.

Le C++ du dépôt ajoute la couche jeu (caméra, input, rapports, HUD) via des **API
stables**. Les réglages physiques (valeurs numériques, bones) vivent dans le Blueprint
dérivé / Details panel — voir `SETUP-UNREAL.md`.

## Flux
```
Enhanced Input (IMC_Car + IA_*)
      │  SetThrottle/Brake/Steering/Handbrake, SetTargetGear
      ▼
AApexVehiclePawn ──► UChaosWheeledVehicleMovementComponent (Chaos)
      │                    ├─ WheelSetups[4] : UApexWheelFront ×2, UApexWheelRear ×2
      │                    ├─ EngineSetup (TorqueCurve, MaxRPM)
      │                    ├─ TransmissionSetup (ratios, manuelle)
      │                    └─ DifferentialSetup (RWD)
      ├─ SpringArm + Camera (caméra poursuite)
      ▼
AApexHUD ◄── lit GetForwardSpeed / GetEngineRotationSpeed / GetCurrentGear
```

## Fichiers (`Source/Apex/`)
| Fichier | Rôle |
|---|---|
| `ApexVehiclePawn.h/.cpp` | Pawn joueur : caméra, Enhanced Input, passage de rapports, reset |
| `ApexWheelFront.h/.cpp` | Roue avant (directrice, freinée, non motrice) — `UChaosVehicleWheel` |
| `ApexWheelRear.h/.cpp` | Roue arrière (motrice, frein à main) — `UChaosVehicleWheel` |
| `ApexHUD.h/.cpp` | HUD télémétrie (Canvas) |
| `ApexGameMode.h/.cpp` | Branche le HUD |
| `Apex.Build.cs` | Deps : ChaosVehicles, PhysicsCore, EnhancedInput |

## Pourquoi le réglage physique n'est pas dans le C++
Les membres de `EngineSetup`/`TransmissionSetup`/`SteeringSetup` de Chaos changent de
nom/forme entre versions UE (ex. `ReverseGearRatio` vs `ReverseGearRatios`). Les mettre
dans le C++ casserait la compilation selon ta version. Le Details panel est stable et
versionné avec l'asset → plus sûr. Valeurs recommandées : `SETUP-UNREAL.md` §5.

## Frontières
- **Chaos** : toute la physique (boîte noire configurée).
- **Pawn** : glue input → Chaos, caméra, rapports.
- **Présentation** : HUD (lecture seule).

## Réglages critiques
- `DefaultEngine.ini` : substepping ON, 6 substeps, dt max 0.0083.
- Centre de masse bas (Physics Asset) = le plus gros gain de stabilité.
- Collision châssis = box simplifiée, pas la silhouette complète.
