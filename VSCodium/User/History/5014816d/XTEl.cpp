#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>



int main()
{
    // Initializing window
    sf::Vector2u windowSize(800, 600);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Bouncing square");
    window.setFramerateLimit(120);


    // Initializing rectangle
	const int RECT_WIDTH = 48;
	const int RECT_HEIGHT = 48;

    sf::RectangleShape rect;

    sf::Vector2f rectanglePos((windowSize.x / 2.0f) - RECT_WIDTH, (windowSize.y / 2.0f) - RECT_HEIGHT);

    rect.setPosition(rectanglePos);
    rect.setSize(sf::Vector2f(RECT_WIDTH, RECT_HEIGHT));

    float xVelocity = 3;
    float yVelocity = 3;

	// Loading background texture
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Textures-16.png", sf::IntRect(144, 96, 16, 16)))
	{
		std::cout << "Error loading background textures.. " << std::endl;
		return -1;
	}
	backgroundTexture.setRepeated(true);


	// Loading rectangle texture
	sf::Texture rectTexture;
	if (!rectTexture.loadFromFile("Textures-16.png", sf::IntRect(32, 0, 16, 16)))
	{
		std::cout << "Error loading rectangle textures.. " << std::endl;
		return -1;
	}
	rectTexture.setRepeated(false);
	rect.setTexture(&rectTexture);


	// Creating background sprite
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
 


    // Initialize the clock to measure frame time
    sf::Clock frameClock;

	// Initializing clock to sync speed to frames
	sf::Clock speedClock;

	// Initialize the speed of the square
	float squareSpeed = 200; // pixels per second

    // Initialize the font and text for the FPS display
    sf::Font font;
    if (!font.loadFromFile("arcade.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
        return -1;
    }

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);


	sf::Text pauseText;
	pauseText.setFont(font);
	pauseText.setCharacterSize(32);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setPosition((windowSize.x / 2.0f) - 32, (windowSize.y / 2.0f) - 16);
	pauseText.setString("PAUSED");



	bool isPaused = false;

    // Main loop
    while (window.isOpen())
    {
        // Check for events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close the window when the close button is clicked
            if (event.type == sf::Event::Closed) window.close();

            // Respond to the window being resized
            if (event.type == sf::Event::Resized)
            {
                // Update the view to the new size of the window
                // sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                // window.setView(sf::View(visibleArea));
				windowSize = window.getSize();
            }

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        	{
				pauseText.setPosition((windowSize.x / 2.0f) - 32, (windowSize.y / 2.0f) - 16);
            	isPaused = !isPaused;
        	}

		}

		// Measure elapsed time since last frame
		sf::Time elapsedTime = speedClock.restart();

	// Calculate the distance the square should move based on elapsed time
	float distance = squareSpeed * elapsedTime.asSeconds();

	// Calculate the current frame time and fps
	sf::Time frameTime = frameClock.restart();
	float fps = 1.f / frameTime.asSeconds();

	if (!isPaused)
	{

		if (rectanglePos.x <= 0 || rectanglePos.x >= windowSize.x - RECT_WIDTH) xVelocity *= -1;
		if (rectanglePos.y <= 0 || rectanglePos.y >= windowSize.y - RECT_HEIGHT) yVelocity *= -1;

		// "physics"
		rectanglePos.x += xVelocity * distance;
		rectanglePos.y += yVelocity * distance;

		rect.setPosition(rectanglePos);

		// Render
		window.clear();
    	backgroundSprite.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
		window.draw(backgroundSprite);
		window.draw(rect);
		window.draw(fpsText);
		window.display();

	}
	else if (isPaused)
	{
		// Render
		window.clear();
		pauseText.setPosition((windowSize.x / 2.0f) - 32, (windowSize.y / 2.0f) - 16);
		backgroundSprite.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
		window.draw(backgroundSprite);
		window.draw(rect);
		window.draw(fpsText);
		window.draw(pauseText);
		window.display();
	}

	// Update the FPS text
	fpsText.setString("FPS " + std::to_string((int)fps));
	}

	return 0;
}
