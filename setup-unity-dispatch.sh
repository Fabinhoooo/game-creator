#!/usr/bin/env bash
# ============================================================================
# setup-unity-dispatch.sh  (v2 — + connexions assets Sketchfab / Unity MCP)
# Kit de dispatch modèle + sources d'assets pour dev Unity 3D (solo + multi).
# Un seul fichier : lance-le à la RACINE de ton projet Unity (à côté d'Assets/).
#   bash setup-unity-dispatch.sh
# ============================================================================
set -euo pipefail
mkdir -p .claude/agents .claude/commands

# --- CLAUDE.md -------------------------------------------------------------
cat > CLAUDE.md << 'EOF'
# Projet — Jeu vidéo Unity 3D (solo + multijoueur)

## Contexte
- Moteur Unity, 3D, solo ET multijoueur. C# (MonoBehaviour + ScriptableObjects).
- Coût : utiliser le modèle le moins cher qui fait le job. Opus réservé au fort enjeu.

## Politique de dispatch modèle (OBLIGATOIRE)
Délègue chaque tâche au bon subagent (.claude/agents/) :
| Subagent | Modèle | Pour |
|----------|--------|------|
| unity-netcode-perf | opus   | netcode/multi, shaders/compute, perf, architecture, gros refactors |
| unity-gameplay     | sonnet | DÉFAUT : gameplay, UI, save/load, câblage, debug 1er passage |
| unity-boilerplate  | haiku  | boilerplate : getters, commentaires, rename, DTO, [SerializeField] |

Debug : Sonnet d'abord ; 2 échecs sur le même bug -> escalade Opus.
Ne dégrade jamais une tâche netcode/shader/perf pour économiser.

## Sources d'assets (MCP) — RÈGLES
Serveurs dans .mcp.json :
- `freeassets` : sources gratuites. CC0 (usage commercial libre, zéro attribution) =
  Kenney, Quaternius, Poly Haven, ambientCG. Mixte (à vérifier) = OpenGameArt, itch.io,
  audio. AUCUNE clé requise pour les sources CC0. À PRIVILÉGIER.
- `sketchfab` : catalogue plus large, licences mixtes, clé API requise. Secondaire.
- `unity` (optionnel) : import dans l'éditeur.

1. PRIORITÉ CC0 : propose d'abord Kenney/Quaternius/Poly Haven/ambientCG. N'utilise
   Sketchfab/OpenGameArt/itch.io que si rien de convenable en CC0, et vérifie alors
   la licence asset par asset. Exclus tout ce qui n'est pas autorisé en commercial.
2. CONFIRMATION : ne télécharge JAMAIS sans mon accord. Propose 2-4 options
   (nom, source, licence, polycount/format si dispo), j'en choisis une.
3. ATTRIBUTION : pour un asset CC-BY (ou Poly Haven dont l'API demande un crédit
   visible), ajoute une ligne dans CREDITS.md à la racine (crée-le si absent).
4. Format glb/gltf, dépôt dans Assets/Art/Imported/. Si le MCP `unity` est actif et
   l'éditeur ouvert, importe l'asset ; sinon indique le chemin.

## Note plan
Session par défaut sur Sonnet (settings.json). Si l'épinglage `model` des subagents
est ignoré (bug connu sur certains Max), reste sur Sonnet et /model opus à la main
pour les tâches unity-netcode-perf.
EOF

# --- settings.json ---------------------------------------------------------
cat > .claude/settings.json << 'EOF'
{
  "model": "sonnet"
}
EOF

# --- .mcp.json  (connexions MCP, partagé projet) ---------------------------
# Sketchfab : clé via variable d'env SKETCHFAB_API_KEY (ne commite pas ta clé).
# Unity : décommente après avoir installé le package MCP Unity dans le projet.
cat > .mcp.json << 'EOF'
{
  "mcpServers": {
    "freeassets": {
      "command": "npx",
      "args": ["-y", "threenative-asset-mcp"]
    },
    "sketchfab": {
      "command": "npx",
      "args": ["-y", "sketchfab-mcp-server"],
      "env": {
        "SKETCHFAB_API_KEY": "${SKETCHFAB_API_KEY}"
      }
    }
  }
}
EOF
# --- Guide d'installation du pont MCP Unity --------------------------------
cat > INSTALL-UNITY-MCP.md << 'EOF'
# Pont MCP Unity — réduire les pauses au minimum

Une fois ce pont branché, Claude Code peut agir DANS l'éditeur : créer scènes,
prefabs, matériaux, composants ; ajouter des assets à la scène ; lancer le Play
mode ; faire tourner les tests ; recompiler ; lire la console. Les pauses de /jeu
tombent aux seules vraies décisions.

