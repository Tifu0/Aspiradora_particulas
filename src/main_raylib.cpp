

#include "raylib.h"
#include "ConjuntoParticulas.hpp"

using namespace std;

int main(int argc, const char * argv[]){
    if(argc >= 3){
        const int screenWidth = 600;
        const int screenHeight = 600;
        Color v[8] = {YELLOW, BLUE, MAROON, GREEN, BLACK, PINK, MAGENTA, BROWN};

        InitWindow(screenWidth, screenHeight, "Aspiradora");
        SetTargetFPS(60);

        ConjuntoParticulas c(stoi(argv[2]) + 1);
        c.obtener(0) = Particula(Vector2D(0.0,0.0),Vector2D(aleatorio(-MAX_VEL,MAX_VEL),aleatorio(-MAX_VEL,MAX_VEL)),Vector2D(0.0,0.0),stoi(argv[1]),10);
        for(int i = 1; i < c.size(); i++){
            c.obtener(i).setAceleracion(Vector2D(0.0,0.0));
        }
        
        //Mi robot aspiradora siempre estará en la posicición 0 del conjunto

        bool pause = false;

        while(!WindowShouldClose()){

            if(IsKeyPressed(KEY_SPACE)) pause = !pause;

            if(!pause){
                //comportamiento de la aspiradora (c.obtener(0))

                if(IsKeyPressed(KEY_RIGHT)){
                    Vector2D vel = c.obtener(0).getVelocidad();
                    double velx = vel.getX();
                    if(velx < 0){
                        vel.setX(-velx);
                        c.obtener(0).setVelocidad(vel);
                    }
                }
                if(IsKeyPressed(KEY_LEFT)){
                    Vector2D vel = c.obtener(0).getVelocidad();
                    double velx = vel.getX();
                    if(velx > 0){
                        vel.setX(-velx);
                        c.obtener(0).setVelocidad(vel);
                    }
                }
                if(IsKeyPressed(KEY_UP)){
                    Vector2D vel = c.obtener(0).getVelocidad();
                    double vely = vel.getY();
                    if(vely > 0){
                        vel.setY(-vely);
                        c.obtener(0).setVelocidad(vel);
                    }
                }
                if(IsKeyPressed(KEY_DOWN)){
                    Vector2D vel = c.obtener(0).getVelocidad();
                    double vely = vel.getY();
                    if(vely < 0){
                        vel.setY(-vely);
                        c.obtener(0).setVelocidad(vel);
                    }
                }

                if (c.size() == 1) {
                    c.obtener(0).setVelocidad(Vector2D(0.0, 0.0));
                }

                //comportamiento de ambas

                if(IsKeyPressed(KEY_ENTER)){
                    for(int i = 0; i < stoi(argv[2]);i++){
                        Particula p = Particula();
                        p.setAceleracion(Vector2D(0.0,0.0));
                        c.agregar(p);
                    }
                    if (c.obtener(0).getVelocidad().getX() == 0 && c.obtener(0).getVelocidad().getY() == 0) {
                        c.obtener(0).setVelocidad(Vector2D(aleatorio(-MAX_VEL,MAX_VEL),aleatorio(-MAX_VEL,MAX_VEL)));
                    }
                }

                for (int i = c.size()-1; i >= 1; i--) {
                    if (c.obtener(0).colision(c.obtener(i))) {
                        c.borrar(i);
                    }
                }
                
                //comportamiento de las particulas

                c.gestionarColisiones();

                for(int i = 0; i < c.size(); i++){
                    c.obtener(i).mover();
                    c.obtener(i).rebotar();
                }
            }

            BeginDrawing();
                ClearBackground(RAYWHITE);


                DrawCircle(c.obtener(0).getPosicion().getX(),c.obtener(0).getPosicion().getY(),c.obtener(0).getRadio(),RED);
                for(int i = 1; i < c.size(); i++){
                    DrawCircle(c.obtener(i).getPosicion().getX(), c.obtener(i).getPosicion().getY(), c.obtener(i).getRadio(), v[i % 8]);
                }

                DrawText("SPACE para pausar ESC para salir", GetScreenWidth() * 0.05, GetScreenHeight() * 0.9, 25, LIGHTGRAY);
                if(c.size() == 1){
                    DrawText("Habitacion limpia", GetScreenWidth() * 0.3, GetScreenHeight() * 0.4, 35, GREEN);
                }
                if (pause)
                    DrawText("PAUSED", GetScreenWidth() * 0.4, GetScreenHeight() * 0.4, 35, GRAY);
                DrawFPS(GetScreenWidth() * 0.87, GetScreenHeight() * 0.01);
                //c_str() es una funcion usada en ejemplo2.cpp de ejemplosRaylib.zip para convertir el string a const char*
                DrawText(("Particulas: " + to_string(c.size()-1)).c_str(), 10, 10, 25, GRAY);
            EndDrawing();
        }

        CloseWindow();

        return 0;
    } else{
        cerr << "El uso de este programa es: ./bin/aspiradora radio num_particulas.\n";
        return 1;
    }
}