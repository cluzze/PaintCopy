#pragma once

class Text {
 public:
  Text(SDL_Renderer* renderer, const std::string& font_path, int font_size,
       const std::string& message_text, const SDL_Color& color) {
    _text_texture =
        loadFont(renderer, font_path, font_size, message_text, color);
    SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w,
                     &_text_rect.h);
  }

  void display(int x, int y, SDL_Renderer* renderer) {
    _text_rect.x = x;
    _text_rect.y = y;
    SDL_RenderCopy(renderer, _text_texture, nullptr, &_text_rect);
  }

  SDL_Texture* loadFont(SDL_Renderer* renderer, const std::string& font_path,
                        int font_size, const std::string& message_text,
                        const SDL_Color& color) {
    TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);

    if (!font) {
      std::cerr << "Failed to load font " << '"' << font_path << '"';
    }

    auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);

    if (!text_surface) {
      std::cerr << "Failed to create surface";
    }

    auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    if (!text_texture) {
      std::cerr << "Failed to create texture";
    }

    SDL_FreeSurface(text_surface);
    return text_texture;
  }

 private:
  SDL_Texture* _text_texture = nullptr;
  SDL_Rect _text_rect;
};