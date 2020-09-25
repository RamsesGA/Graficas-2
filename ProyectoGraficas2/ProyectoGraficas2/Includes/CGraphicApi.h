#pragma once

/// <summary>
/// Clase donde...
/// </summary>
class CGraphicApi {

	private:

	public:
		///
		///Métodos
		/// 
		CGraphicApi() = default;
		~CGraphicApi() = default;

		/// <summary>
		/// Función para guardar la información
		/// para la generación de una ventana
		/// </summary>
		void InitWindow();

		/// <summary>
		/// Función para guardar los valores
		/// de los recursos necesarios
		/// </summary>
		void InitDevice();

		/// <summary>
		/// Función para poder procesar los datos
		/// y mostrarlos en pantalla
		/// </summary>
		void Render();
};