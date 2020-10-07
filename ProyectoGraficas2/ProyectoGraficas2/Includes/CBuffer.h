#pragma once

class CBuffer {

	public:
		///
		/// Métodos
		/// 
		
		///Constructor
		CBuffer() = default;
		///Destructor
		~CBuffer() = default;
		
		/// <summary>
		/// Inicialización de valores para OpenGL y DirectX,
		/// Falta el target, este lo defino yo
		/// </summary>
		/// <param name="_bufferOGL">Especifica el nombre de un objeto de búfer</param>
		/// <param name="_byteWidth">Tamaño del búfer en bytes</param>
		/// <param name="_usage">Identificar cómo se espera que se lea y escriba el búfer</param>
		/// <param name="_bindFlags">Identifique cómo se vinculará el búfer a la canalización</param>
		/// <param name="_CPUAccessFlags">Indicadores de acceso a la CPU
		///	o 0 si no es necesario acceder a la CPU</param>
		/// <param name="_miscFlags">Indicadores varios o 0 si no se utilizan</param>
		/// <param name="_structureByteStride">El tamaño de cada elemento 
		///	en la estructura del búfer</param>
		virtual void Init(unsigned int _bufferOGL,
						  unsigned int _byteWidth, unsigned int _usage,
						  unsigned int _bindFlags, unsigned int _CPUAccessFlags,
						  unsigned int _miscFlags, unsigned int _structureByteStride,
						  const void* _pSysMem) = 0;
};