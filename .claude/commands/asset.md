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
