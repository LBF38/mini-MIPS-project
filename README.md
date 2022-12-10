# Projet VM pour le cours d'Architecture des ordinateurs

## Description

Projet concernant le cours d'Architecture des ordinateurs de l'ENSTA Bretagne.
Création d'une Machine Virtuelle pour comprendre le fonctionnement des ordinateurs et leur architecture interne.
Création d'un assembleur en python pour convertir des instructions rédigées en assembleur, en un fichier binaire à exécuter sur la VM.

## Liste des instructions disponibles

Lien vers le fichier qui contient l'ensemble des instructions disponibles dans la VM et reconnu par l'Assembleur :
[Instructions](instructions.md)

## Comment utiliser le projet

### Assembleur

Pour lancer l'assembleur, utiliser le format :

```bash
./src/assembleur.py [dossier/source.txt] [dossier/destination.bin]
```

Exemple :

```bash
./src/assembleur.py data/asm.txt bin/asm.bin
```

> Si vous ne mettez pas le nom du fichier de destination, par défaut l'assembleur écrira dans `bin/[nom source].bin`

### VM

Pour lancer la VM, utiliser le format :

```bash
./bin/vm bin/[source].bin
```

Exemple :

```bash
./bin/vm bin/asm.bin
```

> Note: Vous pouvez compiler les fichiers de la VM (qui est en C) avec le makefile en utilisant `make`

### Remarques

Ces commandes sont exécutés dans le dossier du projet soit par exemple sous Linux : `~/projet_VM_archiNum$`

## Démonstration

Pour démontrer l'utilisation de l'assembleur et de la VM, vous pourrez trouver des exemples de codes en assembleur dans le dossier `data/`.

Ces fichiers respectent la sémantique choisie pour les instructions de base de la VM. Vous pouvez la retrouver dans le fichier [instructions.md](instructions.md).

### Liste des fichiers d'exemples

Je vais vous présenter les fichiers d'exemples que vous pouvez trouver dans le dossier `data/`, en vous donnant une courte explication de leur fonctionnement.

- `asm.txt` : Ce fichier contient un exemple de code en assembleur. Il est utilisé pour démontrer l'utilisation de l'assembleur. Il permet de tester les commentaires, les instructions de base, les labels et les lignes vides.
- `affiche12.txt` : Ce fichier contient un exemple de code en assembleur pour afficher 12 en effectuant une boucle de 12 itérations.
- `factorial.txt` : Ce fichier contient un exemple de code en assembleur pour afficher le factoriel d'un nombre. On demande à l'utilisateur une valeur à calculer et on peut ainsi calculer la factorielle associée. On peut demander une valeur entre 0 et 12.

> Pour ce programme, le facteur limitant est le stack pointer qui peut être trop faible par rapport à la valeur demandée par l'utilisateur.
> A voir comment on peut améliorer cela en calculant une valeur de stack pointer plus grande en fonction de la valeur demandée par l'utilisateur et de la mémoire maximale disponible.
>
> On est également limité par la représentation des nombres. On ne peut pas dépasser 2^32-1 (4294967295) car on utilise un `uint32_t` pour stocker les nombres.

- `fibonnaci.txt` : Ce fichier contient un exemple de code en assembleur pour afficher la suite de Fibonnaci. Le code va demander une valeur à l'utilisateur et la suite de Fibonnaci sera calculée en fonction de cette valeur.
  
> Pour ce programme, le facteur limitant est le même que celui de `factorial.txt` : la représentation des nombres va conditionner la valeur maximale disponible à calculer et à afficher.

- `boucle.txt` : Ce fichier contient un exemple de code en assembleur pour lancer une boucle et afficher son indice.
- `helloworld.txt` : Ce fichier contient un exemple de code en assembleur pour afficher "Hello World!".

> Note: `helloworld.txt` ne fonctionne pas pour le moment car les données de type `string` ne sont pas encore reconnues ni traitées par l'assembleur.

- `instruction_test.txt` : Ce fichier contient l'ensemble des instructions disponibles dans ma sémantique d'asm. Il m'a permis de tester toutes les fonctions une à une et de vérifier leur fonctionnement, lorsque j'avais des problèmes d'implémentation.

> Une meilleure méthode aurait été de faire des tests unitaires directement sur l'assembleur. Je les implémenterais si j'ai le temps. (voir [#10](https://github.com/LBF38/projet_VM_archiNum/issues/10))

### Autres idées de programme à réaliser

Vous trouverez ici quelques idées de programmes à réaliser en assembleur pour tester l'assembleur et la VM. Ces idées viennent du cours d'Architecture des ordinateurs de l'ENSTA Bretagne et des idées des professeurs.

- Calcul des points de la droite $y = ax + b$ à partir des paramètres fournis par l'utilisateur.
- Calcul matriciel, multiplication matricielle.
- Implémentation de l'Algorithme de Bresenham pour tracer une droite. ([Algorithme de Bresenham](https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_segment_de_Bresenham))
- Suite de Syracuse. ([Suite de Syracuse](https://fr.wikipedia.org/wiki/Suite_de_Syracuse))

## Ressources

Lien vers l'article "VM in C" : [Register VM in C](https://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C)

Lien vers une autre source "LC-3 VM": [LC-3 VM](https://www.jmeiners.com/lc3-vm/index.html)

Table ASCII : \
![Table ASCII](https://www.asciitable.com/asciifull.gif)
