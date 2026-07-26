#include "WImage.h"

#include "../window/WindowManager.h"

WImage::WImage(string filename, bool alpha) {
    name = filename;

    SDL_Surface* tmp = IMG_Load(name.c_str());
    if (alpha) {
        SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 0, 0, 255));
    }
    image = SDL_CreateTextureFromSurface(WindowManager::getInstance()->getRenderer(), tmp);
    SDL_FreeSurface(tmp);
}

WImage::WImage(int w, int h, bool alpha) {
    SDL_Surface* tmp = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    if (alpha) {
        SDL_FillRect(tmp, NULL, SDL_MapRGB(tmp->format, 0, 0, 255));
        SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 0, 0, 255));
    }
    image = SDL_CreateTextureFromSurface(WindowManager::getInstance()->getRenderer(), tmp);
    SDL_FreeSurface(tmp);
}

WImage::WImage(int w, int h, int r, int g, int b, int a) {
    SDL_Surface* tmp = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(tmp, NULL, SDL_MapRGB(tmp->format, r, g, b));
    image = SDL_CreateTextureFromSurface(WindowManager::getInstance()->getRenderer(), tmp);
    SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);
    setAlpha(a);
    SDL_FreeSurface(tmp);
}

WImage::WImage(SDL_Texture* texture) {
    image = texture;
}

WImage::WImage() {
}

WImage::~WImage() {
    SDL_DestroyTexture(image);
}

SDL_Texture* WImage::getImage() {
    return image;
}

void WImage::setAlpha(int alpha) {
    SDL_SetTextureAlphaMod(image, alpha);
}

WImage* WImage::createClip() {
    SDL_Surface* tmp = SDL_CreateRGBSurface(0, GAME_SIZE_W, GAME_SIZE_H, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(WindowManager::getInstance()->getRenderer(), NULL, SDL_PIXELFORMAT_ARGB8888, tmp->pixels, tmp->pitch);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(WindowManager::getInstance()->getRenderer(), tmp);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(tmp);
    return new WImage(texture);
}
