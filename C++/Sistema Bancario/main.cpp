
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <ctime>

using namespace std;

class administrador
{
	private:
		string usuario;
		string contra;
	public:
		void set_usuario (string);
		void set_contra (string);
		bool validar (string, string);
		administrador();
};

class cuenta_bancaria
{
	private:
		string titular;
		string contra;
		float fondos;
		cuenta_bancaria *siguiente;
	public:
		cuenta_bancaria();
		void set_titular (string);
		void set_contra (string);
		void set_plata (float);
		string get_titular (void);
		float get_plata (void);
		string get_contra (void);
		void set_siguiente (cuenta_bancaria *);
		void get (void);
		cuenta_bancaria *get_siguiente(void);
};

typedef cuenta_bancaria *p_cuenta_bancaria;

void mensaje_principal (void);
char menu_principal (void);
void limpiar_pantalla (void);

void recuperar_cuentas (p_cuenta_bancaria *);
void crear_cuenta (p_cuenta_bancaria *);
void eliminar_cuenta (p_cuenta_bancaria *);
bool listar_cuentas (p_cuenta_bancaria);
void acceso_fondos(p_cuenta_bancaria);
void cambiar_contra (p_cuenta_bancaria);
void retirar (p_cuenta_bancaria); 
void ingresar (p_cuenta_bancaria); 
void actualizar_base_de_cuentas (p_cuenta_bancaria);
void liberar_memoria (p_cuenta_bancaria *);

void historial_fecha (void);
void historial_crear_cuenta (string, string);
void historial_eliminar_cuenta (string, string);
void historial_cambiar_contra (string, string, string);
void historial_retirar (string, float, float);
void historial_ingresar (string, float, float);

administrador::administrador ()
{
	usuario = "admin";
	contra = "admin";	
}

void administrador::set_usuario (string _usuario)
{
	usuario = _usuario;
}

void administrador::set_contra (string _contra)
{
	contra = _contra;
}

bool administrador::validar (string _usuario, string _contra)
{
	bool flag_usuario = false, flag_contra = false, flag = false;
	if (_usuario == usuario) flag_usuario = true;
	if (_contra == contra) flag_contra = true;
	flag = flag_usuario && flag_contra;
	return flag;
}

cuenta_bancaria::cuenta_bancaria()
{
	titular = "VACIO";
	contra = "VACIO";
	fondos = 0;
	siguiente = NULL;
}

void cuenta_bancaria::set_titular (string _titular)
{
	titular = _titular;
}

void cuenta_bancaria::set_contra (string _contra)
{
	contra = _contra;
}

void cuenta_bancaria::set_plata (float _fondos)
{
	fondos = _fondos;
}

string cuenta_bancaria::get_titular (void)
{
	return titular;
}

float cuenta_bancaria::get_plata (void)
{
	return fondos;
}

string cuenta_bancaria::get_contra (void)
{
	return contra;
}

void cuenta_bancaria::set_siguiente (cuenta_bancaria *_siguiente)
{
	siguiente = _siguiente;
}

void cuenta_bancaria::get (void)
{
	//cout << "<<<< Cuenta Bancaria - " << titular << " >>>>" << endl;
	cout << ">>> Cuenta Bancaria: " << titular << endl;
	cout << "\t - Contraseña: " << contra << endl;
	cout << "\t - Fondos: " << fondos <<  endl;
	cout << "------------------------------------------------------" << endl;
}

cuenta_bancaria* cuenta_bancaria::get_siguiente()
{
	return siguiente;
}

administrador admin;

time_t tiempo = time(NULL);
struct tm* fecha_hora = localtime(&tiempo); 

int main()
{
	char input;
	bool flag;
	p_cuenta_bancaria comienzo = NULL;
	recuperar_cuentas(&comienzo);
	mensaje_principal();
	do
	{
		input = menu_principal();
		if ((input == 'c') || (input == 'C')) crear_cuenta(&comienzo);
		else if ((input == 'e') || (input == 'E')) eliminar_cuenta(&comienzo);
		else if ((input == 'l') || (input == 'L'))
		{
			flag = listar_cuentas(comienzo);
			if (flag) break;
		}
		else if ((input == 'f') || (input == 'F')) acceso_fondos(comienzo);
		else if ((input == 'x') || (input == 'X')) cambiar_contra(comienzo);
		else if ((input == 'r') || (input == 'R')) retirar(comienzo);
		else if ((input == 'i') || (input == 'I')) ingresar(comienzo);
	}while ((input != 'p') && (input != 'P'));
	actualizar_base_de_cuentas(comienzo);
	liberar_memoria(&comienzo);
	cout << "Cerrando programa..." << endl;
	return 0;
}

