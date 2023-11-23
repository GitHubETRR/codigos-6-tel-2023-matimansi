
#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

void advertencia (void);
int menu_principal (void);
int menu_cuadrado (void);
int menu_rectangulo (void);
int menu_circulo (void);
bool func_cuadrado (void);
bool func_rectangulo (void);
bool func_circulo (void);

class formas_geometricas
{
	private:
		float area, perimetro;
	public:
		void set_area (float);
		void set_perimetro (float);
		float get_area (void);
		float get_perimetro (void);
};

class cuadrado : public formas_geometricas
{
	private:
		float lado;
	public:
		cuadrado (float);
		void set (float);
		void calcular_area (void);
		void calcular_perimetro (void);
		float get (void);
};

class rectangulo : public formas_geometricas
{
	private:
		float alto, ancho;
	public:
		rectangulo (float, float);
		void set (float, float);
		void calcular_area (void);
		void calcular_perimetro (void);
		float get_alto (void);
		float get_ancho (void);
};

class circulo : public formas_geometricas
{
	private:
		float radio, diametro;
		double pi = M_PI;
	public:
		circulo (float);
		circulo (float, float);
		void set (float);
		void set (float, float);
		void calcular_diametro (float);
		void calcular_area (void);
		void calcular_perimetro (void);
		float get_radio (void);
		float get_diametro (void);
};

void formas_geometricas::set_area (float _area)
{
	area = _area;
}

void formas_geometricas::set_perimetro (float _perimetro)
{
	perimetro = _perimetro;
}

float formas_geometricas::get_area (void)
{
	return area;
}

float formas_geometricas::get_perimetro (void)
{
	return perimetro;
}

cuadrado::cuadrado (float _lado)
{
	set_area(0);
	set_perimetro(0);
	if (_lado > 0) set(_lado);
	else
	{
		cout << "No se puede asignar un valor < 0 a la medida del lado, se le asignara 0cm" << endl;
		set(0);
	}
}

void cuadrado::set (float _lado)
{
	if (_lado > 0)
	{
		lado = _lado;
		cout << "Se creo un cuadrado de " << lado << "cm de lado" << endl;
	}
	else cout << "ERROR: La medida del lado debe ser mayor a 0" << endl;
}

void cuadrado::calcular_area (void)
{
	set_area(lado * lado);
}

void cuadrado::calcular_perimetro (void)
{
	set_perimetro(lado * 4);
}

float cuadrado::get (void)
{
	return lado;
}

rectangulo::rectangulo (float _alto, float _ancho)
{
	set_area(0);
	set_perimetro(0);
	set(_alto, _ancho);
}

void rectangulo::set (float _alto, float _ancho)
{
	if ((_alto > 0) && (_ancho > 0))
	{
		alto = _alto;
		ancho = _ancho;
		cout << "Se creo un rectangulo de " << alto << "cm de alto y " << ancho << "cm de ancho" << endl;
	}
	else cout << "ERROR: La medida del lado debe ser mayor a 0" << endl;
}

void rectangulo::calcular_area (void)
{
	set_area(alto * ancho);
}

void rectangulo::calcular_perimetro (void)
{
	set_perimetro((alto * 2) + (ancho * 2));
}

float rectangulo::get_alto (void)
{
	return alto;
}

float rectangulo::get_ancho (void)
{
	return ancho;
}

circulo::circulo (float _radio)
{
	set_area(0);
	set_perimetro(0);
	calcular_diametro(_radio);
	set(_radio, diametro);
}

circulo::circulo (float _radio, float _diametro)
{
	set_area(0);
	set_perimetro(0);
	set(_radio, _diametro);
}

void circulo::calcular_diametro (float _radio)
{
	diametro = _radio * 2;
}

void circulo::set (float _radio)
{
	if (_radio > 0)
	{
		radio = _radio;
		calcular_diametro(radio);
		cout << "Se creo un circulo de " << radio << "cm de radio (" << diametro << "cm de diametro)" << endl;
	}
}

void circulo::set (float _radio, float _diametro)
{
	if ((_radio > 0) && (_diametro > 0))
	{
		radio = _radio;
		diametro = _diametro;
		cout << "Se creo un circulo de " << radio << "cm de radio (" << diametro << "cm de diametro)" << endl;
	}
}

void circulo::calcular_area (void)
{
	set_area(pi * pow(radio, 2));
}

void circulo::calcular_perimetro (void)
{
	set_perimetro(pi * diametro);
}

float circulo::get_radio (void)
{
	return radio;
}

float circulo::get_diametro (void)
{
	return diametro;
}

int main()
{
	int input;
	bool flag = false, salir = true;
	advertencia();
	do
	{
		do
		{
			input = menu_principal();
		} while (!((input >= 0) && (input < 8)));
		switch (input)
		{
			case 1:
				flag = func_cuadrado();
				system("cls");
				break;
			case 2:
				flag = func_rectangulo();
				system("cls");
				break;
			case 3:
				flag = func_circulo();
				system("cls");
				break;
			case 0:
				salir = false;
				break;
		}
	} while (salir);
	cout << "Saliendo..." << endl;
	return 0;
}

