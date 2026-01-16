#pragma once
#include <glad/glad.h>
#include "imgui.h"
#include "imgui_internal.h"
#include <string>
#include <vector>
#include "game_mechanics.hpp"

class Texture
{
public:
    Texture() = default;
    explicit Texture(const std::string& path);

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    ~Texture();

    bool Load(const std::string& path);

    GLuint GetID() const { return m_id; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    bool IsValid() const { return m_id != 0; }

private:
    GLuint m_id = 0;
    int m_width = 0;
    int m_height = 0;
};

class Scene
{
public:
    Scene(ImVec2 window_dimentions);

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    ~Scene() = default;

    void DisplayCharacter(Texture& texture, float coordinate_x, float coordinate_y);
    void DisplayGhosts(Texture* textures, Ghost *ghosts);
    void DisplayMap(Map map, Texture *textures);
    void getDisplayDimensions(float &tile, float &x, float &y);
private:
    float tile_size;
    float x_offset;
    float y_offset;
};

void ShowMainMenu(bool* p_open);
void ShowGameLevel(bool* p_open, Texture* textures, Game& game);
void ShowPauseMenu(bool* p_open, Game& game);
void ShowEndMenu(bool* p_open, Game& game);
void DisplayTexture(Texture& texture, ImVec2 start_position, ImVec2 dimentions);
int GetInputDir();