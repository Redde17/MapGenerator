#include "GlobalInclude.h"
#include "MapHandler.h"

#include <chrono>
#include <thread>
#include <fstream>

using namespace std::chrono_literals;
using std::chrono::duration;
using std::chrono::high_resolution_clock;
#define MAP_X 500
#define MAP_Y 500

MapHandler MH(MAP_X, MAP_Y);
float tempBaseCellValue = 0.45f;
int POIsetSize = 10;
int POIamount = 0;
bool vertexMapChanged = false;

void initMap(MapHandler& MH);
void imGuiMapToolsSet();

//need code refactor
int main() {
    std::cout << "Program start" << std::endl;
    sf::RenderWindow mainWindow(sf::VideoMode(1000, 800), "MapGenerator");

    initMap(MH);
    int POIamount = MH.getPOIamount();

    ImGui::SFML::Init(mainWindow);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    sf::Clock deltaClock;
    while (mainWindow.isOpen())
    {
        //event handling
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type) {
            case sf::Event::Closed:
                mainWindow.close();
                break;
            default:
                break;
            }

        }

        ImGui::SFML::Update(mainWindow, deltaClock.restart());

        //ImGUI docking implementation
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        //Main Window Docking implementation
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        }

        //create ImGUI windows
        imGuiMapToolsSet();

        mainWindow.clear();
        MH.mapTexture.draw(MH.vertices_map);
        
        ImGui::Begin("RenderWindow", NULL, ImGuiWindowFlags_HorizontalScrollbar);
        ImVec2 imageSize(MH.mapTexture.getSize().x, MH.mapTexture.getSize().y);
        ImVec2 center((ImGui::GetWindowSize().x - MH.mapTexture.getSize().x) * 0.5f, (ImGui::GetWindowSize().y - MH.mapTexture.getSize().y) * 0.5f );
        ImGui::SetCursorPos(center);
        ImGui::Image(MH.mapTexture);
        ImGui::End();

        ImGui::SFML::Render(mainWindow);

        mainWindow.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}

void initMap(MapHandler& MH) {
    auto t1 = high_resolution_clock::now();
    MH.generateMap();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Map generation time: " << ms_double.count() << "ms\n";

    t1 = high_resolution_clock::now();
    MH.generatePOIset(100);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    std::cout << "POI generation time: " << ms_double.count() << "ms\n";
    POIamount = MH.getPOIamount();

    t1 = high_resolution_clock::now();
    MH.generateVertexMap();
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    std::cout << "vertices map generation time: " << ms_double.count() << "ms\n";
}

void imGuiMapToolsSet() {
    ImGui::Begin("Map tools");
    //ImGui::Text("Land Value");
    ImGui::SliderFloat("Land/Sea Ratio", &tempBaseCellValue, 0.0f, 1.0f);
    ImGui::InputInt("POIs set size", &POIsetSize, 1);
    if (ImGui::Button("Generate new POI set")) {
        MH.generatePOIset(POIsetSize);
        vertexMapChanged = true;
    }

    if (ImGui::Button("Delete all POIs")) {
        MH.deletePOIset();
        vertexMapChanged = true;
    }
    ImGui::End();

    if (tempBaseCellValue != MH.baseCellValue) {
        MH.baseCellValue = tempBaseCellValue;
        vertexMapChanged = true;
    }

    if (vertexMapChanged) {
        vertexMapChanged = false;
        MH.generateVertexMap();
        POIamount = MH.getPOIamount();
    }

    ImGui::Begin("Stats");
    ImGui::Text("Size:\n %d x %d\n", MAP_X, MAP_Y);
    ImGui::Text("Points Of Interest:\n %d\n", POIamount);
    ImGui::End();
}