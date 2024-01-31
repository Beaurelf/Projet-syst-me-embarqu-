# Projet Embarqué avec AVR ATmega324PA

## Introduction

Ce document sert d'introduction et de guide pour le projet embarqué utilisant le microcontrôleur AVR ATmega324PA. L'objectif de ce projet est de développer un système embarqué pour realiser diffferentes epreuves que sont:

- ## identification des coins:
    le bus de cette epreuve est de faire en sorte que le robot poser sur un des 4 coins de la cartes puisse faire un parcour puis retrouver le point initial ou il a ete mis puis affiche le resultat sur le LCD
- ## Parcours sur la carte:
    ici le robot debut au point (1, 1) sur la carte puis effectue le parcours le plus court jusqu'a un niveau precis
     en tenant compte de la position des poteaux.

. Nous utiliserons des composants électroniques standard sur la carte tels que des timers et capteurs comme les suiveurs de ligne et capteurs infra rouge.Nous avons developpés une librairie personnalisée pour faciliter le développement et les operations sur le robot.

## Configuration du Projet

### Matériel Nécessaire

- AVR ATmega324PA
- Carte de développement ou breadboard
- Connecteurs et câbles sertis
- Composants périphériques : piezo, capteur de suivie de ligne, capteur infrarouge
- Programmeur AVR Atmega8

### Environnement de Développement

- Os utilisés : Linux sous distribution fedora.
- Assurez-vous que les extensions ou les plugins nécessaires pour AVR sont installés.
- Configurez les paramètres du projet pour utiliser le compilateur AVR-GCC.
- Le langage de developpement utilisé est le C++.

## Librairie

### Utilisation de la Librairie

Nous avons développé une librairie spécifique pour ce projet, qui facilite l'interaction avec 
les composants matériels sur le robot et la carte mere.
 La documentation détaillée de la librairie se trouve dans le répertoire `lib/`.
### Composante de la librairie
Les composants clés de notre librairie incluent :

- `Button`: Gestion des interactions avec les boutons.
- `Led`: Contrôle des LED pour les signaux visuels.
- `Timer`: Fonctionnalités de temporisation et d'événements programmés pour utiliser le timer materiel pour le compte.
- `Sound`: Production de sons pour les alertes.
- `Navigation`: Algorithme de navigation et de détection de position.
- `ObstacleDetector`: Détection d'obstacles.
- `Can`: Cette classe permet de lire les entrées sur une des broches dû PortA et fait la conversion analogique vers le numérique  pour retourner une valeur.
- `Chrono`: La classe Chrono est une abstraction représentant un chronomètre qui utilise une instance du
Timer (comme défini dans "Timer.hpp") pour suivre le temps
- `Debug`: fourni des outils de débogage pour faciliter le développement. Lorsque le drapeau DEBUG est défini, des
messages de débogage sont affichés. Sinon, ces messages sont supprimés, optimisant ainsi les
performances
- `ExternalInterruptionConfig`: fournit une série de méthodes statiques pour configurer et gérer les
interruptions externes disponibles sur un ATmega324PA
- `ExternalInterruption`: fournit les définitions des méthodes pour gérer les interruptions externes sur un microcontrôleur AVR.
- `LineSensor`: la classe LineSensor fournit des fonctionnalités pour détecter la position d'une ligne
sur laquelle le robot est positionné.
- `Memoire_24`: Cet exemple d'utilisation d'une mémoire eeprom i2c est une modification du programme de Joerg Wunsch
twitest. c fourni avec Winavr
- `Wheel`: Cette classe représente une roue de robot, permettant de régler sa vitesse et sa direction grâce à la
modulation PWM via un objet Timer de type 0
- `Communication`: Permet la communication série (UART) entre le microcontrôleur ATmega324PA et d'autres dispositifs.
Les fonctions incluent l'initialisation de la communication UART,
- `lcm_so1602dtr_m`,`lcm_so1602dtr_m_fw`,`customprocs`: interfaces necessaire fournit pour l'utilisation de la LCD sur le robot

#### Note: 
Certaines elements utils a la librairies sont mis dans le dossiers interfaces tels certaines constantes ou les enum necessaires au fonctionnement
### Installation

Pour installer la librairie, clonez le dépôt et ajoutez-le à votre espace de travail :

```bash
git clone https://githost.gi.polymtl.ca/git/inf1900-1521/projet/

```

## Projet

Pour lancer le projet. vous devez installer le code dans la memoire flash du robot.
utiliser la commande suivante:

```bash
 make install

```
# Structure du Projet

Ce projet est structuré en plusieurs composants clés, chacun ayant un rôle spécifique dans la réalisation des objectifs du système embarqué.

## Répertoire `app`

Le répertoire `app` contient le code source principal de l'application.

- `Dijkstra` : Implémentent l'algorithme de Dijkstra pour le calcul du chemin le plus court. Utilisé pour la navigation du robot sur la carte.
- `main`: Point d'entrée du programme. Initialise le système et démarre les routines principales.
- `Robot`: Définit la classe Robot, qui encapsule les propriétés et les comportements du robot.
- `RobotManager`: Gère l'instances de robot, y compris la création, la configuration et la gestion des activités général du robot.
- `SearchEngine`: Constitue le moteur de recherche qui utilise différents algorithmes pour trouver les coins dans l'epreuve identifier les coins.

## Répertoire `res`

Le répertoire `res` contiendrait les ressources nécessaires au projet, comme les fichiers de configuration ou les données externes comme des constantes ou encore des structres de données utilisées dans le code, mais n'est pas illustré ici.

## Makefile

- `Makefile`: Contient les instructions pour compiler le projet et générer l'exécutable. Utilisez `make` pour compiler et `make install` pour déployer le programme sur le dispositif.

## Répertoire `lib`

Ce répertoire (non illustré ici) contiendrait les bibliothèques personnalisées ou les dépendances tierces nécessaires au projet.

## Auteur

- `Beaurel Fohom`
- `Christ Bouka`
- `Nelson Lekem`
- `Bourchich Aymane`
