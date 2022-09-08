#include <iostream>
#include <fstream>
using namespace std;

void mostrardoble(string vecstr[], int ncol, float vec[]) 
{
	for (int i = 0; i < ncol ; ++i) {
		cout << vecstr[i] << ": " << vec[i] << endl;
	}
}

void sorttriple(float vec[], int ncol, string vecstr[], int svec[])
{
	int i, imin, temp, pos;
	
	for (pos = 0; pos < ncol - 1; pos++) {
		imin = pos;
		for (i = pos + 1; i < ncol; i++) 
			if (vec[i] < vec[imin]) 
				imin = i;
		swap(vec[pos], vec[imin]);//altero el orden del vector
		swap(vecstr[pos], vecstr[imin]);//altero el orden del vector str
		swap(svec[pos], svec[imin]); // altero el orden del 3er vector
	}
}

int mayor(int vec[], int dim)
{
	int imax = 0;

	for (int i = 0; i < dim; ++i) 
		if (vec[i] > vec[imax])
			imax = i;
	 return imax;
}

int main()
{
	const int nclie {8};
	const int nprod {5};
	float kgtransp[nclie][nprod] {}; 
	float kmrecor[nclie][nprod] {};
	int cantentr[nprod] {}; //cant de entregas por producto, sin importar cliente

	string cliente[nclie];
	string tipoprod[nprod];

	ifstream archilec;
	archilec.open("Datos.txt");
	if (!archilec) {
		cout << "Hubo un error al tratar de abrir 'Datos.txt'";
		return 1;
	}
	int iclie, iprod; 
	float kg, km;
	while (archilec >> iclie >> iprod >> kg >> km) {
		kgtransp[iclie][iprod] += kg;
		kmrecor[iclie][iprod] += km;
		++cantentr[iprod]; //cada vez que una entrega (un renglon), aumenta +1

	}
	archilec.close();

	archilec.open("Nombres.txt");
	if (!archilec) {
		cout << "Hubo un error al tratar de abrir 'Nombres.txt'";
		return 1;
	}
	for (int i = 0; i < nclie && archilec >> cliente[i]; ++i); // lee los clientes, 
	for (int i = 0; i < nprod && archilec >> tipoprod[i]; ++i); // lee los productos
	archilec.close();
	
	//PUNTO 1
	cout << "Listado por clientes, de los tipos de productos que superen" <<
			" los 13000 Kg acumulados:\n";
	int topekg = 13000;
	int contcomas;
	int contprod;
	int clientesprods[nclie] {};//cantidad de tipos de productos por cliente (de 0 a 5)

	//listado
	for (int i = 0; i < nclie; ++i) { 
		contcomas = -1;// -1 para no poner una coma extra al final (si tengo 2 palabras, contcomas = 1)
		contprod = 0;
		cout << cliente[i] << ": ";
		for (int j = 0; j < nprod; ++j) {
			if (kgtransp[i][j] > topekg) {
				++contcomas;
				++contprod;
			}
		}
		for (int j = 0; j < nprod; ++j) {
			if (kgtransp[i][j] > topekg) {
				cout << tipoprod[j];
				if (contcomas > 0){
					--contcomas; //ya puse una coma, entonces saco una del contador
					cout << ", ";
				}
			}
		}
		clientesprods[i] = contprod; //se le asigna al cliente la cantidad de tipo de producto
		cout << endl;
	}

	//PUNTO 2
	cout << "\nListado de Km recorridos por un tipo de producto (ascendente):\n";
	int imaxclie = mayor(clientesprods, nclie);

	float listado[nprod] {}; //listado del punto 2 
	for (int i = 0; i < nprod; ++i) {
		listado[i] = kmrecor[imaxclie][i]; 
	}

	sorttriple(listado, nprod, tipoprod, cantentr);
	mostrardoble(tipoprod, nprod, listado);
	cout << endl;

	/* PUNTO 3
	Del listado anterior, tome el tipo de producto con mayor cantidad de kilómetros recorridos e
	informe cuantas entregas se hicieron para ese tipo de producto (sin importar para que cliente). 
	*/
	
	int mayorkm = nprod - 1; //ya que la lista es ascendente entonces agarro el ultimo elemento
	cout << "Cantidad de entregas para el tipo de producto " <<
			tipoprod[mayorkm] << ": " << cantentr[mayorkm]; 
	cout << endl;

	return 0;
}