# Apex — sim de course hyper-réaliste (Unreal Engine 5)

Simulation de conduite **hardcore**, solo, photoréaliste, bâtie sur **Chaos Vehicles**
(plugin natif Epic) + Lumen/Nanite. RWD, boîte manuelle séquentielle.

## Démarrage rapide
1. **UE 5.3+** + Visual Studio 2022 (workload C++) ou Rider.
2. Clic droit `Apex.uproject` > **Generate Visual Studio project files**.
3. Ouvre `Apex.sln`, build **Development Editor**, lance (F5).
4. Suis **[SETUP-UNREAL.md](SETUP-UNREAL.md)** : Blueprint véhicule, roues, Enhanced
   Input, valeurs physiques Chaos recommandées (sim hardcore).

## Docs
- **[GDD.md](GDD.md)** — concept, core loop, scope MVP.
- **[ARCHITECTURE.md](ARCHITECTURE.md)** — découpage C++ + rôle de Chaos.
- **[ROADMAP.md](ROADMAP.md)** — phases et état.
- **[SETUP-UNREAL.md](SETUP-UNREAL.md)** — tout ce qui se fait dans l'éditeur.

## Code (`Source/Apex/`)
`AApexVehiclePawn` (caméra + Enhanced Input + rapports), `UApexWheelFront`/`UApexWheelRear`,
`AApexHUD` (télémétrie), `AApexGameMode`. Le C++ couvre les API stables ; la config
physique Chaos se règle dans l'éditeur (voir ARCHITECTURE § "Pourquoi").

## Limite de pilotage par Claude Code
Sur Unreal, l'assistance agentique est limitée : je peux écrire/modifier le C++, les
specs et le tuning, mais **pas compiler ni agir dans l'éditeur depuis le cloud** (pas
d'équivalent au MCP Unity). Le câblage éditeur et le test restent manuels.

## Legacy — kit Unity (non actif)
Le projet a d'abord été initialisé avec un kit de dispatch Unity (uploadé). Conservé
pour référence mais **non utilisé** : `setup-unity-dispatch.sh`, `GUIDE-COMPLET.md`,
`INSTALL-UNITY-MCP.md`, `.claude/` (agents/commandes Unity), `.mcp.json` (les serveurs
d'assets `freeassets`/`sketchfab` restent utiles, moteur indépendant).
