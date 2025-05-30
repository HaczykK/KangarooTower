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
#include "Soundtrack.h"




enum GameState {
    MENU,
    GAME
};




float lastPlatformY = 550.f; // na pocz¹tku

void generatePlatforms(std::vector<Platform>& platforms, float viewTop) {
    while (lastPlatformY > viewTop - 600.f) {
        float x = static_cast<float>(rand() % 400 + 50); // losowa pozycja X
        lastPlatformY -= 120.f; // co 100px
        platforms.emplace_back(sf::Vector2f(120.f, 20.f), sf::Vector2f(x, lastPlatformY));
    }
}


int main() {

    GameState currentState = MENU;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Kangaroo Tower");
    sf::Image icon;
    if (!icon.loadFromFile("iconv3.png")) {
        std::cerr << "Nie uda³o siê za³adowaæ ikony!" << std::endl;
    }
    else {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    //stale 60 fps
    window.setFramerateLimit(60);

    //tlo menu
    Menu menu(window.getSize().x, window.getSize().y, "T³o menuv1.png"); 

    //soundtrack
    Soundtrack soundtrack;
    soundtrack.load(0, "song1.ogg");
    soundtrack.load(1, "song2.ogg");
    soundtrack.start();

    sf::View view = window.getDefaultView();
    srand(static_cast<unsigned>(time(0)));

    //tlo gry
    Background backgorund("tlov5.png"); //tlo gry

    //sprite gracza
    Player player("kangurv15.png", sf::Vector2f(100.f, 400.f)); //spirte kangura

    std::vector<Platform> platforms;
    platforms.emplace_back(sf::Vector2f(400.f, 20.f), sf::Vector2f(0.f, 580.f));

    const float wallWidth = 50.f;
    Wall leftWall(0.f, 10000.f, wallWidth);
    Wall rightWall(800.f - wallWidth, 10000.f, wallWidth);

    sf::Clock clock;



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == MENU) {
                if (event.type == sf::Event::KeyReleased) {
                    switch (event.key.code) {
                    case sf::Keyboard::W:
                        menu.moveUp();
                        break;
                    case sf::Keyboard::S:
                        menu.moveDown();
                        break;
                    case sf::Keyboard::Enter:
                        switch (menu.getPressedItem()) {
                        case 0: // "Graj"
                            currentState = GAME;
                            break;
                        case 1: // "Opcje"
                            std::cout << "Opcje (do zrobienia)" << std::endl;
                            break;
                        case 2: // "Wyniki"
                            std::cout << "Wyniki (do zrobienia)" << std::endl;
                            break;
                        case 3: // "Wyjdz"
                            window.close();
                            break;
                        }
                        break;
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (currentState == MENU) {
            window.clear();
            soundtrack.update(deltaTime);
            menu.draw(window);
            window.display();
            continue;
        }

        soundtrack.update(deltaTime);

        generatePlatforms(platforms, view.getCenter().y);

        player.handleInput();
        player.update(deltaTime);

        // Kolizja z bocznymi œcianami
        if (player.getBounds().intersects(leftWall.getBounds())) {
            player.setPosition(leftWall.getBounds().left + leftWall.getBounds().width, player.getPosition().y);
        }
        if (player.getBounds().intersects(rightWall.getBounds())) {
            player.setPosition(rightWall.getBounds().left - player.getBounds().width, player.getPosition().y);
        }

        // Kolizja z platformami
        for (auto& platform : platforms)
            platform.draw(window);

        for (auto& platform : platforms) {
            if (player.getBounds().intersects(platform.getBounds()) &&
                player.getVelocity().y > 0 && // gracz spada
                player.getPosition().y + player.getBounds().height <= platform.getPosition().y + 10.f) // dodatkowe zabezpieczenie
            {
                player.land(platform.getPosition().y - player.getBounds().height);
                break;
            }
        }

        // Scrollowanie kamery
        sf::Vector2f playerPos = player.getPosition();

        if (playerPos.y < view.getCenter().y - 100) {
            view.setCenter(view.getCenter().x, playerPos.y + 100);

            //  GENERUJ NOWE PLATFORMY powy¿ej ekranu
            generatePlatforms(platforms, view.getCenter().y);
        }

        window.setView(view);
        // Usuwanie platform z do³u
       // platforms.erase(
       //     std::remove_if(platforms.begin(), platforms.end(), [&](const Platform& p) {
        //        return p.getPosition().y > view.getCenter().y + view.getSize().y;
        //        }),
        //    platforms.end()
       // );


        window.clear(sf::Color::Cyan);


        backgorund.draw(window, view);

        for (auto& platform : platforms)
            platform.draw(window);

        leftWall.draw(window);
        rightWall.draw(window);

        player.draw(window);

        

        window.display();
    }

    return 0;
}