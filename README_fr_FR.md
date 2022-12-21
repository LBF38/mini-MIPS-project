# Projet mini-MIPS

[![GitHub release (latest by date)](https://img.shields.io/github/v/release/lbf38/mini-MIPS-project?style=plastic)](https://github.com/lbf38/mini-MIPS-project/releases/latest)

**README disponible dans les langues suivantes :**

[![English documentation (en_US)](https://img.shields.io/badge/-en__US-blueviolet)](https://github.com/lbf38/mini-MIPS-project/README.md)
[![French documentation (fr_FR)](https://img.shields.io/badge/-fr__FR-blueviolet)](https://github.com/lbf38/mini-MIPS-project/README_fr_FR.md)

## Table des matières

- [Projet mini-MIPS](#projet-mini-mips)
  - [Table des matières](#table-des-matières)
  - [Courte explication du projet](#courte-explication-du-projet)
  - [Installation](#installation)
  - [Utilisation](#utilisation)
    - [Assembleur](#assembleur)
    - [Machine Virtuelle](#machine-virtuelle)
  - [Démonstration](#démonstration)
  - [Une liste d'exemples simples](#une-liste-dexemples-simples)
  - [Idées](#idées)
  - [Ressources](#ressources)
  - [Crédits](#crédits)

*****

## Courte explication du projet

Ce projet est un projet académique réalisé lors de la deuxième année d'étude à l'ENSTA Bretagne (Brest, France).

Il a pour but de reproduire une version simplifiée de l'architecture MIPS (d'où le nom "mini-MIPS") afin de comprendre le fonctionnement d'un ordinateur et de son architecture interne.

Il est composé d'une machine virtuelle (VM) et d'un assembleur.
La première est écrite en C et le second en Python.

## Installation

1. Pour installer le projet, veuillez cloner ce dépôt dans un environnement Linux. Vous pouvez utiliser la commande suivante :

    ```bash
    git clone https://github.com/LBF38/mini-MIPS-project.git
    ```

2. Ensuite, vous pouvez aller dans le dossier correspondant dans votre terminal et utiliser la commande suivante pour compiler la VM :

    ```bash
    make
    ```

3. Vous pouvez maintenant utiliser la VM et l'assembleur.

## Utilisation

### Assembleur

Pour lancer l'assembleur, utilisez le format suivant :

```bash
./src/assembleur.py [folder/source.txt] [folder/destination.bin]
```

>**Note:** Cette commande est exécutée dans le dossier du projet, par exemple sous Linux : `~/mini-MIPS-project$`

Exemple :

```bash
./src/assembleur.py data/asm.txt bin/asm.bin
```

> Si vous ne spécifiez pas le nom du fichier de destination, l'assembleur écrira par défaut dans le fichier `bin/[nom fichier source].bin`

### Machine Virtuelle

Pour lancer la Machine Virtuelle, utilisez le format suivant :

```bash
./bin/vm bin/[source].bin
```

Exemple :

```bash
./bin/vm bin/asm.bin
```

> **Note:** Vous pouvez compiler les fichiers de la Machine Virtuelle (qui sont en C) avec le makefile en utilisant `make`

## Démonstration

Pour démontrer l'utilisation de l'assembleur et de la VM, vous pouvez trouver quelques exemples de code assembleur dans le dossier `data/`.

Ces fichiers respectent la sémantique choisie pour les instructions de base de la VM. Vous pouvez la trouver dans le fichier [instructions.md](docs/instructions.md).

## Une liste d'exemples simples

Dans cette partie, je vais vous présenter les fichiers que vous pouvez trouver dans le dossier `data/`, en vous donnant une courte explication de leur fonctionnement.

- `asm.txt` : Ce fichier contient un exemple de code assembleur. Il est utilisé pour démontrer l'utilisation de l'assembleur. Il permet de tester les commentaires, les instructions de base, les labels et les lignes vides.
- `affiche12.txt` : Ce fichier contient un exemple de code assembleur pour afficher 12 en effectuant une boucle de 12 itérations.
- `factorial.txt` : Ce fichier contient un exemple de code assembleur pour afficher la factorielle d'un nombre. On demande à l'utilisateur une valeur à calculer et on peut ainsi calculer la factorielle associée. Nous pouvons demander une valeur entre 0 et 12.

> Pour ce programme, le facteur limitant est le pointeur de pile qui peut être trop faible par rapport à la valeur demandée par l'utilisateur.
> Nous pouvons voir pour améliorer cela en calculant une valeur de stack pointer plus grande en fonction de la valeur demandée par l'utilisateur et de la mémoire maximale disponible.
>
> Nous sommes également limités par la représentation des nombres. Nous ne pouvons pas dépasser 2^32-1 (4294967295) car nous utilisons un `uint32_t` pour stocker les nombres.

- `fibonnaci.txt` : Ce fichier contient un exemple de code assembleur pour afficher la séquence de Fibonacci. Le code demandera à l'utilisateur une valeur et la séquence de Fibonacci sera calculée en fonction de cette valeur.

> Pour ce programme, le facteur limitant est le même que pour `factorial.txt` : la représentation des nombres conditionnera la valeur maximale disponible à calculer et à afficher.

- `boucle.txt` : Ce fichier contient un exemple de code assembleur pour lancer une boucle et afficher son index.
- `helloworld.txt` : Ce fichier contient un exemple de code assembleur pour afficher "Hello World !".

> Note : `helloworld.txt` ne fonctionne pas pour le moment car les données de type `string` ne sont pas encore reconnues ou traitées par l'assembleur.

- `instruction_test.txt` : Ce fichier contient toutes les instructions disponibles dans ma sémantique asm. Il m'a permis de tester toutes les fonctions une par une et de vérifier leur fonctionnement, lorsque j'avais des problèmes d'implémentation.

> Une meilleure méthode aurait été de faire des tests unitaires directement sur l'assembleur. Je les implémenterais si j'ai le temps. (voir [#10](https://github.com/LBF38/projet_VM_archiNum/issues/10))

## Idées

Vous trouverez ici quelques idées de programmes à réaliser en assembleur pour tester l'assembleur et la VM. Ces idées sont issues du cours d'architecture des ordinateurs de l'ENSTA Bretagne et des idées des professeurs.

- Calculer les points de la droite $y = ax + b$ à partir des paramètres fournis par l'utilisateur.
- Calcul matriciel, multiplication matricielle.
- Mise en œuvre de l'algorithme de Bresenham pour tracer une droite. ([Algorithme de Bresenham](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm))
- Séquence de Syracuse. ([Séquence de Syracuse](https://en.wikipedia.org/wiki/Collatz_conjecture))

## Ressources

- Lien vers l'article "VM en C" : [Registre VM en C](https://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C)
- Lien vers une autre ressource "LC-3 VM" : [LC-3 VM](https://www.jmeiners.com/lc3-vm/index.html)

## Crédits

Ce projet a été réalisé par [Mathis URIEN (@LBF38)](https://github.com/lbf38), étudiant en Conception de Systèmes Numériques à l'ENSTA Bretagne.

Le cours et le projet ont été donnés par les professeurs de l'ENSTA Bretagne.
