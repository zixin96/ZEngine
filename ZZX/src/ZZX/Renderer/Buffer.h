#pragma once

namespace ZZX
{
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t GetSizeOfShaderDataType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float: return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3: return 4 * 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4 * 4;
            case ShaderDataType::Int: return 4;
            case ShaderDataType::Int2: return 4 * 2;
            case ShaderDataType::Int3: return 4 * 3;
            case ShaderDataType::Int4: return 4 * 4;
            case ShaderDataType::Bool: return 1;
        }
        ZZX_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    struct BufferElements
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;
        BufferElements() : Name(), Type(ShaderDataType::None), Size(0), Offset(0), Normalized(false)  {}
        BufferElements(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(GetSizeOfShaderDataType(type)), Offset(0), Normalized(normalized)
        {}

        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
            case ShaderDataType::Float:
                return 1;
            case ShaderDataType::Float2:
                return 2;
            case ShaderDataType::Float3:
                return 3;
            case ShaderDataType::Float4:
                return 4;
            case ShaderDataType::Mat3:
                return 9;
            case ShaderDataType::Mat4:
                return 16;
            case ShaderDataType::Int:
                return 1;
            case ShaderDataType::Int2:
                return 2;
            case ShaderDataType::Int3:
                return 3;
            case ShaderDataType::Int4:
                return 4;
            case ShaderDataType::Bool:
                return 1;
            }

            ZZX_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<BufferElements>& elements)
            : m_Elements(elements)
        {
            // since we now have entire buffer layout inside elements, we can calculate offsets
            ComputeOffsetAndStride();
        }
        inline const std::vector<BufferElements>& GetElements() const { return m_Elements; }
        inline uint32_t GetStride() const { return m_Stride; }
        std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElements>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElements>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElements>::const_iterator end() const { return m_Elements.end(); }
    private:
        void ComputeOffsetAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& ele : m_Elements)
            {
                ele.Offset = offset;
                offset += ele.Size;
                m_Stride += ele.Size;
            }
        }
    private:
        std::vector<BufferElements> m_Elements;
        uint32_t m_Stride = 0;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        virtual void SetData(const void* data, uint32_t size) = 0;

        static Ref<VertexBuffer> Create(uint32_t size, float* vertices); // act as ctor
        static Ref<VertexBuffer> Create(uint32_t size);
    };

    // Currently EBO ONLY supports 32-bit index buffers
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static Ref<IndexBuffer> Create(uint32_t count, uint32_t* indices); // act as ctor
    };
}

