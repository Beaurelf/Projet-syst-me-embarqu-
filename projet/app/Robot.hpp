/**
 * @file Robot.hpp
 * @brief Déclaration de la classe Robot servant à contrôler les fonctionnalités de base d'un robot.
 *
 * La classe Robot agit comme un intermédiaire entre les composants matériels tels que les LED,
 * le système de son et le module de navigation, et les opérations de haut niveau qu'un utilisateur
 * peut vouloir effectuer avec un robot. Elle offre une interface simplifiée pour exécuter
 * des actions comme attendre, activer des LED, jouer des sons ou déplacer le robot.
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 2.0
 * @date [Date]
 */
#include "Led.hpp"
#include "Navigation.hpp"
#include "Button.hpp"
#include "Sound.hpp"
#include "res/enum/PathConfigState.hpp"
#include "res/enum/RobotMode.hpp"
#include "res/struct/RoadSchema.hpp"
#include "res/struct/Corner.hpp"
#include "res/struct/TabSchema.hpp"
#include "avr/interrupt.h"
#include "LineSensor.hpp"
#include "Communication.hpp"
#include "lcm_so1602dtr_m_fw.h"
#include "Chrono.hpp"
#include "customprocs.h"
#include "SearchEngine.hpp"
#include "ObstacleDetector.hpp"
#include "res/consts.hpp"

#ifndef ROBOT_H
#define ROBOT_H

/**
 * @class Robot
 * @brief Classe représentant un robot et permettant de contrôler ses actions.
 *
 * Cette classe fournit des méthodes pour effectuer des opérations courantes telles que
 * allumer des LED, jouer des mélodies ou diriger le robot. Elle encapsule la complexité
 * des composants individuels en offrant une interface unifiée.
 */
class Robot
{
public:
    /**
     * @brief Constructeur pour créer un robot avec des composants spécifiques.
     *
     */
    Robot();

    /**
     * @brief Destructeur par défaut.
     */
    ~Robot() = default;

    /**
     * @brief Met le robot en pause pour une période spécifiée.
     *
     * Cette fonction utilise un délai pour suspendre l'exécution du programme,
     * ce qui empêche toute action ou commande supplémentaire jusqu'à ce que le délai soit écoulé.
     *
     * @param delayMs Durée de l'attente en millisecondes.
     */
    void wait(uint16_t delayMs);

    /**
     * @brief Définit la couleur de la LED du robot et l'allume.
     *
     * Permet de choisir la couleur de la LED du robot parmi les options disponibles
     * et d'activer cette LED immédiatement.
     *
     * @param color La couleur à activer sur la LED du robot.
     */
    void setLedColorOn(const LedColor &color);

    /**
     * @brief Fait clignoter la LED du robot pendant une durée déterminée.
     *
     * Cette fonction active la LED dans la couleur spécifiée, la fait clignoter
     * pendant la période indiquée, puis l'éteint.
     *
     * @param color La couleur de la LED pendant le clignotement.
     * @param duration La durée totale du clignotement en millisecondes.
     */
    void blinkLed(const LedColor &color, uint32_t duration);

    /**
     * @brief Éteint la LED du robot.
     *
     * Désactive la LED actuellement allumée sur le robot.
     */
    void turnOffLed();

    void blinkLed(const LedColor &ledColor, double frequency);

    /**
     * @brief Joue une note de musique en utilisant le système sonore du robot.
     *
     * En fonction du numéro de note passé en paramètre, une fréquence sonore
     * correspondante est générée pour jouer la note.
     *
     * @param noteNumber Le numéro de la note à jouer.
     */
    void playSong(uint8_t noteNumber);

    /**
     * @brief Joue le song du film pirates des caraibes
     */
    void playPiratesDesCaraibesSong();

    /**
     * @brief Arrête la lecture de la musique actuellement jouée par le robot.
     *
     * Coupe la sortie sonore du système sonore du robot, arrêtant ainsi toute note
     * ou mélodie en cours.
     */
    void stopSong();