void mensaje_principal (void)
{
	char decision;
	string usuario, contra;
	bool flag = true;
	cout << "+------------------------------------------------------------------------------------+" << endl;
	cout << "|                              ---- Cuentas Bancarias ----                           |" << endl;
	cout << "| Con este programa podras controlar las cuentas bancarias de n cantidad de personas |" << endl;
	cout << "| Teniendo acceso a:                                                                 |" << endl;
	cout << "| \t- Nombre y Apellido del titular                                              |" << endl;
	cout << "| \t- Contraseña                                                                |" << endl;
	cout << "| \t- Fondos de la cuenta                                                        |" << endl;
	cout << "+------------------------------------------------------------------------------------+" << endl;
	do
	{
		if (flag)
		{
			cout << "                          <<<< Usuario de Administrador >>>>" << endl;
			cout << "El usuario y contraseña de Administrador valen \"admin\" por defecto" << endl;
			cout << "Desea cambiarlo? [S/N]\n>>> ";
			flag = false;
		}
		else
		{
			cout << endl << "El valor ingresado es incorrecto. Se debe ingresar -> [S/N]" << endl << endl;
			cout << "                          <<<< Usuario de Administrador >>>>" << endl;
			cout << "El usuario y contraseña de Administrador valen \"admin\" por defecto" << endl;
			cout << "Desea cambiarlo? [S/N]\n>>> ";
		}
		cin >> decision;
		if ((decision == 's') || (decision == 'S'))
		{
			cout << "Ingrese el usuario\n>>> ";
			cin >> usuario;
			cout << "Ingrese la contraseña\n>>> ";
			cin >> contra;
			admin.set_usuario(usuario);
			admin.set_contra(contra);
		}
	}while ((decision != 's') && (decision != 'S') && (decision != 'n') && (decision != 'N'));
	system("cls");
}

char menu_principal (void)
{
	char input;
	cout << "+----------------------------------------------------+" << endl;
	cout << "|               <<<< MENU PRINCIPAL >>>>             |" << endl;
	cout << "|----------------------------------------------------|" << endl;
	cout << "| > Cuentas:                                         |" << endl;
	cout << "| \t - Crear Cuenta........................[ C ] |" << endl;
	cout << "| \t - Eliminar Cuenta.....................[ E ] |" << endl;
	cout << "| \t - Listar Cuentas......................[ L ] |" << endl;
	cout << "| > Accesos:                                         |" << endl;
	cout << "| \t - Fondos..............................[ F ] |" << endl;
	cout << "| \t - Cambiar Contraseña.................[ X ] |" << endl;
	cout << "| > Fondos:                                          |" << endl;
	cout << "| \t - Retirar.............................[ R ] |" << endl;
	cout << "| \t - Ingresar............................[ I ] |" << endl;
	cout << "| > Salir del programa.........................[ P ] |" << endl;
	cout << "+----------------------------------------------------+" << endl;
	cout << "Ingrese una letra\n>>> ";
	cin >> input;
	return input;
}

void recuperar_cuentas (p_cuenta_bancaria *comienzo)
{
	ifstream archivo ("Files/Datos/Base_de_Datos.txt", ios::in);
	string aux;
	float f_aux;
	if (!(archivo.is_open()))
	{
		cout << "ERROR, No se puede abrir el archivo" << endl;
		exit(1);
	}
	while (true)
	{
		p_cuenta_bancaria nuevo = new cuenta_bancaria;
		nuevo->set_siguiente(NULL);
		getline(archivo, aux);
		nuevo->set_titular(aux);
		getline(archivo, aux);	
		nuevo->set_contra(aux);
		getline(archivo, aux);
		f_aux = stof(aux);
		nuevo->set_plata(f_aux);
		nuevo->set_siguiente(*comienzo);
		*comienzo = nuevo;
		if (archivo.eof()) break;
	}
	archivo.close();
}

void crear_cuenta (p_cuenta_bancaria *comienzo)
{
	p_cuenta_bancaria nuevo = new cuenta_bancaria;
	string nombre_apellido, contra;
	float plata;
	cout << "Ingrese el NOMBRE y APELLIDO del titular de la cuenta\n>>> ";
	cin.ignore();
	getline(cin, nombre_apellido);
	cout << "Ingrese la CONTRASEÑA\n>>> ";
	cin >> contra;
	cout << "Ingrese el DINERO\n>>> ";
	cin >> plata;
	nuevo->set_titular(nombre_apellido);
	nuevo->set_contra(contra);
	nuevo->set_plata(plata);
	nuevo->set_siguiente(*comienzo);
	*comienzo = nuevo;
	cout << "Se creo una cuenta bancaria a nombre de " << nuevo->get_titular() << endl;
	limpiar_pantalla();
	historial_crear_cuenta(nuevo->get_titular(), nuevo->get_contra());
}

