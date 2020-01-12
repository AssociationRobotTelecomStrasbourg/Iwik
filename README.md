# Iwik

Sources for a prototype differential drive robot using two stepper motors driven by TMC2130 drivers by Trinamic

## Software

- [ ] Asynchronous movement
  - [ ] State machine
    - [ ] STOP
    - [ ] ROTATE
    - [ ] TRANSLATE
    - [ ] BRAKE
- [ ] Verify the workings of the odometry
- [ ] Add backward configuration
- [ ] ESP01
  - [ ] Sent movement command [resource](https://github.com/jeelabs/esp-link)

## Hardware

- [ ] Add an extension for a pencil to draw forms
- [ ] Repair the lidar extension

## Formation

### Installation

1. Clone the repository `git clone https://github.com/AssociationRobotTelecomStrasbourg/Iwik.git`
2. Initialize submodule, `git submodule update --init`

### Mouvement

Tout les unitées de distance sont en mm et les angles en radian.
Pour utiliser pi pour les angles, `M_PI`

`turn_and_go(maximum_speed, acceleration)`
`turn_and_go.translateFrom(distance)`
`turn_and_go.rotateFrom(delta_theta)`
`turn_and_go.rotateTo(theta)`
`turn_and_go.goTo(x, y)`

```c++
void loop() {
    // (x, y, theta) donne la position et orientation du robot p
    // (0, 0, 0)
    turn_and_go.translateFrom(500); // Avance de 500 mm
    // (500, 0, 0)
    turn_and_go.rotateFrom(M_PI); // Tourne de M_PI
    // (500, 0, 0)
    turn_and_go.translateFrom(500); // Avance de 500 mm
    // (0, 0, M_PI)
    turn_and_go.rotateFrom(M_PI); // Tourne de M_PI
    // (0, 0, 0)
    delay(1000);
}
```

est équivalent à

```c++
void loop() {
    // (0, 0, 0)
    turn_and_go.goTo(500, 0); // Oriente et avance vers (500, 0)
    turn_and_go.goTo(0, 0); // Oriente vers M_PI puis avance de 500 mm
    // (0, 0, 0)
    turn_and_go.rotateTo(0);
    // (0, 0, 0)
    delay(1000);
}
```

#### Challenges

- Dessine un carré
- Dessine une étoile

### Odométrie

#### Explication

L'odométrie permet de situer le robot dans l'espace en se basant sur la rotation des moteurs, l'entraxe du robot, le périmètre et le ratio de la taille des roues.

On a besoin de la ratio de la taille des roues car elles ne sont pas parfaites et l'une est un peu plus grandes que l'autres.

#### Réglage

Le réglage de l'odométrie est un processus itératif.

On commence par des approximation des paramètres en mesurant directement sur le robot le périmètre des roues, l'entraxe du robot et l'on considère que les roues sont exactement de la même taille.

Une fois ceci fait on utilise les méthodes de calibrations pour affiner les mesures encore et encore jusqu'à ce que l'erreur de positionnement soit négligeable.

- [ ] Ajout de schéma pour illustrer chaque effet des paramètres de l'odométrie

1. Calibre `step_ratio` le ratio de la taille des roues
    1. Utilise `step_ratio_calibration()` dans `setup()`
    2. Change `step_ratio` selon la déviation
        - Sens anti-horaire -> Diminue
        - Sens horaire -> Augmente
2. Calibre `wheel_perimeter` le périmètre des roues
    1. Utilise `wheel_perimeter_calibration()` in `loop()` followed by `delay(1000)`
    2. Change `wheel_perimeter` selon la déviation
        - Too short -> decrease
        - Too far -> increase
        - Utilise l'équation
3. Calibre `center_distance` l'entraxe du robot
    1. Utilise `center_distance_calibration()` in `setup()`
    2. Change `wheel_perimeter` selon la déviation
        - Trop court -> Diminue
        - Trop loin -> Augmente
        - Utilise l'équation

Le programme python `odometry.py` permet de calculer les nouvelles valeurs de `wheel_perimeter` et `center_distance`.

Il suffit de modifier les valeurs dans `odometry.py` et l'exécuter.

`python3 odometry.py`

#### Challenge

- Régler l'odométrie le mieux possible

### Lidar

`lidar.readDistance()`

#### Challenges

- Suis la main d'une certaine distance
- Évite les obstacles sur le chemin

### Gestion de la batterie

`batteryVoltage()` donne la tension en Volt.
