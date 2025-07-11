# Planification de trajectoire 3D pour robot articulé avec obstacles

Ce projet MATLAB permet de **planifier et visualiser la trajectoire optimale d’un robot de 3 degrée de liberté dans un espace 3D**, tout en évitant des obstacles et en respectant les contraintes de la cinématique du robot. L’algorithme s’inspire du RRT\*-connect avec ajustement dynamique du pas et vérification des collisions à chaque étape.

Ce code a été écrite durant les trimestres de l'automne 2024 à l'hiver 2024 par l'équipe de robotique de héka.

## Fonctionnalités principales

* **Génération d’obstacles 3D** et visualisation via enveloppes convexes (`convhulln`, `trisurf`)
* **Algorithme de planification (RRT*-connect amélioré)*\* :

  * Exploration de l’espace 3D avec prise en compte de la présence d’obstacles
  * Ajout de points par tirage aléatoire ou via le gradient pour tendre vers la cible
  * Ajustement dynamique du pas selon la proximité des obstacles
  * Génération d’un arbre de recherche reliant le point de départ et d’arrivée
* **Vérification de collision robot-obstacle** à chaque étape de l’arbre grâce à la cinématique directe
* **Cinématique directe et inverse du robot** :

  * Détermination de la position et de l’orientation du robot pour chaque noeud du chemin
  * Résolution de l’inverse cinématique via optimisation non linéaire (moindres carrés)
* **Reconstruction automatique du chemin optimal** (backtracking sur l’arbre)
* **Visualisation avancée** : obstacles, arbre de recherche, chemin optimal et configurations du robot



## Structure des fonctions

* `calculateGradient` : Ajuste le pas d’avancement en fonction des distances aux obstacles
* `calculatePa` : Calcule la probabilité de bifurcation pour l’exploration aléatoire
* `preliminaryTree` : Génère l’arbre d’exploration (RRT\*-connect) et retourne le meilleur chemin sans collision
* `findBestPath2` : Remonte l’arbre pour reconstruire tous les chemins possibles, puis extrait le meilleur
* `DirectKin` / `InverseKin` : Cinématique directe et inverse du robot à 5 axes/membrures
* `FonctionErreur` : Calcule l’erreur position/orientation pour l’inverse cinématique
* `Rotxyz` : Calcule une matrice de rotation à partir d’angles XYZ (en degrés)
* `sampling` : Tire des points aléatoires dans un ellipsoïde 3D entre le départ et l’arrivée

---

## Prérequis

* **MATLAB** (idéalement R2020 ou ultérieur)
* Toolbox Optimization (pour `lsqnonlin`)
* Toolbox MATLAB de base pour la 3D (`trisurf`, `convhulln`, etc.)

---

## Exécution

1. **Téléchargez ou clonez** ce dépôt et placez tous les fichiers `.m` dans le même dossier.
2. **Lancez** le script principal dans MATLAB (par exemple : `run('script_principal.m')`).
3. **Visualisez** l’arbre de recherche, les obstacles, le chemin optimal et la configuration du robot.
4. Les statistiques de performance s’affichent dans la console MATLAB.

## Quelques exemples de résultats

* Obstacles 3D (polyèdres convexes) affichés avec `trisurf`
* Chemin optimal tracé en vert
* Robot affiché à chaque étape du chemin
* Arbre d’exploration complet tracé en rouge

## Licence

Open-source sous licence MIT (modifiez selon vos besoins).