void eliminar_cuenta (p_cuenta_bancaria *comienzo)
{
    p_cuenta_bancaria actual = *comienzo, anterior = NULL;
    string titular_eliminar, confirmar_contra;
	bool flag = true;
    cout << "Ingrese el titular de la cuenta a eliminar\n>>> ";
    cin.ignore();
    getline(cin, titular_eliminar);
    while (actual != NULL)
    {
        if ((actual->get_titular()) == titular_eliminar)
        {
			flag = false;
			cout << "Ingrese la contraseña\n>>> ";
			cin >> confirmar_contra;
			if ((actual->get_contra()) == confirmar_contra)
			{
				if (anterior != NULL) anterior->set_siguiente(actual->get_siguiente());
				else *comienzo = actual->get_siguiente();
				delete(actual);
				cout << "La cuenta a nombre de " << titular_eliminar << " se elimino exitosamente" << endl;
				historial_eliminar_cuenta(titular_eliminar, confirmar_contra);
				break;
			}
			else
			{
				cout << "La contraseña es incorrecta, la cuenta no se elimino" << endl;
				break;
			}
        }
		anterior = actual;
		actual = actual->get_siguiente();
    }
	if (flag) cout << "La cuenta a nombre de " << titular_eliminar << " no se encontro" << endl;
	limpiar_pantalla();
}

bool listar_cuentas (p_cuenta_bancaria comienzo)
{
	p_cuenta_bancaria aux = comienzo;
	string usuario, contra;
	int intentos = 3;
	bool flag = false;
	while (true)
	{
		cout << "Intentos restantantes: "<< intentos << endl;
		cout << "Ingrese el usuario de administrador\n>>> ";
		cin >> usuario;
		cout << "Ingrese la contraseña de administrador\n>>> ";
		cin >> contra;
		fflush(stdin);
		if (!(admin.validar(usuario, contra)))
		{
			intentos = intentos - 1;
			if (intentos == 0)
			{
				cout << "Te quedaste sin intentos" << endl << endl;
				flag = true;
				break;
			}
		}
		else if (admin.validar(usuario, contra)) break;
	}
	if (admin.validar(usuario, contra))
	{
		cout << "------------------------------------------------------" << endl;
		cout << "\t<<<< Listado de Cuentas Bancarias >>>>" << endl;
		cout << "------------------------------------------------------" << endl;
		while (aux != NULL)
		{
			aux->get();
			aux = aux->get_siguiente();
		}
	}
	if (!flag) limpiar_pantalla();
	return flag;
}

void acceso_fondos(p_cuenta_bancaria comienzo)
{
	p_cuenta_bancaria aux = comienzo;
	string titular_buscar, confirmar_contra;
	float fondos;
	bool flag = true;
	cout << "Ingrese el titular de la cuenta la cual desea ver los fondos\n>>> ";
	cin.ignore();
	getline(cin, titular_buscar);
	while (aux != NULL)
	{
		if (aux->get_titular() == titular_buscar)
		{
			cout << "Ingrese la contraeña\n>>> ";
			cin >> confirmar_contra;
			if (aux->get_contra() == confirmar_contra)
			{
				fondos = aux->get_plata();
				cout << "Fondos disponibles: " << fondos << endl;
				flag = false;
				break;
			}
			else
			{
				cout << "Contraseña incorrecta" << endl;
				flag = false;
				break;
			}
		}
		aux = aux->get_siguiente();
	}
	if (flag) cout << "La cuenta a nombre de " << titular_buscar << " no se encontro" << endl;
	limpiar_pantalla();
}

