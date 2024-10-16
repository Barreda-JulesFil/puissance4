#include <iostream>
#include <cstdlib>

using namespace std;

const int LIGNES = 6;
const int COLONNES = 7;

// Fonction pour effacer l'écran selon le système d'exploitation
void effacerEcran() {
#ifdef _WIN32
    system("cls");  // Effacement de l'écran sous Windows (cmd.exe)
#else
    //cout << "\033[2J\033[H";  // Séquences ANSI pour Linux/Mac ou terminaux compatibles
    system("clear");  // Effacement de l'écran sous Linux
#endif
}

// Fonction pour afficher la grille
void afficherGrille(char grille[LIGNES][COLONNES]) {
    cout << "\n";
    for (int i = 0; i < LIGNES; ++i) {
        cout << " ";
        for (int j = 0; j < COLONNES; ++j) {
            cout << grille[i][j];
            if (j < COLONNES - 1) cout << " | ";
        }
        cout << "\n";
        if (i < LIGNES - 1) cout << "---------------------------\n";
    }
    cout << "---------------------------\n";
    cout << " 1   2   3   4   5   6   7 \n\n";  // Numérotation des colonnes
}

// Fonction pour vérifier si un joueur a gagné
bool verifierVictoire(char grille[LIGNES][COLONNES], char joueur) {
    // Vérification horizontale
    for (int i = 0; i < LIGNES; ++i) {
        for (int j = 0; j < COLONNES - 3; ++j) {
            if (grille[i][j] == joueur && grille[i][j + 1] == joueur && grille[i][j + 2] == joueur && grille[i][j + 3] == joueur) {
                return true;
            }
        }
    }

    // Vérification verticale
    for (int i = 0; i < LIGNES - 3; ++i) {
        for (int j = 0; j < COLONNES; ++j) {
            if (grille[i][j] == joueur && grille[i + 1][j] == joueur && grille[i + 2][j] == joueur && grille[i + 3][j] == joueur) {
                return true;
            }
        }
    }

    // Vérification diagonale ascendante
    for (int i = 3; i < LIGNES; ++i) {
        for (int j = 0; j < COLONNES - 3; ++j) {
            if (grille[i][j] == joueur && grille[i - 1][j + 1] == joueur && grille[i - 2][j + 2] == joueur && grille[i - 3][j + 3] == joueur) {
                return true;
            }
        }
    }

    // Vérification diagonale descendante
    for (int i = 0; i < LIGNES - 3; ++i) {
        for (int j = 0; j < COLONNES - 3; ++j) {
            if (grille[i][j] == joueur && grille[i + 1][j + 1] == joueur && grille[i + 2][j + 2] == joueur && grille[i + 3][j + 3] == joueur) {
                return true;
            }
        }
    }

    return false;
}

// Fonction pour vérifier si la grille est pleine (match nul)
bool estGrillePleine(char grille[LIGNES][COLONNES]) {
    for (int j = 0; j < COLONNES; ++j) {
        if (grille[0][j] == ' ') {
            return false;
        }
    }
    return true;
}

// Fonction pour déposer un jeton dans une colonne
bool deposerJeton(char grille[LIGNES][COLONNES], int colonne, char joueur) {
    // Trouver la première ligne vide dans la colonne (de bas en haut)
    for (int i = LIGNES - 1; i >= 0; --i) {
        if (grille[i][colonne] == ' ') {
            grille[i][colonne] = joueur;
            return true;
        }
    }
    return false;  // Si la colonne est pleine
}

// Fonction pour jouer un tour
void jouerTour(char grille[LIGNES][COLONNES], char joueur) {
    int colonne;
    bool coupValide = false;

    while (!coupValide) {
        cout << "Joueur " << joueur << ", entrez le numéro de colonne (1-7) : ";
        cin >> colonne;
        colonne--;  // Ajustement pour l'indexation du tableau (0-6)

        if (colonne >= 0 && colonne < COLONNES && deposerJeton(grille, colonne, joueur)) {
            coupValide = true;
        } else {
            cout << "Coup invalide, essayez à nouveau.\n";
        }
    }
}

int main() {
    // Initialisation de la grille
    char grille[LIGNES][COLONNES];
    for (int i = 0; i < LIGNES; ++i) {
        for (int j = 0; j < COLONNES; ++j) {
            grille[i][j] = ' ';
        }
    }

    char joueurActuel = 'X';
    bool victoire = false;

    // Boucle principale du jeu
    while (!victoire && !estGrillePleine(grille)) {
        effacerEcran();  // Effacer l'écran selon l'OS

        afficherGrille(grille);
        jouerTour(grille, joueurActuel);

        // Vérifier si le joueur actuel a gagné
        if (verifierVictoire(grille, joueurActuel)) {
            effacerEcran();
            afficherGrille(grille);
            cout << "Félicitations, joueur " << joueurActuel << " a gagné !\n";
            victoire = true;
        } else {
            // Changer de joueur
            joueurActuel = (joueurActuel == 'X') ? 'O' : 'X';
        }
    }

    if (!victoire) {
        effacerEcran();
        afficherGrille(grille);
        cout << "Match nul !\n";
    }

    return 0;
}
