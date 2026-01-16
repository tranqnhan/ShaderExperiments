#include "raylib.h"
#include <utility>

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
    
    // RenderTexture to apply the postprocessing later
    RenderTexture2D buffer1 = LoadRenderTexture(screenWidth, screenHeight);
    RenderTexture2D buffer2 = LoadRenderTexture(screenWidth, screenHeight);
    RenderTexture2D fadeTimeBuffer = LoadRenderTexture(screenWidth, screenHeight);

    Texture2D iTexture = LoadTexture("source/resources/raysan.png");

    int iTextureLoc1 = GetShaderLocation(fadeShader, "iTexture");
    int iFadeTimeLoc1 = GetShaderLocation(fadeShader, "iFadeTime");

    int iTextureLoc2 = GetShaderLocation(fadeTimeShader, "iTexture");
    int iFadeTimeLoc2 = GetShaderLocation(fadeTimeShader, "iFadeTime");
    
    SetTargetFPS(60);
    


    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();
        float mouseX = GetMouseX(); // Or mousePos.x
        float mouseY = GetMouseY(); // Or mousePos.y


        BeginTextureMode(buffer2);
            ClearBackground(BLANK);
            DrawTexture(iTexture, mouseX, mouseY, WHITE);
        EndTextureMode();


        BeginTextureMode(fadeTimeBuffer);
            //ClearBackground(BLANK);
            BeginShaderMode(fadeTimeShader);
                SetShaderValueTexture(fadeTimeShader, iTextureLoc2, buffer2.texture);
                DrawTexture(fadeTimeBuffer.texture, 0, 0, BLANK);
            EndShaderMode();
        EndTextureMode();


/*
        BeginTextureMode(buffer1);
            DrawTexture(iTexture, mouseX, mouseY, WHITE);
        EndTextureMode();


        BeginTextureMode(buffer2);
            ClearBackground(BLACK);
            BeginShaderMode(fadeShader);
                SetShaderValueTexture(fadeShader, iTextureLoc1, buffer1.texture);
                SetShaderValueTexture(fadeShader, iFadeTimeLoc1, fadeTimeBuffer.texture);
                
                // Draw the scene texture (that we rendered earlier) to the screen
                // The shader will process every pixel of this texture
                DrawTextureRec(buffer1.texture,
                    (Rectangle){ 0, 0, (float)buffer1.texture.width, -(float)buffer1.texture.height },
                    (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();
        EndTextureMode();
*/

        BeginDrawing();
            ClearBackground(BLACK);
                DrawTexture(fadeTimeBuffer.texture, 0, 0, WHITE);
            DrawFPS(10, 10);
        EndDrawing();
                    
        // TODO: 
        // std::swap(buffer1, buffer2);
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(buffer1);    // Unload render texture
    UnloadRenderTexture(buffer2);    // Unload render texture
    UnloadRenderTexture(fadeTimeBuffer);    // Unload render texture
    UnloadTexture(iTexture);
    UnloadShader(fadeShader);           // Unload shader
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
