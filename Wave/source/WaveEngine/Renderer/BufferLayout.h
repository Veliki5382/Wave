#ifndef WAVE_BUFFERLAYOUT_H
#define WAVE_BUFFERLAYOUT_H

#include "WaveEngine/Core.h"


namespace wave {

	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool

	};

	struct BufferElement {
	
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Normalized(normalized) {
			switch (type) {
				case ShaderDataType::Float: Size = 4; Count = 1; break;
				case ShaderDataType::Float2: Size = 8; Count = 2; break;
				case ShaderDataType::Float3: Size = 12; Count = 3; break;
				case ShaderDataType::Float4: Size = 16; Count = 4; break;
				case ShaderDataType::Mat3: Size = 36; Count = 9; break;
				case ShaderDataType::Mat4: Size = 64; Count = 16; break;
				case ShaderDataType::Int: Size = 4; Count = 1; break;
				case ShaderDataType::Int2: Size = 8; Count = 2; break;
				case ShaderDataType::Int3: Size = 12; Count = 3; break;
				case ShaderDataType::Int4: Size = 16; Count = 4; break;
				case ShaderDataType::Bool: Size = 1; Count = 1; break;
				default: WAVE_CORE_ASSERT(false, "Unknown ShaderDataType.");
			}
		}

		ShaderDataType Type;
		std::string Name;
		uint32_t Index, Size, Count, Offset;
		bool Normalized;
	};


	class WAVE_API BufferLayout {

	public:
		BufferLayout() {}
		BufferLayout(std::initializer_list<BufferElement> elements) 
		: m_Elements(elements) {
			
			uint32_t currentOffset = 0, index = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Index = index++;
				element.Offset = currentOffset;
				currentOffset += element.Size;
			}
			m_Stride = currentOffset;
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }


		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

}  // namespace wave

#endif
