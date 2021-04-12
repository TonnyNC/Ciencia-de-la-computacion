
#include <iostream>
#include <windows.h>

using namespace std;

char Eleccion(){
    char valor;
    
    do{
        cout << "Elija 'X' o 'O': ";
        cin >> valor;
    } 
    while (valor != 'X' && valor != 'O' && valor != 'x' && valor != 'o' && valor != '0');

     if (valor == 'X' || valor == 'x')
    {
        cout << "Eligio " << valor << endl;
    }
    if (valor == 'O' || valor == 'o' || valor == '0')
    {
        cout << "Eligio " << valor << endl;
    }
    return valor;
}

void iniciar(char mat[5][5]) { 
    char x = '1';
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            if (i % 2 != 0) {
                if (j % 2 != 0) {
                    mat[i - 1][j - 1] = x;
                    x++;
                }
                else
                    mat[i - 1][j - 1] = '|';
            }
            else {
                mat[i - 1][j - 1] = '-';
            }
            
        }

    }
}



void impMatriz(char mat[5][5]) {

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << mat[i][j];
        }
        cout << endl;
    }
}

void ponerX(char mat[5][5], int valor) {
    
    if (valor == 1 ){
        mat[0][0] = 'X';
    }
    else if (valor == 2){
        mat[0][2] = 'X';
    }
    else if (valor == 3) {
        mat[0][4] = 'X';
    }
    else if (valor == 4) {
        mat[2][0] = 'X';
    }
    else if (valor == 5) {
        mat[2][2] = 'X';
    }
    else if (valor == 6) {
        mat[2][4] = 'X';
    }
    else if (valor == 7) {
        mat[4][0] = 'X';
    }
    else if (valor == 8) {
        mat[4][2] = 'X';
    }
    else if (valor == 2) {
        mat[4][4] = 'X';
    }
}

void ponerO(char mat[5][5], int valor) {
    
    if (valor == 1) {
        mat[0][0] = 'O';
    }
    else if (valor == 2) {
        mat[0][2] = 'O';
    }
    else if (valor == 3) {
        mat[0][4] = 'O';
    }
    else if (valor == 4) {
        mat[2][0] = 'O';
    }
    else if (valor == 5) {
        mat[2][2] = 'O';
    }
    else if (valor == 6) {
        mat[2][4] = 'O';
    }
    else if (valor == 7) {
        mat[4][0] = 'O';
    }
    else if (valor == 8) {
        mat[4][2] = 'O';
    }
    else if (valor == 2) {
        mat[4][4] = 'O';
    }
}

void pedir(char matriz[5][5],char op) {
    int ubicacion;
    cout << "Donde poner" << op << " ";
    cin >> ubicacion;
    if (op == 'X' && op == 'x')
        ponerX(matriz, ubicacion);
    else
        ponerO(matriz, ubicacion);
}

int main()
{  
    char matriz[5][5];
    char op = Eleccion();
    iniciar(matriz);
    impMatriz(matriz);
    pedir(matriz, op);
    impMatriz(matriz);
    system("pause");
}