    /**
     * @brief Commande au robot de se déplacer dans une direction à une vitesse donnée.
     *
     * Dirige le robot à se déplacer soit vers l'avant, soit vers l'arrière, soit pour
     * tourner, à une vitesse déterminée par le paramètre de vitesse.
     *
     * @param direction La direction dans laquelle le robot doit se déplacer.
     * @param speedLeft La vitesse à laquelle le roue gauche doit se déplacer.
     * @param speedRight La vitesse à laquelle le roue gauche doit se déplacer.
     */
    void moveTo(const Direction &direction, const double speedLeft, const double speedRight);

    /**
     * @brief Effectue un virage de 90 degrés.
     * @param direction Direction du virage (gauche ou droite).
     *        Permet de spécifier la direction du virage à effectuer.
     */
    void turn90Degre(const Direction &direction);

    /**
     * @brief Effectue un demi-tour de 180 degrés.
     * @param direction Direction initiale du demi-tour (gauche ou droite).
     *        Indique la direction initiale du virage pour le demi-tour.
     */
    void turn180Degre(const Direction &direction);

    /**
     * @brief Effectue un tour complet de 360 degrés.
     * Le robot effectue un tour complet sur lui-même.
     */
    void turn360Degre();

    /**
     * @brief Suit une ligne tracée sur le sol.
     *
     * Le robot utilise ses capteurs pour suivre une ligne tracée sur le sol,
     * en ajustant continuellement sa direction pour rester sur la ligne.
     */
    void followLine();

    /**
     * @brief Recherche une ligne dans une direction spécifiée.
     * @param direction La direction dans laquelle rechercher la ligne.
     *
     * Le robot tourne dans la direction spécifiée jusqu'à ce qu'il détecte une ligne.
     */
    void findLine(const Direction &direction);

    /**
     * @brief Arrête toute activité du robot.
     *
     * Invoque l'arret complet du robot c'est a dire l'arret des moteurs, de la led et le song et timer en
     * gros arret tous le materielle en cours d'utilisation sur le robot.
     */
    void stopRobot();

    /**
     * @brief Arrête tous les mouvements du robot.
     *
     * Invoque l'arrêt de tous les moteurs du robot, le faisant s'arrêter immédiatement
     * de tout déplacement en cours.
     */
    void stopEngine();

    /**
     * @brief Obtient l'objet chrono associé au robot.
     * @return Référence à l'objet Chrono du robot.
     */
    Chrono &getChrono();

    /**
     * @brief Obtient l'objet CornerNode actuel du robot.
     * @return Référence à l'objet CornerNode du robot.
     */
    CornerNode &getCorner();

    /**
     * @brief Définit si le chrono est en cours d'exécution.
     * @param value État du chrono (true pour actif, false sinon).
     */
    void setIsChronoRunning(bool value);

    /**
     * @brief Recherche le coin ou il est placer en premier lieu sur la carte.
     *
     * Le robot se déplace et effectue un parcours jusqu'à ce qu'il trouve le coin
     * sur lequel il a ete place initialement.
     */
    void searchInitialCorner();

    /**
     * @brief Obtient la position actuelle de la ligne par rapport au robot.
     * @return État actuel de la position de la ligne (gauche, droite, centre, tres a gauche , tres a droite).
     */
    LinePosition getLinePosition();

    /**
     * @brief Construit un schéma basé sur l'étape actuelle du parcours.
     * @param step Étape actuelle du parcours.
     */
    void buildSchema(char step);

    /**
     * @brief Affiche les informations d'un nœud de coin spécifique sur la LCD.
     * @param node Le nœud du coin à afficher.
     */
    void displayNode(const Corner &node);

    /**
     * @brief Vérifie si le coin initial ou il a ete mis au debut de l'epreuve a été trouvé.
     * @return true si le coin initial a été trouvé, false sinon.
     */
    bool isInitialCornerFound() const;

    /**
     * @brief Vérifie si le robot est revenu au premier coin.
     * @return true si le robot est revenu au premier coin, false sinon.
     */
    bool isReturnToInitialCorner() const;

    /**
     * @brief Retourne au  coin initial trouvé.
     */
    void goBackToInitialCorner(const Direction &directionToTurnFirst, const Direction &directionToTurnSecond);