void cambiar_contra (p_cuenta_bancaria comienzo)
{
	p_cuenta_bancaria aux = comienzo;
	string titular_buscar, confirmar_contra, nueva_contra, confirmar_nueva_contra;
	string contra_vieja;
	bool flag = true, flag_h = true;
	cout << "Ingrese el titular de la cuenta la cual desea cambiar la contraseña\n>>> ";
	cin.ignore();
	getline(cin, titular_buscar);
	while (aux != NULL)
	{
		if (aux->get_titular() == titular_buscar)
		{
			flag = false;
			cout << "Ingrese la contraeña\n>>> ";
			cin >> confirmar_contra;
			if (aux->get_contra() == confirmar_contra)
			{
				contra_vieja = aux->get_contra();
				do
				{
					cout << "Ingrese la nueva contraseña\n>>> ";
					cin >> nueva_contra;
					cout << "Confirme la nueva contraseña\n>>> ";
					cin >> confirmar_nueva_contra;
					if (nueva_contra == confirmar_nueva_contra)
					{
						aux->set_contra(nueva_contra);
						cout << "Las contraseña se actualizo correctamente" << endl;
						historial_cambiar_contra(aux->get_titular(), contra_vieja, aux->get_contra());
					}
					else cout << "Las contraseñas no coinciden, intentelo de nuevo" << endl;
				}while (nueva_contra != confirmar_nueva_contra);
				break;
			}
			else
			{
				cout << "La la contraseña de la cuenta seleccionada no coincide" << endl;
				flag = false;
				flag_h = false;
				break;
			}
		}
		aux = aux->get_siguiente();
	}
	if (flag) cout << "La cuenta a nombre de " << titular_buscar << " no se encontro" << endl;
	limpiar_pantalla();
}

void retirar (p_cuenta_bancaria comienzo)
{
	p_cuenta_bancaria aux = comienzo;
	string titular_buscar, confirmar_contra;
	float dinero_retirar, fondos;
	bool flag = true;
	cout << "Ingrese el titular de la cuenta la cual desea retirar dinero\n>>> ";
	cin.ignore();
	getline(cin, titular_buscar);
	while (aux != NULL)
	{
		if (aux->get_titular() == titular_buscar)
		{
			flag = false;
			cout << "Ingrese la contraeña\n>>> ";
			cin >> confirmar_contra;
			if (aux->get_contra() == confirmar_contra)
			{
				fondos = aux->get_plata();
				do
				{
					cout << "Ingrese la cantidad de dinero a retirar (Mayor a 0)\n>>> ";
					cin >> dinero_retirar;
					if (dinero_retirar >= fondos) cout << "La cantidad a retirar es mayor a la disponible" << endl;
					if (dinero_retirar <= 0) cout << "No se puede retirar una cantidad de 0 o menor" << endl;
				}while ((dinero_retirar <= 0) || (dinero_retirar >= fondos));
				aux->set_plata(fondos - dinero_retirar);
				cout << "Dinero retirado: " << dinero_retirar << endl;
				cout << "Fondos: " << fondos - dinero_retirar << endl;
				historial_retirar(aux->get_titular(), dinero_retirar, aux->get_plata());
				break;
			}
			else
			{
				cout << "La la contraseña de la cuenta seleccionada no coincide" << endl;
				break;
			}
		}
		aux = aux->get_siguiente();
	}
	if (flag) cout << "La cuenta a nombre de " << titular_buscar << " no se encontro" << endl;
	limpiar_pantalla();
}

void ingresar (p_cuenta_bancaria comienzo)
{
	p_cuenta_bancaria aux = comienzo;
	string titular_buscar, confirmar_contra;
	float dinero_ingresar, fondos;
	bool flag = true;
	cout << "Ingrese el titular de la cuenta la cual desea ingresar dinero\n>>> ";
	cin.ignore();
	getline(cin, titular_buscar);
	while (aux != NULL)
	{
		if (aux->get_titular() == titular_buscar)
		{
			flag = false;
			cout << "Ingrese la contraeña\n>>> ";
			cin >> confirmar_contra;
			if (aux->get_contra() == confirmar_contra)
			{
				fondos = aux->get_plata();
				do
				{
					cout << "Ingrese la cantidad de dinero a ingresar (Mayor a 0)\n>>> ";
					cin >> dinero_ingresar;
					if (dinero_ingresar <= 0) cout << "No se puede ingresar una cantidad de 0 o menor" << endl;
				}while (dinero_ingresar <= 0);
				aux->set_plata(fondos + dinero_ingresar);
				cout << "Dinero ingresado: " << dinero_ingresar << endl;
				cout << "Fondos: " << fondos + dinero_ingresar << endl;
				historial_ingresar(aux->get_titular(), dinero_ingresar, aux->get_plata());
				break;
			}
			else
			{
				cout << "La la contraseña de la cuenta seleccionada no coincide" << endl;
				break;
			}
		}
		aux = aux->get_siguiente();
	}
	if (flag) cout << "La cuenta a nombre de " << titular_buscar << " no se encontro" << endl;
	limpiar_pantalla();
}

