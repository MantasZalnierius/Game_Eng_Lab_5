#include "Game.h"
Coordinator m_Coordinator;
Game::~Game()
{

}

Game::Game(const char* t_title, unsigned int t_x, unsigned int t_y, unsigned int t_width, unsigned int t_height, Uint32 t_flags)
{
    setUpWindow(t_title, t_x, t_y, t_width, t_height, t_flags);
    m_Coordinator.init();
    m_Coordinator.registerComponent<Position>();
	m_Coordinator.registerComponent<Health>();
    m_Coordinator.registerComponent<Renderable>();
    m_Coordinator.registerComponent<InputController>();
    setUpPlayer();
    m_isRunning = true;
}

void Game::setUpPlayer()
{
    m_inputSystem = m_Coordinator.registerSystem<InputSystem>();
	{
		SignatureFilter signature;
        signature.set(m_Coordinator.getComponentType<Position>());
        signature.set(m_Coordinator.getComponentType<Health>());
		m_Coordinator.setSystemSignature<InputSystem>(signature);
	}

    m_renderSystem = m_Coordinator.registerSystem<RenderSystem>();
	{
		SignatureFilter signature;
        signature.set(m_Coordinator.getComponentType<Renderable>());
        signature.set(m_Coordinator.getComponentType<Position>());
        signature.set(m_Coordinator.getComponentType<Health>());
		m_Coordinator.setSystemSignature<RenderSystem>(signature);
	}

    m_healthSystem = m_Coordinator.registerSystem<HealthSystem>();
	{
		SignatureFilter signature;
        signature.set(m_Coordinator.getComponentType<Health>());
		m_Coordinator.setSystemSignature<RenderSystem>(signature);
	}

	Entity entity = m_Coordinator.createEntity();
	m_Coordinator.addComponent(entity, Renderable{RectShape(m_renderer, m_font, "MANTAS", 200, 200)});
    m_Coordinator.addComponent(entity, Position{100.0f, 100.0f});
    m_Coordinator.addComponent(entity, Health{1});
    m_Coordinator.addComponent(entity, InputController{});
}

void Game::update()
{
    while(this->isRunning())
    {
        handleEvents();
        m_renderSystem->Update();
        this->render();
    }
    this->cleanUp();
}

void Game::handleEvents()
{
    SDL_Event eventHandlder;
    while(SDL_PollEvent( &eventHandlder ) != 0)
    {
        switch (eventHandlder.type)
        {
            case SDL_KEYDOWN:
                m_inputSystem->Update(eventHandlder);
                m_healthSystem->Update(eventHandlder);
            break;
        }
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255,255,255,255);
    m_renderSystem->Render();
    SDL_RenderPresent(m_renderer);
}

bool Game::isRunning()
{
    return m_isRunning;
}

void Game::cleanUp()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::run()
{
    this->update();
}

void Game::setUpWindow(const char* t_title, unsigned int t_x, unsigned int t_y, unsigned int t_width, unsigned int t_height, Uint32 t_flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    m_window = SDL_CreateWindow(t_title, t_x, t_y, t_width, t_height, t_flags);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (m_window == nullptr) {
     std::cout << "WINDOW IS NULL \n ERROR IS -> " << SDL_GetError();
    }
    m_font = TTF_OpenFont("times.ttf", 32);
}