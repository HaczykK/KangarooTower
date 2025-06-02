#include "API.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Menu.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"
#include "Wall.h"
#include "CameraManager.h"
#include "ScoreManager.h"
#include "GameOverScreen.h"
#include "Soundtrack.h"
#include "Options.h"

enum GameState 
{
    MENU,
    GAME,
    GAME_OVER,
    SCORES,
    OPTIONS
};

int score = -1;
float lastPlatformY = 550.f; // pocz¹tkowa wysokoœæ

void generatePlatforms(std::vector<Platform>& platforms, float viewTop, sf::Texture* platformTexture) 
{
    while (lastPlatformY > viewTop - 600.f) 
    {
        float x = static_cast<float>(66 + rand() % 500 + 50); // losowa pozycja X
        lastPlatformY -= 140.f;
        platforms.emplace_back(platformTexture, sf::Vector2f(x, lastPlatformY));
    }
}

int main() 
{
    GameState currentState = MENU;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Kangaroo Tower");

    sf::Image icon;
    if (!icon.loadFromFile("iconv3.png")) 
    {
        std::cerr << "Nie uda³o siê za³adowaæ ikony!" << std::endl;
    }
    else 
    {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y, "T³o menuv1.png");

    bool canAcceptInputInMenu = true;

    Soundtrack soundtrack;
    soundtrack.load(0, "song1.ogg");
    soundtrack.load(1, "song2.ogg");
    soundtrack.start();

    sf::View view = window.getDefaultView();
    CameraManager cameraManager(&view, 100.f);

    srand(static_cast<unsigned>(time(0)));

    Background backgorund("tlov5.png");

    Player player("kangurv15.png", sf::Vector2f(300.f, 400.f));

    sf::Texture platformTexture;
    if (!platformTexture.loadFromFile("platformav1.png")) 
    {
        std::cerr << "Nie udalo sie zaladowac platformy!" << std::endl;
        return -1;
    }

    sf::Texture wallTexture;
    if (!wallTexture.loadFromFile("scianav2.png")) 
    {
        std::cerr << "Nie udalo sie zaladowac tekstury scian!" << std::endl;
        return -1;
    }

    std::vector<Platform> platforms;
    platforms.emplace_back(&platformTexture, sf::Vector2f(0.f, 560.f), sf::Vector2f(800.f, 20.f));

    const float wallWidth = 66.f;
    Wall leftWall(&wallTexture, 0.f, wallWidth);
    Wall rightWall(&wallTexture, 800.f - wallWidth, wallWidth);

    ScoreManager scoreManager;
    GameOverScreen gameOverScreen(window.getSize().x);

    sf::Clock clock;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == MENU) 
            {
                if (event.type == sf::Event::KeyReleased) 
                {
                    if (event.key.code == sf::Keyboard::Enter) 
                    {
                        if (canAcceptInputInMenu) 
                        {
                            switch (menu.getPressedItem()) 
                            {
                            case 0:
                                currentState = GAME;
                                break;
                            case 1:
                                currentState = OPTIONS;;
                                break;
                            case 2:
                                currentState = SCORES;
                                break;
                            case 3:
                                window.close();
                                break;
                            }
                            canAcceptInputInMenu = false;  // zablokuj do czasu a¿ puœci Enter
                        }
                    }
                    else if ((event.key.code == sf::Keyboard::W) || (event.key.code == sf::Keyboard::Up)) 
                    {
                        menu.moveUp();
                    }
                    else if ((event.key.code == sf::Keyboard::S) || (event.key.code == sf::Keyboard::Down)) 
                    {
                        menu.moveDown();
                    }
                }

                // Odblokuj ponownie, jeœli ENTER zosta³ puszczony
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) 
                {
                    canAcceptInputInMenu = true;
                }
            }

            if (currentState == GAME_OVER) 
            {
                gameOverScreen.update(event);
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (currentState == MENU) 
        {
            window.clear();
            soundtrack.update(deltaTime);
            menu.draw(window);
            window.display();
            continue;
        }

        if (currentState == GAME_OVER) 
        {
            if (gameOverScreen.isDone()) 
            {
                std::string nick = gameOverScreen.getEnteredName();
                try 
                {
                    scoreManager.saveScoreToFile(nick);
                }
                catch (...) 
                {
                    std::cerr << "Nie udalo sie zapisac wyniku!" << std::endl;
                }

                // Resetuj GameOverScreen
                gameOverScreen.reset();

                // Reset gry
                player.reset(sf::Vector2f(300.f, 400.f));
                platforms.clear();
                lastPlatformY = 550.f;
                platforms.emplace_back(&platformTexture, sf::Vector2f(0.f, 560.f), sf::Vector2f(800.f, 20.f));
                view = window.getDefaultView();
                cameraManager = CameraManager(&view, 100.f);
                scoreManager.reset();

                currentState = MENU; 
                canAcceptInputInMenu = false;// Wróæ do menu
                continue;
            }

            //  USTAW WIDOK, RYSUJ T£O + DODAJ GameOverScreen
            window.setView(window.getDefaultView());  //  bardzo wa¿ne
            window.clear();

            backgorund.draw(window, window.getView());  // <rysuj t³o (to samo co w grze)
            gameOverScreen.draw(window);                //  teksty Game Over, wynik, wpisz nick
            window.display();
            continue;
        }


        if (currentState == SCORES)
        {
            window.clear();
            soundtrack.update(deltaTime);

            std::vector<std::string> scores = scoreManager.getScoresAsStrings();
            sf::Font font;
            if (!font.loadFromFile("NoctraDrip-OutlineMelt.ttf"))
            {
                std::cerr << "Nie udalo sie zaladowac czcionki!" << std::endl;
            }

            sf::Texture backgr;
            backgr.loadFromFile("tlowyniki.png");
            sf::Sprite spr;
            spr.setTexture(backgr);
            window.draw(spr);

            float y = 50.f;
            for (const auto& line : scores)
            {
                sf::Text text;


                text.setFont(font);
                text.setString(line);
                text.setCharacterSize(25);
                text.setFillColor(sf::Color::White);
                text.setPosition(50.f, y);
                y += 40.f;

                window.draw(text);
            }


            window.display();

            // wyjœcie z ekranu wyników klawiszem ESC
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                currentState = MENU;
                sf::sleep(sf::milliseconds(200)); // krótki delay, by nie wróciæ za szybko
            }

            continue;
        }


        if (currentState == OPTIONS) 
        {
            window.clear();
            soundtrack.update(deltaTime);

            sf::Texture option_background;
            option_background.loadFromFile("tloopcji.png");
            sf::Sprite optbckgr;
            optbckgr.setTexture(option_background);
            window.draw(optbckgr);

            sf::Font font;
            if (!font.loadFromFile("NoctraDrip-OutlineMelt.ttf")) 
            {
                std::cerr << "Nie udalo sie zaladowac czcionki!" << std::endl;
            }

            sf::Text title("Opcje", font, 36);
            title.setPosition(300.f, 50.f);
            title.setFillColor(sf::Color::Yellow);

            sf::Text volumeText("Glosnosc muzyki: " + std::to_string((int)Options::musicVolume), font, 28);
            volumeText.setPosition(200.f, 150.f);
            volumeText.setFillColor(sf::Color::White);

            window.draw(title);
            window.draw(volumeText);
            window.display();

            // Sterowanie g³oœnoœci¹
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
            {
                Options::volumeDown();
                sf::sleep(sf::milliseconds(150));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
            {
                Options::volumeUp();
                sf::sleep(sf::milliseconds(150));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
            {
                currentState = MENU;
                sf::sleep(sf::milliseconds(200));
            }

            continue;
        }


        

        

        if (currentState == MENU) 
        {
            window.clear();
            soundtrack.update(deltaTime);
            menu.draw(window);
            window.display();
            continue;
        }

        

           

        // GAME logic
        soundtrack.update(deltaTime);
        generatePlatforms(platforms, view.getCenter().y, &platformTexture);
        player.handleInput();
        player.update(deltaTime);

        if (!cameraManager.isActivated() && player.getVelocity().y < 0.f) 
        {
            cameraManager.activate();
        }

        if (player.getBounds().intersects(leftWall.getBounds())) 
        {
            player.setPosition(leftWall.getBounds().left + leftWall.getBounds().width, player.getPosition().y);
            player.bounceFromWall(true);
        }
        if (player.getBounds().intersects(rightWall.getBounds())) 
        {
            player.setPosition(rightWall.getBounds().left - player.getBounds().width, player.getPosition().y);
            player.bounceFromWall(false);
        }

        for (auto& platform : platforms) 
        {
            scoreManager.updateScoreIfNeeded(player, platform, cameraManager);
        }

        sf::Vector2f playerPos = player.getPosition();

        bool gameOver = cameraManager.update(deltaTime, playerPos);
        if (gameOver) {
            std::cout << "Game Over!\n";
            gameOverScreen.setScore(scoreManager.getScore());
            currentState = GAME_OVER;
            continue;
        }

        window.setView(view);
        window.clear(sf::Color::Cyan);

        platforms.erase(
            std::remove_if(platforms.begin(), platforms.end(), [&](const Platform& p) 
                {
                return p.getPosition().y > view.getCenter().y + view.getSize().y;
                }),
            platforms.end()
        );

        leftWall.update(view);
        rightWall.update(view);
        backgorund.draw(window, view);

        for (auto& platform : platforms)
            platform.draw(window);

        leftWall.draw(window);
        rightWall.draw(window);

        player.draw(window);
        scoreManager.draw(window, view);

        window.display();
    }

    return 0;
}
