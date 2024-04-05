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

int main() {
    std::cout << "Program start" << std::endl;

    initMap(MH);
    int POIamount = MH.getPOIamount();

    ImGui::SFML::Init(*MH.window);

    sf::Clock deltaClock;
    while (MH.window->isOpen())
    {
        sf::Event event;
        while (MH.window->pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            switch (event.type) {
            case sf::Event::Closed:
                MH.window->close();
                break;
            default:
                break;
            }
        }
        ImGui::SFML::Update(*MH.window, deltaClock.restart());

        imGuiMapToolsSet();



        MH.window->clear();
        MH.window->draw(MH.vertices_map);
        ImGui::SFML::Render(*MH.window);
        MH.window->display();
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

    ImGui::BeginChild("Stats");
    ImGui::Text("Size:\n %d x %d\n", MAP_X, MAP_Y);
    ImGui::Text("Points Of Interest:\n %d\n", POIamount);
    ImGui::EndChild();
}