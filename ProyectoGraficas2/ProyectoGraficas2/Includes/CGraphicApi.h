#pragma once
#include <string>

/// <summary>
/// Clase padre donde podremos a�adir 
/// nuevas funciones para generalizar
/// una api gr�fica
/// </summary>
class CGraphicApi {

	private:
	
	public:
		///
		///M�todos
		/// 
		CGraphicApi() = default;
		~CGraphicApi() = default;

		virtual void Init() = 0;

		virtual void Update() = 0;

		virtual void Exit() = 0;
	
		///
		/// Create
		/// 

		virtual bool InitWindow() = 0;


		/*
		Vamos por pasos:
		Primero pasa a una funci�n llamada wWinMain, recibe de par�metrop lo siguiente:

		HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow

		despu�s de eso, va a entrar en una condici�n de chequeo para el init window,
		en el init window recibe de par�metro lo siguiente:

		HINSTANCE hInstance, int nCmdShow

		ah� adentro lo que m�s dest�ca es el uso de:

		WNDCLASSEX

		donde ah� rellena doce campos, y pasa a generar la pantalla, antes de salir, manda a llamar una funci�n
		WndProc, donde recibe estos par�metros

		HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam

		aqu� adentro tiene un switch donde dice WM PAINT o WM DESTROY, pero termin� en el
		default que tiene llamado DefWindowProc, que regresa esos par�metros.

		Nos regresamos a la funci�n anteriror y termina finalmente por llamar una funci�n definida como
		ShowWindow, por lo tanto ya podemos ver una venta.

		Regresdamos a la condici�n donde ten�amos el InitWindow

		Y de ah� pasamos al Device...



		*/
};