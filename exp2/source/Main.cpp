#include "raylib.h"
#include <iostream>
#include <utility>

#define PLATFORM_DESKTOP

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "fade effect");

    // Load shader to be used on postprocessing
    Shader shader = LoadShader(0, TextFormat("source/resources/shaders/glsl%i/fade.fs", GLSL_VERSION));
    
    // RenderTexture to apply the postprocessing later
    RenderTexture2D buffer1 = LoadRenderTexture(screenWidth, screenHeight);
    RenderTexture2D buffer2 = LoadRenderTexture(screenWidth, screenHeight);

    Texture2D iTexture = LoadTexture("source/resources/raysan.png");
    
    //float iResolution[2] = { (float)screenWidth, (float)screenHeight };

    int iTextureLoc = GetShaderLocation(shader, "iTexture");

    //SetShaderValue(shader, iResolutionLoc, iResolution, SHADER_UNIFORM_VEC2);
    
    SetTargetFPS(60);
    


    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();
        float mouseX = GetMouseX(); // Or mousePos.x
        float mouseY = GetMouseY(); // Or mousePos.y

        // Draw
        //----------------------------------------------------------------------------------
        BeginTextureMode(buffer1);
            //ClearBackground(BLACK);
            DrawTexture(iTexture, mouseX, mouseY, WHITE);
        EndTextureMode();
        
        BeginTextureMode(buffer2);
            ClearBackground(BLACK);
            BeginShaderMode(shader);
                SetShaderValueTexture(shader, iTextureLoc, buffer1.texture);
                
                // Draw the scene texture (that we rendered earlier) to the screen
                // The shader will process every pixel of this texture
                DrawTextureRec(buffer1.texture,
                    (Rectangle){ 0, 0, (float)buffer1.texture.width, -(float)buffer1.texture.height },
                    (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
        EndTextureMode();



        BeginDrawing();
            ClearBackground(BLACK);

                DrawTextureRec(buffer2.texture,
                    (Rectangle){ 0, 0, (float)buffer2.texture.width, -(float)buffer2.texture.height },
                    (Vector2){ 0, 0 }, WHITE);

            DrawFPS(10, 10);
        EndDrawing();

        std::swap(buffer1, buffer2);
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(buffer1);    // Unload render texture
    UnloadRenderTexture(buffer2);    // Unload render texture
    UnloadTexture(iTexture);
    UnloadShader(shader);           // Unload shader
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
