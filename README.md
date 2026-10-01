# game-creator

Kit de dev de jeux **Unity 3D** piloté par **Claude Code** : dispatch automatique
du modèle selon la tâche (Opus/Sonnet/Haiku), sources d'assets gratuites (CC0) via
MCP, et un orchestrateur bout-en-bout (`/jeu`) qui enchaîne GDD → archi → proto →
systèmes → assets → réseau → optim → build.

## Démarrage

1. Copier ce dépôt à la racine d'un projet Unity (à côté de `Assets/`).
2. Prérequis : **Node.js 18+** (pour les serveurs MCP `freeassets`/`sketchfab`).
3. Lancer `claude` dans le projet, vérifier `/mcp` (→ `freeassets` connecté).
4. Point d'entrée : `/jeu <idée du jeu en une phrase>`.

Détails complets : **[GUIDE-COMPLET.md](GUIDE-COMPLET.md)**.
Pont éditeur Unity (agir dans l'éditeur) : **[INSTALL-UNITY-MCP.md](INSTALL-UNITY-MCP.md)**.

## Contenu

- `CLAUDE.md` — politique de dispatch modèle + règles d'assets/licences.
- `.claude/agents/` — 3 subagents (`unity-netcode-perf`, `unity-gameplay`, `unity-boilerplate`).
- `.claude/commands/` — `/jeu`, `/asset`, et les 10 `/tranche-*`.
- `.mcp.json` — serveurs d'assets (`freeassets` CC0 sans clé, `sketchfab` optionnel).
- `setup-unity-dispatch.sh` — script générateur (source de vérité de ce kit).
