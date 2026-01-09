#include "raylib.h"
#include <iostream>

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

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - ascii rendering");

    // Load shader to be used on postprocessing
    Shader shader = LoadShader(0, TextFormat("resources/shaders/glsl%i/trail.fs", GLSL_VERSION));
    
    // RenderTexture to apply the postprocessing later
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    Texture2D iTexture = LoadTexture("resources/raysan.png");
    int iTime = 0;
    //float iResolution[2] = { (float)screenWidth, (float)screenHeight };
    
    // Get shader variable locations
    int iTimeLoc = GetShaderLocation(shader, "iTime");
   // int iResolutionLoc = GetShaderLocation(shader, "iResolution");
    int iTextureLoc = GetShaderLocation(shader, "iTexture");

    std::cout << iTimeLoc << " " << iTextureLoc << std::endl;

    //SetShaderValue(shader, iResolutionLoc, iResolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, iTimeLoc, &iTime, SHADER_UNIFORM_INT);
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        iTime += 1;
        SetShaderValue(shader, iTimeLoc, &iTime, SHADER_UNIFORM_INT);

        // Draw
        //----------------------------------------------------------------------------------
        BeginTextureMode(target);
            ClearBackground(BLACK);
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);

            BeginShaderMode(shader);
                SetShaderValueTexture(shader, iTextureLoc, iTexture);
                
                // Draw the scene texture (that we rendered earlier) to the screen
                // The shader will process every pixel of this texture
                DrawTextureRec(target.texture,
                    (Rectangle){ 0, 0, (float)target.texture.width, (float)target.texture.height },
                    (Vector2){ 0, 0 }, WHITE);
            EndShaderMode();

            DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);    // Unload render texture
    UnloadTexture(iTexture);
    UnloadShader(shader);           // Unload shader
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
