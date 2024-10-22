pour toute question ou problème concernant cette doc contactez moi à :

mail : erwan.martin666@gmail.com 

insta : erwan_martin

ou trouvez moi sur linkedin.

# Guide utilisateur

J’avais fait des derniers tests sur le robot qui n’ont pas marché, il va falloir remettre les bons programmes. Fiez vous à la section suivante pour upload les bonnes versions.

**ATTENTION** : Je retiens votre attention sur le fait que le programme n’était pas sécurisé, j’avais un souci en fait le Raspberry envoyait des commandes serial en continu à l’arduino et celui ci à certains moment n’était “pas pret” à recevoir du serial. L’arduino alors plantait mais les drivers restaient dans le même état. donc si le robot était en train de rouler, il continuait sa route, ce qui peut être dangereux vu son poids. Bien que le robot puisse rouler théoriquement j’ai préféré ne pas le mettre en circulation libre dans le hall précisément pour cette raison. Les tests mentionnés plus haut avaient pour but de régler ce problème en établissant un protocole de communication sécurisé au niveau de cette communication Serial, mais ils n’ont pas été concluants et j’ai terminés l’école sans pouvoir terminer cette sécurisation (ca me déchire le cœur mdr). Le message étant passé, voici comment piloter le robot une fois les programmes fonctionnels réuploadés.

1. Allumez le robot avec l’interrupteur à l’intérieur de la sphère (pensez a brancher/recharger la batterie)
2. attendez entre 30 secondes et 1/2 minute
3. connectez votre smartphone ou un ordinateur au réseau “BB8_Hotspot” qui apparait
4. allez dans un navigateur et tapez l’ip 192.168.4.1
5. Pilotez le robot avec le joystick

Pour un pilotage optimal vous devez évidemment refermer la sphère (d’ou le problème pour arreter le robot il faut réouvrir la sphère c’est au moins 4 vis à dévisser en même temps qu’il roule, faites bien attention, que le robot se casse est une chose, mais évitez de vous blesser).

# Guide plus technique

pour se connecter une fois le robot allumé, la commande sera:

```bash
ssh bb8@192.168.4.1
```

(normalement c’est ca

envoyez un mail à [erwan.martin666@gmail.com](mailto:erwan.martin666@gmail.com) afin d’avoir le mot de passe root du bb8.

# Montage

Le guide de montage se trouve ici dans mon drive (il n’y restera pas indéfiniment je pense)

https://drive.google.com/file/d/1l6Ph_m1TDdqeMdkyFY4mCtKBUVavWGxr/view?usp=sharing

Notez bien qu’on a du changer des pièces car c’étaient des références américaines, meme pour les moteurs etc, on a du charcuter des pièces pour faire rentrer certains moteurs etc. ne vous fiez pas à 1000% à cette documentation :)

## branchements de la doc originelle:

![image](https://github.com/user-attachments/assets/a4b86a78-5f96-40f6-9130-fd373df78b6f)


on a viré la partie son et fait des branchements plus spécifiques.

## Branchements de l’arduino aux drivers

Tableau driver par rapport a l’arduino MEGA:

| X | L_EN | R_EN | L_PWM | R_PWM |
| --- | --- | --- | --- | --- |
| Drive1 | 7 | 8 | 12 | 13 |
| Drive2 | 7 | 8 | 12 | 13 |
| Balance (side to side) | 6 | 9 | 10 | 11 |

# Control programs

Un arduino controle directement les drivers avec les pins, et il écoute le serial du raspberry pi. Le câble qui les relie est branché du Raspberry en USB vers le Serial de l’Arduino.

## Arduino MEGA

le dernier code de  l’arduino mega qui fonctionnait se trouve dans le repo dans:

**/test/maindrive/liaisonInterfaceWeb/final_basic_code.ino**

Attention, il faut reflasher ce code et remodifier la page web et le programme python lancé par le Raspberry pour que tout refonctionne.

## Raspberry pi et interface web

Il y a deux éléments ici:

- le server web contenant la page web que l’utilisateur chargera qui affiche le joystick et envoie les requêtes au Raspberry.
pour le remplacer dans le Raspberry c’est dans: **/var/www/html** (quelque part par la)
l’html se trouve dans le repo dans : **/test/maindrive/interface_web/intex.html**
- le programme python servant d’API, qui recoit les requêtes de la page web, fait el traitement et envoie les commandes en Serial à l’Arduino.
ce programme python pour le remplacer doit se trouver à la racine de l’utilisateur bb8 (normalement). Il doit garder son nom sinon la procédure de lancement au démarrage finira en erreur.
il se trouve dans le github dans :  **/test/maindrive/interface_web/server.py**

# Architecture de controle
Voici un schéma de l'architecture pour aider à visualiser le processus:
![BB8_global_schema_rogne](https://github.com/user-attachments/assets/65465662-120b-4446-85ef-d05efff853ec)

vous avez en 1 une demande du navigateur web de la machine utilisateur au serveur web, le serveur web envoie la page en 2, puis des requètes sont envoyés depuis la page à l'API en 3. L'API va ensuite via Serial donner des information de controle à l'arduino en 4. Pour finir l'Arduino va piloter les moteurs gràce à ces informations en PWM en 5.
