#include "Game.h"
EcsManager m_ecsManager;
Game::~Game()
{

}

Game::Game(const char* t_title, unsigned int t_x, unsigned int t_y, unsigned int t_width, unsigned int t_height, Uint32 t_flags)
{
    setUpWindow(t_title, t_x, t_y, t_width, t_height, t_flags);
    setUpCoordinator();
    setUpECS();
    m_isRunning = true;
}

void Game::setUpCoordinator()
{
    m_ecsManager.init();
    m_ecsManager.registerComponent<Position>();
	m_ecsManager.registerComponent<Health>();
    m_ecsManager.registerComponent<Renderable>();
    m_ecsManager.registerComponent<InputController>();
    m_ecsManager.registerComponent<Ai>();
}

void Game::setUpECS()
{
    setUpSystems();
    setUpPlayer();
    setUpVillan();
    setUpCortana();
    setUpDinkyDi();
}

void Game::setUpSystems()
{
    m_inputSystem = m_ecsManager.registerSystem<InputSystem>();
	{
		SignatureFilter signature;
        signature.set(m_ecsManager.getComponentType<Position>());
        signature.set(m_ecsManager.getComponentType<Health>());
        signature.set(m_ecsManager.getComponentType<InputController>());
		m_ecsManager.setSystemSignature<InputSystem>(signature);
	}

    m_renderSystem = m_ecsManager.registerSystem<RenderSystem>();
	{
		SignatureFilter signature;
        signature.set(m_ecsManager.getComponentType<Renderable>());
        signature.set(m_ecsManager.getComponentType<Position>());
        signature.set(m_ecsManager.getComponentType<Health>());
		m_ecsManager.setSystemSignature<RenderSystem>(signature);
	}

    m_healthSystem = m_ecsManager.registerSystem<HealthSystem>();
	{
		SignatureFilter signature;
        signature.set(m_ecsManager.getComponentType<Health>());
		m_ecsManager.setSystemSignature<RenderSystem>(signature);
	}

    m_aiSystem = m_ecsManager.registerSystem<AiSystem>();
	{
		SignatureFilter signature;
        signature.set(m_ecsManager.getComponentType<Position>());
        signature.set(m_ecsManager.getComponentType<Ai>());
		m_ecsManager.setSystemSignature<AiSystem>(signature);
	}
}

void Game::setUpPlayer()
{
    Entity player = m_ecsManager.createEntity();
	m_ecsManager.addComponent(player, Renderable{RectShape(m_renderer, m_font, "PLAYER", 200, 200)});
    m_ecsManager.addComponent(player, Position{100.0f, 100.0f});
    m_ecsManager.addComponent(player, Health{1});
    m_ecsManager.addComponent(player, InputController{});
}

void Game::setUpVillan()
{
    Entity villan = m_ecsManager.createEntity();
	m_ecsManager.addComponent(villan, Renderable{RectShape(m_renderer, m_font, "VILLAN", 200, 200)});
    m_ecsManager.addComponent(villan, Position{300.0f, 300.0f});
    m_ecsManager.addComponent(villan, Health{1});
    m_ecsManager.addComponent(villan, Ai{});
}

void Game::setUpCortana()
{
    Entity cortana = m_ecsManager.createEntity();
	m_ecsManager.addComponent(cortana, Renderable{RectShape(m_renderer, m_font, "CORTANA", 200, 200)});
    m_ecsManager.addComponent(cortana, Position{500.0f, 500.0f});
    m_ecsManager.addComponent(cortana, Health{1});
}

void Game::setUpDinkyDi()
{
    Entity dinkyDi = m_ecsManager.createEntity();
    m_ecsManager.addComponent(dinkyDi, Position{500.0f, 800.0f});
}

void Game::update()
{
    while(this->isRunning())
    {
        handleEvents();
        m_aiSystem->Update();
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
                m_inputSystem->handleEvents(eventHandlder);
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