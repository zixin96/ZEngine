#pragma once

#include "ZZX/Core/Core.h"

namespace ZZX
{
	enum class FrameBufferTextureFormat
	{
		None = 0,

		// color
		RGBA8,
		RED_INTEGER,

		// depth/stencil
		DEPTH24STENCIL8,

		// defaults
		Depth = DEPTH24STENCIL8
	};

	struct FrameBufferTextureSpecification
	{
		FrameBufferTextureSpecification() = default;
		FrameBufferTextureSpecification(FrameBufferTextureFormat format)
			: TextureFormat(format)
		{}
		FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
		// TODO: filtering/wrap
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments)
			: Attachments(attachments)
		{}
		std::vector<FrameBufferTextureSpecification> Attachments;
	};

    struct FramebufferSpecification
    {
        uint32_t Width, Height;
		FramebufferAttachmentSpecification Attachments;
        uint32_t Samples = 1;
        bool SwapChainTarget = false;
    };


    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Resize(uint32_t w, uint32_t h) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;
		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;
        virtual const FramebufferSpecification& GetSpecification() const = 0;
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
        static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
    };
}

