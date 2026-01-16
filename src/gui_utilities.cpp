#include <iostream>
#include "gui_utilities.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string& path)
{
    Load(path);
}

bool Texture::Load(const std::string& path)
{
    if (m_id != 0)
        glDeleteTextures(1, &m_id);

    int channels;
    stbi_uc* data = stbi_load(path.c_str(), &m_width, &m_height, &channels, 4);

    if (!data)
        return false;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        m_width,
        m_height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );

    stbi_image_free(data);
    return true;
}

Texture::~Texture()
{
    if (m_id != 0)
        glDeleteTextures(1, &m_id);
}

Texture::Texture(Texture&& other) noexcept
{
    *this = std::move(other);
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (this != &other)
    {
        m_id = other.m_id;
        m_width = other.m_width;
        m_height = other.m_height;

        other.m_id = 0;
    }
    return *this;
}

Scene::Scene(ImVec2 window_dimentions)
{
    if (window_dimentions.x * 31 / 28 >= (window_dimentions.y - 20))
    {
        tile_size = (window_dimentions.y - 20) / 31;
        x_offset = (window_dimentions.x - tile_size * 28) / 2;
        y_offset = 0 + 10;
    }
    else
    {
        tile_size = window_dimentions.x / 28;
        x_offset = 0;
        y_offset = ((window_dimentions.y - 20) - tile_size * 31) / 2 + 10;
    }
    //std::cout << tile_size << " " << x_offset << " " << y_offset << std::endl;
}

void Scene::DisplayCharacter(Texture& texture, float coordinate_x, float coordinate_y)
{
    DisplayTexture(texture, ImVec2(tile_size * (coordinate_x - 0.5) + x_offset, tile_size * (coordinate_y - 0.5) + y_offset), ImVec2(tile_size, tile_size));
}

void Scene::DisplayGhosts(Texture* textures, Ghost* ghosts)
{
    DisplayCharacter(textures[8], ghosts[0].x_coordinate, ghosts[0].y_coordinate);
    DisplayCharacter(textures[8], ghosts[1].x_coordinate, ghosts[1].y_coordinate);
    DisplayCharacter(textures[8], ghosts[2].x_coordinate, ghosts[2].y_coordinate);
    DisplayCharacter(textures[8], ghosts[3].x_coordinate, ghosts[3].y_coordinate);
}

void Scene::DisplayMap(Map map, Texture* textures)
{
    // 0 = œciana
    // 1 = punkt
    // 2 = power pellet
    // 3 = pusty korytarz
    // 4 = tunel
    // 5 = wnêtrze domu duchów
    // 6 = brama domu duchów
    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            if (map(j, i) == 0)
            {
                DisplayTexture(textures[4], ImVec2(tile_size * j + x_offset, tile_size * i + y_offset), ImVec2(tile_size, tile_size));//sciana
            }
            if (map(j, i) == 1)
            {
                DisplayTexture(textures[5], ImVec2(tile_size * j + x_offset, tile_size * i + y_offset), ImVec2(tile_size, tile_size));//punkt
            }
            if (map(j, i) == 2)
            {
                DisplayTexture(textures[6], ImVec2(tile_size * j + x_offset, tile_size * i + y_offset), ImVec2(tile_size, tile_size));//power pellet
            }
            if (map(j, i) == 6)
            {
                DisplayTexture(textures[7], ImVec2(tile_size * j + x_offset, tile_size * i + y_offset), ImVec2(tile_size, tile_size));//brama domu duchów
            }
        }
    }
}

void Scene::getDisplayDimensions(float& tile, float& x, float& y)
{
    tile = tile_size;
    x = x_offset;
    y = y_offset;
}

void ShowMainMenu(bool *p_open)
{
    using namespace ImGui;
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
    SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);

    if (Begin("Main menu", &p_open[0], flags))
    {
        SetCursorPos(ImVec2(GetWindowWidth() * 0.5 - CalcTextSize("PAC-MAN").x / 2, GetWindowHeight() * 0.2));
        Text("PAC-MAN");               // Display some text (you can use a format strings too)
        SetCursorPos(ImVec2(GetWindowWidth() * 0.2, GetWindowHeight() * 0.6));
        SetWindowFontScale(GetWindowHeight() * 0.01);
        if (Button("PLAY", ImVec2(GetWindowWidth() * 0.6, GetWindowHeight() * 0.2)))
        {
            p_open[0] = false;
            p_open[1] = true;
            p_open[2] = false;
            p_open[3] = false;
        }
        for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1))
        {
            if (!IsKeyDown(key)) continue;
            //std::cout << key << std::endl;
            if (key == 525)
            {
                p_open[0] = false;
                p_open[1] = true;
                p_open[2] = false;
                p_open[3] = false;
            }
        }
        ImGui::End();
    }
}