void actualizar_base_de_cuentas (p_cuenta_bancaria comienzo)
{
	p_cuenta_bancaria aux = comienzo;
	float x;
	string y;
	bool flag = false;
	ofstream archivo ("Files/Datos/Base_de_Datos.txt", ios::out);
	if (!(archivo.is_open()))
	{
		cout << "ERROR, No se puede abrir el archivo" << endl;
		exit(1);
	}
	while (aux != NULL)
	{
		if(flag==true) archivo << endl;
		else flag=true;
		archivo << aux->get_titular() << endl;
		archivo << aux->get_contra() << endl;
		x = aux->get_plata();
		y = to_string(x);
		archivo << y ;
		aux = aux->get_siguiente();
	
	}
	archivo.close();
	cout << "Se actualizo la base de datos" << endl;
}

void liberar_memoria (p_cuenta_bancaria *comienzo)
{
	p_cuenta_bancaria actual;
	cout << "Liberando memoria..." << endl;
	while (*comienzo != NULL)
	{
		actual = *comienzo;
		*comienzo = (*comienzo)->get_siguiente();
		delete(actual);
	}
	cout << "Memoria liberada" << endl;
}

void limpiar_pantalla (void)
{
	cout << endl << "Presione [ ENTER ] para continuar";
	fflush(stdin);
	getchar();
	system("cls");
}

void historial_fecha (void)
{
	ofstream historial ("Files/Historial.txt", ios::app);
	historial << "----------------------------------------" << endl;
	
	//historial << (ahora->tm_year + 1900) << "/" << (ahora->tm_mon + 1) << "/" << ahora->tm_mday << endl;
	
	historial << (fecha_hora->tm_year + 1900) << "/";

	if ((fecha_hora->tm_mon + 1) < 10) historial << "0" << (fecha_hora->tm_mon + 1) << "/";
	else historial << (fecha_hora->tm_mon + 1) << "/";
	
	if ((fecha_hora->tm_mday) < 10) historial << "0" << fecha_hora->tm_mday;
	else historial << fecha_hora->tm_mday;

	historial << " - ";
	
	//historial << ahora->tm_hour << ":" << ahora->tm_min << ":" << ahora->tm_sec << endl;
	
	if (fecha_hora->tm_hour < 10) historial << "0" << fecha_hora->tm_hour << ":";
	else historial << fecha_hora->tm_hour << ":";

	if (fecha_hora->tm_min < 10) historial << "0" << fecha_hora->tm_min << ":";
	else historial << fecha_hora->tm_min << ":";

	if (fecha_hora->tm_sec < 10) historial << "0" << fecha_hora->tm_sec << endl;
	else historial << fecha_hora->tm_sec << endl;

	historial.close();
}

void historial_crear_cuenta (string _titular, string _contra)
{
	ofstream historial ("Files/Historial.txt", ios::app);
	historial_fecha();
	historial << "<<<< Cuenta Creada >>>>" << endl;
	historial << "Titular: " << _titular << endl;
	historial << "Contraseña: " << _contra << endl;
	historial.close();
}

void historial_eliminar_cuenta (string _titular, string _contra)
{
	ofstream historial ("Files/Historial.txt", ios::app);
	historial_fecha();
	historial << "<<<< Cuenta Eliminada >>>>" << endl;
	historial << "Titular: " << _titular << endl;
	historial << "Contraseña: " << _contra << endl;
	historial.close();
}

void historial_cambiar_contra (string _titular, string _contra_a, string _contra_n)
{
	ofstream historial ("Files/Historial.txt", ios::app);
	historial_fecha();
	historial << "<<<< Actualizacion de Contraseña >>>>" << endl;
	historial << "Titular: " << _titular << endl;
	historial << "Contraseña anterior: " << _contra_a << endl;
	historial << "Contraseña nueva: " << _contra_n << endl;
	historial.close();
}

void historial_retirar (string _titular, float _retiro, float _fondos)
{
	ofstream historial ("Files/Historial.txt", ios::app);
	historial_fecha();
	historial << "<<<< Dinero Retirado >>>>" << endl;
	historial << "Titular: " << _titular << endl;
	historial << "Dinero retirado: " << _retiro << endl;
	historial << "Fondos disponibles: " << _fondos << endl;
	historial.close();
}

void historial_ingresar (string _titular, float _ingreso, float _fondos)
{
	ofstream historial ("Files/Historial.txt", ios::app);
	historial_fecha();
	historial << "<<<< Dinero Ingresado >>>>" << endl;
	historial << "Titular: " << _titular << endl;
	historial << "Dinero ingresado: " << _ingreso << endl;
	historial << "Fondos disponibles: " << _fondos << endl;
	historial.close();
}
