//Made BY Abdul Ahad Ali Khan, Ahmed Abubakar Riaz & Ahmad 

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace sf;
using namespace std;

// rect rect collision detection helper function
bool collides(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2) {
		return true;
	}
	return false;
}

int main() {
	
	// create the window and set general settings. Plant the seeds
	RenderWindow window(VideoMode(1000, 600), "Flappy Bird");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	srand(time(0));

	// all sounds and their buffers will rest in this singleton struct
	struct Sounds {
		SoundBuffer chingBuffer;
		SoundBuffer hopBuffer;
		SoundBuffer dishkBuffer;
		Sound ching;
		Sound hop;
		Sound dishk;
	} sounds;

	// load sounds
	sounds.chingBuffer.loadFromFile("./audio/score.wav");
	sounds.hopBuffer.loadFromFile("./audio/flap.wav");
	sounds.dishkBuffer.loadFromFile("./audio/crash.wav");
	sounds.ching.setBuffer(sounds.chingBuffer);
	sounds.hop.setBuffer(sounds.hopBuffer);
	sounds.dishk.setBuffer(sounds.dishkBuffer);

	// all textures remain in here. Flappy has 3 textures, which will repeadetly draw, creating the illusion of flying.
	struct Textures {
		Texture flappy[3];
		Texture pipe;
		Texture background;
		Texture gameover;
	} textures;

	// load textures
	textures.background.loadFromFile("./images/background.png");
	textures.pipe.loadFromFile("./images/pipe.png");
	textures.gameover.loadFromFile("./images/gameover.png");
	textures.flappy[0].loadFromFile("./images/flappy1.png");
	textures.flappy[1].loadFromFile("./images/flappy2.png");
	textures.flappy[2].loadFromFile("./images/flappy3.png");

	// flappy singleton struct.
	// v = vertical speed
	// frame = which texture to print
	struct Flappy {
		double v = 0;
		int frame = 0;
		Sprite sprite;
	} flappy;

	// initial position, scale
	flappy.sprite.setPosition(250, 300);
	flappy.sprite.setScale(2, 2);

	// resizable array of sprites representing pipes
	vector<Sprite> pipes;

	// waiting = game not started yet
	// started = playing
	// gameover = game is over
	enum GameState { waiting,
					 started,
					 gameover };


	// game settings in singleton game struct
	// frames counts total frames passed since the beginning of time
	struct Game {
		int score = 0;
		int highscore = 0;
		int frames = 0;
		GameState gameState = waiting;
		Sprite background[3];
		Sprite gameover;
		Text pressC;
		Text scoreText;
		Text highscoreText;
		Font font;
	} game;


