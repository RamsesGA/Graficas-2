#pragma once
#include <string>

/// <summary>
/// Clase padre donde podremos añadir 
/// nuevas funciones para generalizar
/// una api gráfica
/// </summary>
class CGraphicApi {

	private:
		///
		///Métodos
		/// 

		///
		/// Funciones internas
		/// 

		virtual bool MainInit() = 0;

		virtual bool InitWindow() = 0;

		virtual bool InitDevice() = 0;

	public:
		///
		///Métodos
		/// 
		
		///Constructor
		CGraphicApi() = default;
		///Destructor
		~CGraphicApi() = default;

		///
		/// Funciones para el usuario
		/// 
		
		///
		/// C R E A T E
		/// 

		virtual bool CreatePixelShader() = 0;

		virtual bool CreateVertexShader() = 0;

		virtual bool CreateVertexBuffer() = 0;

		virtual bool CreateIndexBuffer() = 0;

		virtual bool CreateConstBuffNeverChanges() = 0;

		virtual bool CreateConstBuffChangeOnResize() = 0;

		virtual bool CreateConstBuffChangeEveryFrame() = 0;

		virtual bool CreateTexture2D() = 0;

		virtual bool CreateInputLayout() = 0;

		virtual bool CreateSamplerState() = 0;

		///
		/// S E T´s
		/// 

		virtual bool SetPixelShader() = 0;

		virtual bool SetVertexShader() = 0;

		virtual bool SetVertexBuffer() = 0;

		virtual bool SetIndexBuffer() = 0;
					 
		virtual bool SetConstBuffNeverChanges() = 0;
					 
		virtual bool SetConstBuffChangeOnResize() = 0;
					 
		virtual bool SetConstBuffChangeEveryFrame() = 0;
		
		virtual bool SetTexture2D() = 0;

		virtual bool SetInputLayout() = 0;

		virtual bool SetSamplerState() = 0;
};