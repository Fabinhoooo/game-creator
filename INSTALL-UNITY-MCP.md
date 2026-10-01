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
