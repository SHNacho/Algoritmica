#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Función para hallar la subsecuencia más corta con programación dinámica
string subsecuencia(string a, string b){
	
	int a_tam= a.size();
	int b_tam= b.size();
	string subsecuencia="";
	
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
	
	//Matriz con los valores
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
	
	//Matriz con las flechas
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
	cout << endl;
	
	//Calculo de la subsecuencia
	
	int i= a_tam;
	int j= b_tam;
	
	while (matrizpadres[i][j]!=0){
		if (matrizpadres[i][j]==1){
			subsecuencia= a[i-1] + subsecuencia;
			i= i-1;
			j= j-1;
		}
		else if (matrizpadres[i][j]==2)
			i= i-1;
		else if (matrizpadres[i][j]==3)
			j= j-1;
	}
	
	
	//Return
	return subsecuencia;
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
