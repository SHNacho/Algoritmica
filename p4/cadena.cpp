#include <iostream>
#include <string>

using namespace std;


string subsecuencia(string a, string b){
	if (a.length()==0 || b.length()==0){
		return "";
	}
	else if (a[a.length()-1]==b[b.length()-1]){
		return subsecuencia(a.substr(0, a.length()-1), b.substr(0, b.length()-1))+a[a.length()-1];
	}
	else{
		string c= subsecuencia(a,b.substr(0, b.length()-1));
		string d= subsecuencia(a.substr(0, a.length()-1),b);
		if(c.length()>d.length())
			return c;
		else
			return d;
	}
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
