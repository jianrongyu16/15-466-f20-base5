#include "Mode.hpp"

#include "Scene.hpp"
#include "WalkMesh.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>
#include <unordered_set>
#include <random>
#include <limits>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up, space;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//player info:
	struct Player {
		WalkPoint at;
		//transform is at player's feet and will be yawed by mouse left/right motion:
		Scene::Transform *transform = nullptr;
		//camera is at player's head and will be pitched by mouse up/down motion:
		Scene::Camera *camera = nullptr;
	} player;

	std::vector<Scene::Transform*> brights;
	std::vector<Scene::Transform*> darks;
	std::vector<glm::vec3> brights_pos;
	std::vector<glm::vec3> darks_pos;

    std::deque<size_t> packages;
    std::unordered_set<size_t> delivered;
    std::unordered_set<size_t> indelivery;

    float dead = 0.0f;
	float best_time = std::numeric_limits<float>::max();
	float timer = 0.0f;

};
