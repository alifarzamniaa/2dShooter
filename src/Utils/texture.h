#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL3/SDL.h>

class Texture
{
  public:
    Texture();

    Texture(const Texture& other) = delete;

    Texture& operator=(const Texture& other) = delete;

    Texture(Texture&& other) noexcept;

    Texture& operator=(Texture&& other) noexcept;

    SDL_Texture* operator->();

    const SDL_Texture* operator->() const;

    bool LoadTexture(const char* path, SDL_Renderer* renderer);

    SDL_Texture* GetTexture();

    const SDL_Texture* GetTexture() const;

    int GetWidth() const;
    int GetHeight() const;

    ~Texture();

  private:
    SDL_Texture* texture;
};
#endif
