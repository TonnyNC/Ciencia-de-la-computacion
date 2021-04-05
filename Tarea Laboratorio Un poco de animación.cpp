#include <iostream>
#include <windows.h> 

using namespace std;

void EscaleraAA(int escalera, int persona) { //Permite mostrar la escalera con escalones definidos y con una persona donde se desee
    int x = 1;
    if (persona == -escalera) {
        cout << "_P_";
    }
    else {
        cout << "___";
    }

    for (int i = 0; i < escalera * 2; i++) {
        cout << "    ";
    }
    if (persona == escalera * 2) {
        cout << "_P_" << endl;
    }
    else {
        cout << "___" << endl;
    }

    for (int i = escalera; i > 0; i--) {
        for (int j = 1; j < x; j++) {
            cout << "    ";
        }
        if (persona == -i + 1) {
            if (-i + 1 == 0) {
                cout << -i << " |___";
            }
            else
                cout << -i << " |_P_";
        }
        else {
            cout << -i << " |___";
        }

        for (int j = 1; j < (2 * i) - 1; j++) {
            cout << "    ";
        }
        if (persona == i - 1) {
            if (i - 1 == 0) {

                cout << "P" << "__|" << i << " " << endl;;
            }
            else
                cout << "_P_| " << i << " " << endl;


        }
        else {
            cout << "___| " << i << " " << endl;
        }

        x++;
    }
}

void EscaleraFija(int escalera) { //Permite mostrar la escalera con escalones definidos 
    cout << "___";
    int x = 1;
    for (int i = 0; i < escalera * 2; i++) {
        cout << "    ";
    }
    cout << "___" << endl;


    for (int i = escalera; i > 0; i--) {
        for (int j = 1; j < x; j++) {
            cout << "    ";
        }
        cout << -i << " |___";

        for (int j = 1; j < (2 * i) - 1; j++) {
            cout << "    ";
        }
        cout << "___| " << i << " " << endl;
        x++;
    }
}

void AnimarArriba(int escalera) { //Imprime la persona subiendo escalera
    for (int i = -escalera; i <= escalera * 2; i++)
    {
        EscaleraAA(escalera, i);
        Sleep(500);
        system("cls");
    }

}

void AnimarAbajo(int escalera) { //Imprime la persona bajando escalera
    for (int i = escalera * 2; i >= -escalera; i--)
    {
        EscaleraAA(escalera, i);
        Sleep(500);
        system("cls");
    }

}

int main()
{
    int a;
    cout << "Escalera de 3 fija" << endl;
    EscaleraFija(3);
    cout << "Espere 5 segundos";
    Sleep(5000);
    system("cls");

    cout << "Defina escalones para animar: ";
    cin >> a;
    AnimarArriba(a);
    system("cls");
    AnimarAbajo(a);
}