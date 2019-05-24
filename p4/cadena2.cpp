#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Función de reconstrucción recursiva
string reconstruccion(vector <vector <int>> matriz, string a, string b, int i, int j){
	if (i==0 || j==0)
		return "";
	else if (a[i-1] == b[j-1])
		return reconstruccion (matriz, a, b, i-1, j-1) + a[i-1];
	else if (matriz[i-1][j]>matriz[i][j-1])
		return reconstruccion (matriz, a, b, i-1, j);
	else
		return reconstruccion (matriz, a, b, i, j-1);
}


//Función para hallar la subsecuencia más corta con programación dinámica
string subsecuencia(string a, string b){
	
	int a_tam= a.size();
	int b_tam= b.size();
	
	//Creacion de la matriz con los valores y la matriz con las direcciones
	vector <vector <int>> matriz(a_tam+1, vector <int> (b_tam+1, 0));
	vector <vector <int>> matrizpadres(a_tam+1, vector <int> (b_tam+1, 0));
	
	for (int i=1; i<a_tam+1; i++){
		for (int j=1; j<b_tam+1; j++){
			if (a[i-1]==b[j-1]){
				matriz[i][j]= matriz[i-1][j-1]+1;
				matrizpadres[i][j]= 1;
			}
			else{
				if (matriz[i-1][j]>matriz[i][j-1]){
					matriz[i][j]= matriz[i-1][j];
					matrizpadres[i][j]= 2;
				}
				else{
					matriz[i][j]= matriz[i][j-1];
					matrizpadres[i][j]= 3;
				}
			}
		}
	}
	
	
	
	//Impresion de la matriz con los valores
	cout << "    ";
	
	for (int i=0; i<b_tam; i++)
		cout << b[i] << " ";
	
	cout << endl;
	
	for (int i=0; i<a_tam+1; i++){
		if(i>0)
			cout << a[i-1] << " ";
		else
			cout << "  ";
		for (int j=0; j<b_tam+1; j++){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	
	//Impresion de la matriz con las direcciones
	cout << endl;
	cout << endl;
	cout << "    ";
	
	for (int i=0; i<b_tam; i++)
		cout << b[i] << " ";
	
	cout << endl;
	
	for (int i=0; i<a_tam+1; i++){
		if(i>0)
			cout << a[i-1] << " ";
		else
			cout << "  ";
		for (int j=0; j<b_tam+1; j++){
			if (matrizpadres[i][j]==0)
				cout << "0 ";
			else if (matrizpadres[i][j]==1)
				cout << "\\ ";
			else if (matrizpadres[i][j]==2)
				cout << "| ";
			else if (matrizpadres[i][j]==3)
				cout << "- ";
		}
		cout << endl;
	}
	
	
	//Return
	return reconstruccion(matriz, a, b, a_tam, b_tam);
}


int main(int argc, char **argv){
	
	if(argc != 3){
        cout << "ERROR en los argumentos. Hay que indicar 2 cadenas de caracteres." << endl;
        exit(-1);
    }
    
    string cadena1= argv[1];
    string cadena2= argv[2];
    
    cout << subsecuencia(cadena1, cadena2) << endl;
    
    return 0;
}
