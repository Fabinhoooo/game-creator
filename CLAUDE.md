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