void advertencia (void)
{
	cout << "+==============================================+" << endl;
	cout << "|               <<<< Cuidado >>>>              |" << endl;
	cout << "|----------------------------------------------|" << endl;
	cout << "| Si se desea escribir valores con decimales,  |" << endl;
	cout << "| se deberea utilizar [ . ] en lugar de [ , ]  |" << endl;
	cout << "|----------------------------------------------|" << endl;
	cout << "| Cada vez que se actualicen las medidas de    |" << endl;
	cout << "| cualquier forma geometrica, se deberan       |" << endl;
	cout << "| calcular nuevamente el Area y el Perimetro   |" << endl;
	cout << "| para poder actualizarlos en base a las       |" << endl;
	cout << "| nuevas medidas                               |" << endl;
	cout << "+==============================================+" << endl;
	fflush(stdin);
	cout << "\n[ ENTER ] para continuar";
	getchar();
	system("cls");
}

int menu_principal (void)
{
	int input;
	cout << "+=========================================+" << endl;
	cout << "|         <<<< Menu Principal >>>>        |" << endl;
	cout << "|-----------------------------------------|" << endl;
	cout << "| > Cuadrado........................[ 1 ] |" << endl;
	cout << "| > Rectangulo......................[ 2 ] |" << endl;
	cout << "| > Circulo.........................[ 3 ] |" << endl;
	cout << "|-----------------------------------------|" << endl;
	cout << "| > Salir...........................[ 0 ] |" << endl;
	cout << "+=========================================+" << endl;
	cout << ">>> ";
	cin >> input;
	return input;
}

int menu_cuadrado (void)
{
	int input;
	cout << "+=========================================+" << endl;
	cout << "|         <<<< Menu Cuadrado >>>>         |" << endl;
	cout << "|-----------------------------------------|" << endl;
	cout << "| > Actualizar medida lado..........[ 1 ] |" << endl;
	cout << "| > Calcular Area...................[ 2 ] |" << endl;
	cout << "| > Calcular Perimetro..............[ 3 ] |" << endl;
	cout << "| > Ver medida lado.................[ 4 ] |" << endl;
	cout << "| > Ver Area........................[ 5 ] |" << endl;
	cout << "| > Ver Perimetro...................[ 6 ] |" << endl;
	cout << "|-----------------------------------------|" << endl;
	cout << "| > Menu Principal..................[ 0 ] |" << endl;
	cout << "+=========================================+" << endl;
	cout << ">>> ";
	cin >> input;
	return input;
}

int menu_rectangulo (void)
{
	int input;
	cout << "+=============================================+" << endl;
	cout << "|          <<<< Menu Rectangulo >>>>          |" << endl;
	cout << "|---------------------------------------------|" << endl;
	cout << "| > Actualizar medidas (Alto y Ancho)...[ 1 ] |" << endl;
	cout << "| > Calcular Area.......................[ 2 ] |" << endl;
	cout << "| > Calcular Perimetro..................[ 3 ] |" << endl;
	cout << "| > Ver Alto............................[ 4 ] |" << endl;
	cout << "| > Ver Ancho...........................[ 5 ] |" << endl;
	cout << "| > Ver Area............................[ 6 ] |" << endl;
	cout << "| > Ver Perimetro.......................[ 7 ] |" << endl;
	cout << "|---------------------------------------------|" << endl;
	cout << "| > Menu Principal......................[ 0 ] |" << endl;
	cout << "+=============================================+" << endl;
	cout << ">>> ";
	cin >> input;
	return input;
}

int menu_circulo (void)
{
	int input;
	cout << "+=======================================================+" << endl;
	cout << "|                 <<<< Menu Circulo >>>>                |" << endl;
	cout << "|-------------------------------------------------------|" << endl;
	cout << "| > Actualizar medidas............................[ 1 ] |" << endl;
	cout << "| > Calcular Area.................................[ 2 ] |" << endl;
	cout << "| > Calcular Perimetro............................[ 3 ] |" << endl;
	cout << "| > Ver Radio.....................................[ 4 ] |" << endl;
	cout << "| > Ver Diametro..................................[ 5 ] |" << endl;
	cout << "| > Ver Area......................................[ 6 ] |" << endl;
	cout << "| > Ver Perimetro.................................[ 7 ] |" << endl;
	cout << "|-------------------------------------------------------|" << endl;
	cout << "| > Menu Principal................................[ 0 ] |" << endl;
	cout << "+=======================================================+" << endl;
	cout << ">>> ";
	cin >> input;
	return input;
}

