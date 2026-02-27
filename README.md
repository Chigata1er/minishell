# Minishell

**Minishell** est un projet de l’école 42 visant à créer un **interpréteur de commandes minimaliste** inspiré de Bash. L’objectif est de comprendre le fonctionnement interne d’un shell et de gérer l’exécution de commandes en ligne de commande.

---

## 💡 Objectifs du projet

* Implémenter un **shell interactif** capable de :

  * Exécuter des commandes système (comme `ls`, `pwd`, `echo`, etc.)
  * Gérer les **redirections** (`>`, `<`, `>>`) et les **pipes** (`|`)
  * Gérer les **variables d’environnement**
  * Supporter les **built-ins** : `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`

* Comprendre la gestion des **processus**, **fork**, **execve**, et **signaux**.

---

## 🛠️ Installation

1. Cloner le dépôt :

```bash
git clone <URL_DU_DEPOT>
```

2. Compiler le programme :

```bash
make
```

3. Lancer le shell :

```bash
./minishell
```

---

## 📝 Usage

* Lancer des commandes système :

```bash
minishell> ls -l
```

* Utiliser les redirections :

```bash
minishell> echo "Hello" > file.txt
```

* Utiliser les pipes :

```bash
minishell> ls | grep ".c"
```

* Built-ins :

```bash
minishell> cd ../
minishell> export VAR=value
minishell> echo $VAR
```

---

## ⚙️ Compilation & nettoyage

* Compiler : `make`
* Supprimer les fichiers objets : `make clean`
* Supprimer le binaire : `make fclean`
* Recompiler proprement : `make re`

---

## 📌 Points techniques

* **Parsing des commandes** : gestion des quotes simples et doubles, espaces multiples.
* **Gestion des erreurs** : commandes invalides, fichiers introuvables, etc.
* **Signal handling** : Ctrl+C pour interrompre les commandes, Ctrl+D pour quitter le shell.
* **Memory management** : allocation dynamique et libération de toutes les ressources.

---

## 🔗 Ressources

* [Documentation officielle 42](https://github.com/42School)