    /**
     * @brief Recherche le premier coin et y retourne apres avoir fini l'identification.
     *
     * Le robot cherche le premier coin grace a son parcours et y retourne lorsqu'il a devine
     * ou il a ete poser.
     */
    void searchInitialCornerAndReturn();

    // Méthodes de gestion des boutons sur la carte mère

    /**
     * @brief Vérifie si le bouton poussoir de la carte mere est pressé.
     *
     * @return true si le bouton est pressé, false sinon.
     */
    bool isButtonMotherBoardPressed();

    /**
     * @brief Vérifie si le bouton de validation sur le breadBoard est pressé.
     *
     * @return true si le bouton est pressé, false sinon.
     */
    bool isButtonValidationPressed();

    /**
     * @brief Vérifie si le bouton de selection sur le breadboard est pressé.
     *
     * @return true si le bouton est pressé, false sinon.
     */
    bool isButtonSelectionPressed();

    /**
     * @brief Définit le mode de fonctionnement du robot.
     * @param mode Le mode de fonctionnement à définir.
     */
    void setMode(const RobotMode &mode);

    /**
     * @brief Obtient le mode de fonctionnement actuel du robot.
     * @return Mode de fonctionnement actuel du robot.
     */
    RobotMode getMode() const;

    /**
     * @brief Affiche le menu de definition du mode effectuer un trajet du robot pour la selection des coordonnees.
     * @param pathConfigState État du curseur de selection.
     * @param yes pour valider ou pas les coordonnees selectionnes pour le trajet.
     */
    void displayJourneyMode(const volatile PathConfigState &pathConfigState, bool yes = true);

    // Méthodes de gestion des points de coordonnées

    /**
     * @brief incremente la ligne des coordonnnees du point de destination a definir pour le trajet.
     */
    void incrementPointRow();

    /**
     * @brief incremente la colonne des coordonnnees du point de destination a definir pour le trajet.
     */
    void incrementPointCol();

    /**
     * @brief Avance le robot avant d'effectuer un virage.
     *
     * Cette méthode permet au robot d'avancer d'une certaine distance ou pendant un certain temps
     * avant d'initier un virage, pour s'assurer d'avoir suffisamment d'espace pour manœuvrer.
     */
    void forwardBeforeTurn();

    /**
     * @brief Réinitialise le point final de navigation du robot.
     *
     * Cette méthode remet à zéro le point final de la route ou du chemin que le robot est en train de suivre,
     * permettant de commencer un nouveau tracé ou d'effectuer une nouvelle navigation.
     */
    void resetFinalPoint();

    /**
     * @brief Obtient le point initial de départ du robot.
     * @return Une référence constante aux coordonnées du point initial.
     *
     * Cette méthode retourne les coordonnées du point de départ initial du robot, qui peut être utilisé
     * comme référence pour les calculs de navigation ou de positionnement.
     */
    const Coordinate &getInitialPoint() const;

    /**
     * @brief Obtient le point final de destination du robot.
     * @return Une référence constante aux coordonnées du point final.
     *
     * Cette méthode retourne les coordonnées du point final de la destination du robot, indiquant
     * l'objectif de navigation ou le point d'arrivée de son trajet.
     */
    const Coordinate &getFinalPoint() const;

    /**
     * @brief Obtient le point de coordonnée actuel du robot.
     * @return Une référence constante aux coordonnées actuelles du robot.
     *
     * Cette méthode fournit la position actuelle du robot en termes de coordonnées, utile pour le suivi en temps réel
     * de sa position et pour la prise de décision en matière de navigation.
     */
    const Coordinate &getCurrentPoint() const;

    /**
     * @brief Définit le schéma de route pour le robot.
     * @param roadSchema Le schéma de route à suivre.
     */
    void setRoad(const RoadSchema &roadSchema);

    /**
     * @brief Prend une décision basée sur les directions données.
     * @param dir1 Première direction à considérer.
     * @param dir2 Seconde direction à considérer.
     */
    bool isGoForwardBeforeTakeDecision();

    void setIsGoForwardBeforeTakeDecision(bool value);

    void turnWithDecision(const CardinalDirection &dir1, const CardinalDirection &dir2);

