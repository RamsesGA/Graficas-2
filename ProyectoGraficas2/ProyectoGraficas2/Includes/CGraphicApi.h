#pragma once
#include <string>

/// <summary>
/// Clase padre donde podremos añadir 
/// nuevas funciones para generalizar
/// una api gráfica
/// </summary>
class CGraphicApi {

	private:
	
	public:
		///
		///Métodos
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
		Primero pasa a una función llamada wWinMain, recibe de parámetrop lo siguiente:

		HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow

		después de eso, va a entrar en una condición de chequeo para el init window,
		en el init window recibe de parámetro lo siguiente:

		HINSTANCE hInstance, int nCmdShow

		ahí adentro lo que más destáca es el uso de:

		WNDCLASSEX

		donde ahí rellena doce campos, y pasa a generar la pantalla, antes de salir, manda a llamar una función
		WndProc, donde recibe estos parámetros

		HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam

		aquí adentro tiene un switch donde dice WM PAINT o WM DESTROY, pero terminó en el
		default que tiene llamado DefWindowProc, que regresa esos parámetros.

		Nos regresamos a la función anteriror y termina finalmente por llamar una función definida como
		ShowWindow, por lo tanto ya podemos ver una venta.

		Regresdamos a la condición donde teníamos el InitWindow

		Y de ahí pasamos al Device...



		*/
};