Source : https://github.com/CoderGamester/mcp-unity  (MIT, Unity 6+, Node 18+)

## Une seule fois
1. Node.js 18+ installé :  node --version
2. Dans Unity : Window > Package Manager > "+" (haut-gauche) >
   "Add package from git URL..." > colle :
       https://github.com/CoderGamester/mcp-unity.git
   > Add. Attends l'import.
3. Connecte-le à Claude Code : Tools > MCP Unity > Server Window >
   bouton "Configure Claude Code (Project)".
   -> Ça ajoute l'entrée "mcp-unity" dans le .mcp.json du projet (chemin relatif,
      portable). VÉRIFIE ensuite que .mcp.json contient toujours AUSSI "freeassets"
      et "sketchfab" (ne les écrase pas ; au besoin, remets-les).
4. (pour tests/Play mode) Edit > Project Settings > Editor > "Enter Play Mode
   Settings" > DÉCOCHE "Reload Domain" (sinon la connexion saute en Play mode).

## À CHAQUE session de travail
5. Unity ouvert > Tools > MCP Unity > Server Window > "Start Server".
   La pastille passe au vert quand Claude Code est connecté.
6. Lance Claude Code dans le projet :  claude
   Vérifie :  /mcp   (doit lister "mcp-unity" connecté)
   Teste :    "crée une scène vide nommée Level1"

## Sécurité (déjà bon par défaut)
- Un token d'auth par projet est généré automatiquement (Library/McpUnity/).
- L'install de packages Unity par l'IA est DÉSACTIVÉE par défaut. Ne l'active
  (Server Window > "Allow Package Installation") que si tu sais pourquoi.

## Ce que ça NE fait toujours pas
- Créer le projet Unity lui-même : fais d'abord un projet vide via Unity Hub.
- Tourner sans Unity ouvert : le serveur vit dans l'éditeur (sauf mode headless
  -batchmode avancé, hors scope ici).
EOF
rm -f .claude/UNITY_MCP_SNIPPET.json 2>/dev/null || true