bool func_cuadrado (void)
{
	int input;
	bool flag = false;
	float lado, output;
	do
	{
		cout << "Ingrese la medida del lado en cm\n>>> ";
		cin >> lado;
	} while (lado <= 0);
	cuadrado cuad(lado);
	fflush(stdin);
	cout << "\n[ ENTER ] para continuar";
	getchar();
	do
	{
		do
		{
			system("cls");
			input = menu_cuadrado();
		} while (!((input >= 0) || (input < 7)));
		switch (input)
		{
			case 1:
				cout << "Ingrese la medida del lado en cm\n>>> ";
				cin >> lado;
				cuad.set(lado);
				break;
			case 2:
				cuad.calcular_area();
				cout << "Se calculo el area del cuadrado" << endl;
				break;
			case 3:
				cuad.calcular_perimetro();
				cout << "Se calculo el perimetro del cuadrado" << endl;
				break;
			case 4:
				output = cuad.get();
				cout << "La medida del lado es de " << output << "cm" << endl;
				break;
			case 5:
				output = cuad.get_area();
				cout << "El Area es de " << output << "cm^2" << endl;
				break;
			case 6:
				output = cuad.get_perimetro();
				cout << "El Perimetro es de " << output << "cm" << endl;
				break;
			case 0:
				flag = true;
				break;
		}
		if (!flag)
		{
			fflush(stdin);
			cout << "\n[ ENTER ] para continuar";
			getchar();
		}
	} while(!flag);
	return flag;
}

bool func_rectangulo (void)
{
	int input;
	bool flag = false;
	float ancho, alto, output;
	do
	{
		cout << "Ingrese la medida del alto en cm\n>>> ";
		cin >> alto;
		cout << "Ingrese la medida del ancho en cm\n>>> ";
		cin >> ancho;
	} while ((ancho <= 0) && (alto <= 0));
	rectangulo rect(ancho, alto);
	fflush(stdin);
	cout << "\n[ ENTER ] para continuar";
	getchar();
	do
	{
		do
		{
			system("cls");
			input = menu_rectangulo();
		} while (!((input >= 0) && (input <= 7)));
		switch (input)
		{
			case 1:
				cout << "Ingrese la medida del alto en cm\n>>> ";
				cin >> alto;
				cout << "Ingrese la medida del ancho en cm\n>>> ";
				cin >> ancho;
				rect.set(alto, ancho);
				break;
			case 2:
				rect.calcular_area();
				cout << "Se calculo el area del rectangulo" << endl;
				break;
			case 3:
				rect.calcular_perimetro();
				cout << "Se calculo el perimetro del rectangulo" << endl;
				break;
			case 4:
				alto = rect.get_alto();
				cout << "El alto del rectangulo es de " << alto << "cm" << endl;
				break;
			case 5:
				ancho = rect.get_ancho();
				cout << "El ancho del rectangulo es de " << ancho << "cm" << endl;
				break;
			case 6:
				output = rect.get_area();
				cout << "El Area es de " << output << "cm^2" << endl;
				break;
			case 7:
				output = rect.get_perimetro();
				cout << "El Perimetro es de " << output << "cm" << endl;
				break;
			case 0:
				flag = true;
				break;
		}
		if (!flag)
		{
			fflush(stdin);
			cout << "\n[ ENTER ] para continuar";
			getchar();
		}
	} while (!flag);
	return flag;
}

bool func_circulo (void)
{
	int input;
	bool flag = false;
	float radio, output;
	do
	{
		cout << "Ingrese el radio del circulo\n>>> ";
		cin >> radio;
	} while (radio <= 0);
	circulo circ(radio);
	circ.calcular_diametro(radio);
	fflush(stdin);
	cout << "\n[ ENTER ] para continuar";
	getchar();
	do
	{

		do
		{
			system("cls");
			input = menu_circulo();
		} while (!((input >= 0) && (input <= 7)));
		switch (input)
		{
			case 1:
				cout << "Ingrese la medida del radio en cm\n>>> ";
				cin >> radio;
				circ.set(radio);
				circ.calcular_diametro(radio);
				break;
			case 2:
				circ.calcular_area();
				cout << "Se calculo el area del circulo" << endl;
				break;
			case 3:
				circ.calcular_perimetro();
				cout << "Se calculo el perimetro del circulo" << endl;
				break;
			case 4:
				output = circ.get_radio();
				cout << "El radio del circulo es de " << output << "cm" << endl;
				break;
			case 5:
				output = circ.get_diametro();
				cout << "El diametro del circulo es de " << output << "cm" << endl;
				break;
			case 6:
				output = circ.get_area();
				cout << "El area del circulo es de " << output << "cm^2" << endl;
				break;
			case 7:
				output = circ.get_perimetro();
				cout << "El perimetro del circulo es de " << output << "cm" << endl;
				break;
			case 0:
				flag = true;
				break;
		}
		if (!flag)
		{
			fflush(stdin);
			cout << "\n[ ENTER ] para continuar";
			getchar();
		}
	} while (!flag);
	return flag;
}
