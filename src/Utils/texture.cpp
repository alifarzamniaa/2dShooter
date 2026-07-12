#include "texture.h"
#include "../Logger/logger.h"
#include "SDL3_image/SDL_image.h"
#include <string>

Texture::Texture() : texture(nullptr)
{
}

Texture::Texture(Texture&& other) noexcept : texture(nullptr)
{
    if (&other == this)
    {
        return;
    }
    texture = other.texture;
    other.texture = nullptr;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (&other == this)
    {
        return *this;
    }
    SDL_DestroyTexture(texture);
    texture = other.texture;
    other.texture = nullptr;
    return *this;
}

SDL_Texture* Texture::operator->()
{
    return texture;
}

const SDL_Texture* Texture::operator->() const
{
    return texture;
}

bool Texture::LoadTexture(const char* path, SDL_Renderer* renderer)
{
    if (!renderer)
    {
        Logger::Error("Renderer does not exist to create Texture");
        return false;
    }
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    SDL_Surface* surface = IMG_Load(path);
    bool succeed = false;
    if (surface)
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture)
        {
            succeed = true;
        }
        else
        {
            std::string error = "Cannot create Texture from surface with path: ";
            error.append(path);
            Logger::Error(error);
        }
    }
    else
    {
        std::string error = "Cannot create surface from path: ";
        error.append(path);
        Logger::Error(error);
    }
    SDL_DestroySurface(surface);
    return succeed;
}

SDL_Texture* Texture::GetTexture()
{
    return texture;
}

const SDL_Texture* Texture::GetTexture() const
{
    return texture;
}

int Texture::GetWidth() const
{

    return texture ? texture->w : 0;
}

int Texture::GetHeight() const
{
    return texture ? texture->h : 0;
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}
