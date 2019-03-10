Deroulement de la scéance :

- Maintenant que la construction est terminé je peux enfin tester mon programme !
- Le programme est consultable ici : https://github.com/CharlyDucrocq/RouletteAuto/blob/master/Documents/Programmes/Roulette.ino
- Le programme n'as pas fonctionner tout de suite. Premièrement il fallait cabler le système. Après avoir perdu du temps sur de bêtes erreurs de cablage, j'ai pu remarquer que les fonctions attachInterrup ne fonctionnaient que sur les entrées 2 et 3 mais grâce a la bibliothèque PinChangeInt que monsieur Masson, que je remercie, m'a conseillé, j'ai pu les associer aux entrées analogiques de A0 à A4.
- Mise à part cela et quelques modifications sur la construction afin que les capteurs d'aimant capte correctement et quelques corrections de programme, cela conclut cette scéance. Cependant, la salle nous a été mis a disposition le jeudi suivant, me permettant de continuer la programmation.
- Après quelque test, la roue fourni des resultats de différence temporel entre la réponse du capteur d'aiment le plus recent et le capteur de proximité. 
- Cependant, ces valeurs étant trop variable d'un essai à un autre, sans parler des abbérance qui peuvent sortir. De ce fait, j'ai préféré faire tourner la roue plusieurs tours afin de fournir plusieurs résultats et de les traiter. D'abord en repérant et retirant les valeurs abberantes, ensuite en faisant la moyenne des valeur saisie. 
- Cette scéance supplémentaire s'est terminé après avoir corrigé tous les bugs de la fonction qui gérera cette demande nommé "traitement" (voir programme).

- A l'heure ou j'écris cette phrase, nous somme le lendemain, le vendredi, et je suis actuellement en train de realiser divers test de mon programme afin d'assimiler les résultat aux différentes cases numerotés.
- Les resultats sont prometteurs, les ecarts entre les differents essais semblent correspondre sans trop d'écart d'un essai à l'autre sur une meme case.
- Ci-contre un lien vers un tableau exel resumant ces mesures : https://github.com/CharlyDucrocq/RouletteAuto/blob/master/Documents/Relev%C3%A9s_temps_Roulette.xlsx
- Si tout se passe bien, le programme sera capable de renvoyer les bon numéro avant la présentation, si tel est le cas vous verrais ci dessous une MAJ affirmant cette reussite avec vidéo a l'appuie.
- Mauvaise nouvelle : La courroie s'est mise à sauté pour une raison que j'ignore alors que je n'ai pris que un tiers des mesures... Impossible de refaire fonctionner correctement le système... J'espère que changer la courroie ou la roue denté qui l'entraine suffira à résoudre le problème mais je ne sais pas si je pourrai avoir accés à la salle avec tout le matériel avant la présentation de mercredi. Je croise les doigts.


Ci dessous des photo du rendu actuel de cette partie du projet :

![Avancement actuel](https://github.com/CharlyDucrocq/RouletteAuto/blob/master/Documents/Images/20190308_192647.jpg?raw=true)

