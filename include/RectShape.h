#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <functional>
#include <string>

class RectShape
{
public:
    RectShape() = default;
    RectShape(SDL_Renderer* t_renderer,  TTF_Font* t_font, std::string t_name, float t_w, float t_h) :
        m_renderer(t_renderer), m_font(t_font), m_name(t_name), m_w(t_w), m_h(t_w)
    {
        m_rectangle.w = m_w;
        m_rectangle.h = m_h;

        SDL_Surface* tempSurf = TTF_RenderText_Solid(m_font, m_name.c_str(), SDL_Color{255,255,255});

        m_text = SDL_CreateTextureFromSurface(m_renderer, tempSurf);

        SDL_QueryTexture(m_text, NULL, NULL, &m_textRect.w, &m_textRect.h);

        SDL_FreeSurface(tempSurf);
    }
    ~RectShape() {}
    void render()
    {
        SDL_RenderDrawRect(m_renderer, &m_rectangle);
        SDL_RenderCopy(m_renderer, m_text, NULL, &m_textRect);
        SDL_RenderCopy(m_renderer, m_counterText, NULL, &m_healthCounterRect);
    }

    void update(int t_health, int t_x, int t_y)
    {
        updateText(m_renderer, m_font, std::to_string(t_health), t_x, t_y);
    }

    int getXPos() { return m_y; }

    int getYPos() { return m_x; }

    SDL_Rect getRect() { return m_rectangle; }

    void updateText(SDL_Renderer* t_renderer, TTF_Font* t_font,std::string t_healthCounter, int t_x, int t_y)
    {
        m_rectangle.x = t_x;
        m_rectangle.y = t_y;
        setUpText(t_renderer, t_font, t_x, t_y);
        setUpHealthCounter(t_renderer, t_font, t_healthCounter, t_x, t_y);
    }

    void setUpText(SDL_Renderer* t_renderer, TTF_Font* t_font, int t_x, int t_y)
    {
        m_textRect.x = t_x + (m_rectangle.w / 2.0f) - (m_textRect.w / 2.0f);
        m_textRect.y = t_y + (m_rectangle.w / 2.0f) - (m_textRect.h / 2.0f);
    }

    void setUpHealthCounter(SDL_Renderer* t_renderer, TTF_Font* t_font,std::string t_healthCounter, int t_x, int t_y)
    {
        std::string healthText = "HEALTH: " + t_healthCounter; 
        SDL_Surface* tempSurf = TTF_RenderText_Solid(t_font, healthText.c_str(), SDL_Color{255,255,255});

        m_counterText = SDL_CreateTextureFromSurface(m_renderer, tempSurf);

        SDL_QueryTexture(m_counterText, NULL, NULL, &m_healthCounterRect.w, &m_healthCounterRect.h);

        m_healthCounterRect.x = t_x + (m_rectangle.w / 2.0f) - (m_textRect.w / 2.0f);
        m_healthCounterRect.y = t_y + (m_rectangle.w / 2.0f) - (m_textRect.h / 2.0f) + 125;

        SDL_FreeSurface(tempSurf);
    }

private:
    SDL_Renderer* m_renderer;
    TTF_Font* m_font;
    SDL_Texture* m_text;
    SDL_Texture* m_counterText;
    float m_x;
    float m_y;
    float m_w;
    float m_h;
    SDL_Rect m_rectangle;
    SDL_Rect m_textRect;
    SDL_Rect m_healthCounterRect;
    std::string m_name;
    float m_textX;
    float m_textY;
};