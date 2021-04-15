#pragma once

#include "ZZX/Renderer/Framebuffer.h"


namespace ZZX
{

    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer();
        void RecreateBuffer();
        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void Resize(uint32_t w, uint32_t h) override;
		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;
        virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { ZZX_CORE_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index]; }
    private:
        uint32_t m_RendererID = 0;
        FramebufferSpecification m_Specification;

		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecifications;
		FrameBufferTextureSpecification m_DepthAttachmentSpecification;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
    };
}



