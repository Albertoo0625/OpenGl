// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include"Texture.h"
#include"Vendor/stb_image/stb_image.h"
#include<iostream>



Texture::Texture(const std::string& path)
    :m_Renderer_id(0),m_filepath(path),m_localbuffer(nullptr),m_Width(0),m_Height(0),m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_localbuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    
    glGenTextures(1, &m_Renderer_id);
    glBindTexture(GL_TEXTURE_2D, m_Renderer_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);




    glcall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localbuffer));
    
   
    glGenerateMipmap(GL_TEXTURE_2D);

    if (m_localbuffer) {
        stbi_image_free(m_localbuffer);
    }
    else {
        std::cout<<
       stbi_failure_reason();
    }
    
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_Renderer_id);
}




void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_Renderer_id);
}

void Texture::UnBind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}