# --- SUBAGENTS -------------------------------------------------------------
cat > .claude/agents/unity-netcode-perf.md << 'EOF'
---
name: unity-netcode-perf
description: >
  Ingénieur Unity haut de gamme. À UTILISER pour multijoueur/netcode (NGO, Mirror,
  Photon, Fishnet, RPC, server-authoritative, prédiction, réconciliation, lag
  compensation, replication, synchro d'état) ; OU shaders/compute/HLSL ; OU perf
  (profiler, GC alloc, draw calls, batching, frame drops, DOTS/ECS/Burst) ; OU
  architecture et gros refactors. Pas pour gameplay standard ni boilerplate.
model: opus
---
Ingénieur Unity senior réseau/perf/archi (jeu 3D solo + multi).
Netcode : correction (autorité serveur, déterminisme) > latence > bande passante.
Perf : mesure (Profiler) avant d'optimiser ; zéro alloc/frame en boucle chaude.
Archi : propose le découpage avant de coder ; signale les impacts long terme.
EOF

cat > .claude/agents/unity-gameplay.md << 'EOF'
---
name: unity-gameplay
description: >
  Ingénieur gameplay Unity 3D — subagent PAR DÉFAUT. Scripting C#/MonoBehaviour
  standard : mécaniques, controllers, input, UI, inventaire, combat, ScriptableObjects,
  save/load, IA basique, câblage scènes/prefabs, debug 1er passage. Défaut pour tout
  ce qui n'est pas réseau, shaders, perf ou boilerplate.
model: sonnet
---
Ingénieur gameplay efficace ; gros du volume.
Code C# propre, testable, sans sur-ingénierie. Debug : hypothèse->vérif->correction ;
après 2 échecs sur bug réseau/shader/perf, escalade vers unity-netcode-perf.
Pas de logique réseau ici : passe par les systèmes dédiés.
EOF

cat > .claude/agents/unity-boilerplate.md << 'EOF'
---
name: unity-boilerplate
description: >
  Assistant rapide/économe pour boilerplate mécanique UNIQUEMENT : getters/setters,
  commentaires XML, rename, reformat, DTO/struct/enum simples, [SerializeField], stubs.
  Pas dès qu'il y a design, debug, réseau, shaders ou perf.
model: haiku
---
Tâches mécaniques, vite, sans fioritures. Applique exactement la demande.
Zéro décision de design ; sinon renvoie vers unity-gameplay ou unity-netcode-perf.
EOF

# --- COMMANDES /tranche-* --------------------------------------------------
cat > .claude/commands/tranche-gdd.md << 'EOF'
---
description: Tranche 0 — GDD / concept.
argument-hint: [idée ou pitch du jeu]
---
Cadrage conception, modèle de session (Sonnet). Idée : $ARGUMENTS
Produis : 1) core loop en une phrase 2) 3-5 systèmes clés 3) scope MVP vs plus tard
4) spécificités multi à trancher tôt. Ne code rien. UNE question si un choix bloque.
EOF
cat > .claude/commands/tranche-archi.md << 'EOF'
---
description: Tranche 1 — Architecture (fort enjeu -> Opus).
argument-hint: [périmètre à architecturer]
---
Délègue à **unity-netcode-perf** (Opus). Périmètre : $ARGUMENTS
Avant code : découpage managers + responsabilités ; pattern retenu + pourquoi ;
frontière gameplay/réseau ; structure dossiers. Attends validation avant d'implémenter.
EOF
cat > .claude/commands/tranche-proto.md << 'EOF'
---
description: Tranche 2 — Prototype / core loop.
argument-hint: [mécanique à prototyper]
---
Délègue à **unity-gameplay** (Sonnet). Mécanique : $ARGUMENTS
Scène jouable minimale, input inclus. Direct, pas de sur-ingénierie.
EOF
cat > .claude/commands/tranche-systeme.md << 'EOF'
---
description: Tranche 3 — Système gameplay.
argument-hint: [système à implémenter]
---
Délègue à **unity-gameplay** (Sonnet). Système : $ARGUMENTS
Propre, testable, respecte l'archi. Pas de réseau ici : expose des hooks si besoin.
EOF
cat > .claude/commands/tranche-netcode.md << 'EOF'
---
description: Tranche réseau (fort enjeu -> Opus).
argument-hint: [feature réseau]
---
Délègue à **unity-netcode-perf** (Opus). Feature : $ARGUMENTS
Ordre : correction (autorité serveur, déterminisme) > latence > bande passante.
Précise la stack si besoin (NGO, Mirror, Photon, Fishnet).
EOF
cat > .claude/commands/tranche-contenu.md << 'EOF'
---
description: Tranche 4 — Contenu & boilerplate.
argument-hint: [tâche répétitive]
---
Délègue à **unity-boilerplate** (Haiku). Tâche : $ARGUMENTS
Exactement la demande, rien de plus. Pas de design ; sinon renvoie vers unity-gameplay.
EOF
cat > .claude/commands/tranche-debug.md << 'EOF'
---
description: Tranche 5 — Debug (Sonnet, escalade Opus).
argument-hint: [bug / erreur]
---
Délègue à **unity-gameplay** (Sonnet). Bug : $ARGUMENTS
Hypothèse->vérif->correction. 2 échecs OU bug réseau/shader/perf : STOP et escalade
vers **unity-netcode-perf** (Opus) en résumant ce qui a été tenté.
EOF
cat > .claude/commands/tranche-optim.md << 'EOF'
---
description: Tranche 6 — Optimisation (fort enjeu -> Opus).
argument-hint: [cible / symptôme perf]
---
Délègue à **unity-netcode-perf** (Opus). Cible : $ARGUMENTS
Mesure (Profiler) avant d'optimiser. Cause identifiée, pas intuition. Priorise le gain réel.
EOF
cat > .claude/commands/tranche-build.md << 'EOF'
---
description: Tranche 7 — Build & release.
argument-hint: [plateforme cible]
---
Délègue à **unity-gameplay** (Sonnet). Plateforme : $ARGUMENTS
Étapes concrètes (Build/Player Settings, pièges plateforme). Droit au but.
EOF

