# Apex — Jeu vidéo Unreal Engine 5 (sim de course hyper-réaliste, solo)

## Contexte
- Moteur **Unreal Engine 5** (5.3+). C++ + Blueprints. Physique via **Chaos Vehicles**.
- Sim hardcore, solo, RWD, boîte manuelle séquentielle. Photoréalisme : Lumen/Nanite.
- Code sous `Source/Apex/`. Config éditeur : voir `SETUP-UNREAL.md`.

## Règles de code
- Respecte les conventions UE : `A`/`U`/`F`/`E` prefixes, `UPROPERTY`/`UFUNCTION`,
  `TObjectPtr`, includes générés (`*.generated.h`) en dernier.
- **Ne mets pas** la config numérique Chaos (EngineSetup/TransmissionSetup/…) dans le
  C++ : les noms de membres varient selon la version UE et casseraient le build.
  Utilise des `UPROPERTY(EditAnywhere)` + le Details panel, et documente les valeurs
  dans `SETUP-UNREAL.md`. Le C++ ne touche qu'aux API stables (Set*Input, SetTargetGear,
  Get*). 
- Pas de code non compilable spéculatif : si une API est incertaine selon la version,
  signale-le explicitement plutôt que de deviner.

## Politique modèle (coût)
- Opus réservé au fort enjeu : architecture, physique/Chaos complexe, perf, refactors.
- Sonnet par défaut : gameplay, UI/HUD, Enhanced Input, câblage, debug 1er passage.
- Haiku : boilerplate pur (getters, enums, DTO).
- Debug : Sonnet d'abord ; 2 échecs sur le même bug → escalade Opus.

## Limite d'exécution
Impossible de compiler du C++ UE ni d'agir dans l'éditeur depuis le cloud (pas de pont
MCP Unreal mature). Pour toute étape éditeur/compilation : écris EXACTEMENT quoi faire,
puis attends le retour de l'utilisateur.

## Sources d'assets (MCP) — RÈGLES
Serveurs dans `.mcp.json` (`freeassets`, `sketchfab`) — moteur-indépendants, utiles ici.
1. PRIORITÉ CC0 : Kenney/Quaternius/Poly Haven/ambientCG d'abord. Sketchfab/OpenGameArt/
   itch.io seulement si rien en CC0, licence vérifiée asset par asset. Exclus le non-commercial.
   Pour une voiture : il faut un **Skeletal Mesh riggé** (roues sur os séparés).
2. CONFIRMATION : ne télécharge jamais sans accord. Propose 2-4 options (nom, source,
   licence, polycount/format).
3. ATTRIBUTION : asset CC-BY / Poly Haven → ligne dans `CREDITS.md` (crée-le si absent).
4. Dépôt dans `Content/Art/` (importé via l'éditeur Unreal côté utilisateur).

## Legacy
Le kit de dispatch Unity (`.claude/agents`, `.claude/commands`, `setup-unity-dispatch.sh`,
`GUIDE-COMPLET.md`, `INSTALL-UNITY-MCP.md`) est conservé mais **non actif** (pivot Unreal).
