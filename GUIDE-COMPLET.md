# Système complet — Dev de jeux Unity 3D piloté par Claude Code

Tout ce qui a été construit, dans l'ordre d'installation. Tu pars d'un prompt,
Claude Code choisit le bon modèle à chaque étape, récupère les assets gratuits,
et agit dans Unity. Il reste 3 choses que toi seul peux faire (fin du document).

---

## 1. Installer le kit de dispatch (le cœur)

À la racine de ton projet Unity (à côté de `Assets/`) :

```
bash setup-unity-dispatch.sh
```

Ça génère : `CLAUDE.md`, `.claude/settings.json`, 3 subagents, 11 commandes,
`.mcp.json` (sources d'assets) et `INSTALL-UNITY-MCP.md`.

Le dispatch automatique :
- Opus  → netcode/multi, shaders, perf, architecture
- Sonnet (défaut) → gameplay, UI, câblage, debug 1er passage
- Haiku → boilerplate

---

## 2. Bibliothèques d'assets gratuites (aucune clé)

Déjà branché par le kit via le serveur `freeassets`. Prérequis : **Node.js 18+**.
Sources CC0 (usage commercial libre, zéro attribution) : Kenney, Quaternius,
Poly Haven, ambientCG. + OpenGameArt / itch.io / audio (licences à vérifier).

Vérifie : lance `claude` dans le projet, tape `/mcp` → `freeassets` doit être connecté.

Optionnel — **Sketchfab** (catalogue plus large, licences mixtes, clé API requise) :
```
export SKETCHFAB_API_KEY="ta_cle"   # à mettre dans ~/.zshrc ou ~/.bashrc
```
(génère la clé : compte Sketchfab > Settings > API token ; ne la commite jamais.)

---

## 3. Pont MCP Unity (laisse Claude agir dans l'éditeur)

Suis `INSTALL-UNITY-MCP.md`. Résumé :
1. Node.js 18+.
2. Unity : Window > Package Manager > "+" > Add package from git URL >
   `https://github.com/CoderGamester/mcp-unity.git`
3. Tools > MCP Unity > Server Window > bouton **Configure Claude Code (Project)**
   (vérifie que `.mcp.json` garde aussi freeassets/sketchfab).
4. Edit > Project Settings > Editor > Enter Play Mode Settings > décoche **Reload Domain**.
5. À chaque session : Server Window > **Start Server** (pastille verte = connecté).

Débloqué : créer scènes/prefabs/matériaux, câbler composants, ajouter des assets à
la scène, lancer le Play mode, faire tourner les tests, recompiler, lire la console.

---

## 4. Navigateur (reproduire "ouvrir Sketchfab et se connecter")

Pour naviguer un site d'assets comme un humain (login inclus) : **Claude in Chrome**.
Il n'existe PAS de connecteur Sketchfab OAuth ; le navigateur est la vraie façon de
reproduire l'expérience "il ouvre le site, je me connecte".

Install (une fois) :
1. Installe l'extension **Claude for Chrome** dans ton navigateur.
2. Connecte-la à ton compte Claude (bouton Connect dans l'extension).
3. Dans une session Claude : demande "ouvre sketchfab.com et trouve-moi X".
   Claude ouvre l'onglet ; tu te connectes si besoin ; il navigue.
   Les téléchargements et actions irréversibles te demandent confirmation.

Limite : le navigateur dépose le fichier dans ton dossier Téléchargements ; c'est
ensuite le MCP Unity (ou toi) qui l'importe dans `Assets/`. Pour du volume, préfère
`freeassets` (CC0, sans clé).

---

## 5. Lancer le pipeline complet

Un seul prompt :
```
/jeu un roguelike coop 3D où l'on cultive un donjon vivant
```
Claude enchaîne GDD → archi → proto → systèmes → assets → réseau → optim → build,
en basculant de modèle tout seul. Il ne s'arrête qu'aux checkpoints : scope, archi,
téléchargements d'assets.

Commandes manuelles (si tu préfères piloter) :
`/asset`, `/tranche-gdd`, `/tranche-archi`, `/tranche-proto`, `/tranche-systeme`,
`/tranche-netcode`, `/tranche-contenu`, `/tranche-debug`, `/tranche-optim`, `/tranche-build`.

Mode mains-libres (ne demande plus à chaque édition) :
```
claude --permission-mode acceptEdits
```

---

## Ce qui est automatique vs manuel

| Étape | Qui |
|-------|-----|
| Game design, architecture, tout le code C# | Claude |
| Choix du modèle par tâche (coût optimisé) | Claude |
| Recherche + téléchargement d'assets gratuits | Claude (download sur ton accord) |
| Créer scènes/prefabs, Play mode, tests, console | Claude (via MCP Unity) |
| Naviguer un site d'assets + login | Claude in Chrome (tu te connectes) |

## Les 3 choses que TOI SEUL peux faire (incompressible)

1. **Installer les extensions/logiciels** : Unity, l'extension Claude for Chrome,
   Node.js. Et **créer le projet Unity de départ** (projet vide via Unity Hub).
2. **Te connecter / autoriser** : login Sketchfab, "Autoriser l'accès", mot de passe.
   Par sécurité, Claude ne saisit jamais d'identifiants à ta place.
3. **Garder Unity ouvert + cliquer "Start Server"** une fois par session de travail.

Tout le reste est automatisable.