    /**
     * @brief Prend une décision sur la direction à suivre.
     *
     * Le robot analyse sa position actuelle et décide de la direction à suivre.
     */
    void takeDecision();

    /**
     * @brief Suit le chemin défini dans le schéma de route.
     *
     * Le robot suit le chemin défini, en prenant des décisions à chaque intersection.
     */
    void followRoad();

    /**
     * @brief Obtient le prochain point de coordonnée sur la route.
     * @return Le prochain point de coordonnée.
     */
    Coordinate getNextPoint() const;

    /**
     * @brief Met à jour le point de coordonnée actuel du robot.
     */
    void updateCurrentPoint();

    /**
     * @brief Routine à exécuter en fin de route.
     *
     * Actions à effectuer lorsque le robot atteint la fin de son parcours.
     */
    void endRoadRoutine();

    /**
     * @brief Vérifie si le robot est à la fin du trajet.
     * @return true si le robot est à la fin du trajet, false sinon.
     */
    bool isRoadEnd() const;

    /**
     * @brief Vérifie si un obstacle a été détecté.
     * @return true si un obstacle a été détecté, false sinon.
     */
    bool isObstacleDetected() const;

    /**
     * @brief Routine à exécuter lorsqu'un obstacle est détecté.
     *
     * Actions à effectuer lorsque le robot détecte un obstacle sur son chemin.
     */
    void routineWhenObstacleDetected();

    /**
     * @brief Définit si le trajet a ete effectuer au complet.
     * @param value État de completion du trajet (true si pas encore termine, false sinon).
     */
    void setIsRoadEnd(bool value);

private:
    Led led_;                           // objet Led pour la gestion des LED.
    Sound sound_;                       // objet Sound pour la gestion des sons.
    Navigation nav_;                    // Objet pour la gestion de la navigation du robot.
    Chrono chrono_;                     // Gère le chronométrage pour diverses tâches temporisées du robot.
    SearchEngine searchEngine_;         // Moteur de recherche utilisé pour la recherche de coin.
    LCM lcm_;                           // Interface pour communiquer avec un écran LCD.
    Button buttonMotherBoard_;          // Bouton sur la carte mère pour les interactions utilisateur.
    Button buttonValidation_;           // Bouton pour valider les sélections ou les commandes.
    Button buttonSelection_;            // Bouton pour naviguer dans les menus ou les options.
    LineSensor lineSensor_;             // Capteur de ligne pour la détection et le suivi de lignes au sol.
    ObstacleDetector obstacleDetector_; // Détecteur d'obstacles pour éviter les collisions.
    LinePosition linePosition_;         // Position actuelle par rapport à la ligne détectée.
    CornerNode initialCorner_;          // coin Initial détecté pour l'identification des coins.
    bool isChronoRunning_;              // Indique si le chronomètre est actif.
    bool isFirstChronoRunning_;         // Indique si le premier chronomètre (pour un usage spécifique) est actif.
    TabSchema currentSchema_;           // Schéma actuel construit par le robot pour la navigation lors de son parcours.
    bool isInitialCornerFound_;         // Indique si le premier coin a été trouvé.
    bool isReturnToIntialaCorner_;      // Indique si le robot est revenu au premier coin.
    bool isObstacleDetected_;           // Indique si un obstacle a été détecté.
    bool isGoForwardBeforeTakeDecision_;
    RobotMode mode_;                     // Mode actuel de fonctionnement du robot.
    Coordinate initialPoint_;            // Point initial de départ du robot.
    Coordinate currentPoint_;            // Point de coordonnée actuel du robot.
    Coordinate finalPoint_;              // Point final de destination du robot.
    RoadSchema roadSchema_;              // Schéma de la route ou du trajet à suivre.
    CardinalDirection initialDirection_; // Direction initiale du robot.
    uint8_t currentIndexRoad_;           // Index actuel dans le schéma de route.
    CardinalDirection currentDirection_; // Direction courante, commence par START.
    CardinalDirection nextDirection_;    // Direction suivante à prendre par le robot.
    bool isRoadEnd_;                     // Indique si le robot est arrivé à la fin de la route prévue.
};

#endif