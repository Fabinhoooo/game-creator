# SETUP — Apex sur Unreal Engine 5 (ce que TU fais dans l'éditeur)

Le C++ de ce dépôt couvre ce qui a une API stable (caméra, Enhanced Input, passage
de rapports, HUD). La **config physique Chaos** et le **câblage mesh/roues** se font
dans l'éditeur (plus fiable d'une version UE à l'autre). Étapes exactes ci-dessous.

Prérequis : **UE 5.3+** (testé pour 5.4), **Visual Studio 2022** (Windows) ou Rider,
avec la charge de travail "Game development with C++".

---

## 1. Générer et compiler le projet
1. Clone ce dépôt (il contient `Apex.uproject` + `Source/`).
2. Clic droit sur `Apex.uproject` > **Generate Visual Studio project files**.
   (ou `UnrealBuildTool`/`GenerateProjectFiles`). Si `EngineAssociation` ne matche
   pas ta version : clic droit > **Switch Unreal Engine version** et choisis la tienne.
3. Ouvre `Apex.sln`, build en **Development Editor**, puis lance (F5). L'éditeur ouvre.
   - Plugins **Chaos Vehicles** et **Enhanced Input** sont déjà activés par le `.uproject`.

## 2. Mesh de voiture + Physics Asset (asset requis — voir `/asset`)
Chaos a besoin d'un **Skeletal Mesh** avec un os par roue.
1. Importe un modèle de voiture avec roues séparées (FBX skeletal, ou rig les roues).
   - Assets CC0/gratuits : demande `/asset une voiture de course low poly riggée`.
     À défaut, le véhicule de démo du **Vehicle Template** d'Epic sert de placeholder.
2. Crée/ajuste le **Physics Asset** (collision du châssis = 1 box simplifiée, pas la
   silhouette complète — crucial pour la stabilité).

## 3. Blueprint du véhicule (BP dérivé du C++)
1. Content Browser > Blueprint Class > **AApexVehiclePawn** → `BP_ApexVehicle`.
2. Mesh component : assigne ton Skeletal Mesh + son Anim Blueprint (ou `VehicleAnimationInstance`).
3. Dans le **Vehicle Movement Component** (Details), règle les valeurs du tableau §5.
4. **Wheel Setups** (4 entrées) :
   | Index | Wheel Class | Bone Name (selon ton skeleton) |
   |------|-------------|-------------------------------|
   | 0 | `ApexWheelFront` | os roue avant gauche |
   | 1 | `ApexWheelFront` | os roue avant droite |
   | 2 | `ApexWheelRear`  | os roue arrière gauche |
   | 3 | `ApexWheelRear`  | os roue arrière droite |

## 4. Enhanced Input (assets à créer puis assigner sur le BP)
1. Crée un **Input Mapping Context** `IMC_Car`.
2. Crée les **Input Actions** (type entre parenthèses) :
   - `IA_Throttle` (Axis1D), `IA_Brake` (Axis1D), `IA_Steer` (Axis1D),
     `IA_Handbrake` (Digital bool), `IA_GearUp` (Digital), `IA_GearDown` (Digital),
     `IA_Look` (Axis2D), `IA_Reset` (Digital).
3. Mappe dans `IMC_Car` (clavier + manette) :
   | Action | Clavier | Manette |
   |--------|---------|---------|
   | Throttle | W / ↑ | Gâchette droite (RT) |
   | Brake | S / ↓ | Gâchette gauche (LT) |
   | Steer | A/D (−/+, modifier "Negate" sur A) | Stick gauche X |
   | Handbrake | Espace | A / Croix |
   | GearUp | E | RB |
   | GearDown | Q | LB |
   | Look | Souris XY | Stick droit |
   | Reset | R | Start |
4. Sur `BP_ApexVehicle` (Class Defaults > Apex|Input) : assigne `IMC_Car` et les 8 IA.

## 5. Valeurs physiques "sim hardcore" recommandées (Movement Component)
Ajuste au feeling ensuite. Unités UE : cm, kg, N·m.

**Engine Setup**
- Max Torque ≈ **310**, Max RPM ≈ **7500**
- Torque Curve (RPM → couple normalisé 0..1) : 900→0.4, 2500→0.75, 5000→1.0, 6500→0.95, 7200→0.8, 7500→0.5
- Engine Rev Up MOI ≈ 5, Rev Down Rate ≈ 600

**Transmission Setup**
- **Use Automatic Gears : OFF** (hardcore, boîte manuelle séquentielle)
- Final Ratio ≈ **3.9**
- Forward Gear Ratios : [3.6, 2.2, 1.6, 1.2, 1.0, 0.85]
- Reverse Gear Ratio(s) : 3.2
- Gear Change Time ≈ 0.2, Transmission Efficiency ≈ 0.9

**Differential** : Rear Wheel Drive (RWD). (FWD/AWD : voir `ApexWheel*` `bAffectedByEngine`.)

**Steering** : Steering Curve (vitesse km/h → facteur) : 0→1.0, 40→0.7, 120→0.35
(réduit le braquage à haute vitesse = stabilité).

**Aérodynamique / châssis**
- Drag Coefficient ≈ 0.3–0.6 (selon version : champ `DragCoefficient`).
- Downforce : via Aerofoils (ajoute 1 aerofoil arrière orienté vers le bas) OU
  augmente l'appui par la masse et un centre de gravité bas.
- Centre de masse : abaisse-le (dans le Physics Asset) — le plus gros levier de stabilité.

**Masse** (Mesh/Physics Asset) : ≈ 1200–1400 kg.

## 6. Projet & test
1. `Project Settings > Maps & Modes` : Default GameMode = `ApexGameMode` (déjà via
   `DefaultEngine.ini`). Default Pawn = None ; place `BP_ApexVehicle` dans le niveau
   et coche **Auto Possess Player = Player 0**.
2. Crée un sol/piste avec collision. Play. Le HUD (vitesse/RPM/rapport) s'affiche.

## 7. Vers le photoréalisme (une fois que ça roule)
- Lumen (GI/réflexions) + éclairage HDRI, matériaux PBR (carrosserie = clear coat).
- Nanite sur l'environnement (pas sur le skeletal de la voiture).
- Post-process : exposition auto, motion blur, bloom léger, color grading.
- Son moteur (RPM → pitch) via MetaSounds.

---

## Limite honnête (pilotage par Claude Code)
Sur Unreal, je ne peux pas compiler ni agir dans l'éditeur depuis ici (pas
d'équivalent mature au MCP Unity). Je suis fort sur : écrire/modifier le C++,
specs, tuning de valeurs, debug de logique. Le câblage éditeur et le PIE restent
manuels de ton côté.
