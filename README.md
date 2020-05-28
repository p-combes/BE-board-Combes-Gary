# Assistant de jardinage connecté

L'assistant de jardinage connecté est un programme complet qui permet de monitorer les plantes d'une jardinière connectée avec arrosage automatique et éclairement intelligent. L'application utilise pour la démonstration un environnement simulé également compris dans le pack téléchargeable ici.

## Compilation et exécution

La ligne de commande suivante permet de compiler et d'exécuter le projet

```bash
g++ -Wall -Wextra -Werror *.cpp -o appli && ./appli
```
Cependant, nous avons réalisé le projet sous CodeBlocks avons toujours compilé/executé via le logiciel. Nous recommandons donc cette approche. 

## Usage

L'execution du programme provoque l'affichage dans le terminal des données enregistrées par les différents capteurs ainsi que les actions en cours.
La simulation est une journee de printemps, nous avons implémenté pour le test deux plantes : Cactus et Tulipe. Vous pouvez observer sur le terminal les différents paramètres et les décisions du sytème.
