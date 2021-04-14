#include "zzxpch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace ZZX
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size, float* vertices)
    {
        ZZX_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_RendererID); 
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
    {
        ZZX_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_RendererID); 
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        ZZX_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        ZZX_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        ZZX_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    //  IndexBuffer /////////////////////////////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count, uint32_t* indices)
        : m_Count(count)
    {
        ZZX_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_RendererID); 
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        ZZX_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        ZZX_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        ZZX_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}