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
```
./src/assembleur.py [dossier/source.txt] [dossier/destination.bin]
```

Exemple :
```
./src/assembleur.py data/asm.txt bin/asm.bin
```

> Si vous ne mettez pas le nom du fichier de destination, par défaut l'assembleur écrira dans `bin/[nom source].bin`

### VM

Pour lancer la VM, utiliser le format :
```
./bin/vm bin/[source].bin
```

Exemple :
```
./bin/vm bin/asm.bin
```

> Note: Vous pouvez compiler les fichiers de la VM (qui est en C) avec le makefile en utilisant `make`

### Remarques

Ces commandes sont exécutés dans le dossier du projet soit par exemple sous Linux : `~/projet_VM_archiNum$`

## Ressources

Lien vers l'article "VM in C" : [Register VM in C](https://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C)

Lien vers une autre source "LC-3 VM": [LC-3 VM](https://www.jmeiners.com/lc3-vm/index.html)

Table ASCII : \
![Table ASCII](https://www.asciitable.com/asciifull.gif)
