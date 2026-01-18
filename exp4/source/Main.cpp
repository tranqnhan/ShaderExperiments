#include "raylib.h"
#include "rlgl.h"

#include <utility>
#include <cmath>

#include <iostream>

#define GLSL_VERSION            330

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "fade effect");

    // Load shader to be used on postprocessing
    Shader fadeTimeShader = LoadShader(0, TextFormat("source/resources/shaders/glsl%i/fadeTime.fs", GLSL_VERSION));
    Shader fadeShader = LoadShader(0, TextFormat("source/resources/shaders/glsl%i/fade.fs", GLSL_VERSION));
    Shader trailShader = LoadShader(0, TextFormat("source/resources/shaders/glsl%i/trail.fs", GLSL_VERSION));
    
    // RenderTexture to apply the postprocessing later
    RenderTexture2D buffer1 = LoadRenderTexture(screenWidth, screenHeight);
    RenderTexture2D buffer2 = LoadRenderTexture(screenWidth, screenHeight);
    RenderTexture2D fadeTimeBuffer1 = LoadRenderTexture(screenWidth, screenHeight);
    RenderTexture2D fadeTimeBuffer2 = LoadRenderTexture(screenWidth, screenHeight);

    Texture2D iTexture = LoadTexture("source/resources/object.png");

    int iTextureLoc1 = GetShaderLocation(fadeShader, "iTexture");
    int iFadeTimeLoc1 = GetShaderLocation(fadeShader, "iFadeTime");

    int iTextureLoc2 = GetShaderLocation(fadeTimeShader, "iTexture");
    int iFadeTimeLoc2 = GetShaderLocation(fadeTimeShader, "iFadeTime");
    
    SetTargetFPS(60);
    

    BeginTextureMode(fadeTimeBuffer2);
        ClearBackground(BLANK);
    EndTextureMode();

    float preMouseX, preMouseY, mouseX, mouseY;
    
    Vector2 mousePos = GetMousePosition();

    mouseX = GetMouseX();
    mouseY = GetMouseY();

    while (!WindowShouldClose())
    {
        preMouseX = mouseX;
        preMouseY = mouseY;

        mouseX = GetMouseX(); // Or mousePos.x
        mouseY = GetMouseY(); // Or mousePos.y

        float dx = mouseX - preMouseX;
        float dy = mouseY - preMouseY;
        float dist = std::sqrt(dx * dx + dy * dy);
        float normX = dx / dist;
        float normY = dy / dist;

        BeginTextureMode(buffer2);
            ClearBackground(BLANK);

            BeginShaderMode(trailShader);
            for (int i = 0; i < dist; i++) {
                DrawTexture(iTexture, preMouseX + normX * i, preMouseY + normY * i, WHITE);
            }
            EndShaderMode();

        EndTextureMode();


        BeginTextureMode(fadeTimeBuffer1);
            rlDisableColorBlend(); 
            
            BeginShaderMode(fadeTimeShader);
                SetShaderValueTexture(fadeTimeShader, iTextureLoc2, buffer2.texture);
                SetShaderValueTexture(fadeTimeShader, iFadeTimeLoc2, fadeTimeBuffer2.texture);
                
                DrawTextureRec(fadeTimeBuffer2.texture,
                    (Rectangle){ 0, 0, (float)fadeTimeBuffer2.texture.width,-(float)fadeTimeBuffer2.texture.height },
                    (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
            
            rlEnableColorBlend();  
        EndTextureMode();



        BeginTextureMode(buffer1);
            DrawTextureRec(buffer2.texture,
                (Rectangle){ 0, 0, (float)buffer2.texture.width,-(float)buffer2.texture.height },
                (Vector2){ 0, 0 }, WHITE);
        EndTextureMode();


        BeginTextureMode(buffer2);
            ClearBackground(BLANK);
            BeginShaderMode(fadeShader);
                SetShaderValueTexture(fadeShader, iTextureLoc1, buffer1.texture);
                SetShaderValueTexture(fadeShader, iFadeTimeLoc1, fadeTimeBuffer1.texture);

                DrawTextureRec(buffer1.texture,
                    (Rectangle){ 0, 0, (float)buffer1.texture.width, -(float)buffer1.texture.height },
                    (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
        EndTextureMode();


        BeginDrawing();
            ClearBackground(BLACK);

                DrawTexture(iTexture, mouseX, mouseY, WHITE);
                
                DrawTextureRec(buffer2.texture,
                    (Rectangle){ 0, 0, (float)buffer2.texture.width, -(float)buffer2.texture.height },
                    (Vector2){ 0, 0 }, WHITE);
                
            DrawFPS(10, 10);
        EndDrawing();

        std::swap(buffer1, buffer2);
        std::swap(fadeTimeBuffer1, fadeTimeBuffer2);
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(buffer1);    // Unload render texture
    UnloadRenderTexture(buffer2);    // Unload render texture
    UnloadRenderTexture(fadeTimeBuffer1);    // Unload render texture
    UnloadRenderTexture(fadeTimeBuffer2);    // Unload render texture
    UnloadTexture(iTexture);
    UnloadShader(fadeShader);           // Unload shader
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
