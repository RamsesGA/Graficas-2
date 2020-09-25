#pragma once

/// <summary>
/// Clase donde...
/// </summary>
class CGraphicApi {

	private:

	public:
		///
		///M�todos
		/// 
		CGraphicApi() = default;
		~CGraphicApi() = default;

		/// <summary>
		/// Funci�n para guardar la informaci�n
		/// para la generaci�n de una ventana
		/// </summary>
		void InitWindow();

		/// <summary>
		/// Funci�n para guardar los valores
		/// de los recursos necesarios
		/// </summary>
		void InitDevice();

		/// <summary>
		/// Funci�n para poder procesar los datos
		/// y mostrarlos en pantalla
		/// </summary>
		void Render();
};