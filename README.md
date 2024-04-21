# Robotique
Code et algorithmes de contrôle robotique

## Explications et raisonnement du contrôleur utilisé
L'objectif de ce contrôleur est de permettre au code de contrôle d'amener le moteur à une position désirée par l'équipe robotique. Un encodeur par moteur est utilisé pour obtenir une rétroaction sur la position actuelle du moteur.

Pour la première version du contrôleur utilisé pour gérer le mouvement des moteurs, nous utilisons un contrôleur Proportionnel-Dérivé (PD). Il est voulu que la composante intégrale, d'habitude utilisée (contrôleur PID), car l'objectif est d'atteindre la position désirée par l'équipe robotique sans jamais dépasser la valeur d'angle à atteindre. Le temps mis pour atteindre cette valeur n'est pas critique (se compte dans l'ordre des secondes et doit rester contrôlé). 

Il n'est donc pas nécessaire d'utiliser une composante intégrale dans le contrôleur pour faire converger plus rapidement le moteur vers sa position désirée. Référez vous au [lien suivant](https://ctms.engin.umich.edu/CTMS/index.php?example=Introduction&section=ControlPID) pour de plus amples informations à propos de l'utilité de chaque composante d'un contrôleur commun.

## Test de Ziegler-Nichols
Dans le code de test, vous pourrez observer 'deux' versions. La première permet de simuler un système qui ne comporte qu'une valeur **K_CRITICAL**. Cette valeur, impliquée dans le calcul de la fréquence du PWM qui contrôle la vitesse du moteur, fais en sorte que le système complet oscille perpétuellement avec la même amplitude. De cette oscillation, on obtient donc la valeur **K_CRITICAL** et **T_CRITICAL** (la période de l'oscillation constante). Ce test, effectué généralement à la main, est le test de Ziegler-Nichols.

Les valeurs du contrôleur PD découlent donc de ces deux valeurs. [La page wikipedia suivante](https://en.wikipedia.org/wiki/Ziegler%E2%80%93Nichols_method) donne les valeurs de KP et KD à utiliser lorsque l'on veut un système spécifique selon les résultats obtenus par le test de Ziegler-Nichols. **Notez que ces valeurs sont à titre indicatif et doivent être adaptées à chaque système lors des tests physiques**.

## Véritable calcul de la fréquence PWM
La 'deuxième' partie du fichier de test du PID consiste à calculer une nouvelle fréquence de PWM en utilisant les valeurs **KP** et **KD** calculées grâce au test de Ziegler-Nichols. C'est une simple équation mettant en commun l'erreur et l'erreur dérivée sur la position.

## Simulation VS réalité
Il existe une différence entre la simulation et la réalité: Au sein de la simulation, nous simulons l'évolution de la position du moteur sans prendre en compte des éléments comme la charge supportée par le moteur à l'instant _t_ ou encore les différentes forces externes qui pourraient être appliquées lors du mouvement du moteur. C'est le problème d'une simulation aussi simpliste que celle-ci. Les tests du contrôleur actuel (et futur) doivent donc être faits pour évaluer n'importe quelle situation dans laquelle évoluera le moteur (et plus généralement le bras robotique!).

## Questions? Réponses
Section servant de FAQ pour la simulation. À remplir au fil du temps.