# --- COMMANDE /asset (Sketchfab -> Unity, semi-auto, licence vérifiée) -----
cat > .claude/commands/asset.md << 'EOF'
---
description: Cherche un asset 3D sur Sketchfab, vérifie la licence, et (sur accord) télécharge/importe.
argument-hint: [description de l'asset, ex: "caisse en bois low poly"]
---
Délègue à **unity-gameplay** (Sonnet). Recherche demandée : $ARGUMENTS

Procédure OBLIGATOIRE :
1. Cherche via le MCP **freeassets** EN PRIORITÉ (sources CC0 : Kenney, Quaternius,
   Poly Haven, ambientCG). N'utilise sketchfab/OpenGameArt/itch.io que si rien de
   convenable en CC0.
2. Présente 2-4 options : nom, SOURCE, LICENCE, polycount/format si dispo. Préfère
   le CC0. Exclus toute licence non commerciale.
3. ATTENDS mon choix. Ne télécharge rien sans mon accord explicite.
4. Après accord : télécharge en glb/gltf dans Assets/Art/Imported/. Si l'asset est
   CC-BY ou Poly Haven, ajoute l'attribution dans CREDITS.md (crée-le si absent).
5. Si le MCP unity est actif et l'éditeur ouvert, importe l'asset ; sinon indique le chemin.
EOF

# --- ORCHESTRATEUR /jeu (un prompt -> tout le pipeline) --------------------
cat > .claude/commands/jeu.md << 'EOF'
---
description: Orchestrateur bout-en-bout — d'une idée à un projet Unity jouable. Pilote toutes les tranches.
argument-hint: [idée du jeu en une phrase]
---
Tu es l'ORCHESTRATEUR du projet. Idée de départ : $ARGUMENTS

Tu pilotes TOUT le pipeline en déléguant chaque phase au bon subagent (donc au bon
modèle) et en récupérant les assets gratuits. Reste sur le modèle de session (Sonnet)
pour coordonner ; délègue le travail lourd. Tu ne t'arrêtes QU'aux checkpoints marqués.

D'ABORD : écris ROADMAP.md (liste des phases + état [ ]/[x] + une ligne de résumé par
phase). Tiens-le à jour après CHAQUE phase.

Déroulé :
- P0 GDD : core loop, 3-5 systèmes, scope MVP, points multi à trancher.
  >>> CHECKPOINT : fais-moi valider le scope (1 question max) avant de continuer.
- P1 Architecture : délègue à **unity-netcode-perf** (Opus) — découpage managers,
  patterns, frontière gameplay/réseau, structure de dossiers.
  >>> CHECKPOINT : fais-moi valider l'archi avant d'écrire du code.
- P2 Prototype : délègue à **unity-gameplay** — scène jouable, mécanique principale, input.
- P3 Systèmes MVP : délègue à **unity-gameplay** (et **unity-boilerplate** pour le répétitif),
  un système à la fois, dans l'ordre du ROADMAP.
- P4 Assets : pour chaque besoin visuel/audio, applique la procédure /asset
  (freeassets CC0 d'abord). >>> CHECKPOINT par lot : propose, j'approuve les téléchargements.
- P5 Réseau (si multi) : délègue à **unity-netcode-perf** (Opus).
- P6 Optimisation : quand le MVP tourne, délègue à **unity-netcode-perf** (Opus).
- P7 Build : délègue à **unity-gameplay**.

RÈGLES :
- N'interromps QU'aux >>> CHECKPOINT (scope, archi, téléchargements). Sinon enchaîne
  sans me demander.
- Après chaque phase : mets à jour ROADMAP.md + donne un résumé de 2 lignes.
- Si une étape exige l'éditeur Unity (créer le projet, compiler, tester, importer un
  asset) et que le MCP `unity` n'est pas actif, STOP, dis-moi EXACTEMENT quoi faire
  dans l'éditeur, attends mon "ok", puis reprends où tu en étais.
- Respecte la politique de dispatch modèle et de licences du CLAUDE.md.
EOF


cat << 'MSG'
✅ Kit v2 installé (dispatch modèles + bibliothèques gratuites + Sketchfab).

PRÊT TOUT DE SUITE (aucune clé) :
  - freeassets : Kenney, Quaternius, Poly Haven, ambientCG (CC0) + OpenGameArt/itch/audio.
    Requiert juste Node.js 18+ (tourne via npx).

OPTIONNEL :
  - Sketchfab (catalogue plus large, licences mixtes) : génère une clé
    (compte Sketchfab > Settings > API token) puis, avant de lancer Claude Code :
        export SKETCHFAB_API_KEY="ta_cle"   (à mettre dans ~/.zshrc/.bashrc ; ne la commite pas)
  - MCP Unity Editor (réduit les pauses au minimum) : suis INSTALL-UNITY-MCP.md
    (package git + bouton "Configure Claude Code (Project)" + Start Server).

Lance 'claude' ici, puis : /mcp (vérifie freeassets), /agents, / (commandes).

>>> POINT D'ENTRÉE PRINCIPAL — un seul prompt fait tout :
        /jeu un roguelike coop 3D où l'on cultive un donjon vivant
    L'orchestrateur enchaîne GDD -> archi -> proto -> systèmes -> assets -> réseau
    -> optim -> build, en choisissant le modèle par phase. Il ne s'arrête qu'aux
    checkpoints (scope, archi, téléchargements d'assets).

Commandes manuelles si tu préfères piloter : /asset, /tranche-archi, /tranche-netcode...
(Alternative assets plus complète, à installer à part : le MCP "ASSETMCP" génère
 automatiquement CREDITS.md et un ASSET_MANIFEST.json.)
MSG