void ShowGameLevel(bool* p_open, Texture* textures, Game& game)
{
    using namespace ImGui;
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMouseInputs;
    const ImGuiViewport* viewport = GetMainViewport();
    SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
    SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);
    if (Begin("Main menu", &p_open[1], flags))
    {
        Scene scena(GetWindowSize());
        scena.DisplayMap(game.getMap(), textures);
        ImGui::SetCursorPos(ImVec2(0, 0));
        Text("Points: %d", game.getPoints());
        ImGui::SetWindowFontScale(ImGui::GetWindowHeight() * 0.001);
        for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) 
        {
            if (!IsKeyDown(key)) continue;
            /*SameLine();
            Text(IsNamedKey(key) ? "\"%s\"" : "\"%s\" %d", GetKeyName(key), key); 
            SameLine(); 
            Text("(%.02f)", GetKeyData(key)->DownDuration); 
            std::cout << key << std::endl;*/
            if (key == 526)
            {
                p_open[0] = false;
                p_open[1] = false;
                p_open[2] = true;
                p_open[3] = false;
            }
        }
        game.setInputDirection(GetInputDir());
        game.movePlayer(1 / GetIO().Framerate);
        game.checkForCollectible();
        game.updateGhosts(1 / GetIO().Framerate);
        scena.DisplayCharacter(textures[0], game.getPlayerX(), game.getPlayerY());
        scena.DisplayGhosts(textures, game.getGhosts());
        if (game.checkVictory() || game.checkPacmanCollision())
        {
            p_open[0] = false;
            p_open[1] = false;
            p_open[2] = false;
            p_open[3] = true;
        }
        /**/
        SetWindowFontScale(GetWindowHeight() * 0.002);
        Map mapa_test;
        float display_tile_size, display_x_offset, display_y_offset;
        scena.getDisplayDimensions(display_tile_size, display_x_offset, display_y_offset);
        for (const Node& n : mapa_test.getNodes())
        {
            //scena.DisplayCharacter(textures[8], n.x_coordinate + 0.5, n.y_coordinate + 0.5);
            ImGui::SetCursorPos(ImVec2(display_tile_size * n.x_coordinate + display_x_offset, display_tile_size * n.y_coordinate + display_y_offset));
            Text("%d", mapa_test.findNodeAt(n.x_coordinate, n.y_coordinate));
        }

        End();
    }
}

void ShowPauseMenu(bool* p_open, Game& game)
{
    using namespace ImGui;
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
    SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);

    if (Begin("Pause menu", &p_open[2], flags))
    {
        SetCursorPos(ImVec2(GetWindowWidth() * 0.5 - CalcTextSize("Game paused").x / 2, GetWindowHeight() * 0.15));
        Text("Game paused");               // Display some text (you can use a format strings too)
        SetCursorPos(ImVec2(GetWindowWidth() * 0.25, GetWindowHeight() * 0.4));
        SetWindowFontScale(GetWindowHeight() * 0.006);
        if (Button("Continue", ImVec2(GetWindowWidth() * 0.5, GetWindowHeight() * 0.15)))
        {
            p_open[0] = false;
            p_open[1] = true;
            p_open[2] = false;
            p_open[3] = false;
        }
        SetCursorPos(ImVec2(GetWindowWidth() * 0.25, GetWindowHeight() * 0.7));
        if (Button("Exit", ImVec2(GetWindowWidth() * 0.5, GetWindowHeight() * 0.15)))
        {
            p_open[0] = true;
            p_open[1] = false;
            p_open[2] = false;
            p_open[3] = false;
            Game new_game;
            game = new_game;
        }
        ImGui::End();
    }
}

void ShowEndMenu(bool* p_open, Game& game)
{
    using namespace ImGui;
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
    SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);

    if (Begin("End menu", &p_open[3], flags))
    {
        if (game.checkVictory())
        {
            SetCursorPos(ImVec2(GetWindowWidth() * 0.5 - CalcTextSize("Victory").x / 2, GetWindowHeight() * 0.15));
            Text("Victory");               // Display some text (you can use a format strings too)
        }
        else
        {
            SetCursorPos(ImVec2(GetWindowWidth() * 0.5 - CalcTextSize("Defeat").x / 2, GetWindowHeight() * 0.15));
            Text("Defeat");               // Display some text (you can use a format strings too)
        }
        SetCursorPos(ImVec2(GetWindowWidth() * 0.25, GetWindowHeight() * 0.4));
        SetWindowFontScale(GetWindowHeight() * 0.006);
        if (Button("Main menu", ImVec2(GetWindowWidth() * 0.5, GetWindowHeight() * 0.15)))
        {
            p_open[0] = true;
            p_open[1] = false;
            p_open[2] = false;
            p_open[3] = false;
            Game new_game;
            game = new_game;
        }
        ImGui::End();
    }
}

void DisplayTexture(Texture& texture, ImVec2 start_position, ImVec2 dimentions)
{
    ImGui::SetCursorPos(start_position);
    if (texture.IsValid())
    {
        ImGui::Image(
            (ImTextureID)(intptr_t)texture.GetID(),dimentions);
    }
    else
    {
        throw("Invalid texture");
    }
}

int GetInputDir()
{
    using namespace ImGui;
    for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1))
    {
        if (!IsKeyDown(key)) continue;
        //std::cout << key << std::endl;
        if (key == 513)
        {
            return 1;//W lewo
        }
        if (key == 514)
        {
            return 2;//W prawo
        }
        if (key == 515)
        {
            return 3;//W gore
        }
        if (key == 516)
        {
            return 4;//W dol
        }
    }
    return 0;
}