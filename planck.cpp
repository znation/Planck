#include "constants.h"
#include "fps.h"
#include "frame.h"
#include "planck.h"

#include "SDL_ttf.h"

#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
	SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
	//Open the font
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr){
		std::cout << "TTF_OpenFont";
		return nullptr;
	}	
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr){
		TTF_CloseFont(font);
		std::cout << "TTF_RenderText";
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
		std::cout << "CreateTexture";
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr){
	SDL_RenderCopy(ren, tex, clip, &dst);
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr){
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr){
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture(tex, ren, dst, clip);
}

Planck::Planck() {
}
 
int Planck::run() {
  SDL_Event event;

  // init
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  SDL_Window *win = SDL_CreateWindow("Planck", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (win == nullptr){
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 2;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr){
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 3;
  }

  if (TTF_Init() != 0){
    std::cout << "TTF_Init";
    SDL_Quit();
    return 4;
  }

  FPS fps;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> real;

  while (m_running) {
    while (SDL_PollEvent(&event)) {
      // process events
      if (event.type == SDL_QUIT) {
        m_running = false;
      }
    }

    // process loop logic
    SDL_Color color = { 210, 210, 210, 255 };
    std::ostringstream ss;
    ss << fps.get();
    ss << " fps";
    SDL_Texture *image = renderText(ss.str(), "./SourceSansPro-Regular.ttf",
      color, 14, renderer);
    if (image == nullptr) {
      TTF_Quit();
      SDL_Quit();
      return 5;
    }

    TimeDomainFrame frame = m_mic.sample();

    // render
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    renderTexture(image, renderer, 10, 10);
    if (frame.left.render(renderer) != 0) { return 6; }

    SDL_RenderPresent(renderer);
  }

  TTF_Quit();
  SDL_Quit();
  return 0;
}
 
int main(int argc, char* argv[]) {
  Planck p;
  return p.run();
}
