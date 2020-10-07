#pragma once

class CBuffer {

	public:
		///
		/// M�todos
		/// 
		
		///Constructor
		CBuffer() = default;
		///Destructor
		~CBuffer() = default;
		
		/// <summary>
		/// Inicializaci�n de valores para OpenGL y DirectX,
		/// Falta el target, este lo defino yo
		/// </summary>
		/// <param name="_bufferOGL">Especifica el nombre de un objeto de b�fer</param>
		/// <param name="_byteWidth">Tama�o del b�fer en bytes</param>
		/// <param name="_usage">Identificar c�mo se espera que se lea y escriba el b�fer</param>
		/// <param name="_bindFlags">Identifique c�mo se vincular� el b�fer a la canalizaci�n</param>
		/// <param name="_CPUAccessFlags">Indicadores de acceso a la CPU
		///	o 0 si no es necesario acceder a la CPU</param>
		/// <param name="_miscFlags">Indicadores varios o 0 si no se utilizan</param>
		/// <param name="_structureByteStride">El tama�o de cada elemento 
		///	en la estructura del b�fer</param>
		virtual void Init(unsigned int _bufferOGL,
						  unsigned int _byteWidth, unsigned int _usage,
						  unsigned int _bindFlags, unsigned int _CPUAccessFlags,
						  unsigned int _miscFlags, unsigned int _structureByteStride,
						  const void* _pSysMem) = 0;
};